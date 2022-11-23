https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
//=================================================================
// The main program file.
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <stdlib.h>

// Project includes
#include "globals.h"
#include "hardware.h"
#include "city_landscape_public.h"
#include "missile_public.h"
#include "player_public.h"

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

int num_city_g = 4;
// function prototypes
void set_random_seed(Timer);
int city_landscape_update(void);
int was_player_hit(void);
void missile_contact(void); 

int main()
{
    GameInputs inputs; 
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    pc.printf("Program Starting");

    // Game state variables
    int num_remain_city; // number of cities currently on the landscape
    int player_alive; // 1 if alive, 0 if hit
    
    testDLL();
    // Timer to measure game update speed (secondarily used to generate random seed)
    Timer t;
    int dt; // delta time
    set_random_seed(t); // Already implemented.
    
    //Initialization functions (already implemented)
    city_landscape_init(num_city_g);
    missile_init();
    player_init();        
    pc.printf("Initialization complete\n");

    while(1)
    {
        t.start();
        // Generate new missiles and draw all active missiles at current 
        // positions. (Already implemented.)
        missile_generator();
        
        // Draw all active anti-missiles (aka player missiles) at current 
        // positions. (Already implemented.)
        player_missile_draw();
        
        // Detect missile collisions with city/land and update status.
        // You need to implement this (see specification below).
        num_remain_city = city_landscape_update();
        
        // Detect missile collision with player aircraft.
        // You need to implement this (see specification below).
        player_alive = was_player_hit(); //returns 0 if player is hit; else 1
        
        // Detect missile collisions with player anti-missiles.
        // You need to implement this (see specification below).
        missile_contact();
    
        // You must complete the implementation of this function in hardware.cpp:
        inputs = read_inputs();

        // You must write the code to dispatch to the correct action (e.g., 
        // player_moveLeft/Right, player_fire, etc.) based on the inputs read.
        // You must also implement player_moveLeft/moveRight/fire (see player
        // module).

               
        // You must write code to detect and implement game over.        
        if (player_alive) break; // replace this line

        // Compute update time to control timing of the game loop.
        // (Already implemented... you're welcome.)
        t.stop();
        dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
    pc.printf("out of main loop\n");
    
    // You must write code to free up any dynamically allocated objects such
    // as lists of missiles (hint: destroyList can be used for doubly linked
    // lists).
    
    return 0;
}

/** Detect whether any missile has hit a city and if so, call 
    city_demolish (hint: city_get_info may be useful).
    Also, if any missile has hit a city or the landscape,
    mark the missile's status as MISSILE_EXPLODED 
    which will cue the missile's deletion and erasure from the screen 
    on the next missile_generator call.
    @return  Number of remaining cities.
*/
int city_landscape_update(void){
    // Complete this function.
    return num_city_g;
}

/** Detect whether any missile has hit the player aircraft and if so, call 
    player_destroy (hint: player_get_info may be useful) and mark the 
    missile's status as MISSILE_EXPLODED which will cue the missile's deletion
    and erasure from the screen on the next missile_generator call.
    @return 1 if the player aircraft was hit and 0 otherwise.
*/
int was_player_hit(){
    return 0;
}

/** Detect whether any missile has hit any player missile and if so, 
    mark the status of both the missile and the player missile as 
    MISSILE_EXPLODED which will cue the missile's deletion and erasure 
    from the screen on the next missile_generator call.
*/
void missile_contact(void) {
}

/* We need a random number generator (e.g., in missile_create to generate
   random positions for the missiles to start, making the game different
   every time).  C provides a pseudo random number generator (in stdlib) but
   it requires that we give it a different seed for each new game.  A common
   way to do this is to sample a clock and use the time as the seed.  However
   if we do this by starting a simple Timer t when the mbed starts running the 
   program and then sample it (t.read_ms), we will always get exactly the same
   time sample -- t.read_ms will always occur at the same time in the program's
   execution.  We introduce variability in when we sample the time by waiting
   for the user to push any button before we call t.read_ms.
*/
void set_random_seed(Timer t) {
    GameInputs inputs; 
    t.start();
    uLCD.printf("Push any button to start.\n");
    while(1){
      inputs = read_inputs();
      if (inputs.b1 || inputs.b2 || inputs.b3) break;
      }
    uLCD.cls();
    t.stop();
    int seed = t.read_ms();    
    srand(seed);
    }

