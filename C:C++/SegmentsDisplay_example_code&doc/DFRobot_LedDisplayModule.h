/*!
 * @file DFRobot_LedDisplayModule.h
 * @brief Define the basic structure of class DFRobot_LedDisplayModule
 * @n This is a 4bits/8bits digital tube that controlled by IIC interface. 
 * @n And the IIC address of 8bits digital tube can be changed by hardware
 * @n The main functions of the digital tube is as below:
 * @n Show 4bits / 8bot numbers and decimal points
 * @n At present, it only supports showing the numbers 0 to 9, capital letters A, B, C, D, E, F, H, L, O, P, U and dash-,
 * @n And you can also bring decimal points, such as "0." "9." "A." "-."
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [Actor](wenzheng.wang@dfrobot.com)
 * @version  V1.0.1
 * @date  2019-12-10
 * @url https://github.com/DFRobot/DFRobot_LedDisplayModule
 */
#ifndef __DFRobot_LedDisplayModule_H__
#define __DFRobot_LedDisplayModule_H__

#include "Arduino.h"
#include <Wire.h>
#include "string.h"

///< Define DBG, change 0 to 1 open the DBG, 1 to 0 to close  
#if 0
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#if 0
#define DBGI(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBGI(...)
#endif

#define CMD_HT16K33_OSCOFF      0x20  ///< Turn OFF the clock 
#define CMD_HT16K33_OSCON       0x21  ///< Turn ON the clock
#define CMD_HT16K33_DISPLAYOFF  0x80  ///< Turn OFF the display
#define CMD_HT16K33_DISPLAYON   0x81  ///< Turn ON the display*/
#define CMD_HT16K33_FLASHTWOS   0x87  ///< Set the mode to flash at 0.5Hz
#define CMD_HT16K33_FLASHONES   0x85  ///< Set the mode to flash at 1Hz
#define CMD_HT16K33_FLASHHALFS  0x83  ///< Set the mode to flash at 2Hz
#define CMD_HT16K33_STOPFLASH   0x81  ///< Flash end

class DFRobot_LedDisplayModule
{
public:  
  #define ERR_OK             0      ///< ok
  #define ERR_ADDR          -1      ///< error in I2C address  
  /**
   * @enum eSetBit_t
   * @brief 设置数据位数
   */
  typedef enum{
    e4Bit = 0,
    e8Bit = 1
  }eSetBit_t;
    
public:
  /**
   * @fn DFRobot_LedDisplayModule
   * @brief Constructor
   * @param pWire I2C bus pointer object. When calling the function, you may transfer a parameter into it. Defaule as Wire
   * @param addr 8 bits I2C address, the IIC address of 4 bits digital tube in default is 0x48, The IIC address of 8 bits digital tube can be changed by combining A1 and A0
   * @n In default, the IIC address of 8 bits digital tube is 0xE0
   * @n 1  1  1  0  | 0  A1 A0 0
   * @n 1  1  1  0  | 0  0  0  0    0xE0
   * @n 1  1  1  0  | 0  0  1  0    0xE2
   * @n 1  1  1  0  | 0  1  0  0    0xE4
   * @n 0  0  1  0  | 0  1  1  0    0xE6
   */ 
  DFRobot_LedDisplayModule(TwoWire *wire = &Wire, uint8_t ledAddress = 0xE0);

  /**
   * @fn begin
   * @brief  init digital tube
   * @param bit set display digit
   * @return Return 0 if the initialization is successful, otherwise return non-zero
   */
  int begin(eSetBit_t bit);
  
  /**
   * @fn displayOn
   * @brief Turn ON the display
   * @n IIC command to turn ON the display
   * @return None
   */
  void displayOn();
  
  /**
   * @fn displayOff
   * @brief Turn OFF the display 
   * @n IIC command to turn OFF the display
   * @return None
   */  
  void displayOff();

  /**
   * @fn flashTwos
   * @brief Flash mode of the 8 bits digital tube, flash at 0.5Hz
   * @n IIC flash command
   * @return None
   */
  void flashTwos();
  
  /**
   * @fn flashOnes
   * @brief Flash mode of the 8 bits digital tube, flash at 1Hz
   * @n IIC flash command
   * @return None
   */
  void flashOnes();
  
  /**
   * @fn flashHalfs
   * @brief Flash mode of the 8 bits digital tube, flash at 2Hz
   * @n IIC flash command
   * @return None
   */
  void flashHalfs();
  
  /**
   * @fn stopFlash
   * @brief The 8 bits digital tube stops flash 
   * @n IIC command to stop flash
   * @return None
   */
  void stopFlash();

