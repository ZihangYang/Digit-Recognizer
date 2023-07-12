/*!
 * @file DFRobot_LedDisplayModule.cpp
 * @brief Define the basic structure of class DFRobot_LedDisplayModule
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [Actor](liang.li@dfrobot.com)
 * @version  V1.0.1
 * @date  2019-12-10
 * @url https://github.com/DFRobot/DFRobot_LedDisplayModule
 */

#include <Arduino.h>

#include "DFRobot_LedDisplayModule.h"

DFRobot_LedDisplayModule::DFRobot_LedDisplayModule(TwoWire *wire, uint8_t ledAddress)
{
  _pWire = wire;
  _ledAddress = ledAddress >> 1; 
}

int DFRobot_LedDisplayModule::begin(eSetBit_t bit)
{
  _bit = bit;
  uint8_t state;
  if(_bit == eSetBit_t::e4Bit)
    state = begin4();
  else if(_bit == eSetBit_t::e8Bit)
    state = begin8();
  return state;
}

int DFRobot_LedDisplayModule::begin4()
{
  _pWire->begin();
  if(i2cdetect(_ledAddress) != 0){
      DBG("I2C ADDR ERROR!");
      return ERR_ADDR;
  }
  setBrightness4(0);
  displayOn();
  return 0;
}

int DFRobot_LedDisplayModule::begin8()
{
  _pWire->begin();
  if(i2cdetect(_ledAddress) != 0){
      DBG("I2C ADDR ERROR!");
      return ERR_ADDR;
  }
  i2cWriteCmd(CMD_HT16K33_OSCON);
  displayOn();
  setBrightness8(15);
  return 0;
}
   
void DFRobot_LedDisplayModule::displayOn()
{
  i2cWriteCmd(0x01);        
  i2cWriteCmd(CMD_HT16K33_DISPLAYON); 
}

void DFRobot_LedDisplayModule::displayOff()
{
  i2cWriteCmd(0x00);         
  i2cWriteCmd(CMD_HT16K33_DISPLAYOFF); 
}
  
void DFRobot_LedDisplayModule::flashTwos()
{
  i2cWriteCmd(CMD_HT16K33_FLASHTWOS);
}

void DFRobot_LedDisplayModule::flashOnes()
{
  i2cWriteCmd(CMD_HT16K33_FLASHONES);
}

void DFRobot_LedDisplayModule::flashHalfs()
{
  i2cWriteCmd(CMD_HT16K33_FLASHHALFS);
}

void DFRobot_LedDisplayModule::stopFlash()
{
  i2cWriteCmd(CMD_HT16K33_STOPFLASH);
}

void DFRobot_LedDisplayModule::setBrightness(int brightnessValue)
{
  if(_bit == eSetBit_t::e4Bit)
    setBrightness4(brightnessValue);
  else if(_bit == eSetBit_t::e8Bit)
    setBrightness8(brightnessValue);
}

void DFRobot_LedDisplayModule::setBrightness4(int brightnessValue)
{
  if(brightnessValue == 8) brightnessValue = 0;
  i2cWriteCmd((brightnessValue<<4)|0x01);
}

void DFRobot_LedDisplayModule::setBrightness8(int brightnessValue)
{
  brightnessValue--;
  i2cWriteCmd(0xE0|brightnessValue);
}

void DFRobot_LedDisplayModule::setDisplayArea(int areaData1,int areaData2,int areaData3,int areaData4 ,int areaData5,int areaData6 ,int areaData7 ,int areaData8)
{
  if(_bit == eSetBit_t::e4Bit)
    setDisplayArea4(areaData1,areaData2,areaData3,areaData4);
  else if(_bit == eSetBit_t::e8Bit)
    setDisplayArea8(areaData1,areaData2,areaData3,areaData4,areaData5,areaData6,areaData7,areaData8);
}

void DFRobot_LedDisplayModule::setDisplayArea4(int areaData1 ,int areaData2 ,int areaData3 ,int areaData4 )
{
  if(areaData2==82 && areaData3==82 && areaData4==82)
  {
    displayAreaFlag = 1;
    d11 = areaData1;
  }
  else if(areaData3==82 && areaData4==82)
  {
    displayAreaFlag = 2;
    d21 = areaData1;
    d22 = areaData2;
  }
  else if(areaData4==82)
  {
    displayAreaFlag = 3;
    d31 = areaData1;
    d32 = areaData2;
    d33 = areaData3;
  }
  else
  {
    displayAreaFlag = 4;  
    d41 = areaData1;
    d42 = areaData2;
    d43 = areaData3;
    d44 = areaData4;
  } 
}

