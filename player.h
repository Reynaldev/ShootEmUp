#pragma once

#include "gameobject.h"
#include "bullet.h"

class Player : public GameObject
{
public:
    float speedX = 0;
    float firespeed = 0;
    float nextFirespeed = 0;
    int maxAmmo = 0;
    int ammo = 0;
    bool isShoot = false;

    ~Player();

    void create(int maxAmmo, float firespeed);
    void move(float timeStep);
    void shoot(vector<Bullet> &bulletPool, vector<Bullet> &bullets);
    void destroy();
    
    void input(SDL_Event &e);
};
