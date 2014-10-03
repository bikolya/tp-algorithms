#include <stdio.h>

void factorize(int num) {
    int num_tmp = num;

    for (int div = 2; 2 * div < num + 1; ) {
        if (num_tmp % div == 0) {
            printf("%d ", div);
            num_tmp /= div;
        }
        else {
            ++div;
        }
    }
    if (num == num_tmp)
        printf("%d\n", num);
}

int main() {
    int num;
    scanf("%d", &num);
    factorize(num);
    return 0;
}