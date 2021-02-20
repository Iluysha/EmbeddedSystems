#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "header.h"
#include <string>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

int n = 10;
int w = 1500;
int N = 256;

int *arrA = new int[n];
int *arrQ = new int[n];

map<float, float> real;
map<float, float> irreal;

float myFunc(float t) {
	float res = 0;
	for (int i = 0; i < n; i++) {
		res += arrA[i] * sin(w / n * (i + 1) * t + arrQ[i]);
	}
	return res;
}

void Table(float myFunc(float t), int N) {
	for (int t = 0; t < N; t++) {
		for (int i = 0; i < N; i++) {
			if (real.find(i * t) == real.end()) {
				real[i * t] = cos(4 * M_PI * i * t / N);
				irreal[i * t] = sin(4 * M_PI * i * t / N);
			}
		}
	}
}

float Fourier(float myFunc(float t), float t) {
	float real1 = 0;
	float irreal1 = 0;
	float real2 = 0;
	float irreal2 = 0;
	for (int i = 0; i < N / 2; i++) {
		real1 += myFunc(2 * i + 1) * real.find(i * t)->second;
		irreal1 += myFunc(2 * i + 1) * irreal.find(i * t)->second;
		real2 += myFunc(2 * i) * real.find(i * t)->second;
		irreal2 += myFunc(2 * i) * irreal.find(i * t)->second;
	}
	if (t < N / 2) {
		return sqrt(pow(real2 + real1 * cos(4 * M_PI * t / N), 2) + 
			        pow(irreal2 + irreal1 * sin(4 * M_PI * t / N), 2));
	}
	else {
		return sqrt(pow(real2 - real1 * cos(4 * M_PI * t / N), 2) + 
			        pow(irreal2 - irreal1 * sin(4 * M_PI * t / N), 2));
	}
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
	LineTo(hdc, 730, 520);

	MoveToEx(hdc, 800, 380, NULL);
	LineTo(hdc, 800, 650);

	MoveToEx(hdc, 800, 520, NULL);
	LineTo(hdc, 1320, 520);

	TextOut(hdc, 205, 30, "x", 1);
	TextOut(hdc, 1280, 202, "t", 1);
	TextOut(hdc, 205, 390, "F", 1);
	TextOut(hdc, 700, 522, "t", 1);
	TextOut(hdc, 805, 380, "%", 1);
	TextOut(hdc, 1300, 502, "N", 1);
	TextOut(hdc, 180, 90, "10", 2);
	TextOut(hdc, 180, 415, "20", 2);
	TextOut(hdc, 780, 415, "30", 2);
	TextOut(hdc, 780, 520, "20", 2);

	for (int i = 0; i <= N; i += 20) {
		std::stringstream s;
		s << (float)(i);
		TextOut(hdc, 205 + 4 * i, 202, (s.str()).c_str(), (s.str()).size());
	}

	Table(myFunc, N);

	for (int i = 0; i <= N; i++) {
		MoveToEx(hdc, 200 + 4 * i, 200 - 10 * myFunc(i), NULL);
		LineTo(hdc, 200 + 4 * (i + 1), 200 - 10 * myFunc(i + 1));
	}

	for (int i = 0; i < N; i++) {
		MoveToEx(hdc, 200 + 2 * i, 520 - Fourier(myFunc, i) / 2, NULL);
		LineTo(hdc, 200 + 2 * (i + 1), 520 - Fourier(myFunc, i + 1) / 2);
	}
	
	real.clear();
	irreal.clear();
	float percent = 100;
	for (int i = 100; i <= 1000; i += 100) {
		real.clear();
		irreal.clear();
		std::stringstream s;
		s << (float)(i);
		TextOut(hdc, 790 + i / 2, 522, (s.str()).c_str(), (s.str()).size());

		Table(myFunc, i);
		MoveToEx(hdc, 800 + (i - 100) / 2, 520 - percent, NULL);
		percent = 1000 * real.size() / (i * i) - 200;
		LineTo(hdc, 800 + i / 2, 520 - percent);
	}
}

