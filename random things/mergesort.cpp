    #include <iostream>
    using namespace std;

    int stepCount = 0;

    void printRange(int arr[], int l, int r) {
        cout << "[";
        for (int i = l; i <= r; ++i) {
            cout << arr[i];
            if (i < r) cout << " ";
        }
        cout << "]";
    }

    void merge(int arr[], int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;

        // array sementara (basic new/delete)
        int* L = new int[n1];
        int* R = new int[n2];

        for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
        for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

        cout << "Langkah " << ++stepCount << " - Merge ";
        printRange(arr, l, m);
        cout << " dan ";
        printRange(arr, m + 1, r);
        cout << " -> ";
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) arr[k++] = L[i++];
            else              arr[k++] = R[j++];
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];

        printRange(arr, l, r);
        cout << "\n";


    }

    void mergeSort(int arr[], int l, int r) {
        if (l >= r) return;
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }

    void printArray(int A[], int n) {
        for (int i = 0; i < n; ++i) cout << A[i] << " ";
        cout << "\n";
    }

    void hasilMERGESORT(int arr[], int n){
        cout << "Array awal: ";
        printArray(arr, n);

        mergeSort(arr, 0, n - 1);

        cout << "Array terurut (ascending): ";
        printArray(arr, n);
    }


void mergeSortDescending(int arr[], int n) {
    stepCount = 0; // reset langkah (akan menampilkan langkah merge ascending)
    cout << "Array awal: ";
    printArray(arr, n);

    // urutkan ascending dulu dengan mergeSort yang sudah ada
    mergeSort(arr, 0, n - 1);

    // balik array jadi descending (tanpa <algorithm>)
    for (int i = 0; i < n / 2; ++i) {
        int tmp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = tmp;
    }

    cout << "Array terurut (descending): ";
    printArray(arr, n);
}

    int main() {
        int n;
        cout << "Masukkan jumlah elemen: ";
        if (!(cin >> n) || n <= 0) {
            cout << "Jumlah elemen tidak valid.\n";
            return 0;
        }

        int* arr = new int[n];

        cout << "Masukkan " << n << " angka (pisahkan dengan spasi): ";
        for (int i = 0; i < n; ++i) cin >> arr[i];

        int pemilihan;
        cout << "Anda ingin mergesort dalam \n" ;
        cout << "1.Ascending 2.Descending : ";
        cin >> pemilihan;

        switch(pemilihan){
            case 1:
                hasilMERGESORT(arr, n);
            break;
            case 2:
                mergeSortDescending(arr, n);
            break;
        }

        return 0;
    }
