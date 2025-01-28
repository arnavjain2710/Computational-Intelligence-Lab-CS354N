#include <iostream>
#include <vector>
using namespace std;

class MPNeuron {
public:
    MPNeuron(int numInputs) {
        weights.resize(numInputs, 1);  // Setting all weights to 1
        threshold = numInputs; // AND gate requires all 1s to output 1 , hence threshold is set to numInputs
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

private:
    vector<int> weights;
    int threshold;
};

int main() {
    int numInputs;
    cout << "Enter the number of input nodes (e.g., 3): ";
    cin >> numInputs;

    cout << "AND Gate Implementation" << endl;
    vector<int> inputs(numInputs);
    cout << "Enter " << numInputs << " inputs (0 or 1): ";
    for (int i = 0; i < numInputs; ++i) {
        cin >> inputs[i];
    }

    MPNeuron neuron(numInputs);
    int output = neuron.computeOutput(inputs);

    cout << "Output: " << output << endl;

    return 0;
}
