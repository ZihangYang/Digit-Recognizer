# Standard Pico library
from machine import Pin
from time import sleep

# User defined library
import led_zy
import mm

# Code
mtx1 = mm.generate_empty_matrix(2,4)
mtx1[0][0] = 1
mtx1[0][1] = 2
mtx1[0][2] = 3
mtx1[0][3] = 4
mtx1[1][0] = 5
mtx1[1][1] = 6
mtx1[1][2] = 7
mtx1[1][3] = 8
print('This is matrix one:', mtx1)

mtx2 = mm.generate_empty_matrix(4,1)
mtx2[0][0] = 1
mtx2[1][0] = 2
mtx2[2][0] = 3
mtx2[3][0] = 4
print('This is matrix two:', mtx2)

mtx3 = mm.matrix_multiplication(mtx1, mtx2)
print('This is dot product of m1 & m2:', mtx3)

# Test code
# print('hello')

# Create a 2D list
# my_list = [[1, 2, 3],
#            [4, 5, 6],
#            [7, 8, 9]]
# my_list[1][2] = 10
# print(my_list)

led_zy.LED_blink(2)

