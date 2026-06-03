#pragma once
#include "../Champion.h"


#define MAX_MINIONS

typedef struct {
    
    Champion blueChampion;
    Champion redChampion;

    Minion minions[MAX_MINIONS];

} gameState;
