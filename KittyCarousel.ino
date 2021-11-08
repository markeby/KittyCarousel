#include "KittyCarousel.h"

//#define DEBUG 1

// initialize the stepper library
CheapStepper Stepper (6,9,10,11);
INDICATOR_C  Indicator;
BUTTON_C     Button;
bool         Pause;

void ButtonAction (uint8_t pinIn)
    {
    Pause  = !Pause;
    }

//------------------------------------------------------------------------------------------------------------
// ProcessSetup - Process monitor for setup and setup execution.
//------------------------------------------------------------------------------------------------------------
inline void  SetParameters ()
    {
    int  low = analogRead(0) / 6;
    int  hi  = analogRead(1) / 6;
    int  spd = analogRead(2) / 35;
    bool clockwise;
    int  distance;
    char buffer[40];

    Stepper.setRpm(spd);
    distance = random (low, hi);
    clockwise = ( random (1,3) > 1) ? true : false;
    Stepper.newMoveDegrees (clockwise, distance);
#ifdef DEBUG
    sprintf (buffer, "L=%4.4d  H=%4.4d  S=%4.4d  A=%4.4d  C=%d", low, hi, spd, distance, clockwise);
    Serial << buffer << endl;
#endif //DEBUG
    }

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
// loop - primary program loop
//------------------------------------------------------------------------------------------------------------
void loop()
    {
    unsigned long now = millis ();

    Button.process (now);

    if ( Pause)
        Indicator.Flash (2, 240);
    else
        Indicator.On ();

    if ( !Pause )
        {
        Stepper.run();
        if (Stepper.getStepsLeft() == 0)
            SetParameters ();
        }
    }

//------------------------------------------------------------------------------------------------------------
// setup - primary input output and system setup
//------------------------------------------------------------------------------------------------------------
void setup()
    {
    Serial.begin (9600);                // init serial

    pinMode (DEBUG_LED, OUTPUT);        //debug to LED 13
    digitalWrite (DEBUG_LED, LOW);

    Button.setup (BUTTON_PAUSE, BUTTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);
    Button.registerCallbacks (NULL, ButtonAction,  NULL,  NULL);

    Indicator.Setup (BUTTON_LIGHT);
    Pause = true;

    randomSeed(analogRead(3) * analogRead (4));
    SetParameters ();
    }
