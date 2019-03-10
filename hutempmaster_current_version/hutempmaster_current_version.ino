#include <WiFi.h>
#include <Preferences.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define AP_SSID  "HuTemp"                                   //can set ap hostname here
#define BME_SCK 14
#define BME_MISO 32
#define BME_MOSI 15
#define BME_CS 33
#define SEALEVELPRESSURE_HPA (1013.25)


WiFiServer server(80);                                      //port 80 to send data to esp during AP mode
Preferences preferences;                                    //create instance of preferences memory to store setup parameters
WiFiClient client;                                          //create client instance
              
const int ledTrigger_1 = 13;                                //pin for led
static volatile bool wifi_connected = false;                //default wifi value
String wifiSSID, wifiPassword, sensorID, servIp, interval;  //string hold setup parameters
String urlString;                                           //string to send to database when writing data
byte ip[4];                                                 //byte array for ip
byte mac[6];                                                //mac address
char strMac[32] = "";                                       //hold characters for string mac address

//Adafruit_BME680 bme; // I2C
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);  //SPI configuration

void setup() {
  
      Serial.begin(115200);
      pinMode(ledTrigger_1, OUTPUT);
      WiFi.onEvent(WiFiEvent);
      WiFi.mode(WIFI_MODE_APSTA);
      WiFi.softAP(AP_SSID);
      Serial.println("AP Started");
      Serial.print("AP SSID: ");
      Serial.println(AP_SSID);
      Serial.print("AP IPv4: ");
      Serial.println(WiFi.softAPIP());

      // Get stored parameters from memory
      preferences.begin("wifi", false);
      //preferences.clear();
      wifiSSID =  preferences.getString("ssid", "none");     
      wifiPassword =  preferences.getString("password", "none");   
      sensorID = preferences.getString("sensorID", "none");        
      servIp = preferences.getString("serverIP", "none");          
      interval = preferences.getString("interval", "none");        
      preferences.end();

      //Print stored parameters to serial port for debugging purposes
      Serial.print("Stored SSID: ");        
      Serial.println(wifiSSID);
      Serial.print("Stored Password: ");
      Serial.println(wifiPassword);
      Serial.print("Stored sensor ID ");
      Serial.println(sensorID);
      Serial.print("Stored server IP: ");
      Serial.println(servIp);
      Serial.print("Stored Interval: ");
      Serial.println(interval);

      //convert wifi ssid and pass to characters and initialize wifi  
      WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str()); 

      //get mac address and print it for debug
      WiFi.macAddress(mac);
      Serial.print("MAC: ");
      Serial.print(mac[0],HEX);
      Serial.print(":");
      Serial.print(mac[1],HEX);
      Serial.print(":");
      Serial.print(mac[2],HEX);
      Serial.print(":");
      Serial.print(mac[3],HEX);
      Serial.print(":");
      Serial.print(mac[4],HEX);
      Serial.print(":");
      Serial.println(mac[5],HEX);
      server.begin();   //start webserver

      //check for communication with sensor
      if (!bme.begin()) {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
    
        while (1);  
      } 

      // Set up oversampling and filter initialization
      bme.setTemperatureOversampling(BME680_OS_8X);
      bme.setHumidityOversampling(BME680_OS_2X);
      bme.setPressureOversampling(BME680_OS_4X);
      bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
      bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop() 
{
    	if (wifi_connected) 
    	{
        wifiConnectedLoop();
      } else 
      {
        wifiDisconnectedLoop();
      }
}

