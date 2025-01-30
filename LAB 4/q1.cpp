#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <fstream>
#include <sstream>
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
    file >> numIterations; // number of iterations
    file.ignore(); 

    for (int i = 0; i < numIterations; ++i) {
        cout<<"Iteration "<<i+1<<endl;
        int numInputs, threshold;
        file >> numInputs;  // number of inputs
        file.ignore();  
        file >> threshold;  // threshold 
        file.ignore(); 

        vector<int> inputs(numInputs);
        for (int j = 0; j < numInputs; ++j) {
            file >> inputs[j];  // inputs
        }

    MPNeuron neuron(numInputs, threshold);
    neuron.displayWeights();

    int output = neuron.computeOutput(inputs);
    cout << "For input ";
    for (int j = 0; j < numInputs; ++j) {
            cout << inputs[j] << " ";
        }
    cout << ", the Net output is: " << output << endl;
    cout<<endl;
    }

    return 0;
}











