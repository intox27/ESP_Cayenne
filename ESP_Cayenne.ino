#define DHTTYPE DHT11
#define DHTPIN  D3

#include <CayenneMQTTESP8266.h>
#include "DHT.h"

char ssid[] = "******";
char wifiPassword[] = "******";
char username[] = "******";
char password[] = "******";
char clientID[] = "******";
DHT dht(DHTPIN, DHTTYPE);
float t;
float h;

void setup() {
    Serial.begin(115200);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop(){Cayenne.loop();}

CAYENNE_OUT(0){Cayenne.virtualWrite(0, millis());}

CAYENNE_OUT(1)
{
  do 
  {
    t = dht.readTemperature();
    delay(1000);
  }while  (isnan(t));
  Cayenne.virtualWrite(1, t);
}

CAYENNE_OUT(2)
{
  do 
  {
    h = dht.readHumidity();
    delay(1000);
  }while  (isnan(h));
  Cayenne.virtualWrite(2, h);
}

CAYENNE_OUT(3)
{
  delay(300);
  float plant = ( 1024 - analogRead(A0) );
  byte plantPer = float(plant / 800) * 100;  // ~800 is top range for my sensors
  Cayenne.virtualWrite(3, plantPer);
}

CAYENNE_IN(4)
{
  if (getValue.asInt() == 1) digitalWrite(D5, HIGH);
  else  digitalWrite(D5, LOW);
}

CAYENNE_IN(5)
{
  if (getValue.asInt() == 1) digitalWrite(D6, HIGH);
  else  digitalWrite(D6, LOW);
}

CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
}
