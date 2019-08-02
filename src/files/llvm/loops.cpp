#include <stdio.h>

void countDown() {

    int x = 0;

    while (x < 10) {

        ++x;

    }

}

int addFunc(int a, int b) {

    return a + b;

}

int main() {

    printf("5 + 2 = %i\n", addFunc(5, 2));
    printf("1 + 8 = %i\n", addFunc(1, 8));
    printf("3 + 3 = %i\n", addFunc(3, 3));
    countDown();

    return 0;

}