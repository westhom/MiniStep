// simple 4-step CV sequencer

#include <Automaton.h>
#include <Atm_button.h>
#include <Atm_led.h>

Factory factory;

#define NUM_STEPS 4

Atm_button button_steps[NUM_STEPS];
Atm_led led_steps[NUM_STEPS];
StepSequencer step_machine;

// define start of pins (assuming orderly pin out)
int button_pin_start = 5;
int led_pin_start = 9;

int blink_rate = 250;

void setup() {
  Serial.begin(9600);

  step_machine.begin();

  int pin_count = 0;
  for(int i=0; i<NUM_STEPS; i++){
    //
    // init step LEDs
    //
    led_steps[i].begin(led_pin_start + pin_count);
    led_steps[i].blink(blink_rate).pause(blink_rate);

    // kick off blinking
    led_steps[i].msgWrite(led_steps[i].MSG_BLINK);

    factory.add(led_steps[i]);

    //
    // init step buttons
    //
    button_steps[i].begin(button_pin_start + pin_count);
    button_steps[i].onPress(step_machine, step_machine.MSG_STEP_CHANGE);

    pin_count++;
  }
}

void loop() {
  factory.cycle();
}
