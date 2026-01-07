#include <WiFi.h>
#include <HTTPClient.h>

// --------------------------------------------------------------------------
// CHANGE THESE TO MATCH YOUR NETWORK SETTINGS
// --------------------------------------------------------------------------
const char* ssid = "YOUR_WIFI_SSID";          // Replace with your WiFi Name
const char* password = "YOUR_WIFI_PASSWORD";  // Replace with your WiFi Password

// IMPORTANT: Do NOT use "localhost". Use your computer's local IP address (e.g., 192.168.1.5)
String serverName = "http://192.168.1.100:3000/message"; 
// --------------------------------------------------------------------------

unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
// unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timeDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  // Send an HTTP POST request every timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/json"); 
      
      // Data to send
      String httpRequestData = "{\"message\":\"Hello from ESP32\",\"value\":123}";
      
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
