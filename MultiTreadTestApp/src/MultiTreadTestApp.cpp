//============================================================================
// Name        : MultiTreadTestApp.cpp
// Author      : Hoshino Hitoshi
// Version     :
// Copyright   : Your copyright notice
// Description : Single Thread Version Application
//============================================================================

#include <iostream>
using namespace std;

#include <time.h>


//PI近似値計算関数(事前定義)
double calcpi();

//近似値計算の閾値
static long num_rects = 10000000;

int main() {

	//処理時間計測用
	clock_t c1,c2;
	c1 = clock();

	//PIの近似値を計算する
	double result = calcpi();

	c2 = clock();

	//処理結果表示
	cout << "Computed pi=" << result << endl;

	//処理時間計算
	cout << "Time = " << (double)(c2-c1)/CLOCKS_PER_SEC << "[s]" << endl;


	return 0;
}

/*
 *　PIの近似値を計算する関数(実装)
 */
double calcpi() {

	int i;
	double mid,height,width;
	double sum = 0.0;
	double area;

	width = 1.0 / (double)num_rects;

	for(i = 0; i < num_rects; i++){
		mid = (i + 0.5) * width;
		height = 4.0 / (1.0 + mid * mid);
		sum += height;
	}

	area = width * sum;

	return area;
}
