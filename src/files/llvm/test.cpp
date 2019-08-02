#include <stdlib.h>
#include <stdio.h>
#include "add.h"

// Testcases
const int n = 3;
int T[n][3] = {
    { 1, 2, 3 },
    { 2, 4, 6 },
    { -5, 6, 1}
};
 
// Driver method
int main() {
    printf("\n");
    for (int i = 0; i < n; i++) {
        int c = add(T[i][0], T[i][1]);
        printf("%d + %d = %d?\n", T[i][0], T[i][1], c);
        if (c != T[i][2]) {
            exit(1);
        }
    }
    printf("\n");
}