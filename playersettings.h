#include "main.h"

class PlayerSettings
{
private:
    string name;
    int level;
    int health;
    int highscore; 
public:
    ~PlayerSettings();

    void createPlayer(string playerName);

    string getName();

    void increaseLevel(int amount);
    int getLevel();

    void setHealth(int amount);
    int getHealth();

    void increaseHighscore(int amount);
    int getHighscore();
};