void DFRobot_LedDisplayModule::setDisplayArea8(int areaData1,int areaData2,int areaData3,int areaData4 ,int areaData5,int areaData6 ,int areaData7 ,int areaData8)
{
  if(areaData2==82 && areaData3==82 && areaData4==82 && areaData5==82 && areaData6==82 && areaData7==82 && areaData8==82)
  {
    displayAreaFlag = 1;
    d11 = areaData1;
  }
  else if(areaData3==82 && areaData4==82 && areaData5==82 && areaData6==82 && areaData7==82 && areaData8==82)
  {
    displayAreaFlag = 2;
    d21 = areaData1;
    d22 = areaData2;
  }
  else if(areaData4==82 && areaData5==82 && areaData6==82 && areaData7==82 && areaData8==82)
  {
    displayAreaFlag = 3;
    d31 = areaData1;
    d32 = areaData2;
    d33 = areaData3;
  }
  else if(areaData5==82 && areaData6==82 && areaData7==82 && areaData8==82)
  {
    displayAreaFlag = 4;  
    d41 = areaData1;
    d42 = areaData2;
    d43 = areaData3;
    d44 = areaData4;
  } 
  else if(areaData6==82 && areaData7==82 && areaData8==82)
  {
    displayAreaFlag = 5;
    d51 = areaData1;
    d52 = areaData2;
    d53 = areaData3; 
    d54 = areaData4;
    d55 = areaData5; 
  }
  else if(areaData7==82 && areaData8==82)
  {
    displayAreaFlag = 6;
    d61 = areaData1;
    d62 = areaData2;
    d63 = areaData3; 
    d64 = areaData4;
    d65 = areaData5; 
    d66 = areaData6;
  }
  else if(areaData8==82)
  {
    displayAreaFlag = 7;
    d71 = areaData1;
    d72 = areaData2;
    d73 = areaData3; 
    d74 = areaData4;
    d75 = areaData5; 
    d76 = areaData6; 
    d77 = areaData7; 
  }
  else
  {
    displayAreaFlag = 8;
    d81 = areaData1;
    d82 = areaData2;
    d83 = areaData3; 
    d84 = areaData4;
    d85 = areaData5; 
    d86 = areaData6; 
    d87 = areaData7; 
    d88 = areaData8;  
  } 
}
void DFRobot_LedDisplayModule::print(double sensorData)
{
  if(_bit == eSetBit_t::e4Bit)
    print4(sensorData);
  else if(_bit == eSetBit_t::e8Bit)
    print8(sensorData);
}

void DFRobot_LedDisplayModule::print4(double sensorData)
{
  char cacheBuf[10];
  char cacheData1='0',cacheData2='0',cacheData3='0',cacheData4='0',cacheData5='0';
  double temp = sensorData;
  if(temp < 10)
  {
    dtostrf(temp,1,3,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB_Point2[cacheData1-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break; 
      case 2:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB_Point2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData3-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
      case 3:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB_Point2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData3-48]);i2cWriteData4(a3,TAB2[cacheData4-48]);i2cWriteData4(d1,0x00);break;
      case 4:i2cWriteData4(0,TAB_Point2[cacheData1-48]);i2cWriteData4(1,TAB2[cacheData3-48]);i2cWriteData4(2,TAB2[cacheData4-48]);i2cWriteData4(3,TAB2[cacheData5-48]);break;
    }  
  }
  else if(temp>=10 && temp<100)
  {
    dtostrf(temp,2,2,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break;
      case 2:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB_Point2[cacheData2-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
      case 3:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB_Point2[cacheData2-48]);i2cWriteData4(a3,TAB2[cacheData4-48]);i2cWriteData4(d1,0x00);break;
      case 4:i2cWriteData4(0,TAB2[cacheData1-48]);i2cWriteData4(1,TAB_Point2[cacheData2-48]);i2cWriteData4(2,TAB2[cacheData4-48]);i2cWriteData4(3,TAB2[cacheData5-48]);break;
    } 
  }
  else if(temp>=100 && temp<1000)
  {
    dtostrf(temp,3,1,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break;
      case 2:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData2-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
      case 3:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData2-48]);i2cWriteData4(a3,TAB_Point2[cacheData3-48]);i2cWriteData4(d1,0x00);break;
      case 4:i2cWriteData4(0,TAB2[cacheData1-48]);i2cWriteData4(1,TAB2[cacheData2-48]);i2cWriteData4(2,TAB_Point2[cacheData3-48]);i2cWriteData4(3,TAB2[cacheData5-48]);break;
    }
  }
  else if(temp>=1000)
  {
    dtostrf(temp,4,0,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break;
      case 2:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData2-48]);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
      case 3:sensorGetDisplayAddress4();i2cWriteData4(a1,TAB2[cacheData1-48]);i2cWriteData4(a2,TAB2[cacheData2-48]);i2cWriteData4(a3,TAB2[cacheData3-48]);i2cWriteData4(d1,0x00);break;
      case 4:i2cWriteData4(0,TAB2[cacheData1-48]);i2cWriteData4(1,TAB2[cacheData2-48]);i2cWriteData4(2,TAB2[cacheData3-48]);i2cWriteData4(3,TAB2[cacheData4-48]);break;
    }
  }
}   
  
