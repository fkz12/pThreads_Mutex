// -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 10000
pthread_mutex_t ml = PTHREAD_MUTEX_INITIALIZER;

int shop[5];
int j=0;


void *client() {
	int i, cnt=0, tmp=0, last=0;
	while (cnt!=10000) {
	pthread_mutex_lock(&ml);
	i=rand()%5;
	if (cnt+shop[i]<=N) {
		last=cnt;
		cnt+=shop[i];
		shop[i]=0;
		printf("[customer who had %d]\n+%d in store #[%d] (rest=%d)\nAnd now has %d\n\n",last,cnt-last,i,shop[i],cnt);
	}
	
	else {
		last=cnt;
		tmp=shop[i]-(N-cnt);
		shop[i]=tmp;
		cnt+=(N-cnt);
		printf("[customer who had %d]\n+%d in store #[%d] (rest=%d)\nAnd now has %d\n\n",last,cnt-last,i,shop[i],cnt);

	}

	sleep(2);
	pthread_mutex_unlock(&ml);
	}
	j++;
}

void *adding() {
	int i=0;
	while (j!=3) {
	i=rand()%5;
	shop[i]+=500;	
	for (i=0; i<5; i++)
		printf ("   [%d]   ", shop[i]);
	printf("\n\n");
	sleep(3);
	}
}

int main() {
	
	pthread_t tid[4]; //4 threades
	int i;
	time_t t;
	srand((unsigned) time (&t));
		
	for (i=0; i<5; i++) {
		shop[i]=rand()%(11000-9000+1)+9000; 
		printf ("   [%d]   ", shop[i]);
	}
	printf("\n");
	
		
	for (i=0; i<3; i++)
		pthread_create(&tid[i], NULL, client, NULL);
		pthread_create(&tid[3], NULL, adding, NULL);
			
		

	for (i=0; i<4; i++) 
		pthread_join(tid[i], NULL);

	
	return 0;
}
