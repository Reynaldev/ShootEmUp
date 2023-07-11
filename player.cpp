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

void Player::input(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            this->speedX = -200.0f;
            break;
        case SDLK_RIGHT:
            this->speedX = 200.0f;
            break;
        case SDLK_UP:
            this->isShoot = true;
            break;
        default:
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            this->speedX = 0;
            break;
        case SDLK_RIGHT:
            this->speedX = 0;
            break;
        case SDLK_UP:
            this->isShoot = false;
            break;
        default:
            break;
        }
    }
}

void Player::shoot(Bullet& bullet)
{
    if (this->isShoot)
    {
        if (this->ammo <= 0)
            return;
        
        bullet.x = this->x + sqrt(bullet.w);
        bullet.y = this->y;

        this->ammo--;
    }
}

void Player::move(float timeStep)
{
    this->x += this->speedX * timeStep;
}

void Player::destroy()
{
    SDL_DestroyTexture(this->texture);
    this->~Player();
}