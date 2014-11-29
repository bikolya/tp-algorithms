#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int partition(vector<int> &arr, int left, int right) {
  if (left != right)
    swap(arr[left + rand() % (right - left)], arr[right]);
  int x = arr[right];

  int i = left - 1;
  for (int j = left; j <= right - 1; ++j) {
    if (arr[j] <= x)
      swap(arr[++i], arr[j]);
  }
  swap(arr[i+1], arr[right]);
  return i + 1;
}

int get_kth(vector<int> &arr, const int kth, int left, int right) {
  srand(time(NULL));
  while(1) {
    int pos = partition(arr, left, right);

    if (pos < kth)
      left = pos + 1;
    else if (pos > kth)
      right = pos - 1;
    else
      return arr[kth];
  }
}

int main() {
  int N, kth;
  cin >> N >> kth;

  vector<int> arr;
  int data;
  for (int i = 0; i < N; ++i) {
    cin >> data;
    arr.push_back(data);
  }

  cout << get_kth(arr, kth, 0, N - 1);

  return 0;
}
