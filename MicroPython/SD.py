# A library for the 4-digit 7 segment display module
# ZY

# Standard Pico library
import machine

# User defined library

# Define I2C pins
i2c = machine.I2C(0, scl=machine.Pin(1), sda=machine.Pin(0), freq=115200) #115200

# I2C address of the target device
device_address = 0x48

# Read data from the target device
def read_i2c_data():
    # device_address = 0xE0
    data = i2c.readfrom(device_address, 1)  # Read 6 bytes of data
    return data

# Write data to the target device
def write_i2c_data(data):
    # device_address = 0xE0
    i2c.writeto(device_address, data)

# # Main program
# while True:
#     # Read data from the target device
#     data = read_i2c_data()
#     print("Received data:", data)

#     # Write data to the target device
#     write_data = b'\x00'  # Example data to write
#     write_i2c_data(write_data)

#     time.sleep(1)  # Delay between each I2C operation
