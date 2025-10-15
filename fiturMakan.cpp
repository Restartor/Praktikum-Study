#include <iostream>
#include <string>   

int main() {

    int hunger = 0; // 0 = sangat lapar, 100 = kenyang
    int eggs = 3;
    int bacon = 2;
    int semangka = 1;

    while (true) {
        // Status hunger
        if (hunger == 0) {
            std::cout << "You are very hungry, please eat something!" << std::endl;
        } else if (hunger < 30) {
            std::cout << "You are hungry!" << std::endl;
        } else if (hunger < 70) {
            std::cout << "You are getting full." << std::endl;
        } else if (hunger >= 100) {
            std::cout << "You already full (you cannot eat no more)." << std::endl;
            break;
        }

        // Memilih makanan dan setting makanannya

        std::cout << "Mau makan apa? (telur/bacon/semangka/keluar): ";
        std::string pilihan;
        std::cin >> pilihan;

        if (pilihan == "telur" && eggs > 0 && hunger < 100) { // Cek apakah masih ada telur
            std::cout << "Kamu makan telur." << std::endl;
            eggs--; // Mengurangi jumlah telur
            hunger += 20; // Menambah hunger

            if (hunger > 100) hunger = 100;

        } else if (pilihan == "bacon" && bacon > 0 && hunger < 100) { // Cek apakah masih ada bacon
            std::cout << "Kamu makan bacon." << std::endl;
            bacon--; // Mengurangi jumlah bacon
            hunger += 40; // Menambah hunger

            if (hunger > 100) hunger = 100;
            
        } else if (pilihan == "semangka" && semangka > 0 && hunger < 100){ // Cek apakah masih ada semangka
            std::cout << "kamu makan semangka" << std::endl;
            semangka--; // Mengurangi jumlah semangka
            hunger += 100; // Menambah hunger
            
            if (hunger > 100) hunger = 100; // memastikan hunger tidak lebih dari 100
        }
        else if ((eggs == 0 && pilihan == "telur") || (bacon == 0 && pilihan == "bacon") || (semangka == 0 && pilihan == "semangka")) {
            std::cout << "Makanan tidak tersedia atau habis." << std::endl; // Pesan jika makanan habis atau pilihan tidak valid
        }

        // pilihan keluar dari loop

        else if (pilihan == "keluar") { // Keluar dari loop
            std::cout << "Kamu tidak lapar lagi." << std::endl; // Pesan keluar
            break; // menghancurkan loop
        }

        // Status makanan dan hunger
        std::cout << "Sisa telur: " << eggs << ", sisa bacon: " << bacon << " sisa semangka : "<< semangka << std::endl;
        std::cout << "Hunger: " << hunger << std::endl;
    }
    return 0;
}