void DFRobot_LedDisplayModule::print4(const char *buf1,const char *buf2,const char *buf3,const char *buf4)
{
  if (strcmp(buf1,"82") != 0){
  ledData1 = buf1[0];
  ledData11 = buf1[1];
  }else{
    ledData1 = 10;
    ledData11 = 10;
  }
  if (strcmp(buf2,"82") != 0){
  ledData2 = buf2[0];
  ledData22 = buf2[1];
  }else{
    ledData2 = 10;
    ledData22 = 10;
  }
  if (strcmp(buf3,"82") != 0){
  ledData3 = buf3[0];
  ledData33 = buf3[1];
  }else{
    ledData3 = 10;
    ledData33 = 10;
  }
  if (strcmp(buf4,"82") != 0){
  ledData4 = buf4[0];
  ledData44 = buf4[1]; 
  }else{
    ledData4 = 10;
    ledData44 = 10;
  }  
  
  getDisplayData();
  switch(displayAreaFlag)
  {
    case 1:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);i2cWriteData4(d3,0x00);break;
    case 2:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(a2,data2);i2cWriteData4(d1,0x00);i2cWriteData4(d2,0x00);break;
    case 3:sensorGetDisplayAddress4(); i2cWriteData4(a1,data1);i2cWriteData4(a2,data2);i2cWriteData4(a3,data3);i2cWriteData4(d1,0x00);break;
    case 4:i2cWriteData4(d41-1,data1);i2cWriteData4(d42-1,data2);i2cWriteData4(d43-1,data3);i2cWriteData4(d44-1,data4);break;
  }
  printCacheReset();
}  

