# A library for the 4-digit 7 segment display module (TM1650)
# ZY

# Standard Pico library
import machine

# User defined library

# Class of the target device
class TM1650():

    # Define I2C pins, and the data buffer
    def __init__(self, id_set=0, sda_pin=0, scl_pin=1, freq_set=115200):
        # I2C address of the target device
        self.add_cmd = 0x24     # 0x48
        self.add_digit1 = 0x34  # 0x68
        self.add_digit2 = 0x35  # 0x6A
        self.add_digit3 = 0x36  # 0x6C
        self.add_digit4 = 0x37  # 0x6E

        # digit from 0 to 9
        self.digit_table= [0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67]

        # set a control buffer (Brightness/On/Off)
        self.ctrl_buf = bytearray(b'\x01')

        # set data buffer for 4 digits
        self.data1_buf = bytearray(b'\x00')
        self.data2_buf = bytearray(b'\x00')
        self.data3_buf = bytearray(b'\x00')
        self.data4_buf = bytearray(b'\x00')
        
        # init the IIC
        self.i2c = machine.I2C(id_set, scl=machine.Pin(scl_pin), sda=machine.Pin(sda_pin), freq=freq_set)
        self.display_on()
        self.display_clear()

    # Turn the display on
    def display_on(self):
        self.ctrl_buf = bytearray(b'\x01')
        self.i2c.writeto(self.add_cmd, self.ctrl_buf)

    # Turn the display off
    def display_off(self):
        self.ctrl_buf = bytearray(b'\x00')
        self.i2c.writeto(self.add_cmd, self.ctrl_buf)

    def display_clear(self):
        self.data1_buf = bytearray(b'\x00')
        self.data2_buf = bytearray(b'\x00')
        self.data3_buf = bytearray(b'\x00')
        self.data4_buf = bytearray(b'\x00')

        self.i2c.writeto(self.add_digit1, self.data1_buf)
        self.i2c.writeto(self.add_digit2, self.data2_buf)
        self.i2c.writeto(self.add_digit3, self.data3_buf)
        self.i2c.writeto(self.add_digit4, self.data4_buf)

    def set_digit(self, position, value):
        if position==1:
            self.data1_buf[0] = self.digit_table[value]
        elif position==2:
            self.data2_buf[0] = self.digit_table[value]
        elif position==3:
            self.data3_buf[0] = self.digit_table[value]
        elif position==4:
            self.data4_buf[0] = self.digit_table[value]
        else:
            print('Error position\n')
        
        self.i2c.writeto(self.add_digit1, self.data1_buf)
        self.i2c.writeto(self.add_digit2, self.data2_buf)
        self.i2c.writeto(self.add_digit3, self.data3_buf)
        self.i2c.writeto(self.add_digit4, self.data4_buf)

    def set_integer(self, value):
        self.display_clear()

        str_num = str(int(value))
        for i in range(len(str_num)):
            int_num = int(str_num[i])
            self.set_digit(i+1, int_num)
