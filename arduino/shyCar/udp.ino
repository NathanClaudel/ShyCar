#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// wifi connection variables
const char* ssid = "quantum_wifi";
const char* password = "quantumsecret";
boolean wifiConnected = false;

// UDP variables
unsigned int localPort = 8888;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet


void initConnection()
{
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  // only proceed if wifi connection successful
  if(wifiConnected)
  {  
    udpConnected = connectUDP();
  }
}

signed char *receivePacket()
{
  // check if the WiFi and UDP connections were successful
  if(wifiConnected){
    if(udpConnected){
      // if there’s data available, read a packet
      int packetSize = UDP.parsePacket();
      if(packetSize){
        Serial.println("");
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remote = UDP.remoteIP();
        for (int i =0; i < 4; i++)
        {
          Serial.print(remote[i], DEC);
          if (i < 3)
          {
            Serial.print(".");
          }
        }
        Serial.print(", port ");
        Serial.println(UDP.remotePort());
        
        // read the packet into packetBufffer
        UDP.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
        Serial.println("Contents:");
        Serial.println((int)packetBuffer[0]);
        Serial.println((int)packetBuffer[1]);
      }
    }
  }
  return (signed char *) packetBuffer;
}

void sendAvoiding(bool avoiding)
{          
  /*
  static bool avoidingPrev = false;

  if(avoidingPrev != avoiding)
  {
    avoidingPrev = avoiding;
    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.write(avoiding ? "y" : "n");
    UDP.endPacket();
  }
  */
}


// connect to UDP – returns true if successful or false if not
boolean connectUDP(){
  boolean state = false;
  
  Serial.println("");
  Serial.println("Connecting to UDP");
  
  if(UDP.begin(localPort) == 1){
    Serial.println("Connection successful");
    state = true;
  }
  else{
    Serial.println("Connection failed");
  }
  
  return state;
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  WiFi.hostname("ShyCar");
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
      state = false;
      break;
    }
    i++;
  }
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  return state;
}
