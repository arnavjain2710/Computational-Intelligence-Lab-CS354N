import random
# Dataset for the task
# format [ x1 , x2 , y1] where x1,x2 are inputs and y1 is the output
DATASET = [
    [1, 4, 0],
    [1, 5, 0],
    [2, 4, 0],
    [2, 5, 0],
    [3, 1, 1],
    [3, 2, 1],
    [4, 1, 1],
    [4, 2, 1],
]

def perceptron(weights, data, learning_rate, num_epochs, threshold=0, bias=0 , verbose = False):
    input_size = len(weights)
    if num_epochs == -1:
        num_epochs = 1000
    for epoch in range(num_epochs):
        done = True
        if verbose:
            print(f"\nEpoch: {epoch}")
        for d in data:
            output = bias  # adding bias as its default weight is always 1 .so its contribution to the output will be 1*bias
            for weight, input in zip(weights, d[:input_size]):
                output += weight * input
            if output > threshold:
                output = 1
            else:
                output = 0
            if d[-1] - output:
                for i in range(len(weights)):
                    # print(learning_rate, (d[-1]-output), input)
                    weight = weights[i]
                    input = d[i]
                    weight += learning_rate * (d[-1] - output) * input
                    weights[i] = weight
                    if verbose:
                        print(f"Weight {i} : {weight}")
                bias += learning_rate * (d[-1] - output)
                if verbose:
                    print(f"Bias: {bias}")
                done = False
                # break
        if done:
            print("All y_target = y_true predicted correctly")
            print(f"Converged after {epoch} epochs")
            break
    return weights, bias


def forward(weights, data, threshold, bias):
    input_size = len(weights)
    output = 0
    for weight, input in zip(weights, data[:input_size]):
        output += weight * input
    output += bias
    if output > threshold:
        output = 1
    else:
        output = 0
    return output


dataset = {"Factory Classification": DATASET}

for task, data in dataset.items():
    
    print(f"Task: {task}")
    print("Initialising Hyperparameters...")
    # generating random hyperparameters
    theta = random.uniform(-1, 1)
    init_weights = [random.uniform(-1, 1) for _ in range(3)]
    learning_rate = random.uniform(0.01, 0.5)
    num_epochs = random.randint(100, 1000)
    init_bias = random.uniform(-1, 1)
    
    print(f"Initial Weights: {init_weights}")
    print(f"Learning Rate: {learning_rate}")
    print(f"Threshold: {theta}")
    print(f"Bias: {init_bias}")
    
    verbose = True 
    # running the perceptron algorithm
    # start training
    weights, bias = perceptron(
        init_weights, data, learning_rate, num_epochs, theta, init_bias , verbose
    )
    
    # printing the final weights and bias after convergence
    print("\nFinal Weights:")
    for i, weight in enumerate(weights):
        print(f"Weight {i}: {weight}")
    print(f"Final Bias: {bias}")  
    
    # running validation
    print("\nRunning Validation...")
    for d in data:
        print(
            f"Input: {d[:-1]} \nOutput: {forward(weights, d, theta, bias)}\nActual Value: {d[-1]}"
        )
    print("\n\n\n")