void getTempAndHum()
{
      digitalWrite(ledTrigger_1, HIGH);
      Serial.print("Temperature = ");
      float t = bme.temperature;
      Serial.print(t);
      Serial.println(" *C");
      String tempData;                    //String to hold converted value
      tempData = String(t,1);             //parse float to string, one decimal point

      // not used in our project
      Serial.print("Pressure = ");
      float p = bme.pressure / 100.0;
      Serial.print(p);
      Serial.println(" hPa");

      Serial.print("Humidity = ");
      float h = bme.humidity;
      Serial.print(h);
      Serial.println(" %");
      String humidityData;                //String to hold converted value
      humidityData = String(h,1);         //parse float to string, one decimal point

      //not used in our project
      Serial.print("Gas = ");
      float g = bme.gas_resistance / 1000.0;
      Serial.print(g);
      Serial.println(" KOhms");

      //not used in our project
      Serial.print("Approx. Altitude = ");
      float a = bme.readAltitude(SEALEVELPRESSURE_HPA);
      Serial.print(a);
      Serial.println(" m");
      Serial.println();

      //convert mac to string
      getMacAndConvertToString(mac, 6, strMac);
      Serial.println(strMac);

      //create string that holds values to write to database
      urlString = "GET /datalogger/data.php?temperature=" + tempData + "&humidity=" + humidityData + "&sensorID=" + sensorID + "&MAC=" + strMac; //String to send data to server
      sendDataToServer(urlString);        //send it
      delay(2000);
}


void parseBytes(const char* str, char sep, byte* bytes, int maxBytes, int base) 
{
    for (int i = 0; i < maxBytes; i++) {
        bytes[i] = strtoul(str, NULL, base);  // Convert byte
        str = strchr(str, sep);               // Find next separator
        if (str == NULL || *str == '\0') {
            break;                            // No more separators, exit
        }
        str++;                                // Point to next character after separator
    }
}

void sendDataToServer(String stringToSend)
{
    const char* host = servIp.c_str();        //convert string ip address to char
    
    parseBytes(host, '.', ip, 4, 10);         //parse it  
  
    Serial.println(stringToSend);
    if (client.connect(ip, 80))               //use converted ip on port 80 to connect to database
      { 
          Serial.println("connected");
          client.println(stringToSend);             //send it
          client.println("Connection: close");
          client.println();
    
      }
      else
      {
      Serial.println("connection failed");
      }
}

