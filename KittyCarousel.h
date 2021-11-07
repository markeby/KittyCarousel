#include <InputDebounce.h>
#include <Streaming.h>
#include <CheapStepper.h>

//  I/O pin definitions
#define BUTTON_PAUSE    2
#define BUTTON_LIGHT    3
#define DEBUG_LED      13

#define BUTTTON_DEBOUNCE_DELAY    40      // ms

class INDICATOR_C
    {
private:
    bool   State;
    bool   flash;
    int8_t PinOut;
public:
    INDICATOR_C (int8_t pinOut = -1)
        {
        State = false;
        flash = false;
        }
    ~INDICATOR_C ()
        {}
    void Setup (int8_t pinOut)
        {
        PinOut = pinOut;
        pinMode (PinOut, OUTPUT);   // front panel LED
        digitalWrite (PinOut, HIGH);
        }
    void Light (bool on)
        {
        State = on;
        digitalWrite(PinOut, (on) ? LOW:HIGH);
        }
    void ToggleLight (void)
        {
        Light (!State);
        }
    void Flash (int rate)
        {
        unsigned long d = 1000 / rate;
        unsigned long h = d / 2;
        bool on = (millis () % d) > h;
        if ( on ^ flash )
            {
            flash = !flash;
            ToggleLight ();
            }
        }
    void On (void)
        {
        Light (true);
        }
    void Off (void)
        {
        Light (false);
        }
    };


class BUTTON_C : public InputDebounce
    {
public:
    BUTTON_C (int8_t pinIn = -1, unsigned long debDelay = DEFAULT_INPUT_DEBOUNCE_DELAY, PinInMode pinInMode = PIM_INT_PULL_UP_RES, unsigned long pressedDuration = 0)
        : InputDebounce(pinIn, debDelay, pinInMode, pressedDuration)
        { }
    virtual ~BUTTON_C (void)
        { }
protected:
      };
