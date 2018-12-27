/***************************************************************************
 Room temperature, humidity and pressure
 Комнатная температура, влажность и давление

 Отображение на ЖК-дисплее LCD 1602 (I2C) данных о текущих температуре (°С),
 влажности (%) и давлении (mmHg - мм.рт.ст) с датчика BMP280 (I2C)

 created 26 Dec 2018
 by Alexey Vorotikov
 modified 26 Dec 2018
 by Alexey Vorotikov
 ***************************************************************************/

// подключаем библиотеки
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>

// создаем объект - датчик температуры, влажности и давления:
Adafruit_BME280 bme;

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
  status = bme.begin();
  if (!status) {
    lcd.print("No BME280 sensor!");
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
  temp = bme.readTemperature();
  humi = bme.readHumidity();
  pres = bme.readPressure() / 100.0F / 1.333;
}

void printValues() {

  lcd.clear();
  lcd.setCursor(1, 0);
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
