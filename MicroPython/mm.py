# A library for matrix multiplication
# ZY

# Standard Pico library
import random

# User defined library

# generate a m*n empty matrix
def generate_empty_matrix(m, n, value=0.0):

    empty_matrix = [[value for _ in range(n)] for _ in range(m)]
    
    return empty_matrix

# generate a m*n random matrix
def generate_random_matrix(m, n, low_limit=0.0, high_limit=1.0):

    random_matrix = generate_empty_matrix(m, n)
    for i in range(m):
        for j in range(n):
            random_matrix[i][j] = random.uniform(low_limit, high_limit)
    
    return random_matrix

# matrix multiplication
def matrix_multiplication(m1,m2):

    m1_row = len(m1)
    m1_column = len(m1[0])

    m2_row = len(m2)
    m2_column = len(m2[0])

    if m1_column != m2_row:
        # m1_column must equal to m2_row
        raise ValueError("Invalid input")
    else:
        m3 = generate_empty_matrix(m1_row, m2_column)

        for i in range(m1_row):
            for j in range(m2_column):
                for k in range(m1_column):
                    m3[i][j] += m1[i][k] * m2[k][j]

        return m3