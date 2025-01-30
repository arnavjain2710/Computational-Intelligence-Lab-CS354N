#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class MPNeuron {
public:
    MPNeuron(int numInputs) {
        weights.resize(numInputs, 1);  // Set all weights to 1
        threshold = 1; // OR gate requires at least one input to be 1
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int numIterations;
    file >> numIterations; // Read the number of iterations
    file.ignore(); 

    for (int i = 0; i < numIterations; ++i) {
        cout<<"Iteration "<<i+1<<endl;
        int numInputs;
        file >> numInputs;  // Read the number of inputs for this iteration
        file.ignore();  

        vector<int> inputs(numInputs);
        for (int j = 0; j < numInputs; ++j) {
            file >> inputs[j];  // inputs
        }

        MPNeuron neuron(numInputs);
        int output = neuron.computeOutput(inputs);

        cout << "For input ";
        for (int j = 0; j < numInputs; ++j) {
            cout << inputs[j] << " ";
        }
        cout << ", the output of OR gate is: " << output << endl;
        cout<< endl;
    }

    return 0;
}



