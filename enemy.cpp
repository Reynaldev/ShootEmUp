#include "enemy.h"

Enemy::~Enemy()
{
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->speedY = 0;
    this->health = 0;
    this->setActive(false);
    
    this->texture = NULL;
}

void Enemy::create(float speed, int health)
{
    this->speedY = speed;
    this->health = health;
}

void Enemy::move(float timeStep)
{
    this->y += speedY * timeStep;
}

void Enemy::destroy()
{
    SDL_DestroyTexture(this->texture);
    this->~Enemy();
}