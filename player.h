#pragma once

#ifndef player.h
#include "gameobject.h"
#endif

class Player : public GameObject
{
public:
    ~Player();

    int speedX = 0;

    void Move();
    void Destroy();
};
