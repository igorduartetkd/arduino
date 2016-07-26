#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x9B, 0x36 };
byte ip[] = { 192,168, 129, 157 };


EthernetServer server(8090);
EthernetClient cliente;

int led1 = 5;

String senha = "amoeba";
String readString = String(50);
String statusLed;

//unsigned long previousMillis = 0;        // will store last time LED was updated
//const long interval = 5000;           // interval at which to blink (milliseconds)

void setup() {
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  
  Serial.println("Comunicacao iniciada!");
  
}

void loop() {

  EthernetClient client = server.available();
  //unsigned long currentMillis = millis();
  
  
  if(client) 
  {
    while(client.connected())
    {
      if(client.available()) 
      {
        char c = client.read();
        
        if(readString.length() < 50) {
          readString += (c);
        }
        
        if(c == '\n')
        {
          if(readString.indexOf(senha) >= 0) {
            Serial.println("Acesso liberado!");
            Serial.println("TEXTO LIDO: " + readString);
            digitalWrite(led1, HIGH);
            delay(5000);
            digitalWrite(led1, LOW);
          }
     
    
          // cabeçalho http padrão
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
         
         
          client.println("<!doctype html>");
          client.println("<html>");
          client.println("<head>");
          //client.println("<title>EthernetCliente</title>");
          client.println("<meta name=\"viewport\" content=\"width=320\">");
          client.println("<meta name=\"viewport\" content=\"width=device-width\">");
          client.println("<meta charset=\"utf-8\">");
          client.println("<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">");
          //client.println("<meta http-equiv=\"refresh\" content=\"3; URL=http://192.168.129.157:8090\">");
          client.println("</head>");
          client.println("<body>");
          //client.println("<center>");
          
          /*remover 
          client.println("<font size=\"5\" face=\"verdana\" color=\"green\">Acende</font>");
          client.println("<font size=\"3\" face=\"verdana\" color=\"red\"> ae </font>");
          client.println("<font size=\"5\" face=\"verdana\" color=\"blue\">Maluco</font><br />");
                          
          
          if(digitalRead(led1)) {
            statusLed = "Ligado";
          } else {
            statusLed = "Desligado";
          }
          client.println("<form action=\"led1\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">Rele - "+statusLed+"</button>");
          client.println("</form> <br />");  
           */
          
          readString = "";
          client.stop();
         
        }
      }
      
    }
  }
  
}
