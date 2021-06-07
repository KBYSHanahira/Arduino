#include <Wire.h>                     // Include Wire.h for I2C functionality
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(-1);
#include <Adafruit_NeoPixel.h>

#define NUMSLEDs  2
#define PINSLEDs  10
Adafruit_NeoPixel SLEDs = Adafruit_NeoPixel(NUMSLEDs, PINSLEDs, NEO_RGB + NEO_KHZ800);

void setup()
{
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  pinMode(PINSLEDs,OUTPUT); 
  SLEDs.begin(); // This initializes the NeoPixel library.
  SLEDs.show(); // Initialize all SLEDs to 'off'
  
}
void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  int ch0 = 0; 
  int mode = 1; // mode = 1 Single-ended, mode = 0 Differential
  int ADC8Ch0 = readADS7828(B10010001,ch0, mode); // เธญเนเธฒเธเธเนเธฒเธเนเธญเธ A0
  display.print("CH" + String(ch0) + " = ");
  display.println(String(ADC8Ch0) + "    "); //เนเธชเธ”เธเธเนเธฒเธญเธเธฒเธฅเธญเธเธเนเธญเธ A0
  
  int ch1 = 1; 
  int ADC8Ch1 = readADS7828(B10010001, ch1, mode); // เธญเนเธฒเธเธเนเธฒเธเนเธญเธ A1
  display.print("CH" + String(ch1) + " = ");   
  display.println(String(ADC8Ch1) + "    ");  //เนเธชเธ”เธเธเนเธฒเธญเธเธฒเธฅเธญเธเธเนเธญเธ A1
  
  display.display();
  delay(100);
}
unsigned int readADS7828(unsigned char ads_address, unsigned char channel, bool mode)
{
  ads_address = ads_address >> 1 ; //
  // command address for the channels, allows 0-7 channel mapping in the correct order
  unsigned char channels[8] = {0x00, 0x40, 0x10, 0x50, 0x20, 0x60, 0x30, 0x70};
  unsigned char command = 0;    // Initialize command variable
  unsigned int reading = 0;     // Initialize reading variable

  command = channels[channel];    // put required channel address in command variable

  if (mode) {                     // mode = 1 Single-ended input, mode = 0 Differential input
    command = command ^ 0x80;     // Enable Single-ended mode (toggle MSB, SD bit in datasheet)
  }

  Wire.beginTransmission(ads_address);  // Send a start or repeated start command with a slave address and the R/W bit set to '0' for writing.
  Wire.write(command);            // Then send a command byte for the register to be read.
  Wire.endTransmission();       // Send stop command
  delay(10);
  Wire.requestFrom(ads_address, 2);   // Request 2 bytes from the ADC
  if (2 <= Wire.available())      // if two bytes were received
  {
    reading = Wire.read();        // receive high byte
    reading = reading << 8;       // shift high byte to be high 8 bits
    reading |= Wire.read();       // receive low byte into lower 8 bits
  }
  return reading;         // return the full 12 bits reading from the ADC channel
}
