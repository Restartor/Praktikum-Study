#include <iostream>

using namespace std;

int main(){

    const int size = 99;
     string foods[size];
     int delay[] = {60, 20, 30, 10};
    

    fill(foods, foods + (size/3), "pizza");
    fill(foods + (size/3), foods + (size/3)*2, "ambatukammmmmmmmmmm");
    fill(foods + (size/3)*2, foods + size, "CROOOOOOOOOOOOTZ");


    for (string food : foods)
    {
        cout << food << '\n';
    }
    





    return 0;
}