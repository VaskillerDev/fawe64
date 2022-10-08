#include "libs.h"
#include <math.h>

const uint_8 POITION_EFFECT = 5;

void usePoition()
{
    Player* player = player_getInstance();
    player->health.currentPoints += POITION_EFFECT;
    
    if(player->health.currentPoints > player->health.maxPoints)
    {
        player->health.currentPoints = player->health.maxPoints;
    }
}