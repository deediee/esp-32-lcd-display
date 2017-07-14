
#include <Arduino.h>
#include <WiFi.h>
#include "wifi.h"
IPAddress server(192,168,42,113);
WiFiClient client;
int port = 8888;
bool opakovani_pripojeni_portu = true; 
String typ_zpravy;
String ip;
String text;
String zprava;
char pismeno;
String stringOne = "<\r><\n>";


#define SERIAL_BAUDRATE 115200

#define I2C_SDA 22
#define I2C_SCL 23

#define LCD_I2C_ADDR 0x27
#define LCD_WIDTH 20
#define LCD_HEIGHT 4

#define KEYBOARD_DATA 19
#define KEYBOARD_CLK  18
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <PS2Keyboard.h>

LiquidCrystal_I2C lcd(LCD_I2C_ADDR, LCD_WIDTH, LCD_HEIGHT);
PS2Keyboard keyboard;



void setup()
{      
Serial.begin(115200);
Serial.begin(SERIAL_BAUDRATE);

Serial.println("\n\n\nESP32chat");

Wire.begin(I2C_SDA, I2C_SCL);

lcd.begin(LCD_WIDTH, LCD_HEIGHT);
lcd.backlight();

keyboard.begin(KEYBOARD_DATA, KEYBOARD_CLK);

lcd.backlight();




WiFi.mode(WIFI_STA);

Serial.println("pripojovani... ");

while (WiFi.status() !=WL_CONNECTED)



{
if(WiFi.status()==WL_CONNECT_FAILED||WiFi.status()==WL_CONNECTION_LOST||WiFi.status()==WL_DISCONNECTED)
{
WiFi.begin(ssid,password);
delay(500);
Serial.print("nelze se pripojit snaha o opakovani... ");
Serial.println(" ");
}

}





Serial.println("");
Serial.print("pripojil jsem se k siti ");
Serial.print(ssid);
Serial.print(" s IP adresou ");
Serial.println(WiFi.localIP());




}




void loop()

{
    String moje_ip = WiFi.localIP().toString();

    while (!client.connected())
    {
        Serial.print("pripojovani k portu ");
        if (client.connect(server,port))
        {
            Serial.print(port);
            Serial.println("...");
            Serial.print("pripojeno k portu ");
            Serial.print(port);
            Serial.println("");
            delay(500);
        }
    }

    Serial.setTimeout(99999);
    if (Serial.available())
    {
        zprava=Serial.readStringUntil('\n'); 
        client.println(zprava);
            
    } 

    if (client.available())
    {   
    
        typ_zpravy= client.readStringUntil(':');
        ip= client.readStringUntil(':');
        text= client.readStringUntil('\n');
        text.replace("\\n"," ");
        text.replace("\\r"," ");
        
        Serial.println(' ');
        
        typ_zpravy.replace("m"," pise: " );
        typ_zpravy.replace("c"," con. ");
        typ_zpravy.replace("d"," disc.");
        text.replace("10","");
        
        Serial.print(ip);
        Serial.print(typ_zpravy);
        Serial.print(text);
        Serial.println(" ");

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(ip);
        lcd.print(typ_zpravy);
        lcd.setCursor(0,1);
        lcd.print(text);



       
        

    }   

    if(WiFi.status()==WL_CONNECT_FAILED||WiFi.status()==WL_CONNECTION_LOST||WiFi.status()==WL_DISCONNECTED)
        {
            WiFi.begin(ssid,password);
            Serial.print("odpojeno snaha o opetovne pripojeni");
            Serial.println(" ");
        }

    
}
