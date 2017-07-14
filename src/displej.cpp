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

void setup() {
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println("\n\n\nESP32chat");

    Wire.begin(I2C_SDA, I2C_SCL);

    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
    lcd.backlight();

    keyboard.begin(KEYBOARD_DATA, KEYBOARD_CLK);

    lcd.backlight();
    lcd.print("ahoj");
}

void loop() {
    if (keyboard.available()) {
        lcd.write(keyboard.read());
    }
}