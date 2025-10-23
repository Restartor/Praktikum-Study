def bubble_sort(arr, swapped=False):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j] 
                swapped = True

            print("Langkah ke-", i*n + j + 1, ": ", end=" ")
            for k in range(n):
                print(arr[k], end=" ")
            print()
            if not swapped:
                break
def selection_sort(arr):
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i+1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
                arr[i], arr[min_idx] = arr[min_idx], arr[i]
                return arr
if __name__ == "__main__":
    arr = [64, 34, 25, 12, 22, 90, 100]
    print("Original array:", arr)
    print("Sorted array using bubble sort:", bubble_sort(arr.copy))
    print("Sorted array using selection sort:", selection_sort(arr.copy()))