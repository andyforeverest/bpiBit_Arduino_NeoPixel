#include <Arduino.h>
#include <NeoPixelBrightnessBus.h> // instead of NeoPixelBus.h
#define LED_POWER 2

const uint16_t PixelCount = 25; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 4;     // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 10

#include <MPU9250_asukiaaa.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

MPU9250_asukiaaa mySensor;
float aX, aY;

NeoPixelBrightnessBus<NeoRgbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor mov(colorSaturation, 0, colorSaturation);
RgbColor yellow(colorSaturation, colorSaturation, 0);
RgbColor black(0);

HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslBlack(black);


void readAccelerometer();

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ; // wait for serial attach

  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();

  // this resets all the neopixels to an off state
  strip.Begin();
  strip.Show();

  Serial.println();
  Serial.println("Running...");

  pinMode(LED_POWER, OUTPUT);
  digitalWrite(LED_POWER, HIGH);
  randomSeed(millis());

#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif

  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();
}
unsigned long timp = 0;
uint16_t pauza = 100;

uint8_t matrice[5][5] = {
    {20, 15, 10, 5, 0},
    {21, 16, 11, 6, 1},
    {22, 17, 12, 7, 2},
    {23, 18, 13, 8, 3},
    {24, 19, 14, 9, 4}};

struct led
{
  int8_t row;
  int8_t col;
};

struct led ball = {2, 2};
struct led target = {4, 4};

void loop()
{

  if (mySensor.accelUpdate() == 0 && millis() - timp >= pauza)
  {
    timp += pauza;
    strip.SetPixelColor(matrice[ball.row][ball.col], black);
    strip.Show();
    readAccelerometer();
    strip.SetPixelColor(matrice[ball.row][ball.col], red);
    strip.SetPixelColor(matrice[target.row][target.col], blue);
    if(matrice[ball.row][ball.col] == matrice[target.row][target.col]){
      strip.SetPixelColor(matrice[target.row][target.col], black);
      strip.Show();
      target.row = random(0, 4);
      target.col = random(0, 4);
      pauza -= 5;
      if(pauza < 20)
        pauza = 20;
    }
    strip.Show();
  }
}


void readAccelerometer()
{
  aX = mySensor.accelX();
  aY = mySensor.accelY();
  if (aX < -0.2)
  {
    ball.col++;
    if (ball.col > 4)
      ball.col = 4;
  }
  if (aY > 0.2)
  {
    ball.row--;
    if (ball.row < 0)
      ball.row = 0;
  }
  if (aX > 0.2)
  {
    ball.col--;
    if (ball.col < 0)
      ball.col = 0;
  }
  if (aY < -0.2)
  {
    ball.row++;
    if (ball.row > 4)
      ball.row = 4;
  }
  //Serial.println("accelX: " + String(aX));
  //Serial.println("accelY: " + String(aY));
 
}
