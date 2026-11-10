#include "DHTesp.h"

#define DHT_PIN 15
#define LDR_PIN 34
#define LED_PIN 26
#define BUZZER_PIN 27

DHTesp dht;

const float batasSuhu = 30.0;
const int batasCahaya = 2000;

void setup() {
  Serial.begin(115200);

  dht.setup(DHT_PIN, DHTesp::DHT22);

  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);
}

void loop() {
  TempAndHumidity data = dht.getTempAndHumidity();

  float suhu = data.temperature;
  float kelembapan = data.humidity;
  int cahaya = analogRead(LDR_PIN);

  Serial.println("--------------------");
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" C");

  Serial.print("Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  Serial.print("Cahaya: ");
  Serial.println(cahaya);

  if (cahaya > batasCahaya) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Lampu menyala");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Lampu mati");
  }

  if (!isnan(suhu) && suhu > batasSuhu) {
    tone(BUZZER_PIN, 1000);
    Serial.println("Suhu terlalu panas");
  } else {
    noTone(BUZZER_PIN);
    Serial.println("Suhu normal");
  }

  delay(2000);
}
