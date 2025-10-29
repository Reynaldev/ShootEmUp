#pragma once

#include "main.h"

class PlayerSettings
{
private:
    string name;
    int level;
    int highscore; 
public:
    ~PlayerSettings();

    void createPlayer(string playerName);

    string getName();

    void increaseLevel(int amount);
    int getLevel();

    void increaseHighscore(int amount);
    int getHighscore();

    void reset();
};
