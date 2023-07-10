#pragma once

#include "gameobject.h"

class Player : public GameObject
{
public:
    double speedX = 0;
    double maxAmmo = 1;
    double ammo = maxAmmo;

    ~Player();

    void move();
    void destroy();
};
