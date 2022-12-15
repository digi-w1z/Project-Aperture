#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

#include <DFRobotDFPlayerMini.h>


const unsigned long eventInterval = 300000;
unsigned long previousTime = 0;

#define NUM_LEDS 24
#define PIN 7
#define LED  8
#define LED_2 13
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define BUTTON 11
#define BUTTON_2 12

bool oldState = LOW;
int showType = 0;

static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

void setup() {
  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
  // player.volume(30);
    // Play the first MP3 file on the SD card
   // player.play(1);


    digitalWrite(LED_2, HIGH);
    digitalWrite(LED, HIGH);

    pinMode(LED_2, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
  }

}



  // *** REPLACE FROM HERE ***
void loop() {

    unsigned long currentTime = millis();

    bool newState = digitalRead(BUTTON_2);
    bool newState2 = digitalRead(BUTTON);

    // Set volume to maximum (0 to 30).
    player.volume(30);
    // Play the first MP3 file on the SD card

    if (digitalRead(BUTTON_2) == LOW) {
          //colorWipe(strip.Color(0, 65, 194), 50);
      player.play(2);
      colorWipe(strip.Color(0, 65, 194), 25);
      colorWipe(strip.Color(60, 125, 254), 25);
      colorWipe(strip.Color(0, 65, 194), 25);

}


    if (digitalRead(BUTTON) == LOW) {
      player.play(1);
      colorWipe(strip.Color(255, 165, 0), 25);
      colorWipe(strip.Color(255, 215, 0), 25);
      colorWipe(strip.Color(255, 165, 0), 25);
}

    if (currentTime - previousTime >= eventInterval && digitalRead(BUTTON_2) == HIGH) {
      /* Event code */
      strip.fill((0, 0, 0));
      strip.show();

      /* Update the timing for the next time around */
      previousTime = currentTime;
}

    if (currentTime - previousTime >= eventInterval && digitalRead(BUTTON) == HIGH) {
      strip.fill((0, 0, 0));
      strip.show();
      digitalWrite(LED_2, LOW);

      previousTime = currentTime;
    }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
  

  
