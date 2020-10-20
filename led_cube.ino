/*
  Description: This is a self-driven project to act as an introduction to microcontrollers, as well as
  physical computing. This project use the 4x4x4 led cube project created by KyleTheCreater on instructable 
  as a reference. The link to this reference can be found on my git page under the description for this 
  project. (https://www.instructables.com/4x4x4-LED-Cube-Arduino-Uno/)
  
  This project also serves as a the means to obtain skills in soldering for the creation of the cube which,
  I would have learnt throught University, had there been no restrictions put in place as a result of Covid-19.


  Creator: Thalia Hartwig
  Hardware: Arduino UNO (generic)
  Software: Visual Studio Code --> Arduino Extension
  Date Created: October 19, 2020
  Version: Version 0.0
  Last Revision: October 19, 2020
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

  Digital-Pin Configurations: (notation: (x,y) --> associated pin)
  (0,0) --> 13               (2,0) --> 5
  (0,1) --> 12               (2,1) --> 4
  (0,2) --> 11               (2,2) --> 3
  (0,3) --> 10               (2,3) --> 2
  (1,0) --> 9                (3,0) --> 1
  (1,1) --> 8                (3,1) --> 0
  (1,2) --> 7                (3,2) --> A5
  (1,3) --> 6                (3,3) --> A6

  Analog-Pin Configurations: (notation: (z = 0) --> associated pin)
  (z = 0) --> A0
  (z = 1) --> A1
  (z = 2) --> A2
  (z = 3) --> A3
*/

int cathode[16] = {13,12,11,10,9,8,7,6,5,4,3,2,1,0,A5,A6}; // columns
int anode[4] = {A0,A1,A2,A3}; // layers

void setup() {
  // Dependent on pin configurations
  foreach(cathode[i]) pinMode(cathode[i], OUTPUT);
  foreach(anode[i]) pinMode(anode[i], OUTPUT);
}

void loop() {
  // forks? break --> next pattern
}

//Pattern Algorithims go here
