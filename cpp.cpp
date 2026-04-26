#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

struct Ability {
    string name;
    int damage;
    int cost;
    bool hitAll;
    bool heal;
};

struct Player {
    string className;
    int maxHp;
    int hp;
    int maxMana;
    int mana;
    int gold;
    int level;
    int xp;
    int attack;
    vector<Ability> abilities;
    bool paralyzed;
};

struct Enemy {
    string name;
    int hp;
    int maxHp;
    int attack;
    int xpReward;
    int goldReward;
    bool miniBoss;
    bool mainBoss;
};

int randomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}
