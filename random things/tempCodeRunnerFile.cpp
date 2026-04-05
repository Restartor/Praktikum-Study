#include <iostream>

using namespace std;

void bubbleSort(int arr[], int n){
    bool swapped;
    for(int i=0; i<n-1; i++){
        swapped = false;
        for(int j=0; j<n-i-1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
            cout << "Langkah " << i+1 << ", " << j+1 << ": ";
            for(int k=0; k<n; k++){
                cout << arr[k] << " ";
            }
            cout << endl;
        }
        if(!swapped){
            break;
        }
    }
}


void selectionSort(int arr[], int n){
    for(int i=0; i<n-1; i++){
        int minIndex = i;
        for(int j=i+1; j<n; j++){
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        swap(arr[i] , arr[minIndex]);

    }

}


int main(){
    int arr[] = {64, 34, 25, 12, 22, 90, 100};
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "Array sebelum diurutkan : ";
    for(int i=0; i<n; i++)
    {cout << arr[i] << " "; }

    cout << "Anda ingin mengurutkan dengan metode apa?(1. Bubble Sort / 2.Selection Sort)\n";
  
    int pilihan;
    cout << "Masukkan anda ingin Sort dengan metode apa: \n";
    cout << "1. Bubble Sort\n" << "2. Selection Sort\n";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            bubbleSort(n, arr);
            cout << "Array setelah diurutkan dengan Bubble Sort:";
            for(int i=0; i<n; i++){
                cout << arr[i] << ' ';
            }
            case 2:
            selectionSort(n, arr);
            cout << "Array setelah diurutkan dengan Selection Sort:";
            for(int i=0; i<n; i++){
                cout << arr[i] << ' ';
            }
            default:
            cout << "Pilihan tidak valid bos.";
    }









    return 0;
}