#include <IFTTTMaker.h>
//#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
 #include <ArduinoJson.h>
 #include "DHT.h"
#define DHTPIN D2  
// Uncomment whatever type you're using!
 #define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//------- Replace the following! ------
char ssid[] = "FAF";       // your network SSID (name)
char password[] = "302001000";  // your network key
#define KEY "diwi96TAIPOqj0F--F6L-u"  // Get it from this page https://ifttt.com/services/maker/settings
#define EVENT_NAME "weather_station" // Name of your event name, set when you are creating the applet
 WiFiClientSecure client;
IFTTTMaker ifttt(KEY, client);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  //triggerEvent takes an Event Name and then you can optional pass in up to 3 extra Strings
 if(ifttt.triggerEvent(EVENT_NAME,"Temperature","Humidity","City")){
   Serial.println("Successfully sent");
 } else
 {
  Serial.println("Failed!");
 }
  }
void loop() {
  // Wait a few seconds between measurements.
  delay(10000);
  float h = dht.readHumidity();
   float t = dht.readTemperature();
   float f = dht.readTemperature(true);

 Serial.print(h);
 Serial.print("-");
  Serial.print(t);
   Serial.print("-");
    Serial.print(f);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

 /* Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  */
  // delay(10000);
   bool triggerEvent(String eventName, String value1 = "", String value2 = "", String value3= "");
   if(ifttt.triggerEvent(EVENT_NAME,String (t),String (h),"baghdad")){
    Serial.println("Successfully sent");
  } else
  {
    Serial.println("Failed!");
  }
}