void DFRobot_LedDisplayModule::print8(double sensorData)
{
  char cacheBuf[10];
  char cacheData1='0',cacheData2='0',cacheData3='0',cacheData4='0',cacheData5='0',cacheData6='0',cacheData7='0',cacheData8='0',cacheData9='0';
  double temp = sensorData;
  if(temp<10)
  {
    dtostrf(temp,1,7,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5,&cacheData6,&cacheData7,&cacheData8,&cacheData9);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress8();i2cWriteData(a1,TAB_Point2[cacheData1-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);
             i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);i2cWriteData(d7,0x00);break;
      case 2:sensorGetDisplayAddress8();i2cWriteData(a1,TAB_Point2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData3-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);
             i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);break;
      case 3:sensorGetDisplayAddress8();i2cWriteData(a1,TAB_Point2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData3-48]);i2cWriteData(a3,TAB2[cacheData4-48]);i2cWriteData(d1,0x00);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);break;
      case 4:sensorGetDisplayAddress8();i2cWriteData(a1,TAB_Point2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData3-48]);i2cWriteData(a3,TAB2[cacheData4-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d1,0x00);break;
      case 5:sensorGetDisplayAddress8();i2cWriteData(a1,TAB_Point2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData3-48]);i2cWriteData(a3,TAB2[cacheData4-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;
      case 6:sensorGetDisplayAddress8();i2cWriteData(a1,TAB_Point2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData3-48]);i2cWriteData(a3,TAB2[cacheData4-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(a6,TAB2[cacheData7-48]);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;      
      case 7:sensorGetDisplayAddress8();i2cWriteData(a1,TAB_Point2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData3-48]);i2cWriteData(a3,TAB2[cacheData4-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(a6,TAB2[cacheData7-48]);i2cWriteData(a7,TAB2[cacheData8-48]);i2cWriteData(d1,0x00);break;
      case 8:i2cWriteData(0,TAB_Point2[cacheData1-48]);i2cWriteData(1,TAB2[cacheData3-48]);i2cWriteData(2,TAB2[cacheData4-48]);i2cWriteData(3,TAB2[cacheData5-48]);
             i2cWriteData(4,TAB2[cacheData6-48]);i2cWriteData(5,TAB2[cacheData7-48]);i2cWriteData(6,TAB2[cacheData8-48]);i2cWriteData(7,TAB2[cacheData9-48]);break;
    }
  }
  else if(temp>=10 && temp<100)
  {
    dtostrf(temp,2,6,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5,&cacheData6,&cacheData7,&cacheData8,&cacheData9);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);
             i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);i2cWriteData(d7,0x00);break;
      case 2:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB_Point2[cacheData2-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);
             i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);break;
      case 3:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB_Point2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData4-48]);i2cWriteData(d1,0x00);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);break;
      case 4:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB_Point2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData4-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d1,0x00);break;
      case 5:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB_Point2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData4-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;
      case 6:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB_Point2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData4-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(a6,TAB2[cacheData7-48]);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;      
      case 7:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB_Point2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData4-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(a6,TAB2[cacheData7-48]);i2cWriteData(a7,TAB2[cacheData8-48]);i2cWriteData(d1,0x00);break;
      case 8:i2cWriteData(0,TAB2[cacheData1-48]);i2cWriteData(1,TAB_Point2[cacheData2-48]);i2cWriteData(2,TAB2[cacheData4-48]);i2cWriteData(3,TAB2[cacheData5-48]);
             i2cWriteData(4,TAB2[cacheData6-48]);i2cWriteData(5,TAB2[cacheData7-48]);i2cWriteData(6,TAB2[cacheData8-48]);i2cWriteData(7,TAB2[cacheData9-48]);break;
    }
  }
  else if(temp>=100 && temp<1000)
  {
    dtostrf(temp,3,5,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5,&cacheData6,&cacheData7,&cacheData8,&cacheData9);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);
             i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);i2cWriteData(d7,0x00);break;
      case 2:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);
             i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);break;
      case 3:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB_Point2[cacheData3-48]);i2cWriteData(d1,0x00);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);break;
      case 4:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB_Point2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d1,0x00);break;
      case 5:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB_Point2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;
      case 6:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB_Point2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(a6,TAB2[cacheData7-48]);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;      
      case 7:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB_Point2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData5-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(a6,TAB2[cacheData7-48]);i2cWriteData(a7,TAB2[cacheData8-48]);i2cWriteData(d1,0x00);break;
      case 8:i2cWriteData(0,TAB2[cacheData1-48]);i2cWriteData(1,TAB2[cacheData2-48]);i2cWriteData(2,TAB_Point2[cacheData3-48]);i2cWriteData(3,TAB2[cacheData5-48]);
             i2cWriteData(4,TAB2[cacheData6-48]);i2cWriteData(5,TAB2[cacheData7-48]);i2cWriteData(6,TAB2[cacheData8-48]);i2cWriteData(7,TAB2[cacheData9-48]);break;
    }
  }
  else if(temp>=1000 && temp<10000)
  {
    dtostrf(temp,4,4,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5,&cacheData6,&cacheData7,&cacheData8,&cacheData9);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);
             i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);i2cWriteData(d7,0x00);break;
      case 2:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);
             i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);break;
      case 3:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(d1,0x00);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);break;
      case 4:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB_Point2[cacheData4-48]);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d1,0x00);break;
      case 5:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB_Point2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;
      case 6:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB_Point2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(a6,TAB2[cacheData7-48]);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;      
      case 7:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB_Point2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData6-48]);i2cWriteData(a6,TAB2[cacheData7-48]);i2cWriteData(a7,TAB2[cacheData8-48]);i2cWriteData(d1,0x00);break;
      case 8:i2cWriteData(0,TAB2[cacheData1-48]);i2cWriteData(1,TAB2[cacheData2-48]);i2cWriteData(2,TAB2[cacheData3-48]);i2cWriteData(3,TAB_Point2[cacheData4-48]);
             i2cWriteData(4,TAB2[cacheData6-48]);i2cWriteData(5,TAB2[cacheData7-48]);i2cWriteData(6,TAB2[cacheData8-48]);i2cWriteData(7,TAB2[cacheData9-48]);break;
    }
  }
  else if(temp>=10000 && temp<100000)
  {
    dtostrf(temp,5,3,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5,&cacheData6,&cacheData7,&cacheData8,&cacheData9);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);
             i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);i2cWriteData(d7,0x00);break;
      case 2:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);
             i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);break;
      case 3:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(d1,0x00);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);break;
      case 4:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d1,0x00);break;
      case 5:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB_Point2[cacheData5-48]);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;
      case 6:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB_Point2[cacheData5-48]);i2cWriteData(a6,TAB2[cacheData7-48]);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;      
      case 7:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB_Point2[cacheData5-48]);i2cWriteData(a6,TAB2[cacheData7-48]);i2cWriteData(a7,TAB2[cacheData8-48]);i2cWriteData(d1,0x00);break;
      case 8:i2cWriteData(0,TAB2[cacheData1-48]);i2cWriteData(1,TAB2[cacheData2-48]);i2cWriteData(2,TAB2[cacheData3-48]);i2cWriteData(3,TAB2[cacheData4-48]);
             i2cWriteData(4,TAB_Point2[cacheData5-48]);i2cWriteData(5,TAB2[cacheData7-48]);i2cWriteData(6,TAB2[cacheData8-48]);i2cWriteData(7,TAB2[cacheData9-48]);break;
    }
  }
  else if(temp>=100000 && temp<1000000)
  {
    dtostrf(temp,6,2,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5,&cacheData6,&cacheData7,&cacheData8,&cacheData9);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);
             i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);i2cWriteData(d7,0x00);break;
      case 2:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);
             i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);break;
      case 3:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(d1,0x00);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);break;
      case 4:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d1,0x00);break;
      case 5:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData5-48]);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;
      case 6:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData5-48]);i2cWriteData(a6,TAB_Point2[cacheData6-48]);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;      
      case 7:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData5-48]);i2cWriteData(a6,TAB_Point2[cacheData6-48]);i2cWriteData(a7,TAB2[cacheData8-48]);i2cWriteData(d1,0x00);break;
      case 8:i2cWriteData(0,TAB2[cacheData1-48]);i2cWriteData(1,TAB2[cacheData2-48]);i2cWriteData(2,TAB2[cacheData3-48]);i2cWriteData(3,TAB2[cacheData4-48]);
             i2cWriteData(4,TAB2[cacheData5-48]);i2cWriteData(5,TAB_Point2[cacheData6-48]);i2cWriteData(6,TAB2[cacheData8-48]);i2cWriteData(7,TAB2[cacheData9-48]);break;
    }
  }
  else if(temp>=1000000 && temp<10000000)
  {
    dtostrf(temp,7,1,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5,&cacheData6,&cacheData7,&cacheData8,&cacheData9);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);
             i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);i2cWriteData(d7,0x00);break;
      case 2:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);
             i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);break;
      case 3:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(d1,0x00);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);break;
      case 4:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d1,0x00);break;
      case 5:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData5-48]);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;
      case 6:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData5-48]);i2cWriteData(a6,TAB2[cacheData6-48]);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;      
      case 7:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData5-48]);i2cWriteData(a6,TAB2[cacheData6-48]);i2cWriteData(a7,TAB_Point2[cacheData7-48]);i2cWriteData(d1,0x00);break;
      case 8:i2cWriteData(0,TAB2[cacheData1-48]);i2cWriteData(1,TAB2[cacheData2-48]);i2cWriteData(2,TAB2[cacheData3-48]);i2cWriteData(3,TAB2[cacheData4-48]);
             i2cWriteData(4,TAB2[cacheData5-48]);i2cWriteData(5,TAB2[cacheData6-48]);i2cWriteData(6,TAB_Point2[cacheData7-48]);i2cWriteData(7,TAB2[cacheData9-48]);break;
    }
  }
  else if(temp>=10000000)
  {
    dtostrf(temp,8,0,cacheBuf);
    sscanf(cacheBuf,"%c%c%c%c%c%c%c%c%c",&cacheData1,&cacheData2,&cacheData3,&cacheData4,&cacheData5,&cacheData6,&cacheData7,&cacheData8,&cacheData9);
    switch(displayAreaFlag)
    {
      case 1:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);
             i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);i2cWriteData(d7,0x00);break;
      case 2:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(d1,0x00);i2cWriteData(d2,0x00);
             i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);i2cWriteData(d6,0x00);break;
      case 3:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(d1,0x00);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d5,0x00);break;
      case 4:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(d2,0x00);i2cWriteData(d3,0x00);i2cWriteData(d4,0x00);i2cWriteData(d1,0x00);break;
      case 5:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData5-48]);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;
      case 6:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData5-48]);i2cWriteData(a6,TAB2[cacheData6-48]);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;      
      case 7:sensorGetDisplayAddress8();i2cWriteData(a1,TAB2[cacheData1-48]);i2cWriteData(a2,TAB2[cacheData2-48]);i2cWriteData(a3,TAB2[cacheData3-48]);i2cWriteData(a4,TAB2[cacheData4-48]);
             i2cWriteData(a5,TAB2[cacheData5-48]);i2cWriteData(a6,TAB2[cacheData6-48]);i2cWriteData(a7,TAB2[cacheData7-48]);i2cWriteData(d1,0x00);break;
      case 8:i2cWriteData(0,TAB2[cacheData1-48]);i2cWriteData(1,TAB2[cacheData2-48]);i2cWriteData(2,TAB2[cacheData3-48]);i2cWriteData(3,TAB2[cacheData4-48]);
             i2cWriteData(4,TAB2[cacheData5-48]);i2cWriteData(5,TAB2[cacheData6-48]);i2cWriteData(6,TAB2[cacheData7-48]);i2cWriteData(7,TAB2[cacheData8-48]);break;
    }
  }
}

