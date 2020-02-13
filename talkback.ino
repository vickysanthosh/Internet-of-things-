#include<Arduino.h>
#include<ESP8266WiFi.h>
#include<ESP8266WiFiMulti.h>
#include<ESP8266HTTPClient.h>
#define USE_SERIAL Serial
ESP8266WiFiMulti WiFiMulti;
const int relay=15;
void setup()
{
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(relay,OUTPUT);
  USE_SERIAL.begin(115200);
  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();
  for(uint8_t t=4; t>0;t--)
  {
    USE_SERIAL.printf("[SETUP]WAIT%d...\n",t);
    USE_SERIAL.flush();
    delay(1000);
  }
  WiFiMulti.addAP("vicky","vickypass");
}
void loop()
{
  if((WiFiMulti.run()==WL_CONNECTED))
  {
    HTTPClient http;
    USE_SERIAL.print("[HTTP]begin...\n");
    http.begin("http://api.thingspeak.com/talkbacks/37478/commands/17650639?api_key=5P8IOAZ27KE3DPT1");
    USE_SERIAL.print("[HTTP]GET...\n");
    int httpCode = http.GET();
    if(httpCode > 0)
    {
      USE_SERIAL.printf("[HTTP]GET...code:%d\n",httpCode);
      if(httpCode==HTTP_CODE_OK)
      {
        String payload = http.getString();
        USE_SERIAL.println(payload);
        if(payload=="LEDOFF")
        {
          digitalWrite(relay,LOW);
        }
        else if(payload=="LEDON")
        {
          digitalWrite(relay,HIGH);
        }
        else
        {
          USE_SERIAL.printf("[HTTP]GET...failed,error:%s\n",http.errorToString(httpCode).c_str());
        }
        http.end();
    }
    delay(2000);
  }
}
}
