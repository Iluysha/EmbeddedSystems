#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "header.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int n = 10;
int w = 1500;
int N = 256;

int *arrA = new int[n];
int *arrQ = new int[n];

float myFunc(float t) {
	float res = 0;
	for (int i = 0; i < n; i++) {
		res += arrA[i] * sin(w / n * (i + 1) * t + arrQ[i]);
	}
	return res;
}

float Fourier(float myFunc(float t), float t) {
	float real = 0;
	float irreal = 0;
	for (int i = 0; i < N; i++) {
		real += myFunc(i) * cos(2 * M_PI * i * t / N);
		irreal += myFunc(i) * sin(2 * M_PI * i * t / N);
	}
	return sqrt(pow(real, 2) + pow(irreal, 2));
}

void print(HDC hdc, PAINTSTRUCT ps) {
	for (int i = 0; i < n; i++) {
		arrA[i] = (rand() % 2 + 1);
		arrQ[i] = (rand() % 10);
	}

	MoveToEx(hdc, 200, 25, NULL);
	LineTo(hdc, 200, 350);

	MoveToEx(hdc, 150, 200, NULL);
	LineTo(hdc, 1300, 200);

	MoveToEx(hdc, 200, 380, NULL);
	LineTo(hdc, 200, 650);

	MoveToEx(hdc, 150, 520, NULL);
	LineTo(hdc, 1300, 520);

	TextOut(hdc, 205, 30, "x", 1);
	TextOut(hdc, 1280, 202, "t", 1);
	TextOut(hdc, 205, 390, "F", 1);
	TextOut(hdc, 1280, 522, "t", 1);
	TextOut(hdc, 180, 90, "10", 2);
	TextOut(hdc, 180, 415, "20", 2);

	for (int i = 0; i <= N; i+=20) {
		std::stringstream s;
		s << (float)(i);
		TextOut(hdc, 205 + 4 * i, 202, (s.str()).c_str(), (s.str()).size());
		TextOut(hdc, 205 + 4 * i, 522, (s.str()).c_str(), (s.str()).size());
	}

	for (int i = 0; i <= N; i++) {
		MoveToEx(hdc, 200 + 4 * i, 200 - 10 * myFunc(i), NULL);
		LineTo(hdc, 200 + 4 * (i + 1), 200 - 10 * myFunc(i + 1));
	}

	for (int t = 0; t < N; t++) {
		MoveToEx(hdc, 200 + 4 * t, 520 - Fourier(myFunc, t) / 2, NULL);
		LineTo(hdc, 200 + 4 * (t + 1), 520 - Fourier(myFunc, t + 1) / 2);
	}
}