void DFRobot_LedDisplayModule::print(const char *buf1,const char *buf2,const char *buf3,const char *buf4,const char *buf5,const char *buf6,const char *buf7,const char *buf8)
{
  if(_bit == eSetBit_t::e4Bit)
    print4(buf1,buf2,buf3,buf4);
  else if(_bit == eSetBit_t::e8Bit)
    print8(buf1,buf2,buf3,buf4,buf5,buf6,buf7,buf8);

}
void DFRobot_LedDisplayModule::print8(const char *buf1,const char *buf2,const char *buf3,const char *buf4,const char *buf5,const char *buf6,const char *buf7,const char *buf8)
{
  String data = "82";
  if (strcmp(buf1,"82") != 0){
  ledData1 = buf1[0];
  ledData11 = buf1[1];
  }else{
    ledData1 = 10;
    ledData11 = 10;
  }
  if (strcmp(buf2,"82") != 0){
  ledData2 = buf2[0];
  ledData22 = buf2[1];
  }else{
    ledData2 = 10;
    ledData22 = 10;
  }
  if (strcmp(buf3,"82") != 0){
  ledData3 = buf3[0];
  ledData33 = buf3[1];
  }else{
    ledData3 = 10;
    ledData33 = 10;
  }
  if (strcmp(buf4,"82") != 0){
  ledData4 = buf4[0];
  ledData44 = buf4[1]; 
  }else{
    ledData4 = 10;
    ledData44 = 10;
  }  
 
  if (strcmp(buf5,"82") != 0){
  ledData5 = buf5[0];
  ledData55 = buf5[1];
  }else{
    ledData5 = 10;
    ledData55 = 10;
  }
  if (strcmp(buf6,"82") != 0){
  ledData6 = buf6[0];
  ledData66 = buf6[1];
  }else{
    ledData6 = 10;
    ledData66 = 10;
  }
  if (strcmp(buf7,"82") != 0){
  ledData7 = buf7[0];
  ledData77 = buf7[1];
  }else{
    ledData7 = 10;
    ledData77 = 10;
  }
  if (strcmp(buf8,"82") != 0){
  ledData8 = buf8[0];
  ledData88 = buf8[1]; 
  }else{
    ledData8 = 10;
    ledData88 = 10;
  } 
  
  getDisplayData();
  switch(displayAreaFlag)
  {
  case 1:sensorGetDisplayAddress8();i2cWriteData(a1,data1);i2cWriteData(d7,0x00);i2cWriteData(d6,0x00);i2cWriteData(d5,0x00);
                                     i2cWriteData(d4,0x00);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;  
  case 2:sensorGetDisplayAddress8();i2cWriteData(a1,data1);i2cWriteData(a2,data2);i2cWriteData(d6,0x00);i2cWriteData(d5,0x00);
                                     i2cWriteData(d4,0x00);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;  
  case 3:sensorGetDisplayAddress8();i2cWriteData(a1,data1);i2cWriteData(a2,data2);i2cWriteData(a3,data3);i2cWriteData(d5,0x00);
                                     i2cWriteData(d4,0x00);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break; 
  case 4:sensorGetDisplayAddress8();i2cWriteData(a1,data1);i2cWriteData(a2,data2);i2cWriteData(a3,data3);i2cWriteData(a4,data4);
                                     i2cWriteData(d4,0x00);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break;
  case 5:sensorGetDisplayAddress8();i2cWriteData(a1,data1);i2cWriteData(a2,data2);i2cWriteData(a3,data3);i2cWriteData(a4,data4);
                                     i2cWriteData(a5,data5);i2cWriteData(d3,0x00);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break; 
  case 6:sensorGetDisplayAddress8();i2cWriteData(a1,data1);i2cWriteData(a2,data2);i2cWriteData(a3,data3);i2cWriteData(a4,data4);
                                     i2cWriteData(a5,data5);i2cWriteData(a6,data6);i2cWriteData(d2,0x00);i2cWriteData(d1,0x00);break; 
  case 7:sensorGetDisplayAddress8();i2cWriteData(a1,data1);i2cWriteData(a2,data2);i2cWriteData(a3,data3);i2cWriteData(a4,data4);
                                     i2cWriteData(a5,data5);i2cWriteData(a6,data6);i2cWriteData(a7,data7);i2cWriteData(d1,0x00);break;
  case 8:i2cWriteData(d81-1,data1);i2cWriteData(d82-1,data2);i2cWriteData(d83-1,data3);i2cWriteData(d84-1,data4);
         i2cWriteData(d85-1,data5);i2cWriteData(d86-1,data6);i2cWriteData(d87-1,data7);i2cWriteData(d88-1,data8);break;
  } 
  printCacheReset();
}

