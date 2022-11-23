https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
//=================================================================
// Implementation for the player module
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
#include "player_private.h"

PLAYER player; // structure of player

PLAYER player_get_info(void){ // getter for user to acquire info without accessing structure
    return player;
}

// initialize the player's position, missile status, draw player, 
void player_init(void) {    
    player.x = PLAYER_INIT_X; player.y = PLAYER_INIT_Y; player.status = ALIVE;    
    player.playerMissiles = create_dlinkedlist();    
    player.delta = PLAYER_DELTA;
    player.width = PLAYER_WIDTH; 
    player.height = PLAYER_HEIGHT;
    player_draw(PLAYER_COLOR);
}

// move player PLAYER_DELTA pixels to the left, except if it would go off screen.
void player_moveLeft(void) { 
    // Complete this function.  Hint: one way to animate moving an object is to
    // "erase" it at its current position (draw it using the background color)
    // and redraw it at the new position.
}

// move player PLAYER_DELTA pixels to the right, except if it would go off screen.
void player_moveRight(void) { 
    // Complete this function.
}

// generate an active missile to shoot 
void player_fire() { 
    // Complete this function.  It should allocate a PLAYER_MISSILE, initialize
    // it and insert it into the player's playerMissiles list.
}

// draw/updates the line of any active missiles, "erase" deactive missiles
void player_missile_draw(void) {
  PLAYER_MISSILE* playerMissile;
  LLNode* current = player.playerMissiles->head;
  while(current){
    playerMissile = (PLAYER_MISSILE*)current->data;                    
    if(playerMissile->status == PMISSILE_EXPLODED) {
      //pc.printf("pmd:exploded\n");
      uLCD.line(playerMissile->x, player.y-player.delta, playerMissile->x, playerMissile->y, BACKGROUND_COLOR);
      //pc.printf("deleting node...\n");
      deleteNode(player.playerMissiles, current);
      //pc.printf("node deleted.\n");
    }
    else { // update missile position
      playerMissile->y -= PLAYER_MISSILE_SPEED;
      if (playerMissile->y < 0) {
        //pc.printf("pmd:at top of screen\n");
        uLCD.line(playerMissile->x, player.y-player.delta, playerMissile->x, 0, BACKGROUND_COLOR);
        // Remove from list   
        //pc.printf("deleting node...\n");
        deleteNode(player.playerMissiles, current);
        //pc.printf("node deleted.\n");             
      }
      else {
        //pc->printf("pmd:normal\n");
        // draw missile
        uLCD.line(playerMissile->x, playerMissile->y+PLAYER_MISSILE_SPEED, playerMissile->x, playerMissile->y, PLAYER_MISSILE_COLOR);
      }
    }  
    current = current->next;              
  }
}
    

// ==== player_private.h implementation ====
void player_draw(int color) {
    uLCD.filled_rectangle(player.x, player.y, player.x+player.width, player.y+player.height, color); 
    uLCD.filled_rectangle(player.x+player.delta, player.y-player.delta, player.x+player.width-player.delta, player.y+player.height, color);
}

// destroy and "erase" the player off the screen. change status to DESTROYED
void player_destroy() {
    player_draw(BACKGROUND_COLOR);
    player.status = DESTROYED;
}
