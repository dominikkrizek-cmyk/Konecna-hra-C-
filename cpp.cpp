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

        showPlayer(p);

        cout << "\nSchopnosti:\n";
        for (int i = 0; i < p.abilities.size(); i++) {
            cout << i + 1 << ") " << p.abilities[i].name;

            if (p.abilities[i].heal) {
                cout << " - leci " << p.abilities[i].damage;
            } else if (p.abilities[i].hitAll) {
                cout << " - poskozeni vsem nepriteli " << p.abilities[i].damage;
            } else {
                cout << " - poskozeni " << p.abilities[i].damage;
            }

            cout << ", cena many: " << p.abilities[i].cost << endl;
        }

        cout << "\nChces tuto classu potvrdit?\n";
        cout << "1) Ano\n";
        cout << "2) Ne, vybrat jinou\n";
        cout << "Volba: ";

        int confirm = getChoice(1, 2);

        if (confirm == 1) {
            return p;
        }
    }
}

void levelUp(Player& p) {
    int requiredXp = p.level * 25;

    while (p.xp >= requiredXp) {
        p.xp -= requiredXp;
        p.level++;

        int oldHp = p.maxHp;
        int oldMana = p.maxMana;
        int oldAttack = p.attack;

        p.maxHp += 5;
        p.maxMana += 3;
        p.attack += 1;
        p.hp = p.maxHp;
        p.mana = p.maxMana;

        cout << "\nNOVY LEVEL POSTAVY!\n";
        cout << "Max zivoty: " << oldHp << " => " << p.maxHp << endl;
        cout << "Max mana: " << oldMana << " => " << p.maxMana << endl;
        cout << "Utok: " << oldAttack << " => " << p.attack << endl;

        requiredXp = p.level * 25;
    }
}

bool enemiesAlive(const vector<Enemy>& enemies) {
    for (const Enemy& e : enemies) {
        if (e.hp > 0) return true;
    }
    return false;
}

void showEnemies(const vector<Enemy>& enemies) {
    cout << "\nNepratele:\n";
    for (int i = 0; i < enemies.size(); i++) {
        cout << i + 1 << ") " << enemies[i].name
             << " HP: " << enemies[i].hp << "/" << enemies[i].maxHp;

        if (enemies[i].hp <= 0) cout << " [MRTVY]";
        cout << endl;
    }
}

void monsterShout(const Enemy& e) {
    vector<string> shouts = {
        "Rrrr! Rozdrtim te!",
        "Tvoje zlato bude moje!",
        "Dneska nikam neprojdes!",
        "Priprav se na bolest!",
        "Tady tvoje cesta konci!"
    };

    cout << e.name << ": \"" << shouts[randomNumber(0, shouts.size() - 1)] << "\"\n";
}

void staticoreMechanic(Player& p, Enemy& staticore, bool playerMissed) {
    if (playerMissed && staticore.hp > 0) {
        staticore.hp += 5;
        if (staticore.hp > staticore.maxHp) staticore.hp = staticore.maxHp;

        staticore.attack += 1;

        cout << "\nStaticore se dobiji statickou energii!\n";
        cout << "Ziskal +5 HP a +1 silu utoku.\n";
    }
}

