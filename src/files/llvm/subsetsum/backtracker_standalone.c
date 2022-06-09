#include <stdio.h>
#include <stdlib.h>
#include <time.h>

short *flag;
int N,K,correspond=0;
unsigned int *check,X=0;
clock_t t1,t2;

void init(){
	int i,j;
	
	printf("N=");
	scanf("%d",&N);
	
	check=malloc(sizeof(unsigned int)*(N+1));
	//pritf("RAND_MAX=%d",RAND_MAX);
	srand((unsigned)time(NULL));
	//printf("\n///check list///\n");
	for(i=1;i<=N;i++){
		check[i]=rand()%1000000+1;
		//printf("%ldyen ",check[i]);
	}
	//printf("\n");
	
	K=rand()%N+1;
	flag=malloc(sizeof(short)*(N+1));
	for(i=1;i<=N;i++)flag[i]=0; //flagã ®åˆ æœŸåŒ–
	i=0;
	while(i<=K){
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
	do{
		while(check[j]>v) j++;
		while(v>check[k]) k--;
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
		t2=clock();
		double record=(double) (t2-t1)/CLOCKS_PER_SEC;
		
		//çµ æžœã Šã‚ˆã ³å‡¦ç †æ™‚é–“ã ®å‡ºåŠ›
		printf("\nAnswer : ");
		for(k=1;k<=N+1;k++){
			if(flag[k]==1){
				if(t==0) t=1;
				else if(t==1) printf("+");
				printf("%d",check[k]);
			}
		}
		printf("\n\nThinking time : %f sec . \n",record);
		if(record<=60) printf("Triumph!\n");
		else printf("Failure...\n");
		return;
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

int main(){
	int i;
		
	init();
	t1=clock();
	for(i=1;i<=N;i++)flag[i]=0; //flagã ®åˆ æœŸåŒ–
	quicksort(1,N);
	func(0,0);
	
	return 0;	
}
