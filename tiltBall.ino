
#include <NeoPixelBrightnessBus.h> // instead of NeoPixelBus.h
#define LED_POWER      2

const uint16_t PixelCount = 25; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 4;  // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 128

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

uint8_t matrice[5][5] = {
  {20, 15, 10, 5, 0},
  {21, 16, 11, 6, 1},
  {22, 17, 12, 7, 2},
  {23, 18, 13, 8, 3},
  {24, 19, 14, 9, 4}
};

struct led {
  int8_t row,
  int8_t col, 
  uint8_t val
};

struct led ball = {0, 0, 0};
struct led target = {4, 4, 24};

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial attach

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
  strip.SetBrightness(100);
}


void loop()
{
  if(millis() - timp >= pauza)
  {
    timp += pauza;
    readAccelerometer();
    refreshDisplay();
    
    
  }
  //delay(500);
#if 0
  Serial.println("Colors R, G, B, W...");

  // set the colors,
  // if they don't match in order, you need to use NeoGrbFeature feature
  strip.SetPixelColor(0, red);
  strip.SetPixelColor(5, green);
  strip.SetPixelColor(10, blue);
  strip.SetPixelColor(15, white);
  // the following line demonstrates rgbw color support
  // if the NeoPixels are rgbw types the following line will compile
  // if the NeoPixels are anything else, the following line will give an error
  //strip.SetPixelColor(3, RgbwColor(colorSaturation));
  strip.Show();


  delay(500);

  Serial.println("Off ...");

  // turn off the pixels
  strip.SetPixelColor(0, black);
  strip.SetPixelColor(5, black);
  strip.SetPixelColor(10, black);
  strip.SetPixelColor(15, black);
  strip.Show();

  delay(500);

  Serial.println("HSL Colors R, G, B, W...");

  // set the colors,
  // if they don't match in order, you may need to use NeoGrbFeature feature
  strip.SetPixelColor(0, hslRed);
  strip.SetPixelColor(1, hslGreen);
  strip.SetPixelColor(2, hslBlue);
  strip.SetPixelColor(3, hslWhite);
  strip.Show();


  delay(500);

  Serial.println("Off again...");

  // turn off the pixels
  strip.SetPixelColor(0, hslBlack);
  strip.SetPixelColor(1, hslBlack);
  strip.SetPixelColor(2, hslBlack);
  strip.SetPixelColor(3, hslBlack);
#endif
  int poz = random(0, 25);
  int cul = random(0, 5);
  for (int i = 0; i < 100; i++)
  {
    culoareChange(poz, cul);
    strip.SetBrightness(i);
    delay(1);
  }
  for (int i = 100; i >= 0; i--)
  {
    culoareChange(poz, cul);
    strip.SetBrightness(i);
    delay(1);
  }
  delay(30);

}

void culoareChange(int p, int c) {
  int cul = c;
  int poz = p;
  if (cul == 0)
    strip.SetPixelColor(poz, red);
  else if (cul == 1)
    strip.SetPixelColor(poz, green);
  else if (cul == 2)
    strip.SetPixelColor(poz, blue);
  else if (cul == 3)
    strip.SetPixelColor(poz, white);
  else if (cul == 4)
    strip.SetPixelColor(poz, mov);
  strip.Show();
}
