# Standard Pico library
import machine
# from machine import Pin
from time import sleep
import random

# User defined library
import led_zy
import MM
import NN
import SD

# Code

# b1 = MM.generate_random_matrix(2, 2, -10, 10)
# print(b1)
# print(NN.softmax(b1))

# Test code
# print('hello')

display = SD.TM1650()
display.set_integer(123)
sleep(1)
display.set_integer(23)

# cycle = 0
# cycle = int(input("Enter cycle: "))

led_zy.LED_blink(2)

