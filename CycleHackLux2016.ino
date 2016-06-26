// Include NeoPixel for on-board Pixel
#include <Adafruit_NeoPixel.h>

// GPS library includes
#include <Adafruit_GPS.h>
#ifdef __AVR__ 
 #include <SoftwareSerial.h>
#endif

// Dotstar LED-Strip includes
#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 72 // Number of LEDs in strip

#define PIN 8

// on-board pixel
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

// Here's how to control the LEDs from any two pins:
#define DATAPIN    9
#define CLOCKPIN   6

// Define strip object
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

// Connect to the GPS on the Serial1 hardware port
Adafruit_GPS GPS(&Serial1);
     
// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false
     
// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
     
void setup()
{
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");
     
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz
     
  // Request updates on antenna status, comment out to keep quiet
  //GPS.sendCommand(PGCMD_ANTENNA);

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
    clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif

  strip.begin(); // Initialize pins for output
  strip.setBrightness(200);
  strip.show();  // Turn all LEDs off ASAP

  pixel.begin();
  pixel.show();

  delay(1000);
  // Ask for firmware version
  Serial1.println(PMTK_Q_RELEASE);

}

     // Color to be defined: BRG (NOT RGB)
int      head  = 0, tail = -3; // Index of first 'on' and 'off' pixels
uint32_t color = 0xFF0000;      // 'On' color (starts red)
uint32_t blue = 0xFF0000;
uint32_t red = 0x00FF00;
uint32_t green = 0x0000FF;
uint32_t yellow = 0x06ED78;
uint32_t orange = 0x47FF63;
uint32_t white = 0xFFFFFF;

uint32_t timer = millis();

// Maximum speed in km/h
int MAXSPEED = 40;

// Convert to knots
int MAXSPEEDK = MAXSPEED / 1.852;

// Define LEDs per Knot  
int LEDpK = NUMPIXELS / MAXSPEEDK ;

// Fill the pixel with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void fullRed()
{
  uint16_t p;
  
  for(p=0; p<NUMPIXELS; p++) {
    strip.setPixelColor(p, red);
  }
  strip.show();
}

void fullWhite()
{
  uint16_t p;
  
  for(p=0; p<NUMPIXELS; p++) {
    strip.setPixelColor(p, white);
  }
  strip.show();
}


void blank()
{
  uint16_t p;
  
  for(p=0; p<NUMPIXELS; p++) {
    strip.setPixelColor(p, 0);
  }
  strip.show();
}

void fullGreen()
{
  uint16_t p;
  
  for(p=0; p<NUMPIXELS; p++) {
    strip.setPixelColor(p, green);
  }
  strip.show();
}

void speedUp()
{
  // uint16_t p;

  //for (long i = NUMPIXELS-1; i >= 0; --i) {
  //  Serial.print(i);
  //  strip.setPixelColor(i, green);
  //  delay(random(150,350));
  //  if (i == 10) {
  //    delay(500);
  // }
  //  strip.show();
  //}

  for(long p=NUMPIXELS-1; p>(NUMPIXELS*0.1); --p) {
    if (p > 50) {
      strip.setPixelColor(p, red);
    }
    else {
      if (p > 29) {
       strip.setPixelColor(p, yellow);
      }
    else {
      if (p > 1) {
       strip.setPixelColor(p, green);
      }
    }
    }

    if (p > 50) {
      delay(random(150,350));
    }
          else {
        delay(random(150,250));
          }
    if (p == 10) {
      delay(500);
    }

    if (p == random(50,60) ) {
      delay(random(10,70));
    }

    if (p == random(30,50) ) {
      delay(random(50,300));
    }

    if (p == random(20,30) ) {
      delay(random(100,700));
    }

    
    strip.show();
  }
}

void constantVar()
{
  uint16_t p;
  
  for(p=(NUMPIXELS*0.3); p<(NUMPIXELS*0.8); p++) {
    strip.setPixelColor(p, green);
    delay(random(150,350));
    if (p == 23) {
      delay(500);
    }
    strip.show();
  }
    delay(1500);

    for(p=(NUMPIXELS*0.8)-5; p<(NUMPIXELS*0.8)+5; p++) {
      strip.setPixelColor(p, green);
      delay(150);
      if (p == 23) {
        delay(500);
      }
      strip.show();
    } 
      delay(1500);
}

void swipeDown()
{
    uint16_t p;
    for(p=0; p<NUMPIXELS; p++) {
      Serial.println(p);
      strip.setPixelColor(p, 0);
      if (p > 50) {
        delay(random(250,300));
      }
      else {
        delay(random(150,250));
      }
      if (p == 42) {
        delay(1500);
      }
      if (p == 23) {
        delay(3000);
      }
      if (p == 64) {
        delay(700);
      }
      strip.show();
    }
}

void loop() // run over and over again
{
//  strip.setPixelColor(head, red); // 'On' pixel at head
//  strip.setPixelColor(NUMPIXELS, 0);     // 'Off' pixel at tail
//  strip.show();                     // Refresh strip

  //blank();
  
  //speedUp();

  //constantVar();

  //fullGreen();

  //swipeDownRed();
  
//  delay(20);                        // Pause 20 milliseconds (~50 FPS)

//  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
//    head = 0;                       //  Yes, reset head index to start
//    if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
//      color = 0xFF0000;             //   Yes, reset to red
//  }
//  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index

  // read data from the GPS in the 'main loop'
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }
  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis()) timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
//    Serial.println(LEDpK);
//    Serial.println(MAXSPEED);
//    Serial.println(MAXSPEEDK);
      //fullWhite();
      //blank();
      speedUp();
      swipeDown();

    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
      //fullRed();
      //fulleWhite();
      //speedUp();
      //colorWipe(pixel.Color(0, 0, 255), 50); // Blue

      if (GPS.speed < 1) {
        // Set strip
      }
    }
  }
}
