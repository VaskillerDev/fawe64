#include "libs.h"

UT_icd object_icd = {sizeof(Sprite *), NULL, NULL, NULL};

Level* level_new()
{   
    Level* newLevel = (Level*)malloc(sizeof(Level));
    newLevel->levelName = "test";
    utarray_new(newLevel->objects, &object_icd);

    return newLevel;
}

Sprite *level_spawnObject(Level *level)
{
    Sprite *newObject = (Sprite *)malloc(sizeof(Sprite));
    utarray_push_back(level->objects, newObject);

    return newObject;
}

void level_draw(Level *level)
{
    for (Sprite *currentObject = (Sprite *)utarray_front(level->objects);
         currentObject != NULL;
         currentObject = (Sprite *)utarray_next(level->objects, currentObject))
    {
        sprite_Draw(currentObject);
    }
}