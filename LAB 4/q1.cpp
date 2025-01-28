#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
using namespace std;

class MPNeuron {
public:
    MPNeuron(int numInputs, int threshold) {
        this->threshold = threshold;
        // Generate random weights for the inputs
        weights.resize(numInputs);
        for (int i = 0; i < numInputs; ++i) {
            weights[i] = rand() % 2;  
        }
    }

    int computeOutput(const vector<int>& inputs) {
        if (inputs.size() != weights.size()) {
            cout << "Input and weight vectors must have the same size!" << endl;
            return -1; 
        }

        int sum = 0;
        for (size_t i = 0; i < inputs.size(); ++i) {
            sum += inputs[i] * weights[i]; 
        }
        return sum >= threshold ? 1 : 0;
    }

    void displayWeights() {
        cout << "Randomly assigned weights: ";
        for (int weight : weights) {
            cout << weight << " ";
        }
        cout << endl;
    }

private:
    vector<int> weights;
    int threshold;
};

int main() {
    srand(time(0));

    int numInputs, threshold;
    
    cout << "Enter the number of input nodes: ";
    cin >> numInputs;
    cout << "Enter the threshold: ";
    cin >> threshold;
    vector<int> inputs(numInputs);
    cout << "Enter the " << numInputs << " inputs (0 or 1): ";
    for (int i = 0; i < numInputs; ++i) {
        cin >> inputs[i];
    }

    // Create the MPNeuron object with random weights and the provided threshold
    MPNeuron neuron(numInputs, threshold);
    neuron.displayWeights();
    
    int output = neuron.computeOutput(inputs);
    cout << "Net output: " << output << endl;

    return 0;
}