bool battle(Player& p, vector<Enemy> enemies) {
    bool bossBattle = false;
    bool staticoreBattle = false;

    for (Enemy& e : enemies) {
        if (e.miniBoss || e.mainBoss) bossBattle = true;
        if (e.name == "Staticore") staticoreBattle = true;
    }

    cout << "\n=====================================\n";
    cout << "ZACINA SOUBOJ!\n";
    cout << "=====================================\n";

    bool playerTurn = !bossBattle;

    while (p.hp > 0 && enemiesAlive(enemies)) {
        showPlayer(p);
        showEnemies(enemies);

        if (playerTurn) {
            bool playerMissed = false;

            if (p.paralyzed) {
                cout << "\nJsi paralyzovan Staticorem!\n";

                if (randomNumber(1, 100) <= 50) {
                    cout << "Paralyza zpusobila, ze jsi minul svuj tah!\n";
                    playerMissed = true;
                    p.paralyzed = false;

                    if (staticoreBattle) {
                        for (Enemy& e : enemies) {
                            if (e.name == "Staticore") {
                                staticoreMechanic(p, e, true);
                            }
                        }
                    }

                    playerTurn = false;
                    continue;
                } else {
                    cout << "Paralyzu jsi prekonal!\n";
                    p.paralyzed = false;
                }
            }

            cout << "\nTvuj tah:\n";
            for (int i = 0; i < p.abilities.size(); i++) {
                cout << i + 1 << ") " << p.abilities[i].name
                     << " | cena: " << p.abilities[i].cost << endl;
            }

            cout << "Volba: ";
            int choice = getChoice(1, p.abilities.size());
            Ability ability = p.abilities[choice - 1];

            if (p.mana < ability.cost) {
                cout << "Nemas dost many/energie!\n";
                continue;
            }

            p.mana -= ability.cost;

            if (ability.heal) {
                int oldHp = p.hp;
                p.hp += ability.damage;
                if (p.hp > p.maxHp) p.hp = p.maxHp;

                cout << "Lecis se: " << oldHp << " => " << p.hp << endl;
            } else if (ability.hitAll) {
                for (Enemy& e : enemies) {
                    if (e.hp > 0) {
                        e.hp -= ability.damage;
                        if (e.hp < 0) e.hp = 0;
                        cout << e.name << " dostal " << ability.damage << " poskozeni.\n";
                    }
                }
            } else {
                cout << "Vyber cil: ";
                int target = getChoice(1, enemies.size()) - 1;

                if (enemies[target].hp <= 0) {
                    cout << "Tento nepritel uz je mrtvy.\n";
                    continue;
                }

                int dmg = ability.damage + p.attack;
                enemies[target].hp -= dmg;
                if (enemies[target].hp < 0) enemies[target].hp = 0;

                cout << enemies[target].name << " dostal " << dmg << " poskozeni.\n";
            }

            playerTurn = false;
        } else {
            cout << "\nTah nepratel:\n";

            for (Enemy& e : enemies) {
                if (e.hp <= 0) continue;

                monsterShout(e);

                int dmg = e.attack;
                p.hp -= dmg;
                if (p.hp < 0) p.hp = 0;

                cout << e.name << " utoci za " << dmg << " poskozeni.\n";

                if (e.name == "Staticore") {
                    if (randomNumber(1, 100) <= 30) {
                        p.paralyzed = true;
                        cout << "Staticore te zasahl statickou energii! Mas paralyzu.\n";
                    }
                }

                if (p.hp <= 0) {
                    break;
                }
            }

            playerTurn = true;
        }
    }

    if (p.hp <= 0) {
        cout << "\nProhral jsi. Tvoje cesta konci.\n";
        return false;
    }

    int totalXp = 0;
    int totalGold = 0;
    bool killedStaticore = false;

    for (Enemy& e : enemies) {
        totalXp += e.xpReward;

        if (e.mainBoss) {
            killedStaticore = true;
        }

        if (e.miniBoss) {
            totalGold += e.goldReward;
        } else if (!e.mainBoss) {
            if (randomNumber(1, 100) <= 50) {
                totalGold += e.goldReward;
            }
        }
    }

    if (killedStaticore) {
        cout << "\nStaticore byl znicen!\n";
        cout << "Pri zniceni exploduje za 15 poskozeni!\n";

        p.hp -= 15;
        if (p.hp < 0) p.hp = 0;

        if (p.hp <= 0) {
            cout << "Vyhral jsi, ale exploze te zabila. Hra konci.\n";
            return false;
        }

        cout << "Prezils explozi Staticoru!\n";
        cout << "\nGRATULACE! PORAZIL JSI HLAVNIHO BOSSE A VYHRAL JSI HRU!\n";
        return false;
    }

    p.xp += totalXp;
    p.gold += totalGold;

    cout << "\nSouboj vyhran!\n";
    cout << "Ziskavas XP: " << totalXp << endl;
    cout << "Ziskavas zlato: " << totalGold << endl;

    levelUp(p);

    return true;
}

void village(Player& p, int villageNumber) {
    cout << "\n=====================================\n";
    cout << "VESNICE " << villageNumber << endl;
    cout << "=====================================\n";

    bool stay = true;

    while (stay) {
        showPlayer(p);

        cout << "\nCo chces udelat?\n";
        cout << "1) Doplnit zivoty - 8 zlata\n";
        cout << "2) Vylepsit max zivoty +5 - 15 zlata\n";
        cout << "3) Vylepsit max manu +4 - 15 zlata\n";
        cout << "4) Vylepsit utok +1 - 20 zlata\n";
        cout << "5) Odejit z vesnice\n";
        cout << "Volba: ";

        int choice = getChoice(1, 5);

        if (choice == 1) {
            if (p.gold >= 8) {
                p.gold -= 8;
                p.hp = p.maxHp;
                cout << "Zivoty doplneny.\n";
            } else {
                cout << "Nemas dost zlata.\n";
            }
        } else if (choice == 2) {
            if (p.gold >= 15) {
                p.gold -= 15;
                p.maxHp += 5;
                p.hp = p.maxHp;
                cout << "Max zivoty vylepseny.\n";
            } else {
                cout << "Nemas dost zlata.\n";
            }
        } else if (choice == 3) {
            if (p.gold >= 15) {
                p.gold -= 15;
                p.maxMana += 4;
                p.mana = p.maxMana;
                cout << "Max mana vylepsena.\n";
            } else {
                cout << "Nemas dost zlata.\n";
            }
        } else if (choice == 4) {
            if (p.gold >= 20) {
                p.gold -= 20;
                p.attack += 1;
                cout << "Utok vylepsen.\n";
            } else {
                cout << "Nemas dost zlata.\n";
            }
        } else {
            stay = false;
        }
    }
}
