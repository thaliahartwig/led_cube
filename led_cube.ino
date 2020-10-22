
/*
  Description: This is a self-driven project to act as an introduction to microcontrollers, as well as
  physical computing. This project use the 4x4x4 led cube project created by KyleTheCreater on instructable 
  as a reference. The link to this reference can be found on my git page under the description for this 
  project. (https://www.instructables.com/4x4x4-LED-Cube-Arduino-Uno/)
  
  This project also serves as a the means to obtain skills in soldering from the creation of the cube. These are
  skills in would have learnt throught my electrical engineering degree, but were impacted by Covid-19. 

  Creator: Thalia Hartwig
  Hardware: Arduino UNO (generic)
  Software: Arduino IDE
  Date Created: October 19, 2020
  Version: Version 0.0
  Last Revision: October 21, 2020
*/

/*
  Configuration: A right-handed axis of reference is used for this project
                                  z 
                                  |
                                  |
                                  |
                                  |
                                  |
                           (0,0,0)|_______________________ y
                                 /*  *  *  *
                                /*  *  *  *
                               /*  *  *  *
                              /*  *  *  *
                             /
                            /
                           x 
              (above model displays the first layer; z = 0)
  --> connections were done by column (x,y), and by plane (z) A 
  --> digital leads used for columns(cathodes) and analog(anodes) for layers

  Disclaimer: The pin selection was chosen based on wiring I had at time --> not ideal

  Column Configurations: (notation: (x,y) --> associated pin)   
  NOTE: Cathodes --> ON(0), OFF(1)
  (0,0) -->  0              (2,0) --> A4
  (0,1) -->  2              (2,1) --> 4
  (0,2) -->  9              (2,2) --> 7
  (0,3) -->  13             (2,3) --> 11
  (1,0) -->  1              (3,0) --> A5
  (1,1) -->  3              (3,1) --> 5
  (1,2) -->  8              (3,2) --> 6
  (1,3) -->  12             (3,3) --> 10

  Layer Configurations: (notation: (z = 0) --> associated pin)
  NOTE: Anodes --> ON(1), OFF(0)
  (z = 0) --> A3
  (z = 1) --> A0
  (z = 2) --> A1
  (z = 3) --> A2


  Limitations: (UPDATE-WIP)
  - diagonal patterns --> layers share a common anode
  - some limitations are asssociated to various functions. For more 
    details on specific function see description
*/

#define REPEAT  3
/////////////////////////////////////////////////////////////////
// Variables
/////////////////////////////////////////////////////////////////
int cathode[4][4] = {{0,2,9,13},{1,3,8,12},{A4,4,7,11},{A5,5,6,10}}; // cathode[x][y] --> (x,y)
int anode[4] = {A3,A0,A1,A2}; // anode[z] --> z
int sleep = 250;
//int rpt = 3; 

/////////////////////////////////////////////////////////////////
// pin setup and configuration
/////////////////////////////////////////////////////////////////
void setup() {
  for (int x=0; x < 4 ; x++) {
    for (int y=0; y < 4; y++) {
     pinMode(cathode[x][y], OUTPUT); 
    }
  }
  for (int z=0; z < 4; z++) pinMode(anode[z], OUTPUT);
}

/////////////////////////////////////////////////////////////////
// Main program loop
/////////////////////////////////////////////////////////////////
void loop() {
  // NOTE: currently being used for testing --> uncomment patterns
  turn_off();
//  turn_on();
//  turn_on_layers();
//  turn_on_columns();
  
  weave();
//  turn_on_led(0,0,0);
//  delay(sleep);
}


/////////////////////////////////////////////////////////////////
// turns all leds off
/////////////////////////////////////////////////////////////////
void turn_off() {
  for (int x=0; x < 4 ; x++) {
    for (int y=0; y < 4; y++) {
     digitalWrite(cathode[x][y], 1); 
    }
  }
  for (int z=0; z < 4; z++) digitalWrite(anode[z], 0);
  delay(sleep);
}

/////////////////////////////////////////////////////////////////
// turns all leds on
/////////////////////////////////////////////////////////////////
void turn_on() {
  for (int x=0; x < 4 ; x++) {
    for (int y=0; y < 4; y++) {
     digitalWrite(cathode[x][y], 0); 
    }
  }
  for (int z=0; z < 4; z++) digitalWrite(anode[z],1);
  delay(sleep);
}

