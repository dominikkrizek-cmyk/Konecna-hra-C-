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
Player createClass(string name, int hp, int mana, int attack, vector<Ability> abilities) {
    Player p;
    p.className = name;
    p.maxHp = hp;
    p.hp = hp;
    p.maxMana = mana;
    p.mana = mana;
    p.attack = attack;
    p.gold = 20;
    p.level = 1;
    p.xp = 0;
    p.abilities = abilities;
    p.paralyzed = false;
    return p;
}

Player chooseClass() {
    while (true) {
        cout << "\nVyber si classu:\n";
        cout << "1) Paladin\n";
        cout << "2) Lovec\n";
        cout << "3) Mag\n";
        cout << "4) Warlock\n";
        cout << "Volba: ";

        int choice = getChoice(1, 4);
        Player p;

        if (choice == 1) {
            p = createClass("Paladin", 30, 12, 5, {
                {"Uder", 5, 0, false, false},
                {"Uder svetlem", 3, 3, true, false},
                {"Oziveni", 6, 2, false, true}
            });
        } else if (choice == 2) {
            p = createClass("Lovec", 24, 15, 6, {
                {"Vystrel", 6, 0, false, false},
                {"Sipovy dest", 4, 4, true, false},
                {"Prvni pomoc", 5, 3, false, true}
            });
        } else if (choice == 3) {
            p = createClass("Mag", 20, 22, 4, {
                {"Magicka strela", 5, 0, false, false},
                {"Ohniva vlna", 6, 5, true, false},
                {"Leciva magie", 7, 4, false, true}
            });
        } else {
            p = createClass("Warlock", 26, 18, 5, {
                {"Temny uder", 5, 0, false, false},
                {"Prokleti", 5, 4, true, false},
                {"Krvavy ritual", 8, 5, false, true}
            });
        }
