#include <Arduino.h>
#include <EasyButton.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

EasyButton button1(14);  // Button1 connected to GPIO14
EasyButton button2(27);  // Button2 connected to GPIO27
bool b1Pressed = false;
bool b2Pressed = false;

void button1Pressed() {
  Serial.println("Button 1 pressed");
  if(b1Pressed){
    bleKeyboard.release(KEY_MEDIA_VOLUME_UP);
    b1Pressed = false;
  }
}

void button2Pressed() {
  Serial.println("Button 2 pressed");
  if(b2Pressed){
    bleKeyboard.release(KEY_MEDIA_VOLUME_DOWN);
    b2Pressed = false;
  }
}

void setup() {
  Serial.begin(115200);
  button1.begin();
  button2.begin();

  button1.onPressed(button1Pressed);
  button2.onPressed(button2Pressed);

  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

unsigned long lastMessage1 = 0;
unsigned long lastMessage2 = 0;

const unsigned long messageInterval = 10;  // Time in milliseconds between messages

void loop() {
  button1.read();
  button2.read();

  if (button1.isPressed() && (millis() - lastMessage1 >= messageInterval)) {
    Serial.println("Button 1 is currently pressed");
    lastMessage1 = millis();  // Update the time of the last message

    if(bleKeyboard.isConnected() && !b1Pressed){
      b1Pressed = true;
      bleKeyboard.press(KEY_MEDIA_VOLUME_UP);
    }
  }

  if (button2.isPressed() && (millis() - lastMessage2 >= messageInterval)) {
    Serial.println("Button 2 is currently pressed");
    lastMessage2 = millis();  // Update the time of the last message

    if(bleKeyboard.isConnected() && !b2Pressed ){
      b2Pressed = true;
      bleKeyboard.press(KEY_MEDIA_VOLUME_DOWN);
    }
  }
}
