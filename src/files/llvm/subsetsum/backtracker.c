#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "backtracker.h"

short *flag;
int N,K,correspond=0;
unsigned int *check,X=0;
struct timeval t1,t2, tw;
int counter5;

void init(){
	int i,j;
	
	//printf("N=");
	//scanf("%d",&N);
	
	check=malloc(sizeof(unsigned int)*(N+1));
	//printf("RAND_MAX=%d\n",RAND_MAX);
	srand((unsigned)time(NULL));
	//printf("\n///check list///\n");
	for(i=1;i<=N;i++){
		check[i]=rand()%1000000+1;
		//printf("%ldyen ",check[i]);
	}
	//printf("\n");
	
	K=rand()%N+1;
	//printf("K=%d\n", K);
	//K = N;
	//printf("K = %d\n", K);
	flag=malloc(sizeof(short)*(N+1));
	for(i=1;i<=N;i++)flag[i]=0; 
	i=0;
	int counter1 = 0;
	while(i<=K){
		counter1++;
		//if (counter1 >= 1e9 && ((int)counter1 % (int)1e8) == 0) {
		//	printf("counter1=%d\n", counter1);
		//}
		if (counter1 > 1000000000) {
			//printf("while loop going for too long, exiting with error code 100\n");
			exit(100);
		}
		j=rand()%N+1;
		if(flag[j]==0){
			flag[j]=1;
			X=X+check[j];
			i++;
		}
	}
	//printf("\nX=%ldyen\n",X);
}

void swap(int j,int k){
	unsigned int tmp;
	
	tmp=check[j];
	check[j]=check[k];
	check[k]=tmp;
}

int partition(int left,int right){
	int j=left,k=right;
	unsigned int v;
	
	v=check[(left+right)/2];
	int counter2 = 0;
	int counter3 = 0;
	int counter4 = 0;
	do{
		counter2++;
		/*if (counter2 >= 5e5 && ((int)counter2 % (int)1e5) == 0) {
			printf("counter2=%d\n", counter2);
		}*/
		if (counter2 > 1000000000) {
			//printf("while loop going for too long, exiting with error code 100\n");
			exit(100);
		}
		while(check[j]>v) {
			j++;
			counter3++;
			if (counter3 >= 1e6 && ((int)counter3 % (int)1e5) == 0) {
				//printf("counter3=%d\n", counter3);
			}
			if (counter3 > 1000000000) {
				//printf("while loop going for too long, exiting with error code 100\n");
				exit(100);
			}
		}
		while(v>check[k]) {
			k--;
			counter4++;
			if (counter4 >= 1e6 && ((int)counter4 % (int)1e5) == 0) {
				//printf("counter4=%d\n", counter4);
			}
			if (counter4 > 1000000000) {
				//printf("while loop going for too long, exiting with error code 100\n");
				exit(100);
			}
		}
		swap(j,k);
	}while(check[j]!=check[k]);
	
	return j;
}

void quicksort(int left,int right){
	int j;
	
	if(left<right){
		j=partition(left,right);
		quicksort(left,j-1);
		quicksort(j+1,right);
	}
}

void func(unsigned int sum,int i){
	int j,k,t=0;
	
	if(sum==X){
		correspond=1;
		//t2=clock();
		//double record=(double) (t2-t1)/CLOCKS_PER_SEC;
		
		//printf("\nAnswer : ");
		//for(k=1;k<=N+1;k++){
		//	if(flag[k]==1){
		//		if(t==0) t=1;
		//		else if(t==1) printf("+");
		//		printf("%d",check[k]);
		//	}
		//}
		//printf("\n\nThinking time : %f sec . \n",record);
		return;
	}
	counter5++;
	/*if (counter5 >= 1e9 && ((int)counter5 % (int)1e8) == 0) {
		printf("counter5=%d\n", counter5);
	}*/
	if (counter5 > 1000000000) {
		//printf("while loop going for too long, exiting with error code 100\n");
		exit(100);
	}
	else if(sum<X){
		for(j=i+1;(j<=N)&&(correspond==0);j++){
			flag[j]=1;
			func(sum+check[j],j);
		}
	}
	flag[i]=0;
	return;
}

double backtracker(int n){
	int i;	
    N = n;
	//printf("start init\n");
	init();
	//printf("finished init\n");
	gettimeofday(&t1, NULL);  //added 6/14/2021
	for(i=1;i<=N;i++)flag[i]=0;
	quicksort(1,N);
	func(0,0);

	gettimeofday(&t2, NULL);  //added 6/14/2021
	double record = (t2.tv_sec - t1.tv_sec) * 1e6;
    record = (record + (t2.tv_usec - t1.tv_usec)) * 1e-6;
	//printf("\n\nThinking time : %f sec . \n",record);

	return record;	
}
