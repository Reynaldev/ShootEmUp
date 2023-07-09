#include "player.h"

Player::~Player()
{
    this->x = NULL;
    this->y = NULL;
    this->w = NULL;
    this->h = NULL;
    this->speedX = NULL;
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