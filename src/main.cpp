#include <Arduino.h>
#include <EasyButton.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

struct ButtonConfig
{
  EasyButton button;
  bool isPressed;
  uint8_t keyCode;
};

ButtonConfig buttons[] = {
    {EasyButton(4), false, KEY_F11},        // Button1 connected to GPIO14
    {EasyButton(14), false, KEY_F12},       // Button2 connected to GPIO27
    {EasyButton(15), false, KEY_F10}, // Button3 connected to GPIO4
    {EasyButton(27), false, KEY_F9},  // Button4 connected to GPIO5
    {EasyButton(26), false, KEY_F8}      // Button5 connected to GPIO6
};

void pressButton(ButtonConfig &buttonConfig)
{
  if (bleKeyboard.isConnected() && !buttonConfig.isPressed)
  {
    bleKeyboard.press(buttonConfig.keyCode);
    buttonConfig.isPressed = true;
  }
}

void releaseButton(ButtonConfig &buttonConfig)
{
  if (bleKeyboard.isConnected())
  {
    bleKeyboard.release(buttonConfig.keyCode);
    buttonConfig.isPressed = false;
  }
}

void handleButtonPress(ButtonConfig &buttonConfig)
{
  if (buttonConfig.isPressed)
  {
    releaseButton(buttonConfig);

    Serial.print("Button ");
    Serial.print(buttonConfig.keyCode);
    Serial.println(" released");
  }
}

void handleButton1Press()
{
  handleButtonPress(buttons[0]);
}
void handleButton2Press()
{
  handleButtonPress(buttons[1]);
}
void handleButton3Press()
{
  handleButtonPress(buttons[2]);
}
void handleButton4Press()
{
  handleButtonPress(buttons[3]);
}
void handleButton5Press()
{
  handleButtonPress(buttons[4]);
}

void setup()
{
  Serial.begin(115200);

  for (auto &buttonConfig : buttons)
  {
    buttonConfig.button.begin();
  }

  buttons[0].button.onPressed(handleButton1Press);
  buttons[1].button.onPressed(handleButton2Press);
  buttons[2].button.onPressed(handleButton3Press);
  buttons[3].button.onPressed(handleButton4Press);
  buttons[4].button.onPressed(handleButton5Press);

  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop()
{
  for (auto &buttonConfig : buttons)
  {
    buttonConfig.button.read();

    if (buttonConfig.button.isPressed())
    {
      Serial.println(printf("Button %i is currently pressed\n", buttonConfig.keyCode));

      pressButton(buttonConfig);
    }
  }
}
