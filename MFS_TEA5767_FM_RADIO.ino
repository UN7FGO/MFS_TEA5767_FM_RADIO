#include <MFShield.h>
#include <Wire.h>
#include <TEA5767N.h>

// button assignment settings
#define BUTTON_START  2
#define BUTTON_PLUS   3
#define BUTTON_MINUS  1

MFShield mfs;
TEA5767N radio = TEA5767N();

int freq = 1029;
uint32_t t; 

/* ============= BUTTONS HANDLER FUNCTION ============= */
void keyAction (uint8_t key)
{
  switch (key)
  {
    case BUTTON_PLUS:
      freq += 1;
      break;

    case BUTTON_MINUS:
      freq -= 1;
      break;

    case BUTTON_START:
      mfs.showDisplay (false);
      radio.setStandByOn();
      radio.selectFrequency(float(freq) / 10);
      radio.setStandByOff();
      mfs.showDisplay (true);
      break;
  }
  mfs.display(freq, true);     // update counter value on display
}
/* =================================================== */
void setup() {
  //Turns the radio off
  radio.setStandByOff();
  // assign handler function for buttons (see above)
  mfs.onKeyPress (keyAction);
  radio.selectFrequency(float(freq) / 10);
}

void loop() {
  mfs.display(freq, true);     // update counter value on display
  mfs.loop(); 
}
