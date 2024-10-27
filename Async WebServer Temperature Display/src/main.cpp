/**
 * \file main.cpp
 * \author 
 * \brief Создание Веб Сервера на контроллере ESP32-S3 в режиме работы AP. По запросу клиента при изменении
 * значения объекта slider на Веб Странице мы включаем/выключаем встроенный светодиод устройства и выводим 
 * в терминале значения температуры процессора устройства
 * \version 0.1
 * \date 2024-08-27
 * 
 * \copyright Copyright (c) 2024
 * 
 */

// Инструменты фреймворка Arduino
#include <Arduino.h>
// Библиотека для связи микроконтроллера с устройствами через интерфейс I2C
#include <Wire.h>
// Библиотека для создания Веб Сервера 
#include <WebServer.h>
// Библиотека для подключения к беспроводной сети
#include <WiFi.h>

// Подключаем .h файл с кодом Веб страницы
#include "site.h"

/* Логин сети устройства*/
const char *ssid = "Your_ssid";
/* Пароль сети устройства*/
const char *password = "Your_passsword";

/* IP локальной сети*/
IPAddress local_ip(192, 168, 1, 1); 
/* Gateway локальной сети*/
IPAddress gateway(192, 168, 1, 1);
/* Маска локальной сети*/
IPAddress subnet(255, 255, 255, 0);

// Объявление класса WebServer
WebServer server(80);

// Переменная для записи значения температуры
String temp;

// Функция отправка кода веб страницы
void handle_root()
{
    // Отправка кода веб страницы клиенту
    server.send(200, "text/html", HTML);
    // Время обновления веб-страницы
    delay(200);
}

// Функция чтения значения состояния слайдера на веб странице
void UpdateSlider()
{
    // Переменная для записи состояния слайдера 
    String mode_state = server.arg("mode"); 
    // Переменная под целочисленное значение номера режима работы, которое "говорит" клиент
    uint8_t mode;
    // Преобразование переменной в int
    mode = mode_state.toInt();

// Конструкция switch-case для сравнения переменной mode с набором значений
switch (mode)
    {
    // Случай, если mode равен 0 
    case 0 :
        // Выключаем светодиод
        neopixelWrite(48,0,0,0);
        // Вывод сообщения о том, что светодиод выключен
        Serial.println("Turning off");
        break;

    //Случай, если mode равен 1
    case 1:
        // Включаем светодиод с заданными значениями RGB значениями (1 - 255)
        neopixelWrite(48, 80, 80, 80);
        // Вывод сообщения о том, что светодиод включен
        Serial.println("Turning on");
        break;
    }
    // Отправка клиенту текстового сообщения о состоянии mode
    server.send(200, "text/plain", "mode");
}

// Функция инициализации данных и конфигурации работы модуля ESP32-S3
void setup() {
    // Инициализация начала обмена данных при помощи I2C
    Wire.begin();
    // Инициализация последовательного соединения и определение скорости передачи данных в бит/c (бод)
    Serial.begin(115200);
    // Запуск соединения WiFi, создание AP
    WiFi.begin(ssid, password);
    // Ожидание 100 мс
    delay(100);
    // Инициализация 
    WiFi.softAPConfig(local_ip, gateway, subnet);

    // Ивент на подключение к серверу нового клиента
    server.on("/",handle_root);
    // Ивент на изменение значения слайдера
    server.on("/mode",UpdateSlider);
    // Ожидание 250 мс
    delay(250);
    // Запуск сервера
    server.begin();
    // Вывод IP локальной сети устройства
    Serial.println(WiFi.localIP());
}
 
void loop()
{
    // Запись текущего значения температуры в формате string
    temp = String(temperatureRead());

    // Функция для обработки входящего HTTP запроса 
    server.handleClient();
    /* Вывод значения температуры в терминале*/
    Serial.println("Here's your temperature "+ temp);
    Serial.println("Updating...");
    Serial.println();

    // Ожидание 2500 мс
    delay(2500);
}