void DFRobot_LedDisplayModule::i2cWriteCmd(uint8_t cmd)
{
  _pWire->beginTransmission(_ledAddress);
  _pWire->write(cmd);
  _pWire->endTransmission();
}

void DFRobot_LedDisplayModule::i2cWriteData(uint8_t reg ,uint8_t data)
{
  _pWire->beginTransmission(_ledAddress);
  _pWire->write(reg*2);
  _pWire->write(data);
  _pWire->endTransmission();
}

void DFRobot_LedDisplayModule::i2cWriteData4(uint8_t reg ,uint8_t data)
{
  _pWire->beginTransmission((0x68+reg*2)>>1);
  _pWire->write(data);
  _pWire->endTransmission(); 
}

void DFRobot_LedDisplayModule::printCacheReset()
{
  ledData1='0'; 
  ledData11='0'; 
  ledData2='0'; 
  ledData22='0'; 
  ledData3='0'; 
  ledData33='0'; 
  ledData4='0'; 
  ledData44='0'; 
  ledData5='0'; 
  ledData55='0'; 
  ledData6='0'; 
  ledData66='0'; 
  ledData7='0'; 
  ledData77='0'; 
  ledData8='0'; 
  ledData88='0';
}

void  DFRobot_LedDisplayModule::getDisplayData()
{
  if(ledData1==46 || ledData11==46)
  {
    if(ledData1==46)
    {
     data1 = 0x80;
    }
    else
    {
      if(ledData1==45) ledData1 = 84;      
     data1 = TAB_Point2[ledData1-48];
    }
  }
  else
  {
    if(ledData1==45) ledData1 = 84;
   data1 = TAB2[ledData1-48];
  }

  if(ledData2==46 || ledData22==46)
  {
    if(ledData2==46)
    {
      data2 = 0x80;
    }
    else
    {
      if(ledData2==45) ledData2 = 84;      
      data2 = TAB_Point2[ledData2-48];
    }
  }
  else
  {
    if(ledData2==45) ledData2 = 84;
    data2 = TAB2[ledData2-48];
  }

  if(ledData3==46 || ledData33==46)
  {
    if(ledData3==46)
    {
      data3 = 0x80;
    }
    else
    {
      if(ledData3==45) ledData3 = 84;      
      data3 = TAB_Point2[ledData3-48];
    }
  }
  else
  {
    if(ledData3==45) ledData3 = 84;
    data3 = TAB2[ledData3-48];
  }

  if(ledData4==46 || ledData44==46)
  {
    if(ledData4==46)
    {
      data4 = 0x80;
    }
    else
    {
      if(ledData4==45) ledData4 = 84;      
      data4 = TAB_Point2[ledData4-48];
    }
  }
  else
  {
    if(ledData4==45) ledData4 = 84;
    data4 = TAB2[ledData4-48];
  }

  if(ledData5==46 || ledData55==46)
  {
    if(ledData5==46)
    {
      data5 = 0x80;
    }
    else
    {
      if(ledData5==45) ledData5 = 84;      
      data5 = TAB_Point2[ledData5-48];
    }
  }
  else
  {
    if(ledData5==45) ledData5 = 84;
    data5 = TAB2[ledData5-48];
  }

  if(ledData6==46 || ledData66==46)
  {
    if(ledData6==46)
    {
      data6 = 0x80;
    }
    else
    {
      if(ledData6==45) ledData6 = 84;      
      data6 = TAB_Point2[ledData6-48];
    }
  }
  else
  {
    if(ledData6==45) ledData6 = 84;
    data6 = TAB2[ledData6-48];
  }

  if(ledData7==46 || ledData77==46)
  {
    if(ledData7==46)
    {
      data7 = 0x80;
    }
    else
    {
      if(ledData7==45) ledData7 = 84;      
      data7 = TAB_Point2[ledData7-48];
    }
  }
  else
  {
    if(ledData7==45) ledData7 = 84;
    data7 = TAB2[ledData7-48];
  }

  if(ledData8==46 || ledData88==46)
  {
    if(ledData8==46)
    {
      data8 = 0x80;
    }
    else
    {
      if(ledData8==45) ledData8 = 84;      
      data8 = TAB_Point2[ledData8-48];
    }
  }
  else
  {
    if(ledData8==45) ledData8 = 84;
    data8 = TAB2[ledData8-48];
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress41()
{
  int DisplayAreaData[4] = {1,2,3,4};
  
  a1 = d11;
  a1--;
  DisplayAreaData[d11-1] = 0;
  int i = 0;
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>3)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
    }
    else if(i == 1)
    {
      d2 = DisplayAreaData[a];
      d2--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 2)
    {
      d3 = DisplayAreaData[a];
      d3--;
      DisplayAreaData[a] = 0;
      i++;
      break;    
    }   
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress42()
{
  int DisplayAreaData[4] = {1,2,3,4};

  a1 = d21;
  a1--;
  DisplayAreaData[d21-1] = 0;
  a2 = d22;
  a2--;
  DisplayAreaData[d22-1] = 0;
  int i = 0;
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>3)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
    }
    else if(i == 1)
    {
      d2 = DisplayAreaData[a];
      d2--;
      DisplayAreaData[a] = 0;
      i++;
      break;    
    }   
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress43()
{
  int DisplayAreaData[4] = {1,2,3,4};

  a1 = d31;
  a1--;
  DisplayAreaData[d31-1] = 0;
  a2 = d32;
  a2--;
  DisplayAreaData[d32-1] = 0;
  a3 = d33;
  a3--;
  DisplayAreaData[d33-1] = 0;
  int i = 0;  
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>3)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
      break;
    }   
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress81()
{
  int DisplayAreaData[8] = {1,2,3,4,5,6,7,8};

  a1 = d11;
  a1--;
  DisplayAreaData[d11-1] = 0;
  int i = 0;
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>7)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
    }
    else if(i == 1)
    {
      d2 = DisplayAreaData[a];
      d2--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 2)
    {
      d3 = DisplayAreaData[a];
      d3--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 3)
    {
      d4 = DisplayAreaData[a];
      d4--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 4)
    {
      d5 = DisplayAreaData[a];
      d5--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 5)
    {
      d6 = DisplayAreaData[a];
      d6--;
      DisplayAreaData[a] = 0;
      i++;   
    }
    else if(i == 6)
    {
      d7 = DisplayAreaData[a];
      d7--;
      DisplayAreaData[a] = 0;
      i++;
      break;    
    }    
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress82()
{
  int DisplayAreaData[8] = {1,2,3,4,5,6,7,8};

  a1 = d21;
  a1--;
  DisplayAreaData[d21-1] = 0;
  a2 = d22;
  a2--;
  DisplayAreaData[d22-1] = 0;
  int i = 0;
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>7)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
    }
    else if(i == 1)
    {
      d2 = DisplayAreaData[a];
      d2--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 2)
    {
      d3 = DisplayAreaData[a];
      d3--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 3)
    {
      d4 = DisplayAreaData[a];
      d4--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 4)
    {
      d5 = DisplayAreaData[a];
      d5--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 5)
    {
      d6 = DisplayAreaData[a];
      d6--;
      DisplayAreaData[a] = 0;
      i++;
      break;    
    }   
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress83()
{
  int DisplayAreaData[8] = {1,2,3,4,5,6,7,8};

  a1 = d31;
  a1--;
  DisplayAreaData[d31-1] = 0;
  a2 = d32;
  a2--;
  DisplayAreaData[d32-1] = 0;
  a3 = d33;
  a3--;
  DisplayAreaData[d33-1] = 0; 
  int i = 0;
  while(1)
  {  
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>7)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
    }
    else if(i == 1)
    {
      d2 = DisplayAreaData[a];
      d2--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 2)
    {
      d3 = DisplayAreaData[a];
      d3--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 3)
    {
      d4 = DisplayAreaData[a];
      d4--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 4)
    {
      d5 = DisplayAreaData[a];
      d5--;
      DisplayAreaData[a] = 0;
      i++;
      break;    
    }  
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress84()
{

  int DisplayAreaData[8] = {1,2,3,4,5,6,7,8};

  a1 = d41;
  a1--;
  DisplayAreaData[d41-1] = 0;
  a2 = d42;
  a2--;
  DisplayAreaData[d42-1] = 0;
  a3 = d43;
  a3--;
  DisplayAreaData[d43-1] = 0;
  a4 = d44;
  a4--;
  DisplayAreaData[d44-1] = 0;
  int i = 0;
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>7)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
    }
    else if(i == 1)
    {
      d2 = DisplayAreaData[a];
      d2--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 2)
    {
      d3 = DisplayAreaData[a];
      d3--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 3)
    {
      d4 = DisplayAreaData[a];
      d4--;
      DisplayAreaData[a] = 0;
      i++;
      break;    
    }  
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress85()
{
  int DisplayAreaData[8] = {1,2,3,4,5,6,7,8};

  a1 = d51;
  a1--;
  DisplayAreaData[d51-1] = 0;
  a2 = d52;
  a2--;
  DisplayAreaData[d52-1] = 0;
  a3 = d53;
  a3--;
  DisplayAreaData[d53-1] = 0;
  a4 = d54;
  a4--;
  DisplayAreaData[d54-1] = 0;
  a5 = d55;
  a5--;
  DisplayAreaData[d55-1] = 0;
  int i = 0;
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>7)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
    }
    else if(i == 1)
    {
      d2 = DisplayAreaData[a];
      d2--;
      DisplayAreaData[a] = 0;
      i++;    
    }
    else if(i == 2)
    {
      d3 = DisplayAreaData[a];
      d3--;
      DisplayAreaData[a] = 0;
      i++;
      break;    
    }  
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress86()
{
  int DisplayAreaData[8] = {1,2,3,4,5,6,7,8};

  a1 = d61;
  a1--;
  DisplayAreaData[d61-1] = 0;
  a2 = d62;
  a2--;
  DisplayAreaData[d62-1] = 0;
  a3 = d63;
  a3--;
  DisplayAreaData[d63-1] = 0;
  a4 = d64;
  a4--;
  DisplayAreaData[d64-1] = 0;
  a5 = d65;
  a5--;
  DisplayAreaData[d65-1] = 0;
  a6 = d66;
  a6--;
  DisplayAreaData[d66-1] = 0;
  int i = 0;
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>7)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      d1--;
      DisplayAreaData[a] = 0;
      i++; 
    }
    else if(i == 1)
    {
      d2 = DisplayAreaData[a];
      d2--;
      DisplayAreaData[a] = 0;
      i++;
      break;    
    }  
  }
}

