#include <iostream>
using namespace std;

// example for making game situation

int main() {
bool hungry = true;
bool tired;
bool bloodlost = false;
bool injured = false;

cout << (injured ? "Kamu terluka, hati-hati!" : "Kamu sehat-sehat saja!") << endl;
// untuk situasi dimana karakter mu sedang terluka atau tidak
// replacement of if else statement (pengganti if else statement)
// kamu bisa gunakan

cout << "Apakah kamu capek? ";
cin >> tired;
tired = (tired == 1); // convert input to boolean

if (tired) {
    cout << "Kamu capek, istirahat dulu ya!" << endl;
} else {
    cout << "Kamu tidak capek, lanjutkan perjalananmu!" << endl;
}

return 0;
}
/* 
**************** contoh situasi dimana karakter mu sedang capek atau tidak ****************
*********************** kamu bisa gunakan if else statement ***********************
***********************boolean tidak bisa dimasukkan dalam switch case****************
**************** karena switch case hanya menerima integer, char, atau enum****************
 ************************jadi kamu harus gunakan if else statement****************
 *****************untuk situasi dimana karakter mu sedang terluka atau tidak ****************
 */

