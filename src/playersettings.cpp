#include "playersettings.h"

PlayerSettings::~PlayerSettings()
{
    this->name = this->name.empty();
    this->level = 0;
    this->highscore = 0;
}

void PlayerSettings::createPlayer(string playerName)
{
    this->name = name;
    this->level = 0;
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

void PlayerSettings::increaseHighscore(int amount)
{
    this->highscore += amount;
}

int PlayerSettings::getHighscore()
{
    return this->highscore;
}

void PlayerSettings::reset()
{
    this->highscore = 0;
    this->level = 0;
}
