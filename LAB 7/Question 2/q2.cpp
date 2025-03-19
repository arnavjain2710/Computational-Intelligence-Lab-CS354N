#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>

using Matrix = std::vector<std::vector<double>>;
using namespace std;

Matrix load_csv(const std::string& filename) {
    Matrix data;
    std::ifstream file(filename);
    std::string line;
    
    // Skip header
    if(file.good()) std::getline(file, line);
    
    while(std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string value;
        
        while(std::getline(ss, value, ',')) {
            try {
                row.push_back(std::stod(value));
            } catch(const std::exception& e) {
                std::cerr << "Error parsing value: " << value << "\n";
            }
        }
        if(!row.empty()) data.push_back(row);
    }
    return data;
}

void zscore_normalize(Matrix& data) {
    const size_t num_features = data[0].size();
    const size_t num_samples = data.size();
    
    for(size_t col=0; col<num_features; col++) {
        // Calculate mean
        double sum = std::accumulate(data.begin(), data.end(), 0.0,
            [col](double s, const std::vector<double>& row) { return s + row[col]; });
        double mean = sum / num_samples;
        
        // Calculate standard deviation
        double sq_diff = std::accumulate(data.begin(), data.end(), 0.0,
            [col, mean](double s, const std::vector<double>& row) { 
                return s + pow(row[col] - mean, 2); 
            });
        double std_dev = sqrt(sq_diff / num_samples);
        
        // Normalize
        for(auto& row : data) {
            row[col] = (row[col] - mean) / std_dev;
        }
    }
}

class KohonenSOM {
    Matrix weights;
    int input_size;
    int output_size;
    double initial_radius;
    
public:
    KohonenSOM(int n, int m) : input_size(n), output_size(m), 
                              initial_radius(std::max(m, n)/2.0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(-1.0, 1.0);
        
        weights.resize(input_size, std::vector<double>(output_size));
        for(auto& row : weights) {
            std::generate(row.begin(), row.end(), [&](){ return dist(gen); });
        }
    }

    int find_bmu(const std::vector<double>& input) {
        int bmu = 0;
        double min_dist = std::numeric_limits<double>::max();
        
        for(int j=0; j<output_size; j++) {
            double dist = 0.0;
            for(int i=0; i<input_size; i++) {
                dist += pow(input[i] - weights[i][j], 2);
            }
            if(dist < min_dist) {
                min_dist = dist;
                bmu = j;
            }
        }
        return bmu;
    }

    void train(const Matrix& data, int epochs) {
        const double initial_learning_rate = 0.5;
        const double time_constant = epochs / log(initial_radius);
        
        for(int epoch=0; epoch<epochs; epoch++) {
            double learning_rate = initial_learning_rate * exp(-epoch/static_cast<double>(epochs));
            double radius = initial_radius * exp(-epoch/time_constant);
            
            for(const auto& sample : data) {
                int bmu = find_bmu(sample);
                
                // Update neighborhood
                for(int j=0; j<output_size; j++) {
                    double distance_to_bmu = abs(j - bmu);
                    if(distance_to_bmu <= radius) {
                        double influence = exp(-pow(distance_to_bmu, 2)/(2*pow(radius, 2)));
                        
                        for(int i=0; i<input_size; i++) {
                            weights[i][j] += learning_rate * influence * 
                                           (sample[i] - weights[i][j]);
                        }
                    }
                }
            }
        }
    }

    void save_weights(const std::string& filename) {
        std::ofstream outfile(filename);
        for(const auto& row : weights) {
            for(size_t i=0; i<row.size(); i++) {
                outfile << row[i] << (i < row.size()-1 ? "," : "");
            }
            outfile << "\n";
        }
    }
};

int main() {
    Matrix dataset = load_csv("iris_train.csv");
    zscore_normalize(dataset);
    
    const int num_features = dataset[0].size();
    cout<<"Sample Size: "<<dataset.size()<<endl;
    cout<<"Feature Size: "<<num_features<<endl;
    const int output_nodes = 2; 
    
    KohonenSOM som(num_features, output_nodes);
    som.train(dataset, 50);
    som.save_weights("som_weights.csv");
    
    return 0;
}
