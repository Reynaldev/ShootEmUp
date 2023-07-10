#include "playersettings.h"

PlayerSettings::PlayerSettings(string playerName)
{
    this->name = name;
    this->level = 0;
    this->health = 3;
    this->highscore = 0;
}

PlayerSettings::~PlayerSettings()
{
    this->name = this->name.empty();
    this->level = 0;
    this->health = 0;
    this->highscore = 0;
}

string PlayerSettings::getName()
{
    return this->name;
}

void PlayerSettings::increaseLevel(int amount)
{
    this->level += amount;
}

int PlayerSettings::getLevel()
{
    return this->level;
}

void PlayerSettings::setHealth(int amount)
{
    this->health = amount;
}

int PlayerSettings::getHealth()
{
    return this->health;
}

void PlayerSettings::increaseHighscore(int amount)
{
    this->highscore += amount;
}

int PlayerSettings::getHighscore()
{
    return this->highscore;
}