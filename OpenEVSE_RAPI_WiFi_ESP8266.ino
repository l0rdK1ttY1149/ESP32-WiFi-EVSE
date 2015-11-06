/*
 * Copyright (c) 2015 Chris Howell
 *
 * This file is part of Open EVSE.
 * Open EVSE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * Open EVSE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Open EVSE; see the file COPYING.  If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
 
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>

ESP8266WebServer server(80);

const char *ssid = "OpenEVSE";
const char *password = "openevse";
String st;
String privateKey = "";
String node = "";



const char* host = "data.openevse.com";
String url = "/emoncms/input/post.json?node=";
const char* inputID_AMP   = "OpenEVSE_AMP:";
const char* inputID_VOLT   = "OpenEVSE_VOLT:";
const char* inputID_TEMP1   = "OpenEVSE_TEMP1:";
const char* inputID_TEMP2   = "OpenEVSE_TEMP2:";
const char* inputID_TEMP3   = "OpenEVSE_TEMP3:";
const char* inputID_PILOT   = "OpenEVSE_PILOT:";

int amp = 0;
int volt = 0;
int temp1 = 0;
int temp2 = 0;
int temp3 = 0;
int pilot = 0;

int buttonState = 0;
int clientTimeout = 0;
int i = 0;
unsigned long Timer;

void ResetEEPROM(){
  Serial.println("Erasing EEPROM");
  for (int i = 0; i < 512; ++i) { 
    EEPROM.write(i, 0);
    //Always print this so user can see activity during button reset
    Serial.print("#"); 
  }
  EEPROM.commit();   
}

void handleRoot() {
  String s;
  s = "<html><font size='20'><font color=006666>Open</font><b>EVSE</b></font><p><b>Open Source Hardware</b><p>Wireless Configuration<p>Networks Found:<p>";
        //s += ipStr;
        s += "<p>";
        s += st;
        s += "<p>";
        s += "<form method='get' action='a'><label><b><i>WiFi SSID:</b></i></label><input name='ssid' length=32><p><label><b><i>Password  :</b></i></label><input name='pass' length=64><p><label><b><i>Emon Key:</b></i></label><input name='ekey' length=32><p><label><b><i>OpenEVSE:</b></i></label><select name='node'><option value='0'>0 - Default</option><option value='1'>1</option><option value='2'>2</option><option value='3'>3</option><option value='4'>4</option><option value='5'>5</option><option value='6'>6</option><option value='7'>7</option><option value='8'>8</option></select><p><input type='submit'></form>";
        s += "</html>\r\n\r\n";
	server.send(200, "text/html", s);
}

void handleCfg() {
  String s;
  ResetEEPROM();
        

  String qsid = server.arg("ssid");
  String qpass = server.arg("pass");      
  String qkey = server.arg("ekey");
  String qnode = server.arg("node");
  
  Serial.println(qsid);
  Serial.println("");
  qpass.replace("%23", "#");
  qpass.replace('+', ' ');
  for (int i = 0; i < qsid.length(); ++i){
    EEPROM.write(i, qsid[i]);
    Serial.print("Wrote: ");
    Serial.println(qsid[i]); 
  }
  Serial.println("Writing Password to Memory:"); 
  for (int i = 0; i < qpass.length(); ++i){
    EEPROM.write(32+i, qpass[i]);
    Serial.print("Wrote: ");
    Serial.println("*"); 
  }
   Serial.println("Writing EMON Key to Memory:"); 
   for (int i = 0; i < qkey.length(); ++i){
     EEPROM.write(96+i, qkey[i]);
     Serial.print("Wrote: ");
     Serial.println(qkey[i]); 
   }
   Serial.println("Writing EMOM Node to Memory:"); 
   EEPROM.write(129, qnode[i]);
   Serial.print("Wrote: ");
   Serial.println(qnode[i]);  
   EEPROM.commit();
   s = "<html><font size='20'><font color=006666>Open</font><b>EVSE</b></font><p><b>Open Source Hardware</b><p>Wireless Configuration<p>SSID and Password<p>";
   //s += req;
   s += "<p>Saved to Memory...<p>Wifi will reset to join your network</html>\r\n\r\n";
   server.send(200, "text/html", s);
   delay(2000);
   WiFi.disconnect();
   ESP.reset(); 
}

void handleRst() {
  String s;
  s = "<html><font size='20'><font color=006666>Open</font><b>EVSE</b></font><p><b>Open Source Hardware</b><p>Wireless Configuration<p>Reset to Defaults:<p>";
  s += "<p><b>Clearing the EEPROM</b><p>";
  s += "</html>\r\n\r\n";
  ResetEEPROM();
  EEPROM.commit();
  server.send(200, "text/html", s);
  WiFi.disconnect();
  delay(1000);
  ESP.reset();
}

void setup() {
	delay(1000);
	Serial.begin(115200);
  EEPROM.begin(512);
  pinMode(0, INPUT);
  String esid;
  String epass = "";
 
  for (int i = 0; i < 32; ++i){
    esid += char(EEPROM.read(i));
  }
  for (int i = 32; i < 96; ++i){
    epass += char(EEPROM.read(i));
  }
  for (int i = 96; i < 128; ++i){
    privateKey += char(EEPROM.read(i));
  }
  node += char(EEPROM.read(129));
     
  if ( esid != 0 ) { 
    if (WiFi.status() != WL_CONNECTED){
      // test esid
      Serial.print("Configuring Wifi Client...");
      WiFi.mode(WIFI_STA);
      WiFi.disconnect(); 
      WiFi.begin(esid.c_str(), epass.c_str());
      delay(50);
      }
  }
  else {
    Serial.println();
    Serial.print("Configuring access point...");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    int n = WiFi.scanNetworks();
    Serial.print(n);
    Serial.println(" networks found");
    st = "<ul>";
    for (int i = 0; i < n; ++i){
      st += "<li>";
      st += WiFi.SSID(i);
      st += "</li>";
    }
    st += "</ul>";
    delay(100);
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  }
	
  //String req = server.on();
	server.on("/", handleRoot);
  server.on("/a", handleCfg);
  server.on("/reset", handleRst);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
  
  int erase = 0;  
  buttonState = digitalRead(0);
  while (buttonState == LOW) {
    buttonState = digitalRead(0);
    erase++;
    if (erase >= 5000) {
        ResetEEPROM();
        int erase = 0;
        WiFi.disconnect();
        Serial.print("Finished...");
        delay(2000);
        ESP.reset(); 
     } 
   }
   
   if ((millis() - Timer) >= 30000){
     Timer = millis();
     Serial.flush();
     Serial.println("$GE*B0");
     delay(100);
       while(Serial.available()) {
         String rapiString = Serial.readStringUntil('\r');
         if ( rapiString.startsWith("$OK ") ) {
           String qrapi; 
           qrapi = rapiString.substring(rapiString.indexOf(' '));
           pilot = qrapi.toInt();
           Serial.print("RAPI Pilot = ");
           Serial.println(pilot);
         }
       }  
   
     delay(100);
     Serial.flush();
     Serial.println("$GG*B2");
     delay(100);
     while(Serial.available()) {
       String rapiString = Serial.readStringUntil('\r');
       if ( rapiString.startsWith("$OK") ) {
         String qrapi; 
         qrapi = rapiString.substring(rapiString.indexOf(' '));
         amp = qrapi.toInt();
         Serial.print("RAPI Amps = ");
         Serial.println(amp);
         String qrapi1;
         qrapi1 = rapiString.substring(rapiString.lastIndexOf(' '));
         volt = qrapi1.toInt();
         Serial.print("RAPI Volts = ");
         Serial.println(volt);
       }
    }  
    delay(100);
    Serial.flush(); 
    Serial.println("$GP*BB");
    delay(100);
    while(Serial.available()) {
      String rapiString = Serial.readStringUntil('\r');
      if (rapiString.startsWith("$OK") ) {
        String qrapi; 
        qrapi = rapiString.substring(rapiString.indexOf(' '));
        temp1 = qrapi.toInt();
        Serial.print("RAPI Temp 1 = ");
        Serial.println(temp1);
        String qrapi1;
        int firstRapiCmd = rapiString.indexOf(' ');
        qrapi1 = rapiString.substring(rapiString.indexOf(' ', firstRapiCmd + 1 ));
        temp2 = qrapi1.toInt();
        Serial.print("RAPI Temp2 = ");
        Serial.println(temp2);
        String qrapi2;
        qrapi2 = rapiString.substring(rapiString.lastIndexOf(' '));
        temp3 = qrapi2.toInt();
        Serial.print("RAPI Temp3 = ");
        Serial.println(temp3);
      }
    } 
 
// Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      return;
    }
  
// We now create a URL for OpenEVSE RAPI data upload request
  
    String url_amp = inputID_AMP;
    url_amp += amp;
    url_amp += ",";
    String url_volt = inputID_VOLT;
    url_volt += volt;
    url_volt += ",";
    String url_temp1 = inputID_TEMP1;
    url_temp1 += temp1;
    url_temp1 += ",";
    String url_temp2 = inputID_TEMP2;
    url_temp2 += temp2;
    url_temp2 += ","; 
    String url_temp3 = inputID_TEMP3;
    url_temp3 += temp3;
    url_temp3 += ","; 
    String url_pilot = inputID_PILOT;
    url_pilot += pilot;
    url += node;
    url += "&json={";
    url += url_amp;
    if (volt <= 0) {
      url += url_volt;
    }
    if (temp1 != 0) {
      url += url_temp1;
    }
    if (temp2 != 0) {
      url += url_temp2;
    }
    if (temp3 != 0) {
      url += url_temp3;
    }
    url += url_pilot;
    url += "}&apikey=";
    url += privateKey.c_str();
    
// This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    delay(10);
    while(client.available()){
      String line = client.readStringUntil('\r');
    }
    Serial.println(host);
    Serial.println(url);
  }
}