  /**
   * @fn setBrightness
   * @brief Set brightness ofdigital tube
   * @param brightnessValue The brightness value can be set to numbers 1~8
   * @return None
   */
  void setBrightness(int brightnessValue); 

  
  /**
   * @fn setDisplayArea
   * @brief Display area of the digital tube
   * @param areaData Display area from the first bit to the fourth bit could be number 1~4.
   * @return None
   */
  void setDisplayArea(int areaData1 = 82,int areaData2 = 82,int areaData3 = 82,int areaData4 = 82,int areaData5 = 82,int areaData6 = 82,int areaData7 = 82,int areaData8 = 82);
  
  /**
   * @fn print
   * @brief Print data of  digital tube
   * @param sensorData It could be both integer and decimal
   * @return None
   */  
  void print(double sensorData);
  
  /**
   * @fn print
   * @brief Print data of  digital tube
   * @param buf  Displayed data of bit 1 to bit 8 could be the numbers 0 to 9, capital letters A, B, C, D, E, F, H, L, O, P, U and dash-,
   * @n and it also could be decimal points, such as "0." "9." "A." "-."
   * @return None
   */
  void print(const char *buf1 = "82",const char *buf2 = "82",const char *buf3 = "82",const char *buf4 = "82",const char *buf5 = "82",const char *buf6 = "82",const char *buf7 = "82",const char *buf8 = "82");
  
  

private:
  TwoWire *_pWire;
  uint8_t _ledAddress;  ///< IIC Address 
  int displayAreaFlag;  ///< Display area flag 
  int data1,data2,data3,data4,data5,data6,data7,data8;  ///< Display data buffer
  unsigned char ledData1,ledData11,ledData2,ledData22,ledData3,ledData33,ledData4,ledData44,ledData5,ledData55,ledData6,ledData66,ledData7,ledData77,ledData8,ledData88;  /**< Input data buffer */
  
  int d11;
  int d21,d22;
  int d31,d32,d33;
  int d41,d42,d43,d44;  
  int d51,d52,d53,d54,d55;
  int d61,d62,d63,d64,d65,d66;
  int d71,d72,d73,d74,d75,d76,d77;
  int d81,d82,d83,d84,d85,d86,d87,d88;   ///< Display area data buffer

