#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>

void save_dataset(const std::vector<float>& dataset, const std::string& filename) {
    std::ofstream out(filename);
    if(out) {
        for(const auto& val : dataset) {
            out << val << "\n";
        }
    }
}

class SOM {
private:
    std::vector<float> weights;
    float learning_rate;
    float radius;
    int num_neurons;
    
    float neighborhood(float dist, float sigma) {
        return exp(-(dist*dist)/(2*sigma*sigma));
    }

public:
    SOM(int n_neurons, float lr, float init_radius) :
        num_neurons(n_neurons),
        learning_rate(lr),
        radius(init_radius)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        
        weights.resize(n_neurons);
        for(auto& w : weights) {
            w = dist(gen);
        }
    }

    int find_bmu(float input) {
        int bmu_idx = 0;
        float min_dist = INFINITY;
        
        for(int i=0; i<num_neurons; ++i) {
            float dist = fabs(input - weights[i]);
            if(dist < min_dist) {
                min_dist = dist;
                bmu_idx = i;
            }
        }
        return bmu_idx;
    }

    void train(float input, int iteration, int max_iter) {
        int bmu = find_bmu(input);
        
        float current_lr = learning_rate * (1.0 - (float)iteration/max_iter);
        float current_radius = radius * (1.0 - (float)iteration/max_iter);
        
        for(int i=0; i<num_neurons; ++i) {
            float distance_to_bmu = fabs(i - bmu);
            float influence = neighborhood(distance_to_bmu, current_radius);
            weights[i] += current_lr * influence * (input - weights[i]);
        }
    }

    void save_weights(std::ofstream& out, int iteration) const {
        out << "iteration " << iteration << ": ";
        for(size_t i = 0; i < weights.size(); ++i) {
            out << weights[i] << " ";
        }
        out << "\n";
    }

    const std::vector<float>& get_weights() const { return weights; }
};

int main() {
    const int NUM_NEURONS = 15;
    const int EPOCHS = pow(10 , 6);
    const float INIT_LR = 0.01;
    const float INIT_RADIUS = NUM_NEURONS/2.0f;

    SOM som(NUM_NEURONS, INIT_LR, INIT_RADIUS);
    
    std::vector<float> dataset(100);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 10.0f);
    for(auto& val : dataset) {
        val = dist(gen);
    }

    save_dataset(dataset, "dataset.txt");

    std::ofstream weight_file("weights_history.txt");
    
    for(int epoch=0; epoch<EPOCHS; ++epoch) {
        int random_idx = std::rand() % dataset.size();
        float input = dataset[random_idx];
        
        som.train(input, epoch, EPOCHS);
        
        // Save weights for every iteration
        if(weight_file) {
            som.save_weights(weight_file, epoch);
        }
    }

    std::cout << "Training complete. Check weights_history.txt and dataset.txt\n";
    return 0;
}
