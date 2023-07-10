#include "player.h"

Player::~Player()
{
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->speedX = 0;
    this->maxAmmo = 0;
    this->ammo = 0;
    
    this->texture = NULL;
}

void Player::move()
{
    this->x += this->speedX;
    this->speedX = 0;
}

void Player::destroy()
{
    SDL_DestroyTexture(this->texture);
    this->~Player();
}