void getMacAndConvertToString(byte mac[], unsigned int len, char buffer[]){
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (mac[i] >> 4) & 0x0F;
        byte nib2 = (mac[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}
void WiFiEvent(WiFiEvent_t event)
{
  switch (event) {

    case SYSTEM_EVENT_AP_START:
      //can set ap hostname here
      WiFi.softAPsetHostname(AP_SSID);
      //enable ap ipv6 here
      WiFi.softAPenableIpV6();
      break;
      
    case SYSTEM_EVENT_STA_START:
      //set sta hostname here
      WiFi.setHostname(AP_SSID);
      break;
      
    case SYSTEM_EVENT_STA_CONNECTED:
      //enable sta ipv6 here
      WiFi.enableIpV6();
      break;
      
    case SYSTEM_EVENT_AP_STA_GOT_IP6:
      //both interfaces get the same event
      //Serial.print("STA IPv6: ");
      //Serial.println(WiFi.localIPv6());
      //Serial.print("AP IPv6: ");
      //Serial.println(WiFi.softAPIPv6());
      break;
      
    case SYSTEM_EVENT_STA_GOT_IP:
      wifiOnConnect();
      wifi_connected = true;
      break;
      
    case SYSTEM_EVENT_STA_DISCONNECTED:
      wifi_connected = false;
      wifiOnDisconnect();
      break;
      
    default:
      break;
    }
}


String urlDecode(const String& text)
{
    String decoded = "";
    char temp[] = "0x00";
    unsigned int len = text.length();
    unsigned int i = 0;
    while (i < len)
    {
    char decodedChar;
    char encodedChar = text.charAt(i++);
    if ((encodedChar == '%') && (i + 1 < len))
    {
      temp[2] = text.charAt(i++);
      temp[3] = text.charAt(i++);

      decodedChar = strtol(temp, NULL, 16);
    }
    else {
      if (encodedChar == '+')
      {
        decodedChar = ' ';
      }
      else {
        decodedChar = encodedChar;  // normal ascii char
      }
    }
    decoded += decodedChar;
    }
  return decoded;
}

//when wifi connects
void wifiOnConnect()
{
    Serial.println("STA Connected");
    Serial.print("STA SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("STA IPv4: ");
    Serial.println(WiFi.localIP());
    //Serial.print("STA IPv6: ");
    //Serial.println(WiFi.localIPv6());
    WiFi.mode(WIFI_MODE_STA);     //close AP network
}

//when wifi disconnects
void wifiOnDisconnect()
{
    Serial.println("STA Disconnected");
    delay(1000);
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
}

//while wifi is connected
void wifiConnectedLoop()
{
    int readingDelayMin = interval.toInt();                           //read stored interval parameter and convert to int
    const unsigned long intervalMin = readingDelayMin * 60 * 1000UL;  //the timer
    static unsigned long lastSampleTime = 0 - intervalMin;            // initialize such that a reading is due the first time through loop()
    unsigned long now = millis();
      
      if (now - lastSampleTime >= intervalMin)                        //checks time remaining
      {
        lastSampleTime += intervalMin;
        getTempAndHum();                                              //take a reading
        Serial.println(readingDelayMin);                              //for degug to check the interval
      } 
      Serial.print("RSSI: ");
      Serial.println(WiFi.RSSI());
      delay(200);
}

void wifiDisconnectedLoop()
{
    
    WiFiClient client = server.available();   // listen for incoming clients
    
    if (client) {                             // if you get a client,
      Serial.println("New client");           // print a message out the serial port
    
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
            client.print("<form method='get' action='a'><label>SSID: </label><input name='ssid' length=32></br><label>PASSWORD: </label><input name='pass' length=64><br/><label>SensorID: </label><input name='sensorid' length=64></br><label>server IP address: </label><input name='serverIP' length=13></br><label>Iterval: </label><input name='interval' length=16></br><input type='submit'></form>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
            }
          } else if (c != '\r') {  // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
            continue;
          }

          if (currentLine.startsWith("GET /a?ssid=") ) {
            //Expecting something like:
            //GET /a?ssid=blahhhh&pass=poooo
            Serial.println("");

            // read the values from user input for parameters and save it in a string
            String theString = urlDecode(currentLine.substring(currentLine.indexOf('='), currentLine.lastIndexOf(' ')));
            Serial.println(theString);  //print the string for debug
            // Strings to hold parameter values from user
            String qssid;
            String qpass;
            String qsensorID;
            String qserverIp;
            String qinterval;

            // possitions in string to find and seperate substrings
            int ind1;
            int ind2;
            int ind3;
            int ind4;
            int ind5;

            // find all the substrings
            ind1 = theString.indexOf('&');
            qssid = theString.substring(1, ind1);
            ind2 = theString.indexOf('&', ind1+1);
            qpass = theString.substring(ind1+6, ind2);
            ind3 = theString.indexOf('&', ind2+1);
            qsensorID = theString.substring(ind2+10, ind3);
            ind4 = theString.indexOf('&', ind3+1);
            qserverIp = theString.substring(ind3+10, ind4);
            ind5 = theString.indexOf('&', ind4+1);
            qinterval = theString.substring(ind4+10, ind5);

            // prints values, for debug
            Serial.print("ssid: ");
            Serial.println(qssid);
            Serial.print("pass: ");
            Serial.println(qpass);
            Serial.print("sensorID: ");
            Serial.println(qsensorID);
            Serial.print("server IP: ");
            Serial.println(qserverIp);
            Serial.print("interval: ");
            Serial.println(qinterval);

            //save inputed values as startup parameters in device memory
            preferences.begin("wifi", false); // Note: Namespace name is limited to 15 chars
            Serial.println("Writing new ssid");
            preferences.putString("ssid", qssid);
  
            Serial.println("Writing new pass");
            preferences.putString("password", qpass);
           
            Serial.println("Writing new Sensor ID");
            preferences.putString("sensorID", qsensorID);
  
            Serial.println("Writing new server IP address");
            preferences.putString("serverIP", qserverIp);
  
            Serial.println("Writing new reading interval");
            preferences.putString("interval", qinterval);
            delay(300);
            preferences.end();

            // new web page requires http request in the following lines
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
  
            // the content of the HTTP response follows the header:
            
            client.print("<h1>OK! Restarting in 5 seconds...</h1>");
            client.println();
            Serial.println("Restarting in 5 seconds...");
            delay(5000);
            ESP.restart();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


         
    
