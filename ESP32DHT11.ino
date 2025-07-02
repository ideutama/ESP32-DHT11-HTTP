#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#define DHTPIN 4

DHT dht(DHTPIN,DHT11);

const char* ssid = "nama SSID";
const char* password = "password SSID";

const char* serverUrl = "https://namasserver/receive_data.php"; // Ganti dengan URL server Anda
const int httpsPort = 443; // Port HTTPS umumnya adalah 443

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(100);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  //sendSensorData();
}

void sendSensorData() {
  HTTPClient http;

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Buat payload data yang ingin dikirim

  String postData = "sensor=DHT11";
  postData += "&lokasi=lokasi";
  postData += "&data1=" + String(t, 1);  // 1 angka di belakang koma
  postData += "&data2=" + String(h, 1);
  postData += "&data3=0";
  postData += "&keterangan=sukses";

  Serial.print("Sending data to server: ");
  Serial.println(postData);

  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Kirim data dengan metode POST
  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("SUhu = ");
  Serial.print(t);
  Serial.println(" C");
  Serial.print(" Kelembapan = ");
  Serial.print(h);
  Serial.println("&");

  sendSensorData();
  delay(60000);
}
