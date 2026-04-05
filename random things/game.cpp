#include <iostream>


struct karakter
{
    std::string nama;
    int hp;
    int stamina;
    int attack;
    int defense;
    int skill[3];
};


void skillList(karakter &k)
{
    k.skill[1] = k.attack + 10; // Slash
    k.skill[2] = k.defense + 15; // Shield Bash
    k.skill[3] = k.attack + 20; // Power Strike

    

    std::cout << "Skill " << k.nama << ": " << std::endl;
    std::cout << "1. Slash (Attack: " << k.attack + 10 << ", Stamina Cost: 20)" << std::endl;
    std::cout << "2. Shield Bash (Defense: " << k.defense + 15 << ", Stamina Cost: 15)" << std::endl;
    std::cout << "3. Power Strike (Attack: " << k.attack + 20 << ", Stamina Cost: 30)" << std::endl;

    int choice;
    std::cout << "Pilih skill (1-3): ";
    std::cin >> choice;
    switch (choice)
    {    case 1:
        k.attack = k.skill[1];
        k.stamina -= 20;
        break;
    case 2:
        k.defense = k.skill[2];
        k.stamina -= 15;
        break;
    case 3:
        k.attack = k.skill[3];
        k.stamina -= 30;
        break;
    }

}

void attack(karakter &k, karakter &target)
{
    skillList(k);
    int damage = k.attack - target.defense;
    if (damage < 0)
        damage = 0;
    target.hp -= damage;
    std::cout << k.nama << " menyerang " << target.nama << " dengan damage: " << damage << std::endl;
    std::cout << target.nama << " memiliki HP tersisa: " << target.hp << std::endl;


}
void defend(karakter &k)
{
    std::cout << k.nama << " memilih untuk bertahan!" << std::endl;
    k.defense += 10;
    k.stamina -= 10;
    std::cout << k.nama << " meningkatkan defense menjadi: " << k.defense << ", stamina tersisa: " << k.stamina << std::endl;
}

void createCharacter(karakter &k)
{
    std::cout << "Masukkan nama karakter: ";
    std::cin >> k.nama;
    std::cout << "Masukkan hp: ";
    std::cin >> k.hp;
    std::cout << "Masukkan stamina: ";
    std::cin >> k.stamina;
    std::cout << "Masukkan attack: ";
    std::cin >> k.attack;
    std::cout << "Masukkan defense: ";
    std::cin >> k.defense;
}

void displayCharacter(karakter &k)
{
    std::cout << "Nama: " << k.nama << std::endl;
    std::cout << "HP: " << k.hp << std::endl;
    std::cout << "Stamina: " << k.stamina << std::endl;
    std::cout << "Attack: " << k.attack << std::endl;
    std::cout << "Defense: " << k.defense << std::endl;
}

void enemyEncounter(karakter &k)
{
    karakter enemy;
    std::cout << "Anda bertemu dengan musuh!" << std::endl;
    createCharacter(enemy);
    displayCharacter(enemy);
    attack(k, enemy);

}

void prosesgame(karakter &k)
{
    std::cout << "Selamat datang di dunia game!" << std::endl;
    createCharacter(k);
    displayCharacter(k);
    enemyEncounter(k);
}


int main(int argc, char const *argv[])
{
    karakter k;
    prosesgame(k);


    return 0;
}

// game rusak attack tidak jalan, defense tidak jalan, skill tidak jalan, stamina tidak berkurang, hp tidak berkurang, dll