/*
 * PthreadMain.cpp
 *
 *  Created on: 2016/05/08
 *      Author: Hoshino Hitoshi
 */

#include <stdio.h>
#include <pthread.h>

#define NUM_RECTS 1000000
#define NUM_THREADS 4

double gArea = 0.0;
pthread_mutex_t gLock;

void *threadFunction(void *pArg);



/*
 * エントリポイント
 */
int main() {

	pthread_t tHandles[NUM_THREADS];
	int tNum[NUM_THREADS];

	pthread_mutex_init(&gLock,NULL);
	for (int i = 0; i < NUM_THREADS; i++) {
		tNum[i] = i;
		pthread_create(&tHandles[i],NULL,threadFunction,(void *)&tNum[i]);
	}

	for (int j=0;j<NUM_THREADS;j++) {
		pthread_join(tHandles[j],NULL);
	}

	pthread_mutex_destroy(&gLock);
	printf("Completed value of PI: %f¥n",gArea);

}

/*
 * pi近似値計算処理関数
 */
void *theradFunction(void *pArg) {

	int myNum = *((int *)pArg);
	double partialHeight = 0.0,lWidth = 1.0 / NUM_RECTS,x;

	for (int i = myNum; i < NUM_RECTS; i += NUM_THREADS) {
		x = (i + 0.5f) / NUM_RECTS;
		partialHeight += 4.0f / (1.0f + x * x);
	}

	//スレッド排他処理区間
	pthread_mutex_lock(&gLock);
		gArea += partialHeight * lWidth;
	pthread_mutex_lock(&gLock);


}
