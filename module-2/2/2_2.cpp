#include <iostream>
#include <stdio.h>

using namespace std;

struct point {
    int x, y;
};

bool less_point(point lhs, point rhs) {
    if (lhs.x == rhs.x)
        return lhs.y < rhs.y;
    return lhs.x < rhs.x;
}

void input_point(point *el) {
    scanf("%d", &el->x);
    scanf("%d", &el->y);
}

void print(point *polyline, int n) {
    for (int i = 0; i < n; ++i) {
        cout << polyline[i].x << " " << polyline[i].y << endl;
    }
}

void heap_make(point *arr, int n) {
    for (int i = n/2; i >= 1; --i) {
        for (int j = i; j <= n/2;) {
            int k = 2*j;
            if (k+1 <= n && less_point(arr[k], arr[k+1])) ++k;
            if (less_point(arr[j], arr[k])) {
                swap(arr[k], arr[j]);
                j = k;
            }
            else
                break;
        }
    }
}

void heap_pop(point *arr, int n) {
    swap(arr[n], arr[1]);
    for (int i = 1; 2*i < n;) {
        i *= 2;
        if ( i+1 < n && less_point(arr[i], arr[i+1])) {
            i += 1;
        }
        if (less_point(arr[i/2], arr[i])) {
            swap(arr[i/2], arr[i]);
        }
    }
}

void heap_sort(point *polyline, int n) {
    heap_make(polyline - 1, n);
    for(int i = 0; i < n; ++i){
        heap_pop(polyline - 1, n - i);
    }

    print(polyline, n);
}

int main()
{
    int N;
    cin >> N;
    point polyline[N];
    for (int i = 0; i < N; ++i)
        input_point(&polyline[i]);

    heap_sort(polyline, N);
    return 0;
}