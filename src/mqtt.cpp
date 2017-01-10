#include "emonesp.h"
#include "mqtt.h"
#include "config.h"

#include <Arduino.h>
#include <PubSubClient.h>             // MQTT https://github.com/knolleary/pubsubclient PlatformIO lib: 89
#include <WiFiClient.h>

WiFiClient espClient;                 // Create client for MQTT
PubSubClient mqttclient(espClient);   // Create client for MQTT

long lastMqttReconnectAttempt = 0;
int clientTimeout = 0;
int i = 0;


// -------------------------------------------------------------------
// Function to be called when msg is received on MQTT subscribed topic
//
// -------------------------------------------------------------------
void mqttmsg_callback(char* topic, byte* payload, unsigned int length)
{
  DEBUG.println("MQTT message received");
  DEBUG.print("Message arrived [");
  DEBUG.print(topic);
  DEBUG.print("] ");
  for (int i=0;i<length;i++) {
    DEBUG.print((char)payload[i]);
  }
  DEBUG.println();
}

// -------------------------------------------------------------------
// MQTT Connect
// -------------------------------------------------------------------
boolean mqtt_connect()
{
  mqttclient.setServer(mqtt_server.c_str(), 1883);
  mqttclient.setCallback(mqttmsg_callback); //function to be called when mqtt msg is received on subscribed topic
  DEBUG.println("MQTT Connecting...");
  String strID = String(ESP.getChipId());
  if (mqttclient.connect(strID.c_str(), mqtt_user.c_str(), mqtt_pass.c_str())) {  // Attempt to connect
    DEBUG.println("MQTT connected");
    mqttclient.publish(mqtt_topic.c_str(), "connected"); // Once connected, publish an announcement..
    String mqtt_sub_topic = mqtt_topic + "/rapi/#";
    mqttclient.subscribe(mqtt_sub_topic.c_str());
  } else {
    DEBUG.print("MQTT failed: ");
    DEBUG.println(mqttclient.state());
    return(0);
  }
  return (1);
}

// -------------------------------------------------------------------
// Publish to MQTT
// Split up data string into sub topics: e.g
// data = CT1:3935,CT2:325,T1:12.5,T2:16.9,T3:11.2,T4:34.7
// base topic = emon/emonesp
// MQTT Publish: emon/emonesp/CT1 > 3935 etc..
// -------------------------------------------------------------------
void mqtt_publish(String data)
{
  String mqtt_data = "";
  String topic = mqtt_topic + "/" + mqtt_feed_prefix;
  int i=0;
  while (int(data[i])!=0)
  {
    // Construct MQTT topic e.g. <base_topic>/CT1 e.g. emonesp/CT1
    while (data[i]!=':'){
      topic+= data[i];
      i++;
      if (int(data[i])==0){
        break;
      }
    }
    i++;
    // Construct data string to publish to above topic
    while (data[i]!=','){
      mqtt_data+= data[i];
      i++;
      if (int(data[i])==0){
        break;
      }
    }
    // send data via mqtt
    //delay(100);
    DEBUG.printf("%s = %s\r\n", topic.c_str(), mqtt_data.c_str());
    mqttclient.publish(topic.c_str(), mqtt_data.c_str());
    topic = mqtt_topic + "/" + mqtt_feed_prefix;
    mqtt_data="";
    i++;
    if (int(data[i])==0) break;
  }

  String ram_topic = mqtt_topic + "/" + mqtt_feed_prefix + "freeram";
  String free_ram = String(ESP.getFreeHeap());
  mqttclient.publish(ram_topic.c_str(), free_ram.c_str());
}

// -------------------------------------------------------------------
// MQTT state management
//
// Call every time around loop() if connected to the WiFi
// -------------------------------------------------------------------
void mqtt_loop()
{
  if (!mqttclient.connected()) {
    long now = millis();
    // try and reconnect continuously for first 5s then try again once every 10s
    if ( (now < 50000) || ((now - lastMqttReconnectAttempt)  > 100000) ) {
      lastMqttReconnectAttempt = now;
      if (mqtt_connect()) { // Attempt to reconnect
        lastMqttReconnectAttempt = 0;
      }
    }
  } else {
    // if MQTT connected
    mqttclient.loop();
  }
}

void mqtt_restart()
{
  if (mqttclient.connected()) {
    mqttclient.disconnect();
  }
}

boolean mqtt_connected()
{
  return mqttclient.connected();
}
