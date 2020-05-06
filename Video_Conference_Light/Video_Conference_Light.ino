// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      7

#define PIN_UP 10 // Pin for Up button
#define PIN_DOWN 5 // Pin for Down button

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Bounce debouncer_up = Bounce(); 
Bounce debouncer_down = Bounce(); 

int brightness = 25;

void setup() {
  Serial.begin(115200);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pinMode(PIN_UP, INPUT_PULLUP);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  debouncer_up.attach(PIN_UP);
  debouncer_up.interval(3); // interval in ms
  debouncer_down.attach(PIN_DOWN);
  debouncer_down.interval(3); // interval in ms

  pixels.begin(); // This initializes the NeoPixel library.
  update_light();
}

void loop() {
  // Update the Bounce instances :
  debouncer_up.update();
  debouncer_down.update();

  // Get the updated value :
  int btn_up = debouncer_up.read();
  int btn_down = debouncer_down.read();

  if (btn_up == LOW && btn_down == LOW){
    // both buttons are pressed
    // go to sleep
    // TODO: implement sleep
  }
  else if (btn_up == LOW){
    if (brightness < 255) {
      brightness += 1;
      Serial.print("UP BTN: ");
      Serial.println(brightness);
      update_light();
    }
  }
  else if (btn_down == LOW){
    if (brightness > 0) {
      brightness -= 1;
      Serial.print("DOWN BTN: ");
      Serial.println(brightness);
      update_light();
    }
  }
  delay(50);  
}

void update_light(void){
  for(int i=0;i<NUMPIXELS;i++){
    // make sure all are white (doing this once in setup is not good enough when brightness goes low)
    pixels.setPixelColor(i, pixels.Color(255,255,255));
  }
  pixels.setBrightness(brightness);
  pixels.show();
}
