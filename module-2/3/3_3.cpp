#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

struct edge {
  int val;
  bool is_left;
  edge() : val(0), is_left(0) {}
};

struct point {
  int x, y;
};


void input_points(vector<point> &in, size_t N) {
  int data_x, data_y;
  point pnt;
  for(int i = 0; i < N; ++i) {
    cin >> data_x >> data_y;
    pnt.x = data_x;
    pnt.y = data_y;
    in.push_back(pnt);
  }
}

void create_output(edge *out, vector<point> in, size_t N) {
  for(int i = 0; i < N; ++i) {
    out[2 * i].val = in[i].x;
    out[2 * i].is_left = 0;

    out[2 * i + 1].val = in[i].y;
    out[2 * i + 1].is_left = 1;
  }
}

int get_result(edge *A, size_t count) {
  int result = 0;
  int flag = 0;
  for(int i = 0; i < count * 2; ++i) {
    if(flag && i){
      int buf = A[i].val;
      int buf1 = A[i - 1].val;
      result = result + buf - buf1;
    }
    if(A[i].is_left)
      flag ++;
    else
      flag --;
  }
  return result;
}

void merge(edge *A, int left, int mid, int right) {
  int first = left;
  int second = mid + 1;
  int write = 0;
  edge *tmp = new edge[right - left + 1];
  while(first <= mid && second <= right){
    if(A[first].val < A[second].val)
      tmp[write++] = A[first++];
    else
      tmp[write++] = A[second++];
  }

  while(second < right + 1)
    tmp[write++] = A[second++];
  while(first < mid + 1)
    tmp[write++] = A[first++];

  for(write = 0; write < right - left + 1; ++write)
    A[left + write] = tmp[write];
}

void merge_sort(edge *A, int left, int right) {
  int mid;
  if(left < right){
    mid = (left + right) / 2.0;

    merge_sort(A, left, mid);
    merge_sort(A, mid + 1, right);
    merge(A, left, mid, right);
  }
}

int main()
{
  vector<point> in;
  edge *out;

  int N;
  cin >> N;

  if (!(out = (edge*)malloc(2 * N * sizeof(edge)))) {
    return -1;
  }

  input_points(in, N);
  create_output(out, in, N);

  merge_sort(out, 0, N * 2);
  out++;

  cout << get_result(out, N);

  return 0;
}