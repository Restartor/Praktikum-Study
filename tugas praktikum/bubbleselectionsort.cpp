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
        if(minIndex != i){swap(arr[minIndex], arr[i]);}
        cout << "Langkah " << (i + 1) << ":\n";
        for (int k = 0; k < n; ++k) cout << arr[k] << ' ';
        cout << '\n';

    }

}



int main(){
    int arr[] = {64, 34, 25, 12, 22, 90, 100};
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << endl;
    cout << "Array sebelum diurutkan : \n";
    for(int i=0; i<n; i++)
    {cout << arr[i] << " "; }

    cout << "Anda ingin mengurutkan dengan metode apa?\n";
  
    int pilihan;
    cout << "Masukkan anda ingin Sort dengan metode apa: \n";
    cout << "1. Bubble Sort\n" << "2. Selection Sort\n";
    cin >> pilihan;

    if(pilihan == 1){
        bubbleSort(arr, n);
         cout << "Array setelah diurutkan dengan buble sort: ";
         for(int i=0; i<n; i++){
            cout << arr[i] << " ";
         }
         cout << "\n";
         cout << "Bubble sort memiliki " << " Langkah maksimal " << (n-1)*(n)/2 << "\n";
         cout << endl;
    }
    else if(pilihan == 2){
        selectionSort(arr, n);
        cout << "Array setelah diurutkan dengan selection sort: ";
        for(int i=0; i<n; i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
        cout << "Selection sort memiliki " << n-1 << " Langkah\n";
        cout << endl;
    }
    else{
        cout << "pilihan tidak valid \n";
        cout << "Silahkan jalankan program kembali \n";
    }

    









    return 0;
}