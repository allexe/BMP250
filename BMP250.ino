/******************************************************************************
  Temperature, humidity and pressure by BMP250
  Температура, влажность и давление с датчика BMP250

  Отображение на ЖК-дисплее LCD 1602 (I2C) данных о текущих температуре (°С),
  влажности (%) и давлении (mmHg - мм.рт.ст) с датчика BMP280 (I2C). И дисплей
  и датчик подключены по шине I2C

  created 26 Dec 2018
  by Alexey Vorotikov
  modified 13 Jan 2019
  by Alexey Vorotikov
 ******************************************************************************/




/*
//  Calculating dewpoint on the BME280
//  Nathan Seidle @ SparkFun Electronics
//  November 3rd, 2018
//  Feel like supporting our work? Buy a board from SparkFun!
//  https://www.sparkfun.com/products/14348 - Qwiic Combo Board
//  https://www.sparkfun.com/products/13676 - BME280 Breakout Board
//  This example shows how to calculate dew point based on humidity and temperature.
//  Comes from Pavel-Sayekat: https://github.com/sparkfun/SparkFun_BME280_Breakout_Board/pull/6
//  Hardware connections:
//  BME280 -> Arduino
//  GND -> GND
//  3.3 -> 3.3
//  SDA -> A4
//  SCL -> A5
//*/
//
//#include <Wire.h>
//
//#include "SparkFunBME280.h"
//BME280 mySensor;
//
//void setup()
//{
//  Serial.begin(9600);
//  Serial.println("Example showing dewpoint calculation");
//
//  mySensor.setI2CAddress(0x76); //Connect to a second sensor
//  if (mySensor.beginI2C() == false) Serial.println("Sensor connect failed");
//}
//
//void loop()
//{
//  Serial.print("Humidity: ");
//  Serial.print(mySensor.readFloatHumidity(), 0);
//
//  Serial.print(" Pressure: ");
//  Serial.print(mySensor.readFloatPressure()*0.0075, 0);
//
//  Serial.print(" Temp: ");
//  Serial.print(mySensor.readTempC(), 2);
//  //Serial.print(mySensor.readTempF(), 2);
//
//  Serial.print(" Dewpoint: ");
//  //Serial.print(mySensor.dewPointC(), 2);
//  Serial.print(mySensor.dewPointF(), 2);
//
//  Serial.println();
//
//  delay(5000);
//}




// подключаем библиотеки
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
//#include <Adafruit_BME280_in.h>
#include <LiquidCrystal_I2C.h>

// создаем объект - датчик температуры, влажности и давления:
Adafruit_BME280 bme_out;
//Adafruit_BME280_in bme_in;

// создаем объект - экран, передаём используемый адрес и разрешение экрана:
LiquidCrystal_I2C lcd(0x27, 16, 2);


int delayTime;  // интервал опроса датчика

float temp;     // температура
int humi;       // влажность
int pres;       // давление

void setup()
{
  bool status;  // статус датчика bme

  // инициализируем экран:
  lcd.init();
  // включаем подсветку:
  lcd.backlight();
  // устанавливаем курсор в колонку 0, строку 0:
  lcd.clear();
  lcd.setCursor(0, 0);

  //
//  status = bme_in.begin();
//  if (!status) {
//    lcd.print("No BME280 int sensor!");
//    while (1);
//  }

  lcd.setCursor(0, 1);
  //
  status = bme_out.begin();
  if (!status) {
    lcd.print("No BME280 out sensor!");
    while (1);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Default Test");
  delayTime = 10000; // задаём интервал опроса датчика 10сек.
  delay(1000); // даём датчику запуститься

  /*
    // печатаем первую строку
    lcd.print("-28.6C 64% 752mm");
    // устанавливаем курсор в колонку 0, строку 1
    // на самом деле это вторая строка, т.к. нумерация начинается с нуля
    lcd.setCursor(0, 1);
    // печатаем вторую строку
    lcd.print(" 24.2C 42%");
  */
}

void loop()
{
  readValues();
  printValues();
  delay(delayTime);
}


void readValues() {
  temp = bme_out.readTemperature();
  humi = bme_out.readHumidity();
  pres = bme_out.readPressure() / 100.0F / 1.333;
}

void printValues() {

  lcd.clear();

  if (temp >= 0) {
  lcd.setCursor(1, 0); // если температура больше 0, то ставим курсор в 1 столб
  }
  else {
    lcd.setCursor(0, 0); // если температура меньше 0, то оставляем место для "-" 
  }
  lcd.print(temp, 1);
  lcd.setCursor(5, 0);
  lcd.print("C");

  lcd.setCursor(7, 0);
  lcd.print(humi);
  lcd.setCursor(9, 0);
  lcd.print("%");

  lcd.setCursor(11, 0);
  lcd.print(pres);
  lcd.setCursor(14, 0);
  lcd.print("mm");

}
