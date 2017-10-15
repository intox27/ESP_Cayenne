#define DHTTYPE DHT11
#define DHTPIN  D3

#include <CayenneMQTTESP8266.h>
#include "DHT.h"

char ssid[] = "******";
char wifiPassword[] = "******";
char username[] = "******";
char password[] = "******";
char clientID[] = "******";
unsigned long lastMillis = 0;
float h;
float t;
DHT dht(DHTPIN, DHTTYPE);

void setup() {

	Serial.begin(115200);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {

  h = dht.readHumidity();
  t = dht.readTemperature();
  Cayenne.loop();
	if (millis() - lastMillis > 10000) {
		lastMillis = millis();
		Cayenne.virtualWrite(0, lastMillis);
    Cayenne.celsiusWrite(1, t);
    Cayenne.celsiusWrite(2, h);
	}
}

CAYENNE_IN(3)
{
  if (getValue.asInt() == 1) digitalWrite(D5, HIGH);
  else  digitalWrite(D5, LOW);
}
CAYENNE_IN(4)
{
  if (getValue.asInt() == 1) digitalWrite(D6, HIGH);
  else  digitalWrite(D6, LOW);
}
CAYENNE_IN(5)
{
  if (getValue.asInt() == 1) digitalWrite(D7, HIGH);
  else  digitalWrite(D7, LOW);
}

CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
}
