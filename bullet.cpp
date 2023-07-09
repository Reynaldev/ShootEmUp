#include "bullet.h"

Bullet::~Bullet()
{
    this->x = NULL;
    this->y = NULL;
    this->w = NULL;
    this->h = NULL;
    this->speedY = NULL;
}

void Bullet::Move()
{
    this->y += this->speedY;
}

void Bullet::Destroy()
{
    SDL_DestroyTexture(this->texture);
    this->~Bullet();
}