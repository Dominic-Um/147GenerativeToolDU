#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum class ItemType {
    Weapon,
    Equipable
};

struct Modifier {
    string name;
    int damageBonus;
    int speedBonus;
};

struct Wildcard {
    string description;
};

struct Item {
    ItemType type;
    string name;
    bool hasWildcard;
    Wildcard wildcard;
    Modifier modifier;
};

// 1 Weak 2 Normal 3 Strong
int modifierStrength = 2;
// In percent
int wildcardChance = 15;
// -100 to 100 corresponding with positive and negative modifiers
int rarityBias = 0;

vector<string> weaponNames = {
    "Sword",
    "Bow",
    "Axe",
    "Dagger",
    "Hammer",
    "Spear",
    "Crossbow",
    "Scythe",
    "Arquebus",
    "Mace"
};
vector<string> equipableNames = {
    "Ring",
    "Amulet",
    "Helmet",
    "Cloak",
    "Boots",
    "Gauntlets",
    "Chestplate",
    "Belt",
    "Mask",
    "Bracelet"
};

vector<Modifier> negativeModifiers = {
    { "Defective", -5, -2 },
    { "Cracked", -3, -1 },
    { "Cursed", -7, -3 },
    { "Rusty", -4, -2 },
    { "Fragile", -6, -4 }
};

vector<Modifier> neutralModifiers = {
    { "", 0, 0 },
    { "Balanced", 1, 0 },
    { "Standard", 0, 1 },
    { "Reliable", 1, 1 }
};

vector<Modifier> positiveModifiers = {
    { "Divine", 5, 2 },
    { "Legendary", 7, 3 },
    { "Blessed", 4, 3 },
    { "Mythic", 8, 4 },
    { "Ancient", 6, 2 }
};

vector<Wildcard> weaponWildcards = {
    { "5% chance to do infinite damage" },
    { "Chance to stun enemy" },
    { "Double damage on critical hit" },
    { "Chance to ignite enemy" },
    { "Lifesteal on hit" }
};

vector<Wildcard> equipableWildcards = {
    { "10% chance to block damage" },
    { "Passive health regeneration" },
    { "Increases movement speed" },
    { "Reflects small damage to attacker" }
};

Modifier pickModifier() {
    int roll = rand() % 100;

// Skew results based on
    roll += rarityBias;

    if (roll < 33) {
        return negativeModifiers[rand() % negativeModifiers.size()];
    }
    else if (roll < 66) {
        return neutralModifiers[rand() % neutralModifiers.size()];
    }
    else {
        return positiveModifiers[rand() % positiveModifiers.size()];
    }
}

Item generateItem() {
    Item item;
// Type selection
    if (weaponNames.empty() && equipableNames.empty()) {
    cout << "Error: No item names available!\n";
    exit(1);
    }
        else if (weaponNames.empty()) {
    item.type = ItemType::Equipable;
    }
        else if (equipableNames.empty()) {
    item.type = ItemType::Weapon;
    }
// Type selection    
    
        else {
    item.type = (rand() % 2 == 0) ? ItemType::Weapon : ItemType::Equipable;
    }

    if (item.type == ItemType::Weapon) {
        item.name = weaponNames[rand() % weaponNames.size()];
    } else {
        item.name = equipableNames[rand() % equipableNames.size()];
    }


    item.modifier = pickModifier();

    item.modifier.damageBonus *= modifierStrength;
    item.modifier.speedBonus *= modifierStrength;

    item.hasWildcard = (rand() % 100) < wildcardChance;

    if (item.hasWildcard) {
        if (item.type == ItemType::Weapon) {
            item.wildcard = weaponWildcards[rand() % weaponWildcards.size()];
        } else {
            item.wildcard = equipableWildcards[rand() % equipableWildcards.size()];
        }
    }

    return item;
}


void printItem(const Item& item) {
    cout << "Item Type: ";
    if (item.type == ItemType::Weapon) cout << "Weapon\n";
    else cout << "Equipable\n";

    cout << item.modifier.name << " " << item.name << "\n";
    cout << "  Damage Bonus: " << item.modifier.damageBonus << "\n";
    cout << "  Speed Bonus: " << item.modifier.speedBonus << "\n";
    
    if (item.hasWildcard) {
        cout << "  Wildcard: " << item.wildcard.description << "\n";
    }

    cout << "-----------------------------\n";
}

// Custom Input
void inputCustomItems(vector<string>& list, const string& typeName) {
    int count;
    cout << "How many custom " << typeName << "s would you like to add? ";
    cin >> count;

    cin.ignore();

    for (int i = 0; i < count; i++) {
        string name;
        cout << "Enter " << typeName << " name #" << i + 1 << ": ";
        getline(cin, name);
        list.push_back(name);
    }
}

int main() {
    srand(time(0));

    char choice;

    cout << "Use default item lists? (y/n): ";
    cin >> choice;

    if (choice == 'n' || choice == 'N') {
        weaponNames.clear();
        equipableNames.clear();

        inputCustomItems(weaponNames, "Weapon");
        inputCustomItems(equipableNames, "Equipable");
    }

    cout << "\nGenerating Items...\n\n";

    for (int i = 0; i < 20; i++) {
        Item item = generateItem();
        printItem(item);
    }

    return 0;
}