// Библиотека для подключения к беспроводной сети
#include <WiFi.h>
// Библиотека для создания HTTP запросов GET,POST и PUT
#include <HTTPClient.h>

/* Логин сети*/
const char* ssid = "ESP32_S3"; // Ваш SSID
/* Пароль сети*/
const char* password = "esp32_s3"; // Ваш пароль Wi-Fi

// Адрес сервера, к которому будет отправлен GET-запрос
const char* serverName = "http://192.168.1.1/data_temp_2";

void setup() {
  Serial.begin(115200);

  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}
// Основной цикл программы
void loop() {
  if (WiFi.status() == WL_CONNECTED) { // Проверка соединения с Wi-Fi
    HTTPClient http; // Создание объекта HTTPClient

    http.begin(serverName); // Установка адреса сервера
    http.addHeader("Content-Type", "text/plain"); // Установка заголовка

    String message = String(temperatureRead()); // Сообщение для отправки
    int httpResponseCode = http.POST(message); // Отправка POST-запроса с сообщением
    Serial.println(message);

    // Проверка кода ответа
    if (httpResponseCode > 0) {
      String response = http.getString(); // Получение ответа от сервера
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode); // Вывод кода ответа
      Serial.print("Response: ");
      Serial.println(response); // Вывод ответа
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode); // Вывод ошибки
    }

    http.end(); // Освобождение ресурсов
  } else {
    Serial.println("WiFi Disconnected");
  }
// Задержка 1000 мс
  delay(1000); 
}