
/*
  Description: This is a self-driven project to act as an introduction to microcontrollers, as well as
  physical computing. This project use the 4x4x4 led cube project created by KyleTheCreater on instructable 
  as a reference. The link to this reference can be found on my git page under the description for this 
  project. (https://www.instructables.com/4x4x4-LED-Cube-Arduino-Uno/)
  
  This project also serves as a the means to obtain skills in soldering from the creation of the cube. These are
  skills in would have learnt throught my electrical engineering degree, but were impacted by Covid-19. 

  Creator: Thalia Hartwig
  Hardware: Arduino UNO (generic)
  Software: Visual Studio
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

#define RPT     3
#define N       4 // Dimension of cube N x N x N 
#define D2      2 // Dimension of miniture cube
#define SLEEP   100

/////////////////////////////////////////////////////////////////
// Variables
/////////////////////////////////////////////////////////////////
int cathode[N][N] = {{0,2,9,13},{1,3,8,12},{A4,4,7,11},{A5,5,6,10}}; // cathode[x][y] --> (x,y)
int anode[N] = {A3,A0,A1,A2}; // anode[z] --> z

/////////////////////////////////////////////////////////////////
// pin setup and configuration
/////////////////////////////////////////////////////////////////
void setup() {
  for (int x=0; x < N ; x++) {
    for (int y=0; y < N; y++) {
     pinMode(cathode[x][y], OUTPUT); 
    }
  }
  for (int z=0; z < N; z++) pinMode(anode[z], OUTPUT);
}

/////////////////////////////////////////////////////////////////
// Main program loop
/////////////////////////////////////////////////////////////////
void loop() {
  // NOTE: currently being used for testing --> uncomment patterns
  turn_off();
  anode_op(1,3);
  anode_op(1,1);
  cathode_op(1,0,0);
  cathode_op(1,0,2);
  delay(SLEEP);
  // pulse_cube();
  bounce_cube();
  // turn_on();
  // turn_on_layers();
  // turn_on_columns();
  // weave();
  // delay(SLEEP);
  // turn_on_led(0,0,0);
  // delay(SLEEP);
  // vertices();
  // delay(SLEEP);
}

/////////////////////////////////////////////////////////////////
// cathode operation - on/off
// input:
//  on --> boolean
//   x --> int
//   y --> int
/////////////////////////////////////////////////////////////////
void cathode_op(boolean on) {
  for (int x = 0; x < N; x++) {
    for (int y = 0; y < N; y++) {
      digitalWrite(cathode[x][y],!on);
    }
  }
}

void cathode_op(boolean on, int x, int y) {
  digitalWrite(cathode[x][y], !on);
}

/////////////////////////////////////////////////////////////////
// anode operation - on/off
// input:
//  on --> boolean
//   z --> int
/////////////////////////////////////////////////////////////////
void anode_op(boolean on) {
  for (int z = 0; z < N; z++) {
    digitalWrite(anode[z],on);
  }
}

void anode_op(boolean on, int z) {
  digitalWrite(anode[z],on);
}

/////////////////////////////////////////////////////////////////
// turns all leds off
/////////////////////////////////////////////////////////////////
void turn_off() {
  cathode_op(0);
  anode_op(0);
}

/////////////////////////////////////////////////////////////////
// turns all leds on
/////////////////////////////////////////////////////////////////
void turn_on() {
  cathode_op(1);
  anode_op(1);
}

/////////////////////////////////////////////////////////////////
// turns on specific led --> (x,y,z)
// NOTE: (UPDATE --> Limitations)
/////////////////////////////////////////////////////////////////
void turn_on_led(int x, int y, int z) {
  cathode_op(1,x,y);
  anode_op(1,z);
}

/////////////////////////////////////////////////////////////////
// turns off specific led --> (x,y,z)
// NOTE: (UPDATE --> Limitation)
/////////////////////////////////////////////////////////////////
void turn_off_led(int x, int y, int z) {
  cathode_op(0,x,y);
  anode_op(0,z);
}

/////////////////////////////////////////////////////////////////
// turns on columns on after the other in weaving pattern
/////////////////////////////////////////////////////////////////
void turn_on_columns() {
  delay(SLEEP);
  anode_op(1);
  for (int x = 0; x < N; x++) {
    if (x % 2 == 0) {
      for (int y = 0; y < N; y++) {
        digitalWrite(cathode[x][y], 0);
        delay(SLEEP);
      }
    } else {
      for (int y = N - 1; y >= 0; y--) {
        digitalWrite(cathode[x][y], 0);
        delay(SLEEP);
      }
    }
  }
}

/////////////////////////////////////////////////////////////////
// repeating weaving pattern
/////////////////////////////////////////////////////////////////
void weave() {
  delay(SLEEP);
  anode_op(1);
  int rpt = RPT;
  while (rpt > 0) { 
    turn_off();
    for (int z = 0; z < N; z++) digitalWrite(anode[z], 1);
    // on-weave (0,0) --> (3,0) 
    for (int x = 0; x < N; x++) {
      if (x % 2 == 0) {
        for (int y = 0; y < N; y++) {
          digitalWrite(cathode[x][y], 0);
          delay(SLEEP);
        }
      } else {
        for (int y = N - 1; y >= 0; y--) {
          digitalWrite(cathode[x][y], 0);
          delay(SLEEP);
        }
      }
    }
    // off-weave (3,0) --> (3,3)
    for (int y = 0; y < N; y++) {
      if (y % 2 == 0) {
        for (int x = N - 1; x >= 0; x--) {
           digitalWrite(cathode[x][y],1);
           delay(SLEEP);
        }
      } else {
        for (int x = 0; x < N; x++) {
          digitalWrite(cathode[x][y],1);
          delay(SLEEP);
        }
      }
    }
    // on-weave (3,3) --> (0,3)
    for (int x = N - 1; x >= 0; x--) {
      if(x % 2 != 0) {
        for(int y = N - 1 ; y >= 0 ; y-- ) {
          digitalWrite(cathode[x][y],0);
          delay(SLEEP);
        }
      } else {
        for (int y = 0 ; y < N; y++) {
          digitalWrite(cathode[x][y],0);
          delay(SLEEP);
        }
      }
    }
    // off_weave (0,3) --> (0,0)
    for (int y = N - 1; y >= 0; y--) {
      if (y % 2 != 0) {
        for (int x=0; x < N; x++) {
          digitalWrite(cathode[x][y],1);
          delay(SLEEP);
        }
      } else {
        for (int x = N - 1; x >= 0; x--) {
          digitalWrite(cathode[x][y],1);
          delay(SLEEP);
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
  int rpt = RPT;
  while (rpt > 0) {
    turn_off();
    cathode_op(1);
    for (int z = 0; z < N; z++) {
      delay(SLEEP);
      digitalWrite(anode[z],1);
      if (z== N - 1) delay(SLEEP);
    }
    rpt--;
  }
}

/////////////////////////////////////////////////////////////////
// vertices
/////////////////////////////////////////////////////////////////
void vertices() {
  turn_off();
  turn_on_led(0   , 0  , 0  );
  turn_on_led(0   , 0  , N-1);
  turn_on_led(0   , N-1, 0  );
  turn_on_led(0   , N-1, N-1);
  turn_on_led(N-1 , 0  , 0  );
  turn_on_led(N-1 , 0  , N-1);
  turn_on_led(N-1 , N-1, 0  );
  turn_on_led(N-1 , N-1, N-1);
  delay(SLEEP*2);
}

/////////////////////////////////////////////////////////////////
// centered cube (Note: not scaled) 
/////////////////////////////////////////////////////////////////
void center_cube() {
  for (int x = 1; x < 3; x++) {
    for (int y = 1; y < 3; y++) {
      for (int z = 1; z < 3; z++) {
        turn_on_led(x,y,z);
      }
    }
  }
}

/////////////////////////////////////////////////////////////////
// pulsing  cube
/////////////////////////////////////////////////////////////////
void pulse_cube() {
  int rpt = RPT*3;
  while (rpt > 0) {
    turn_off();
    center_cube();
    delay(SLEEP);
//    turn_on();
    vertices();
    rpt--;
  }
}

/////////////////////////////////////////////////////////////////
// Light up 2x2x2 cube
/////////////////////////////////////////////////////////////////
void cube(int &xr, int &yr, int &zr) {
  turn_off();
  for (int z = 0; z < D2; z++) {
    anode_op(1, zr + z);
    for (int x = 0; x < D2; x++) {
      for (int y = 0; y < D2; y++) {
        cathode_op(1, xr + x, yr + y);
      }
    }
  }
  delay(SLEEP);
}

/////////////////////////////////////////////////////////////////
// cube translation
//
// direction --> case between [0,19]
//   (0,0,0) --> translation
// ---------------------------------
//  0   - ( 0, 1, 1)  
//  1   - ( 0, 1,-1) 
//  2   - ( 0,-1,-1) 
//  3   - ( 0,-1, 1) 
//  4   - ( 1, 0, 1) 
//  5   - ( 1, 1, 1) 
//  6   - ( 1, 1, 0) 
//  7   - ( 1, 1,-1) 
//  8   - ( 1, 0,-1) 
//  9   - ( 1,-1,-1) 
//  10  - ( 1,-1, 0)  
//  11  - ( 1,-1, 1) 
//  12  - (-1, 0, 1) 
//  13  - (-1, 1, 1) 
//  14  - (-1, 1, 0) 
//  15  - (-1, 1,-1) 
//  16  - (-1, 0,-1) 
//  17  - (-1,-1,-1) 
//  18  - (-1,-1, 0) 
//  19  - (-1,-1, 1) 
//
/////////////////////////////////////////////////////////////////
void cube_translate(int &xr, int &yr, int &zr, int direction) {
  switch (direction) {
    case 0:
      for (int cnt = 0; cnt < D2; cnt++) {
        yr++;
        zr++;
        cube(xr,yr,zr);
      }
      break;
    case 1:
      for (int cnt = 0; cnt < D2; cnt++) {
        yr++;
        zr--;
        cube(xr,yr,zr);
      }
      break;
    case 2:
      for (int cnt = 0; cnt < D2; cnt++) {
        yr--;
        zr--;
        cube(xr,yr,zr);
      }
      break;
    case 3:
      for (int cnt = 0; cnt < D2; cnt++) {
        yr--;
        zr++;
        cube(xr,yr,zr);
      }
      break;
    case 4:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr++;
        zr++;
        cube(xr,yr,zr);
      }
      break;
    case 5:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr++;
        yr++;
        zr++;
        cube(xr,yr,zr);
      }
      break;
    case 6:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr++;
        yr++;
        cube(xr,yr,zr);
      }
      break;
    case 7:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr++;
        yr++;
        zr--;
        cube(xr,yr,zr);
      }
      break;
    case 8:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr++;
        zr--;
        cube(xr,yr,zr);
      }
      break;
    case 9:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr++;
        yr--;
        zr--;
        cube(xr,yr,zr);
      }
      break;
    case 10:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr++;
        yr--;
        cube(xr,yr,zr);
      }
      break;
    case 11:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr++;
        yr--;
        zr++;
        cube(xr,yr,zr);
      }
      break;
    case 12:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr--;
        zr++;
        cube(xr,yr,zr);
      }
      break;
    case 13:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr--;
        yr++;
        zr++;
        cube(xr,yr,zr);
      }
      break;
    case 14:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr--;
        yr++;
        cube(xr,yr,zr);
      }
      break;
    case 15:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr--;
        yr++;
        zr--;
        cube(xr,yr,zr);
      }
      break;
    case 16:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr--;
        zr--;
        cube(xr,yr,zr);
      }
      break;
    case 17:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr--;
        yr--;
        zr--;
        cube(xr,yr,zr);
      }
      break;
    case 18:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr--;
        yr--;
        cube(xr,yr,zr);
      }
      break;
    case 19:
      for (int cnt = 0; cnt < D2; cnt++) {
        xr--;
        yr--;
        zr++;
        cube(xr,yr,zr);
      }
      break;
  default:
    turn_off();
    break;
  }
}

/////////////////////////////////////////////////////////////////
// bouncing cube: 
//
// dir --> random int [0,3]
// ------------------------
// 0  - left diagonal
// 1  - across diagonal 
// 2  - right disgonal
// 3  - up/down diagonal
//
/////////////////////////////////////////////////////////////////
void bounce_cube() {
  int x = 0, y = 0, z = 0;
  int dir;
  cube(x,y,z);

  while (1) {
    if ( x == 0 && y == 0 && z == 0) {
      dir = random(0,4);
      switch (dir) {
        case 0:
          cube_translate( x, y, z, 0);
          break;
        case 1:
          cube_translate( x, y, z, 6);
          break;
        case 2:
          cube_translate( x, y, z, 4);
          break;
        case 3:
          cube_translate( x, y, z, 5);
          break;
        default: 
          turn_off();
          break;
      }
    } 
    if ( x == 0 && y == 0 && z == 2) {
      dir = random(0,4);
      switch (dir) {
        case 0:
          cube_translate( x, y, z, 1);
          break;
        case 1:
          cube_translate( x, y, z, 6);
          break;
        case 2:
          cube_translate( x, y, z, 8);
          break;
        case 3:
          cube_translate( x, y, z, 7);
          break;
        default: 
          turn_off();
          break;
      }
    }
    if ( x == 0 && y == 2 && z == 0) {
      dir = random(0,4);
      switch (dir) {
        case 0:
          cube_translate( x, y, z, 4);
          break;
        case 1:
          cube_translate( x, y, z, 10);
          break;
        case 2:
          cube_translate( x, y, z, 3);
          break;
        case 3:
          cube_translate( x, y, z, 11);
          break;
        default: 
          turn_off();
          break;
      }
    }
    if ( x == 0 && y == 2 && z == 2) {
      dir = random(0,4);
      switch (dir) {
        case 0:
          cube_translate( x, y, z, 2);
          break;
        case 1:
          cube_translate( x, y, z, 10);
          break;
        case 2:
          cube_translate( x, y, z, 8);
          break;
        case 3:
          cube_translate( x, y, z, 9);
          break;
        default: 
          turn_off();
          break;
      }
    }
    if ( x == 2 && y == 0 && z == 0) {
      dir = random(0,4);
      switch (dir) {
        case 0:
          cube_translate( x, y, z, 12);
          break;
        case 1:
          cube_translate( x, y, z, 14);
          break;
        case 2:
          cube_translate( x, y, z, 0);
          break;
        case 3:
          cube_translate( x, y, z, 13);
          break;
        default: 
          turn_off();
          break;
      }
    }
    if ( x == 2 && y == 0 && z == 2) {
      dir = random(0,4);
      switch (dir) {
        case 0:
          cube_translate( x, y, z, 16);
          break;
        case 1:
          cube_translate( x, y, z, 14);
          break;
        case 2:
          cube_translate( x, y, z, 1);
          break;
        case 3:
          cube_translate( x, y, z, 15);
          break;
        default: 
          turn_off();
          break;
      }
    }
    if ( x == 2 && y == 2 && z == 0) {
      dir = random(0,4);
      switch (dir) {
        case 0:
          cube_translate( x, y, z, 3);
          break;
        case 1:
          cube_translate( x, y, z, 18);
          break;
        case 2:
          cube_translate( x, y, z, 12);
          break;
        case 3:
          cube_translate( x, y, z, 19);
          break;
        default: 
          turn_off();
          break;
      }
    }
    if ( x == 2 && y == 2 && z == 2) {
      dir = random(0,4);
      switch (dir) {
        case 0:
          cube_translate( x, y, z, 2);
          break;
        case 1:
          cube_translate( x, y, z, 18);
          break;
        case 2:
          cube_translate( x, y, z, 16);
          break;
        case 3:
          cube_translate( x, y, z, 17);
          break;
        default: 
          turn_off();
          break;
      }
    }
  }
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
