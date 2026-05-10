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
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getChoice(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;

        if (!cin.fail() && choice >= min && choice <= max) {
            return choice;
        }

        clearInput();
        cout << "Neplatna volba. Zadej cislo " << min << "-" << max << ": ";
    }
}

void showPlayer(const Player& p) {
    cout << "\n=== HRAC ===\n";
    cout << "Classa: " << p.className << endl;
    cout << "Level: " << p.level << endl;
    cout << "XP: " << p.xp << endl;
    cout << "Zivoty: " << p.hp << "/" << p.maxHp << endl;
    cout << "Mana/Energie: " << p.mana << "/" << p.maxMana << endl;
    cout << "Utok: " << p.attack << endl;
    cout << "Zlato: " << p.gold << endl;
}