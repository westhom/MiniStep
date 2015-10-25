#include <Automaton.h>
#include <Atm_button.h>

class StepSequencer : public Machine {
  public:
    StepSequencer( void ) : Machine() { class_label = "STEPSEQ"; };

    bool button_states[ NUM_STEPS ];

    enum { PLAY_FWD, PLAY_REV, PLAY_RANDOM, STOP } STATES;
    enum { STEP_CHANGE, ELSE } EVENTS;
    enum { } ACTIONS;
    enum { MSG_STEP_CHANGE } MESSAGES;

    StepSequencer & begin(){
      const static state_t state_table[] PROGMEM = {
      /*                      ON_ENTER   ON_LOOP  ON_EXIT   STEP_CHANGE  ELSE */
      /* PLAY_FWD    */       -1,        -1,      -1,       -1,          -1,
      /* PLAY_REV    */       -1,        -1,      -1,       -1,          -1,
      /* PLAY_RANDOM */       -1,        -1,      -1,       -1,          -1,
      /* STOP        */       -1,        -1,      -1,       -1,          -1,
      };

      Machine::begin( state_table, ELSE );

      // init button states to off
      for(int i=0; i<NUM_STEPS; i++){
        button_states[i] = false;
      }
      
      return *this;
    }

    int event( int id ){
      switch( id ){
        case STEP_CHANGE:
          return msgRead( MSG_STEP_CHANGE );
      }
      return 0;
    }

    int action( int id ){
      return 0;
    }
}

