from machine import Pin
from time import sleep

led = Pin("LED", Pin.OUT)

print("Hello, Pico!") 
while True:
    led.toggle()
    sleep(1)
