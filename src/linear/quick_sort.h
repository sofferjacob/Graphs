#include <vector>

template<class T>
void partition(std::vector<T>& arr, int low, int high, int res[2]) {
    int comps = 0;
    T pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        comps++;
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) {
            i++; // increment index of smaller element 
            T tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    T temp = arr[high];
    arr[high] = arr[i + 1];
    arr[i + 1] = temp;
    res[0] = i + 1;
    res[1] = comps;
}

template<class T>
int quickSort(std::vector<T>& arr, int low, int high) {
    if (low >= high) return 0;
    int partRes[2] = { -1, -1 };
    partition(arr, low, high, partRes);
    // [low...pi-1]
    int c1 = quickSort(arr, low, partRes[0] - 1);
    // [pi+1...high]
    int c2 = quickSort(arr, partRes[0] + 1, high);
    return partRes[1] + c1 + c2;
}
