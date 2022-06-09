#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "backtracker.h"

int iterations = 10;
int Ns[10] = {100,100,1000,1000,10000,10000,100000,100000,1000000,1000000};
//int N = 10000;

int main() {
	double total_time;
	for (int i = 0; i < iterations; i++) {
		//int N = Ns[i];
		double time = backtracker(Ns[i]);
		total_time += time;
		//printf("%d: N = %d, t = %lf\n",i, N, time);
	}
	//printf("Total time for test.c = %lf\n",total_time);
}
