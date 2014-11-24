#include <iostream>
#include <vector>

using namespace std;

typedef int* iterator_t;

struct less_t{
  bool operator() (const int &lhs, const int &rhs) const {
    return lhs > rhs;
  }
};

void read_data(vector<int> *arr) {
  int data;
  for (;;) {
    cin >> data;
    if (cin.eof()) break;
    arr -> push_back(data);
  }
}

void print_data(vector<int> arr) {
  for (int i = 0; i < arr.size(); ++i) {
    cout << arr[i] << endl;
  }
}

void bubble_sort(iterator_t arr, size_t size, less_t const &less) {
  for (int i = 0; i < size - 1; ++i) {
    bool was_swapped = 0;
    for (int j = 0; j < size - i - 1; ++j) {
      if (less(*(arr + j), *(arr + j + 1))) {
        was_swapped = true;
        swap(arr[j], arr[j+1]);
      }
    }
    if (!was_swapped) break;
  }
}

int main() {
  vector<int> arr;
  less_t less;
  read_data(&arr);
  bubble_sort(&arr[0], arr.size(), less);
  print_data(arr);
  return 0;
}