/////////////////////////////////////////////////////////////////
// turns on specific led --> (x,y,z)
// NOTE: (UPDATE --> Limitations)
/////////////////////////////////////////////////////////////////
void turn_on_led(int x, int y, int z) {
  digitalWrite(cathode[x][y], 0);
  digitalWrite(anode[z], 1);
}

/////////////////////////////////////////////////////////////////
// turns off specific led --> (x,y,z)
// NOTE: (UPDATE --> Limitation)
/////////////////////////////////////////////////////////////////
void turn_off_led(int x, int y, int z) {
  digitalWrite(cathode[x][y], 1);
  digitalWrite(anode[z], 0);
}

/////////////////////////////////////////////////////////////////
// turns on columns on after the other in weaving pattern
/////////////////////////////////////////////////////////////////
void turn_on_columns() {
  delay(sleep);
  for (int z=0; z < 4; z++) digitalWrite(anode[z], 1);
  for (int x = 0; x < 4; x++) {
    if (x % 2 == 0) {
      for (int y=0; y < 4; y++) {
        digitalWrite(cathode[x][y], 0);
        delay(sleep);
      }
    } else {
      for (int y=3; y >= 0; y--) {
        digitalWrite(cathode[x][y], 0);
        delay(sleep);
      }
    }
  }
}

/////////////////////////////////////////////////////////////////
// repeating weaving pattern
/////////////////////////////////////////////////////////////////
void weave() {
  delay(sleep);
  for (int z=0; z < 4; z++) digitalWrite(anode[z], 1);
  int rpt = REPEAT;
  while (rpt > 0) { 
    turn_off();
    for (int z=0; z < 4; z++) digitalWrite(anode[z], 1);
    // on-weave (0,0) --> (3,0) 
    for (int x = 0; x < 4; x++) {
      if (x % 2 == 0) {
        for (int y=0; y < 4; y++) {
          digitalWrite(cathode[x][y], 0);
          delay(sleep);
        }
      } else {
        for (int y=3; y >= 0; y--) {
          digitalWrite(cathode[x][y], 0);
          delay(sleep);
        }
      }
    }
    // off-weave (3,0) --> (3,3)
    for (int y=0; y < 4; y++) {
      if (y % 2 == 0) {
        for (int x=3; x >= 0; x--) {
           digitalWrite(cathode[x][y],1);
           delay(sleep);
        }
      } else {
        for (int x=0; x < 4; x++) {
          digitalWrite(cathode[x][y],1);
          delay(sleep);
        }
      }
    }
    // on-weave (3,3) --> (0,3)
    for (int x=3; x >= 0; x--) {
      if(x % 2 != 0) {
        for(int y=3 ; y >= 0 ; y-- ) {
          digitalWrite(cathode[x][y],0);
          delay(sleep);
        }
      } else {
        for (int y=0 ; y < 4; y++) {
          digitalWrite(cathode[x][y],0);
          delay(sleep);
        }
      }
    }
    // off_weave (0,3) --> (0,0)
    for (int y=3; y >= 0; y--) {
      if (y % 2 != 0) {
        for (int x=0; x < 4; x++) {
          digitalWrite(cathode[x][y],1);
          delay(sleep);
        }
      } else {
        for (int x=3; x >= 0; x--) {
          digitalWrite(cathode[x][y],1);
          delay(sleep);
        }
      }
    }
    rpt--;
  }
}

/////////////////////////////////////////////////////////////////
// turns on leds in layers
/////////////////////////////////////////////////////////////////
void turn_on_layers() {
  int rpt = REPEAT;
  while (rpt > 0) {
    turn_off();
    for (int x=0; x < 4 ; x++) {
      for (int y=0; y < 4; y++) {
       digitalWrite(cathode[x][y], 0); 
      }
    }
    for (int z = 0; z < 4; z++) {
      delay(sleep);
      digitalWrite(anode[z],1);
      if (z==3) delay(sleep);
    }
    rpt--;
  }
}

/////////////////////////////////////////////////////////////////
// pulsing  cube
/////////////////////////////////////////////////////////////////
void pulse_cube() {
  // 
}

/////////////////////////////////////////////////////////////////
// bouncing cube
/////////////////////////////////////////////////////////////////
void bounce_cube() {
  turn_off(); //initialise the cube
}

/*
  Patterns to Generate:
  ____________________________________
  - flicker on
  - rotating plane (not ideal with 4x4x4)
  - bouncing cube
  - random/twinkling
  - stair/stacking
  - cube pulse
*/
