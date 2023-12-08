#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

struct Boss {
	int HP;
	int Damage;
	int Armor;
};

struct Weapon {
	string Name;
	int Cost;
	int Damage;
	int ArmorValue;
};
struct Armor {
	string Name;
	int Cost;
	int Damage;
	int ArmorValue;
};
struct Ring {
	string Name;
	int Cost;
	int Damage;
	int ArmorValue;
};

vector<struct Weapon> Weapons;
vector<struct Armor> Armors;
vector<struct Ring> Rings;

struct Outfit {
	int Cost = 0;
	string Weapon;
	string Armor;
	string Ring;
	string Ring2;
} cheapestOutfit, expensiveOutfit;

vector<string> lines;
string line;

void readFile(string filename) {
	ifstream myFile(filename);

	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			lines.push_back(line);
		}
		myFile.close();
	}
	else
	{
		cout << "Unable to open file";
	}
}

void setUpShop() {
	readFile("shop.txt");
	string data = "Dagger        8     4       0";
	regex rule(R"((\w+)\s+(\w+)\s+(\w+)\s+(\w+))");
	smatch match;
	struct Weapon Weapon;
	struct Armor Armor;
	struct Ring Ring;

	for (int i = 0; i < 6; i++) {
		if (regex_match(lines[i], match, rule)) {
			
			Weapon.Name = match[1];
			Weapon.Cost = stoi(match[2], NULL, 10);
			Weapon.Damage = stoi(match[3], NULL, 10);
			Weapon.ArmorValue = stoi(match[4], NULL, 10);
			Weapons.push_back(Weapon);
		}
	}

	for (int i = 7; i < 14; i++) {
		if (regex_match(lines[i], match, rule)) {
			struct Armor Armor;
			Armor.Name = match[1];
			Armor.Cost = stoi(match[2], NULL, 10);
			Armor.Damage = stoi(match[3], NULL, 10);
			Armor.ArmorValue = stoi(match[4], NULL, 10);
			Armors.push_back(Armor);
		}
	}
	Armor.Name = "None", Armor.Cost = 0, Armor.Damage = 0; Armor.ArmorValue = 0;
	Armors.insert(Armors.begin(), Armor);

	for (int i = 14; i < 21; i++) {
		if (regex_match(lines[i], match, rule)) {
			struct Ring Ring;
			Ring.Name = match[1];
			Ring.Cost = stoi(match[2], NULL, 10);
			Ring.Damage = stoi(match[3], NULL, 10);
			Ring.ArmorValue = stoi(match[4], NULL, 10);
			Rings.push_back(Ring);
		}
	}
	Ring.Name = "None", Ring.Cost = 0, Ring.Damage = 0; Ring.ArmorValue = 0;
	Rings.insert(Rings.begin(), Ring);
}

void simBattle(Boss enemy, Weapon weapon, Armor armor, Ring ring, Ring ring2) {
	int playerHealth = 100;
	int playerDamage = weapon.Damage + armor.Damage + ring.Damage + ring2.Damage;
	int playerArmor = weapon.ArmorValue + armor.ArmorValue + ring.ArmorValue + ring2.ArmorValue;
	int GoldSpent = weapon.Cost + armor.Cost + ring.Cost + ring2.Cost;
	if (weapon.Name == "Greataxe") {
		int m = 2;
	}

	while (playerHealth > 0 && enemy.HP > 0) {
		enemy.HP = (playerDamage - enemy.Armor) > 0 ? enemy.HP - (playerDamage - enemy.Armor) : enemy.HP - 1;
		if (enemy.HP > 0) playerHealth = (enemy.Damage - playerArmor) > 0 ? playerHealth - (enemy.Damage - playerArmor) : playerHealth - 1;

	}

	if(enemy.HP <= 0) {
		if (GoldSpent < cheapestOutfit.Cost) {
			cheapestOutfit.Cost = GoldSpent;
			cheapestOutfit.Weapon = weapon.Name;
			cheapestOutfit.Armor = armor.Name;
			cheapestOutfit.Ring = ring.Name;
			cheapestOutfit.Ring2 = ring2.Name;
		}
	}

	if (playerHealth <= 0) {
		if (GoldSpent > expensiveOutfit.Cost) {
			expensiveOutfit.Cost = GoldSpent;
			expensiveOutfit.Weapon = weapon.Name;
			expensiveOutfit.Armor = armor.Name;
			expensiveOutfit.Ring = ring.Name;
			expensiveOutfit.Ring2 = ring2.Name;
		}
	}
}


int main() {
	setUpShop();
	Boss Boss = { 109, 8, 2 };
	cheapestOutfit.Cost = 150;
	expensiveOutfit.Cost = 0;

	for (int w = 0; w < Weapons.size(); w++) {
		for (int a = 0; a < Armors.size(); a++) {
			for (int r = 0; r < Rings.size(); r++) {
				for (int r2 = 0; r2 < Rings.size(); r2++) {
					if (r != r2 || (r == r2 && r == 0)) simBattle(Boss, Weapons[w], Armors[a], Rings[r], Rings[r2]);
				}
			}
		}
	}
	cout << "The Cheapest Outfit (to beat the boss) is: " << cheapestOutfit.Weapon << ", " << cheapestOutfit.Armor << ", " << cheapestOutfit.Ring << ", " << cheapestOutfit.Ring2 << endl;
	cout << "At a Cost of: " << cheapestOutfit.Cost << endl;

	cout << "The Most Expensive Outfit (to still lose) is: " << expensiveOutfit.Weapon << ", " << expensiveOutfit.Armor << ", " << expensiveOutfit.Ring << ", " << expensiveOutfit.Ring2 << endl;
	cout << "At a Cost of: " << expensiveOutfit.Cost << endl;

}