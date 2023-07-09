#include "enemy.h"

Enemy::~Enemy()
{
    this->x = NULL;
    this->y = NULL;
    this->w = NULL;
    this->h = NULL;
}

void Enemy::destroy()
{
    SDL_DestroyTexture(this->texture);
    this->~Enemy();
}