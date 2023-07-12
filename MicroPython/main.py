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
import tm1650

# Code

b1 = MM.generate_random_matrix(2, 2, -10, 10)
print(b1)
# print(NN.softmax(b1))

# Test code
# print('hello')

# data = b'\x01'
# SD.write_i2c_data(data)
# data = b'\x81'
# SD.write_i2c_data(data)
# data = b'\x68'
# SD.write_i2c_data(data)
# data = b'\xFF'
# SD.write_i2c_data(data)

# SCL_PIN = machine.Pin(1)
# SDA_PIN = machine.Pin(0)
disp = tm1650.TM1650(0, 1)

disp.display_on()

for i in range(1000):
  disp.display_integer(i)

disp.display_clear()
disp.display_off()



# cycle = 0
# cycle = int(input("Enter cycle: "))

led_zy.LED_blink(2)

