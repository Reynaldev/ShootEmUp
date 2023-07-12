#pragma once

#include "gameobject.h"
#include "bullet.h"

class Player : public GameObject
{
public:
    float speedX = 0;
    float firespeed = 0;
    float nextFirespeed = 0;
    int ammo = maxAmmo;
    int maxAmmo = 1;
    bool isShoot = false;

    ~Player();

    void input(SDL_Event& e);
    void move(float timeStep);
    void shoot(vector<Bullet>& bulletPool, vector<Bullet>& bullets);
    void destroy();
};