void DFRobot_LedDisplayModule::getDisplayAddress87()
{
  int DisplayAreaData[8] = {1,2,3,4,5,6,7,8};

  a1 = d71;
  a1--;
  DisplayAreaData[d71-1] = 0;
  a2 = d72;
  a2--;
  DisplayAreaData[d72-1] = 0;
  a3 = d73;
  a3--;
  DisplayAreaData[d73-1] = 0;
  a4 = d74;
  a4--;
  DisplayAreaData[d74-1] = 0;
  a5 = d75;
  a5--;
  DisplayAreaData[d75-1] = 0;
  a6 = d76;
  a6--;
  DisplayAreaData[d76-1] = 0;
  a7 = d77;
  a7--;
  DisplayAreaData[d77-1] = 0;
  int i = 0;
  while(1)
  {
    int a = rand()%11;
    if(DisplayAreaData[a] == 0 || a>7)
    {
      continue;
    }
    else if(i == 0)
    {
      d1 = DisplayAreaData[a];
      DisplayAreaData[a] = 0;
      d1--;
      i++;
      break; 
    } 
  }
}

void DFRobot_LedDisplayModule::sensorGetDisplayAddress4() 
{
  switch(displayAreaFlag)
  {
    case 1:getDisplayAddress41(); break;
    case 2:getDisplayAddress42(); break;
    case 3:getDisplayAddress43(); break;
  }
}

void DFRobot_LedDisplayModule::sensorGetDisplayAddress8() 
{
  switch(displayAreaFlag)
  {
    case 1:getDisplayAddress81(); break;
    case 2:getDisplayAddress82(); break;
    case 3:getDisplayAddress83(); break;
    case 4:getDisplayAddress84(); break;
    case 5:getDisplayAddress85(); break;
    case 6:getDisplayAddress86(); break;
    case 7:getDisplayAddress87(); break;
  }
}

int DFRobot_LedDisplayModule::i2cdetect(uint8_t _ledAddress)
{
  _pWire->beginTransmission(_ledAddress);
  if(_pWire->endTransmission() == 0)
  {
      DBG("Addr ok!");
      return  ERR_OK;
  }
  return ERR_ADDR;
}