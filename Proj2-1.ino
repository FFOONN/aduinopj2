#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

DynamicJsonDocument docd(1024);
DynamicJsonDocument docs1(1024);
DynamicJsonDocument docs2(1024);
WiFiClient client;
PubSubClient mqtt(client);
#define WIFI_STA_NAME "มีแครอทนะ"
#define WIFI_STA_PASS "0638263001Fon"
#define MQTT_SERVER "electsut.trueddns.com"
#define MQTT_PORT 27860
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME "B6215354OANGKHANAaaaaaaabcd"
#define LED_PIN 23
#define sw 5
char out1[256];
char out2[256];
char out3[256];

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Topic= ");
  Serial.print(topic);
  deserializeJson(docd,payload,length);
  serializeJson(docd,out3);
  Serial.print(" : ");
  Serial.println(out3);
  int myLED=docd["LED"];
  Serial.println(myLED);
  const char* ledstate=docd["state"];
  Serial.println(ledstate);
  std::string s =ledstate;
  if(myLED==1){
    if(s=="on"){
      digitalWrite(18,HIGH);
               }
    else if(s=="off"){
      digitalWrite(18,LOW);
      }
      }
  else if(myLED==2){
    if(s=="on"){
      digitalWrite(19,HIGH);
               }
    else if(s=="off"){
      digitalWrite(19,LOW);
      }
      }  
               
           }
           
void setup() {
  Serial.begin(115200);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_STA_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt.setCallback(callback);

}
void loop() {
   if (mqtt.connected() == false) {
    Serial.print("MQTT connecting... ");
    if (mqtt.connect(MQTT_NAME, MQTT_USERNAME, MQTT_PASSWORD)){
      Serial.println("connected");
      mqtt.subscribe("inno/B6215354/Data");
    } 
    else {
      Serial.println("failed");
      delay(1000);
    }
  }

  else {
    mqtt.loop();   
    float ranCount=random(27,39);
    docs1["Temp"] = ranCount;
    serializeJson(docs1,out2);
    mqtt.publish("inno/b6215354/sent2",out2);
    delay(2000);
    }
}
