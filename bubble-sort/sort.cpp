#include <iostream>
#include <utility>

void bubbleSort(int* tab, int n);
void printArray(int* tab, int n);

int main() {
    int tab[] = { 10, 12, 0, 1, 3, 18, 21, 6};
    int n = sizeof(tab) / sizeof(int);

    std::cout << "Before sort:\n";
    printArray(tab, n);

    bubbleSort(tab, n);

    std::cout << "After sort:\n";
    printArray(tab, n);
    return 0;
}

void bubbleSort(int* tab, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (tab[j] > tab[j + 1]) {
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
                // std::swap(tab[j], tab[j + 1]);
            }
        }
    }
}

void printArray(int* tab, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}
