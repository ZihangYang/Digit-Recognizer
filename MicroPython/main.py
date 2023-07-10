# Standard Pico library
from machine import Pin
from time import sleep
import random

# User defined library
import led_zy
import MM
import NN

# Code

# w1, b1, w2, b2 = NN.init_params()
# print(b1)

b1 = MM.generate_random_matrix(5, 1, -10, 10)
print(b1)
print(NN.softmax(b1))

# Test code
# print('hello')

# cycle = 0
# cycle = int(input("Enter cycle: "))

led_zy.LED_blink(2)

