#pragma once

#include "gameobject.h"
#include "bullet.h"

class Player : public GameObject
{
private:
    int health = 0;
    int maxAmmo = 0;
    int ammo = 0;
public:
    float speedX = 0;
    float firespeed = 0;
    float nextFirespeed = 0;
    bool isShoot = false;

    ~Player();

    void create(int maxAmmo, float firespeed);
    void move(float timeStep);
    void shoot(vector<Bullet> &bulletPool, vector<Bullet> &bullets);
    void destroy();
    
    void input(SDL_Event &e);

    void setHealth(int amount);
    int getHealth();

    void setAmmo(int amount);
    void increaseAmmo(int amount);
    int getAmmo();

    void increaseMaxAmmo();
    int getMaxAmmo();

    void increaseFirespeed();
    float getFirespeed();
};
