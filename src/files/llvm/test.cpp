#include <stdlib.h>
#include <stdio.h>
#include "math.h"

// Testcases
const int n = 10;
int T[n][3] = {
    { 1, 2, 3 },
    { 2, 4, 6 },
    { -5, 6, 1},
    {21, 18, 39},
    {49, 6, 55},
    {100, 6, 106},
    {3, 4, 7},
    {-7, 5, -2},
    {2, 8, 10},
    {-178, 178, 0}
};
const int m = 10;
int M[n][3] = {
    {3, 4, 12},
    {-7, 5, -35},
    {2, 8, 16},
    {16, 5, 80},
    {40, 2, 80},
    {1, 2, 2},
    {2, 4, 8},
    {-5, 6, -30},
    {21, 18, 378},
    {49, 6, 294}
};
 
// Driver method
int main() {
    //printf("\n");
    for (int i = 0; i < n; i++) {
        int c = add(T[i][0], T[i][1]);
        //printf("%d + %d = %d?\n", T[i][0], T[i][1], c);
        if (c != T[i][2]) {
            exit(1);
        }
    }
    for (int i = 0; i < m; i++) {
        int c = mult(M[i][0], M[i][1]);
        //printf("%d * %d = %d?\n", M[i][0], M[i][1], c);
        if (c != M[i][2]) {
            exit(1);
        }
    }
    //printf("\n");
}