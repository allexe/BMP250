/******************************************************************************
  Temperature, humidity and pressure by BME280
  Температура, влажность и давление с датчика BME280

  Отображение на ЖК-дисплее LCD 1602 (I2C) данных о текущих температуре (°С),
  влажности (%) и давлении (mmHg - мм.рт.ст) с датчика BMP280 (I2C). И дисплей
  и датчик подключены по шине I2C

  Для работы с датчиком BME280 используется библиотека "SparkFunBME280.h"
  SparkFun Electronics: https://www.sparkfun.com/products/13676
  https://github.com/sparkfun/SparkFun_BME280_Breakout_Board/pull/6
  Эта библиотека позволяет использовать два датчика BME280 с разными адресами
  I2C:
    0х76 - адрес с завода - уличный датчик;
    0x77 - адрес после перепайки - комнатный датчик.

  Hardware connections:
  BME280 -> Arduino
  GND -> GND
  3.3 -> 3.3V
  SDA -> A4
  SCL -> A5

  created 26 Dec 2018
  by Alexey Vorotikov
  modified 18 Jan 2019
  by Alexey Vorotikov
 ******************************************************************************/

#include <Wire.h>
#include "SparkFunBME280.h"
#include <LiquidCrystal_I2C.h>

// создаем объекты - датчики температуры, влажности и давления:
BME280 outSensor;
BME280 intSensor;

// создаем объект - экран, передаём используемый адрес и разрешение экрана:
LiquidCrystal_I2C lcd(0x27, 16, 2);

int   delayTime;    // интервал опроса датчика
float outTemp;      // температура
int   outHumidity;  // влажность
int   outPressure;  // давление
float intTemp;      // температура
int   intHumidity;  // влажность
int   intPressure;  // давление

void setup() {
  
  //  Serial.begin(9600);
  //  Serial.println("Example showing dewpoint calculation");

  outSensor.setI2CAddress(0x76); //Connect to a out sensor
  intSensor.setI2CAddress(0x77); //Connect to a home sensor

  //  if (outSensor.beginI2C() == false) Serial.println("Sensor OUT failed");
  // if (intSensor.beginI2C() == false) Serial.println("Sensor INT failed");

  bool status;  // статус датчика bme

  // инициализируем экран:
  lcd.init();
  // включаем подсветку:
  lcd.backlight();

  // очищаем экран:
  lcd.clear();
  
  // устанавливаем курсор в колонку 0, строку 0;
  lcd.setCursor(0, 0);

  // определяем статус внешнего датчика и ожидаем его подключения:
  status = outSensor.beginI2C();
  if (!status) {
    lcd.print("No BME280 OUT sensor!");
    while (1);

  }

  // устанавливаем курсор в колонку 0, строку 1;
  lcd.setCursor(0, 1);

  // определяем статус внутреннего датчика и ожидаем его подключения:
  status = intSensor.beginI2C();
  if (!status) {
    lcd.print("No BME280 INT sensor!");
    while (1);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Default Test");
  delayTime = 10000; // задаём интервал опроса датчика 10сек.
  delay(1000); // даём датчикам запуститься

}

void loop() {
  
  readValues();
  printValues();
  delay(delayTime);

  //  Serial.print("Humidity: ");
  //  Serial.print(outSensor.readFloatHumidity(), 0);
  //  Serial.print(" / ");
  //  Serial.print(intSensor.readFloatHumidity(), 0);
  //
  //  Serial.print(" Pressure: ");
  //  Serial.print(outSensor.readFloatPressure()*0.0075, 0);
  //  Serial.print(" / ");
  //  Serial.print(intSensor.readFloatPressure()*0.0075, 0);
  //
  //  Serial.print(" Temp: ");
  //  Serial.print(outSensor.readTempC(), 1);
  //  Serial.print(" / ");
  //  Serial.print(intSensor.readTempC(), 1);
  //Serial.print(outSensor.readTempF(), 2);

  //  Serial.print(" Dewpoint: ");
  //  //Serial.print(outSensor.dewPointC(), 2);
  //  Serial.print(outSensor.dewPointF(), 2);

  //Serial.println();

  //delay(5000);
}

void readValues() {
  outTemp = outSensor.readTempC();
  outHumidity = outSensor.readFloatHumidity();
  outPressure = outSensor.readFloatPressure() * 0.0075;
  intTemp = intSensor.readTempC();
  intHumidity = intSensor.readFloatHumidity();
  intPressure = intSensor.readFloatPressure() * 0.0075;
}

void printValues() {

  lcd.clear();

  if (outTemp >= 0) {
    lcd.setCursor(1, 0); // если температура больше 0, то ставим курсор в 1 столб
  }
  else {
    lcd.setCursor(0, 0); // если температура меньше 0, то оставляем место для "-"
  }
  lcd.print(outTemp, 1);
  lcd.setCursor(5, 0);
  lcd.print("C");

  lcd.setCursor(7, 0);
  lcd.print(outHumidity);
  lcd.setCursor(9, 0);
  lcd.print("%");

  lcd.setCursor(11, 0);
  lcd.print(outPressure);
  lcd.setCursor(14, 0);
  lcd.print("mm");


  lcd.setCursor(0, 1);

  lcd.print(intTemp, 1);
  lcd.setCursor(5, 1);
  lcd.print("C");

  lcd.setCursor(7, 1);
  lcd.print(intHumidity);
  lcd.setCursor(9, 1);
  lcd.print("%");

  lcd.setCursor(11, 1);
  lcd.print(intPressure);
  lcd.setCursor(14, 1);
  lcd.print("mm");

}
