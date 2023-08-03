# Standard Pico library
import machine
from time import sleep
import random

# User defined library
import led_zy
import MM
import NN
import SD
import CAM

#////////////////////////////////
# Code for Neural Network

# b1 = MM.generate_random_matrix(2, 2, -10, 10)
# print(b1)
# print(NN.softmax(b1))

#////////////////////////////////

# TM1650

# display = SD.TM1650()
# display.set_integer(0)
# sleep(1)
# display.set_integer(1234)

# cycle = 0
# cycle = int(input("Enter cycle: "))

#////////////////////////////////

# Mini 2MP
# i2c = machine.I2C(0, scl=machine.Pin(1), sda=machine.Pin(0), freq=115200)

# add = 0x30
# ctrl_buf=bytearray(2)

# ctrl_buf[0]=0xff
# ctrl_buf[1]=0x01
# i2c.writeto(add, ctrl_buf)

# red_buf = bytearray(1)

# red_buf[0] = 0x0a
# i2c.writeto(add, red_buf)
# i2c.readfrom_into(add, red_buf)
# print("id_h is: 0x", red_buf.hex())

# red_buf[0] = 0x0b
# i2c.writeto(add, red_buf)
# i2c.readfrom_into(add, red_buf)
# print("id_l is: 0x", red_buf.hex())



# # set the OV2640
# ctrl_buf[0]=0xff
# ctrl_buf[1]=0x01
# i2c.writeto(add, ctrl_buf)
# sleep(0.1)
# ctrl_buf[0]=0x12
# ctrl_buf[1]=0x80
# i2c.writeto(add, ctrl_buf)
# sleep(0.1)

# for data in CAM.OV2640_JPEG_INIT:
#     addr = data[0]
#     val = data[1]
#     if (addr == 0xff and val == 0xff):
#         print('finsih OV2640_JPEG_INIT')
#         break
#     ctrl_buf[0]=addr
#     ctrl_buf[1]=val
#     i2c.writeto(add, ctrl_buf)
#     sleep(0.01)

# for data1 in CAM.OV2640_YUV422:
#     addr = data1[0]
#     val = data1[1]
#     if (addr == 0xff and val == 0xff):
#         print('finsih OV2640_YUV422')
#         break
#     ctrl_buf[0]=addr
#     ctrl_buf[1]=val
#     i2c.writeto(add, ctrl_buf)
#     sleep(0.01)

# for data2 in CAM.OV2640_JPEG:
#     addr = data2[0]
#     val = data2[1]
#     if (addr == 0xff and val == 0xff):
#         print('finsih OV2640_JPEG')
#         break
#     ctrl_buf[0]=addr
#     ctrl_buf[1]=val
#     i2c.writeto(add, ctrl_buf)
#     sleep(0.01)

# ctrl_buf[0]=0xff
# ctrl_buf[1]=0x01
# i2c.writeto(add, ctrl_buf)
# sleep(0.1)

# ctrl_buf[0]=0x15
# ctrl_buf[1]=0x00
# i2c.writeto(add, ctrl_buf)
# sleep(0.1)

# for data3 in CAM.OV2640_160x120_JPEG:
#     addr = data3[0]
#     val = data3[1]
#     if (addr == 0xff and val == 0xff):
#         print('finsih OV2640_160x120_JPEG')
#         break
#     ctrl_buf[0]=addr
#     ctrl_buf[1]=val
#     i2c.writeto(add, ctrl_buf)
#     sleep(0.01)

# '''
# self.wrSensorReg8_8(0xff,0x01)
# self.wrSensorReg8_8(0x12,0x80)
# utime.sleep(0.1)
# self.wrSensorRegs8_8(OV2640_JPEG_INIT);
# self.wrSensorRegs8_8(OV2640_YUV422);
# self.wrSensorRegs8_8(OV2640_JPEG);
# self.wrSensorReg8_8(0xff,0x01)
# self.wrSensorReg8_8(0x15,0x00)
# self.wrSensorRegs8_8(OV2640_320x240_JPEG);
# '''



# camera = CAM.Mini2MP()

# # test Cam
# camera.spi_write(0x00,0x01)
# data = camera.spi_read(0x00)
# print("Test if it is 0x01: 0x", data.hex())

# data = camera.spi_read(0x40)
# print("ArduChip version: 0x", data.hex())

# data = camera.spi_read(0x01)
# print("Capture Control Register: 0x", data.hex())


# # start
# camera.clear_fifo()
# sleep(0.1)
# camera.start_capture()
# sleep(0.1)

# data = camera.spi_read(0x01)
# print("Capture Control Register: 0x", data.hex())
# data = camera.spi_read(0x03)
# print("Sensor Interface Timing Register: 0x", data.hex())
# data = camera.spi_read(0x04)
# print("FIFO control Register: 0x", data.hex())

# rdy = 0
# while(rdy == 0):
#     rdy = camera.image_rdy()
#     rdy_data = camera.spi_read(0x41)
#     print("rdy_data data is: 0x", rdy_data.hex())
#     sleep(0.1)

# length = camera.read_fifo_length()
# print('Data length is', length)

#////////////////////////////////
#test code

# # Define SPI pins
# spi = machine.SPI(0, baudrate=100000, polarity=0, phase=1, sck=machine.Pin(2), mosi=machine.Pin(3), miso=machine.Pin(4))

# # Define the chip select (CS) pin
# cs_pin = machine.Pin(5, machine.Pin.OUT)

# address = 0x01

# w_maskbits = 0x80
# w_buffer=bytearray(2)
# w_buffer[0]=address | w_maskbits
# w_buffer[1]= 0x01

# address = 0x01
# r_maskbits = 0x7f
# r_buffer=bytearray(1)
# r_buffer[0]=address & r_maskbits

# cs_pin.value(0)  # Enable CS (active low)
# spi.write(w_buffer)
# cs_pin.value(1)  # Disable CS (active low)

# sleep(0.1)

# cs_pin.value(0)  # Enable CS (active low)
# spi.write(r_buffer)
# data = spi.read(1)
# cs_pin.value(1)  # Disable CS (active low)

# print("Received data: 0x", data.hex())


#////////////////////////////////

# test LED
led_zy.LED_blink(2)