# A library for neural network
# ZY

# Standard Pico library
import math

# User defined library
import MM

# generate the weight and bias for layers
# make the value of weight and bias between -0.5~0.5
def init_params():
    w1 = MM.generate_random_matrix(10, 784, -0.5, 0.5)
    b1 = MM.generate_random_matrix(10, 1, -0.5, 0.5)
    w2 = MM.generate_random_matrix(10, 10, -0.5, 0.5)
    b2 = MM.generate_random_matrix(10, 1, -0.5, 0.5)

    return w1, b1, w2, b2

# input a number, say X, if X > 0, output = X; if X < 0, output = 0
def ReLU(x):
    return max(x, 0)

# input a number, say X, if X > 0, output = 1; if X < 0, output = 0
def ReLU_derivative(x):
    return x > 0

# input a number, say X, make the output between 0~1
def softmax(x):
    # Calculate the exponential values for each element in the input vector
    exp_values = [math.exp(val) for val in x]

    # Calculate the sum of exponential values
    sum_exp = sum(exp_values)

    # Compute the softmax values by dividing each exponential value by the sum
    y = [val / sum_exp for val in exp_values]

    return y