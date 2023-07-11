#pragma once

#include "gameobject.h"
#include "bullet.h"

class Player : public GameObject
{
public:
    float speedX = 0;
    int maxAmmo = 1;
    int ammo = maxAmmo;
    bool isShoot = false;

    ~Player();

    void input(SDL_Event& e);
    void move(float timeStep);
    void shoot(Bullet& bullet);
    void destroy();
};
