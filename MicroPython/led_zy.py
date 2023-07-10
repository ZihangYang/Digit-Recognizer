# a test library
# ZY

# Standard Pico library
from machine import Pin
from time import sleep

def LED_blink(blink_times):
    led = Pin("LED", Pin.OUT)

    while (blink_times-1) >= 0:
        blink_times -= 1
        led.high()
        sleep(0.5)
        led.low()
        sleep(0.5)
    
    return 1
