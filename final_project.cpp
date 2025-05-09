#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct Character {
    string name;
    int hp, stamina, attack, defense;
};

void initializePlayer(Character &player) {
    player = {"Ashen Knight", 100, 50, 25, 15};
}

void displayIntro() {
    cout << "You enter the arena. Vermillion, Blade of the Crimson Pact awaits.\n";
    cout << "Prepare for a deadly swordfight!\n";
}

int calculateDamage(int attack, int defense) {
    int damage = attack - defense;
    return (damage > 0) ? damage : 1;
}

void block(Character &player) {
    int blockAmount = rand() % 10 + 5;
    player.defense += blockAmount;
    cout << player.name << " braces for impact, increasing defense by " << blockAmount << "!\n";
}

void playerTurn(Character &player, Character &boss) {
    int choice;
    cout << "\n1. Light Attack\n2. Heavy Attack\n3. Block\n> ";
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice. Try again: ";
        cin >> choice;
    }

    int damage = 0;
    if (choice == 1) {
        damage = calculateDamage(player.attack, boss.defense);
        boss.hp -= damage;
        cout << "You strike with Light Attack, dealing " << damage << " damage.\n";
    } else if (choice == 2) {
        if (player.stamina >= 10) {
            damage = calculateDamage(player.attack + 10, boss.defense);
            player.stamina -= 10;
            boss.hp -= damage;
            cout << "You strike with Heavy Attack, dealing " << damage << " damage.\n";
        } else {
            cout << "Not enough stamina for Heavy Attack!\n";
        }
    } else if (choice == 3) {
        block(player);
    }
}

void bossTurn(Character &player, Character &boss) {
    int move = rand() % 3;
    int damage = 0;
    if (move == 0) {
        damage = calculateDamage(boss.attack, player.defense);
        player.hp -= damage;
        cout << boss.name << " strikes! You take " << damage << " damage.\n";
    } else if (move == 1) {
        damage = calculateDamage(boss.attack + 5, player.defense);
        player.hp -= damage;
        cout << boss.name << " strikes with a Heavy Attack! You take " << damage << " damage.\n";
    } else {
        block(boss);
        cout << boss.name << " braces for your next attack, increasing defense.\n";
    }
}

void battleLoop(Character &player, Character &boss) {
    srand(time(0));
    while (player.hp > 0 && boss.hp > 0) {
        cout << "\nPlayer HP: " << player.hp << " | Stamina: " << player.stamina << "\n";
        cout << "Boss HP: " << boss.hp << "\n";
        playerTurn(player, boss);
        if (boss.hp <= 0) break;
        bossTurn(player, boss);
    }
}

void endGame(const Character &player, const Character &boss) {
    if (player.hp > 0) {
        cout << "\nYou defeated " << boss.name << "! Victory is yours.\n";
    } else {
        cout << "\nYou were defeated by " << boss.name << ".\n";
    }
}

int main() {
    Character player, boss = {"Vermillion, Blade of the Crimson Pact", 200, 50, 35, 20};
    
    initializePlayer(player);
    displayIntro();
    battleLoop(player, boss);
    endGame(player, boss);
    
    return 0;
}
