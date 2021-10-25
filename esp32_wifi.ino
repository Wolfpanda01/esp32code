/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
  pins need
  D13-up
  D12-down
  D14-left
  D27-right
  D26-froward
  D25-backward
  D32-clockwise
  D35-counterclockwise
  
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#define up 13
 #define down 12
#define left 14
#define right 27
#define froward 26
#define backward 25
#define clockwise 32
#define counterclockwise 35
// Set these to your desired credentials.
const char *ssid = "Wolfpack";
const char *password = "ClownFish1";

WiFiServer server(80);
 

void setup() {
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(froward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(clockwise, OUTPUT);
  pinMode(counterclockwise, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print ("Welcome to Malia Baker's quad control page"); 
            client.print("<button> <a href=\"/U\">up</a></button><br>");
            client.print("<button <a href=\"/D\">down</a><button><br>");
            client.print("<button> <a href=\"/F\">forward</a></button><br>");
            client.print("<button> <a href=\"/B\">backward</a></button><br>");
            client.print("<button> <a href=\"/L\">left</a></button><br>");
            client.print("<button> <a href=\"/R\">right</a></button><br>");
            client.print("<button> <a href=\"/CW\">cwise</a></button><br>");
            client.print("<button> <a href=\"/C\">countercwise</a></button><br>");
            client.print("<button> <a href=\"/AS\">All stop</a></button><br>");
            

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
              if (currentLine.endsWith("GET /U")) {
                digitalWrite(up, HIGH); 
                digitalWrite(down, LOW);
                digitalWrite(left, LOW);
                digitalWrite(right, LOW);
                digitalWrite(froward, LOW);
                digitalWrite(backward, LOW);
                digitalWrite(clockwise, LOW);
                digitalWrite(counterclockwise, LOW);
              }
              if (currentLine.endsWith("GET /D")) {
                digitalWrite(up, LOW); 
                 digitalWrite(down, HIGH);
                 digitalWrite(left, LOW);
                 digitalWrite(right, LOW);
                 digitalWrite(froward, LOW);
                 digitalWrite(backward, LOW);
                 digitalWrite(clockwise, LOW);
                 digitalWrite(counterclockwise, LOW);
                              
              }
               if (currentLine.endsWith("GET /L")) {
                digitalWrite(up, LOW); 
                 digitalWrite(down, LOW);
                 digitalWrite(left, HIGH);
                 digitalWrite(right, LOW);
                 digitalWrite(froward, LOW);
                 digitalWrite(backward, LOW);
                 digitalWrite(clockwise, LOW);
                 digitalWrite(counterclockwise, LOW);
            }
            if (currentLine.endsWith("GET /R")) {
                digitalWrite(up, LOW); 
                 digitalWrite(down, LOW);
                 digitalWrite(left, LOW);
                 digitalWrite(right, HIGH);
                 digitalWrite(froward, LOW);
                 digitalWrite(backward, LOW);
                 digitalWrite(clockwise, LOW);
                 digitalWrite(counterclockwise, LOW);
          }
           if (currentLine.endsWith("GET /F")) {
                digitalWrite(up, LOW); 
                 digitalWrite(down, LOW);
                 digitalWrite(left, LOW);
                 digitalWrite(right, LOW);
                 digitalWrite(froward, HIGH);
                 digitalWrite(backward, LOW);
                 digitalWrite(clockwise, LOW);
                 digitalWrite(counterclockwise, LOW);
           }
            if (currentLine.endsWith("GET /F")) {
                digitalWrite(up, LOW); 
                 digitalWrite(down, LOW);
                 digitalWrite(left, LOW);
                 digitalWrite(right, LOW);
                 digitalWrite(froward, LOW);
                 digitalWrite(backward, HIGH);
                 digitalWrite(clockwise, LOW);
                 digitalWrite(counterclockwise, LOW);
                 
            }
             if (currentLine.endsWith("GET /B")) {
                digitalWrite(up, LOW); 
                 digitalWrite(down, LOW);
                 digitalWrite(left, LOW);
                 digitalWrite(right, LOW);
                 digitalWrite(froward, LOW);
                 digitalWrite(backward, HIGH);
                 digitalWrite(clockwise, LOW);
                 digitalWrite(counterclockwise, LOW);
                  }
             if (currentLine.endsWith("GET /CW")) {
                digitalWrite(up, LOW); 
                 digitalWrite(down, LOW);
                 digitalWrite(left, LOW);
                 digitalWrite(right, LOW);
                 digitalWrite(froward, LOW);
                 digitalWrite(backward, LOW);
                 digitalWrite(clockwise, HIGH);
                 digitalWrite(counterclockwise, LOW);
                  }
             if (currentLine.endsWith("GET /C")) {
                digitalWrite(up, LOW); 
                 digitalWrite(down, LOW);
                 digitalWrite(left, LOW);
                 digitalWrite(right, LOW);
                 digitalWrite(froward, LOW);
                 digitalWrite(backward, LOW);
                 digitalWrite(clockwise, LOW);
                 digitalWrite(counterclockwise, HIGH);
                  }
             if (currentLine.endsWith("GET /AS")) {
                digitalWrite(up, LOW); 
                 digitalWrite(down, LOW);
                 digitalWrite(left, LOW);
                 digitalWrite(right, LOW);
                 digitalWrite(froward, LOW);
                 digitalWrite(backward, LOW);
                 digitalWrite(clockwise, LOW);
                 digitalWrite(counterclockwise, LOW);
             
             }
      }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
