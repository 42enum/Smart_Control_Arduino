#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Substitua com o SSID e senha da sua rede Wi-Fi
const char* ssid = "SFV";
const char* password = "testedinfra777";

ESP8266WebServer server(80); // Servidor na porta 80

void handleRoot() {
  server.send(200, "text/plain", "ESP8266 Web Server");
}

void handleReceiveData() {
  if (server.hasArg("plain")) {
    String receivedData = server.arg("plain");
    Serial.println(receivedData);
    server.send(200, "text/plain", "Dados recebidos com sucesso");
  } else {
    server.send(200, "text/plain", "Nenhum dado recebido");
  }
}

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  if(WiFi.status()== WL_CONNECTED){
    Serial.print("Conectado");
    Serial.print(WiFi.localIP());
  }
  

  server.on("/", handleRoot);
  server.on("/receiveData", HTTP_POST, handleReceiveData);

  server.begin();
}

void loop() {
  server.handleClient();
}
