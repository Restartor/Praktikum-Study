#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main () {
    srand(time(0)); // Inisialisasi untuk random number generator

    int healthpemain = 100;
    int healthmusuh = 100;
    int healingpotion = 20;
    int isihealingpotion = 3;

    string action;

    while (true) {
        cout << "Health Pemain: " << healthpemain << endl;

        cout << "Health Musuh: " << healthmusuh << endl;

        cout << "Apa yang ingin kamu lakukan? (serang/lari/heal/berlindung): ";
        cin >> action;

        if (action == "serang") {
            int damagepedang = rand() % 15 + 10; 
            healthmusuh -= damagepedang;
            cout << "Kamu menyerang musuh dan memberikan " << damagepedang << " damage!" << endl;

            if (healthmusuh <= 0) {
                cout << "Musuh telah dikalahkan!" << endl;
                break;
            }

            // Musuh menyerang balik
            int damageMusuh = rand() % 20 + 10; // Musuh memberikan damage acak antara 10-30
            healthpemain -= damageMusuh;
            cout << "Musuh menyerang balik dan memberikan " << damageMusuh << " damage!" << endl;

            if (healthpemain <= 0) {
                cout << "Kamu telah dikalahkan oleh musuh!" << endl;
                break;
            }

        } else if (action == "heal") {
            if (isihealingpotion > 0) {
                healthpemain += healingpotion;
                isihealingpotion--;
                cout << "Kamu menggunakan healing potion dan memulihkan " << healingpotion << " health!" << endl;
                cout << "Sisa healing potion: " << isihealingpotion << endl;
                if (healthpemain > 100) healthpemain = 100; // Pastikan health tidak melebihi 100
                    cout  << "Error : Health tidak boleh lebih dari 100!" << endl;
                    isihealingpotion == 0;
            }
            else if (isihealingpotion == 0) {
                cout << "Kamu tidak memiliki healing potion!" << isihealingpotion << endl;

            }

        } else if (action == "berlindung")
            {
                int missChance = rand() % 4; // 0, 1, 2, or 3 (25% chance for 0)
                if (missChance == 0) {
                    cout << "Musuh gagal menyerangmu! Tidak ada damage yang diterima." << endl;
                } else {
                    int damageMusuh = rand() % 7 + 5;
                    healthpemain -= damageMusuh;
                    cout << "Musuh menyerang dan memberikan " << damageMusuh << " damage!" << endl;
                }
            }

        else if (action == "ultimate")
        { int ultimatecharge = rand() % 5; 
         if (ultimatecharge != 0) {
                cout << "Ultimate belum siap! Tunggu beberapa giliran lagi." << endl;
                continue; // Lewati sisa loop dan minta input lagi
            }
            cout << "Kamu menggunakan serangan ultimate!" << endl;
            int damageUltimate = rand() % 60 + 30; // Damage antara 30-90
            cout << "Serangan ultimate memberikan " << damageUltimate << " damage!" << endl;
            healthmusuh -= damageUltimate;
        
         if (healthmusuh <= 0) {
                cout << "Musuh telah dikalahkan!" << endl;
                break;
            }
            
        } else if (action == "lari") {
            cout << "Kamu melarikan diri dari pertarungan!" << endl;
            break;
        }

     else { cout << "Aksi tidak dikenal. Silakan pilih 'serang' atau 'lari'." << endl;}
    }

    return 0;
}