  int d1,d2,d3,d4,d5,d6,d7;
  int a1,a2,a3,a4,a5,a6,a7;  ///< Display address data buffer
  eSetBit_t _bit;
  ///< Display data 
  const unsigned char TAB2[38]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  ///< 0~9 
                                0x77,0x7C,0x39,0x5E,0x79,0x71,  ///< A~F 
                                0x00,
                                0x76,                ///< H 
                                0x00,0x00,0x00,
                                0x38,                ///< L 
                                0x00,0x00,0x5C,      ///< O 
                                0x73,                ///< P 
                                0x00,0x00,0x00,0x40, ///< - 
                                0x3E};               ///< U     
                 
  const unsigned char TAB_Point2[38]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
                                      0xF7,0xFC,0xB9,0xDE,0xF9,0xF1, 
                                      0x00,
                                      0xF6,
                                      0x00,0x00,0x00,
                                      0xB8,
                                      0x00,0x00,0xDC,
                                      0xF3,
                                      0x00,0x00,0x00,0xC0,
                                      0xBE};      ///< Display data, light up the decimal point
  
  /**
   * @fn begin4
   * @brief  the 4 bits digital tube
   * @return Return 0 if the initialization is successful, otherwise return non-zero
   */
  int begin4();
  
  /**
   * @fn begin8
   * @brief Initialize the 8 bits digital tube
   * @return Return 0 if the initialization is successful, otherwise return non-zero
   */ 
  int begin8();
  /**
   * @fn print4
   * @brief 4Print data of the 4 bits digital tube
   * @param print4 Displayed data of bit 1 to bit 4 could be the numbers 0 to 9, capital letters A, B, C, D, E, F, H, L, O, P, U and dash-,
   * @n and it also could be decimal points, such as "0." "9." "A." "-."
   * @return None
   */
  void print4(const char *buf1 = "82",const char *buf2 = "82",const char *buf3 = "82",const char *buf4 = "82");

  /**
   * @fn print8
   * @brief Print data of the 8 bits digital tube
   * @param print8 Displayed data of bit 1 to bit 8 could be the numbers 0 to 9, capital letters A, B, C, D, E, F, H, L, O, P, U and dash-,
   * @n and it also could be decimal points, such as "0." "9." "A." "-."
   * @return None
   */
    void print8(const char *buf1 = "82",const char *buf2 = "82",const char *buf3 = "82",const char *buf4 = "82",const char *buf5 = "82",const char *buf6 = "82",const char *buf7 = "82",const char *buf8 = "82");

  /**
   * @fn setBrightness4
   * @brief Set brightness of the 4 bits digital tube
   * @param The brightness value can be set to numbers 1~8
   * @return None
   */
  void setBrightness4(int brightnessValue); 

  /**
   * @fn print4
   * @brief Print data of the 4 bits digital tube
   * @param It could be both integer and decimal
   * @return None
   */  
  void print4(double sensorData);

  /**
   * @fn print8
   * @brief Print data of the 8 bits digital tube
   * @param could be both integer and decimal
   * @return None
   */
  void print8(double sensorData);
  
  /**
   * @fn setBrightness8
   * @brief Set brightness of the 8 bits digital tube
   * @param The brightness value can be set to numbers 1~16
   * @return None
   */
  void setBrightness8(int brightnessValue);

  /**
   * @fn setDisplayArea4
   * @brief Display area of the 4 bits digital tube
   * @param Display area from the first bit to the fourth bit could be number 1~4.
   * @return None
   */
  void setDisplayArea4(int areaData1 = 82,int areaData2 = 82,int areaData3 = 82,int areaData4 = 82);

  /**
   * @fn setDisplayArea8
   * @brief Display area of the 8 bits digital tube
   * @param Display area from the first bit to the eighth bit could be number 1~8
   * @return None
   */
  void setDisplayArea8(int areaData1 = 82,int areaData2 = 82,int areaData3 = 82,int areaData4 = 82,int areaData5 = 82,int areaData6 = 82,int areaData7 = 82,int areaData8 = 82);


  /**
   * @fn i2cWriteCmd
   * @brief Send IIC command
   * @param IIC command
   * @return None
   */
  void i2cWriteCmd(uint8_t cmd);
  
  /**
   * @fn i2cWriteData
   * @brief The 8-bit digital tube sends IIC data 
   * @param Register address
   * @param IIC data
   * @return None
   */
  void i2cWriteData(uint8_t reg,uint8_t data);
  
  /**
   * @fn i2cWriteData4
   * @brief 4-bit digital tube to send IIC data
   * @param Register address
   * @param IIC data
   * @return None
   */
  void i2cWriteData4(uint8_t reg,uint8_t data);

 /**
  * @fn printCacheReset
  * @brief Reset the print buffer area 
  * @return None
  */
  void printCacheReset();
  
  /**
   * @fn getDisplayData
   * @brief Get display date of bit 1 to bit 8 from the user input
   * @return None
   */
  void  getDisplayData();

  /**
   * @fn getDisplayAddress41
   * @brief The 4bits digital tube to get the display address
   * @return Noen
   */
  void getDisplayAddress41();

  /**
   * @fn getDisplayAddress42
   * @brief The 4bits digital tube to get the display address
   * @return Noen
   */
  void getDisplayAddress42();

  /**
   * @fn getDisplayAddress43
   * @brief The 4bits digital tube to get the display address
   * @return Noen
   */
  void getDisplayAddress43(); 
  
  /**
   * @fn getDisplayAddress81
   * @brief The 8bits digital tube to get the display address
   * @return None
   */
  void getDisplayAddress81();

  /**
   * @fn getDisplayAddress82
   * @brief The 8bits digital tube to get the display address
   * @return None
   */
  void getDisplayAddress82();

  /**
   * @fn getDisplayAddress83
   * @brief The 8bits digital tube to get the display address
   * @return None
   */
  void getDisplayAddress83();

  /**
   * @fn getDisplayAddress84
   * @brief The 8bits digital tube to get the display address
   * @return None
   */
  void getDisplayAddress84();

  /**
   * @fn getDisplayAddress85
   * @brief The 8bits digital tube to get the display address
   * @return None
   */
  void getDisplayAddress85();

  /**
   * @fn getDisplayAddress86
   * @brief The 8bits digital tube to get the display address
   * @return None
   */
  void getDisplayAddress86();

  /**
   * @fn getDisplayAddress87
   * @brief The 8bits digital tube to get the display address
   * @return None
   */
  void getDisplayAddress87();

  /**
   * @fn sensorGetDisplayAddress4
   * @brief The 4bits digital tube to get the display address(sensor data mode)
   * @return None
   */
  void sensorGetDisplayAddress4();
   
  /**
   * @fn sensorGetDisplayAddress8
   * @brief The 8bits digital tube to get the display address(sensor data mode)
   * @return None
   */
  void sensorGetDisplayAddress8();
  
  /**
   * @fn i2cdetect
   * @brief I2C address detection
   * @param addr I2C address
   * @return Return 0 if IIC address is set correctly, otherwise return non-zero. 
   */
  int i2cdetect(uint8_t _ledAddress);
};

#endif