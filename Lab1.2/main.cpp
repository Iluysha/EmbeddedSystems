#include "stdafx.h"
#include "header.h"
#include <string>
#include <cmath>
#include <sstream>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

int n = 10;
int w = 1500;
int N = 64;

int *arrA = new int[n];
int *arrQ = new int[n];
float M1, M2;

float myFunc1(float t) {
	float res = 0;
	for (int i = 0; i < n; i++) {
		res += arrA[i] * sin(w / n * (i + 1) * t + arrQ[i]);
	}
	return res;
}

float myFunc2(float t) {
	float res = 0;
	for (int i = n/2; i > 0; i--) {
		res += arrA[i] * sin(w / n / 2 * (i + 1) * t + arrQ[i]);
	}
	return res;
}

float Correlation(float t, float myFunc(float t)) {
	float res = 0;
	for (int i = 0; i <= N / 2; i++) {
		res += (myFunc(t) - M1) * (myFunc(t + i) - M1);
	}
	return res;
}

float Correlation(float t, float myFunc1(float t), float myFunc2(float t)) {
	float res = 0;
	for (int i = 0; i <= N / 2; i++) {
		res += (myFunc1(t) - M1) * (myFunc2(t + i) - M2);
	}
	return res;
}

void print(HDC hdc, PAINTSTRUCT ps) {
	for (int i = 0; i < n; i++) {
		arrA[i] = (rand() % 2 + 1);
		arrQ[i] = (rand() % 10);
	}

	MoveToEx(hdc, 50, 200, NULL);
	LineTo(hdc, 650, 200);

	MoveToEx(hdc, 700, 200, NULL);
	LineTo(hdc, 1300, 200);

	MoveToEx(hdc, 50, 520, NULL);
	LineTo(hdc, 650, 520);

	MoveToEx(hdc, 700, 520, NULL);
	LineTo(hdc, 1300, 520);

	MoveToEx(hdc, 100, 50, NULL);
	LineTo(hdc, 100, 340);

	MoveToEx(hdc, 750, 50, NULL);
	LineTo(hdc, 750, 340);

	MoveToEx(hdc, 100, 380, NULL);
	LineTo(hdc, 100, 650);

	MoveToEx(hdc, 750, 380, NULL);
	LineTo(hdc, 750, 650);

	TextOut(hdc, 105, 55, "x", 1);
	TextOut(hdc, 640, 205, "t", 1);
	TextOut(hdc, 80, 95, "10", 2);
	TextOut(hdc, 755, 55, "y", 1);
	TextOut(hdc, 1290, 205, "t", 1);
	TextOut(hdc, 730, 95, "10", 2);
	TextOut(hdc, 105, 385, "R(x,x)", 6);
	TextOut(hdc, 640, 525, "t", 1);
	TextOut(hdc, 755, 385, "R(x,y)", 6);
	TextOut(hdc, 1290, 525, "t", 1);

	
	for (int i = 0; i < N; i+=10) {
		std::stringstream s1;
		s1 << i;
		TextOut(hdc, 105 + 8 * i, 205, (s1.str()).c_str(), (s1.str()).size());
		TextOut(hdc, 755 + 8 * i, 205, (s1.str()).c_str(), (s1.str()).size());
	}

	for (int i = 0; i < N; i++) {
		M1 += myFunc1(i + 1);
		M2 += myFunc2(i + 1);
	}
	M1 /= N;
	M2 /= N;

	for (int i = 0; i < N; i++) {
		MoveToEx(hdc, 100 + 8 * i, 200 - 10 * myFunc1(i), NULL);
		LineTo(hdc, 100 + 8 * (i + 1), 200 - 10 * myFunc1(i + 1));
	}

	for (int i = 0; i < N; i++) {
		MoveToEx(hdc, 750 + 8 * i, 200 - 10 * myFunc2(i), NULL);
		LineTo(hdc, 750 + 8 * (i + 1), 200 - 10 * myFunc2(i + 1));
	}

	for (int i = 0; i < N/2; i++) {
		MoveToEx(hdc, 100 + 16 * i, 520 - Correlation(i, myFunc1)/2, NULL);
		LineTo(hdc, 100 + 16 * (i + 1), 520 - Correlation(i+1, myFunc1)/2);
	}

	for (int i = 0; i < N/2; i++) {
		MoveToEx(hdc, 750 + 16 * i, 520 - Correlation(i, myFunc1, myFunc2), NULL);
		LineTo(hdc, 750 + 16 * (i + 1), 520 - Correlation(i+1, myFunc1, myFunc2));
	}
} 