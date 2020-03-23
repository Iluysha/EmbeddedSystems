#include "stdafx.h"
#include "header.h"
#include <string>
#include <cmath>
#include <sstream>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

int w, n, N;
char buf[100];

INT_PTR CALLBACK Set(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			TCHAR buf[32];
			
			GetDlgItemText(hDlg, IDC_EDIT1, buf, 32);
			n = atoi(buf);
			GetDlgItemText(hDlg, IDC_EDIT2, buf, 32);
			w = atoi(buf);
			GetDlgItemText(hDlg, IDC_EDIT3, buf, 32);
			N = atoi(buf);
			
			EndDialog(hDlg, 1);
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
	}
	return (INT_PTR)FALSE;
}

float myFunc(float t, int arrA[], int arrQ[]) {
	float res = 0;
	for (int i = 0; i < n; i++) {
		res += arrA[i] * sin(w / n * (i+1) * t + arrQ[i]);
	}
	return res;
}

void print(HDC hdc, PAINTSTRUCT ps) {
	LOGFONT font;
	font.lfHeight = 12;
	font.lfEscapement = 0;
	font.lfOrientation = 0;
	font.lfUnderline = 0;
	font.lfStrikeOut = 0;
	font.lfPitchAndFamily = 0;

	HFONT hfont;
	hfont = ::CreateFontIndirect(&font);
	SelectObject(ps.hdc, hfont);

	float M = 0;
	float D = 0;
	int *arrA = new int[n];
	int *arrQ = new int[n];
	for (int i = 0; i < n; i++) {
		arrA[i] = (rand() % 2 + 1);
		arrQ[i] = (rand() % 10);
	}

	MoveToEx(hdc, 200, 25, NULL);
	LineTo(hdc, 200, 450);

	MoveToEx(hdc, 150, 250, NULL);
	LineTo(hdc, 1300, 250);

	MoveToEx(hdc, 400, 420, NULL);
	LineTo(hdc, 400, 650);

	MoveToEx(hdc, 380, 620, NULL);
	LineTo(hdc, 970, 620);

	TextOut(hdc, 64, 60, "x", 1);
	TextOut(hdc, 62, 110, "x", 1);
	font.lfHeight = 18;
	hfont = ::CreateFontIndirect(&font);
	SelectObject(ps.hdc, hfont);
	TextOut(hdc, 205, 30, "x", 1);
	TextOut(hdc, 1280, 252, "t", 1);
	TextOut(hdc, 405, 424, "t", 1);
	TextOut(hdc, 950, 624, "N", 1);
	TextOut(hdc, 900, 624, "32768", 5);
	TextOut(hdc, 410, 624, "256", 3);
	
	float *x = new float[N];
	clock_t start0 = clock();
	for (int i = 0; i < N; i += 1) {
		x[i] = myFunc(i, arrA, arrQ);
	}
	clock_t end0 = clock();
	TextOut(hdc, 50, 150, "time =", 6);
	std::stringstream s3;
	s3 << (float)(end0 - start0);
	TextOut(hdc, 100, 150, (s3.str()).c_str(), (s3.str()).size());

	std::ofstream out;
	out.open("data\\data.txt");
	if (out.is_open()) {
		out << start0 << " " << end0 << std::endl;
	}
	else { TextOut(hdc, 100, 300, "Fail", 5); }

	for (int i = 0; i < N; i += 1) {
		MoveToEx(hdc, 200 + 1024 / N * i, 250 - 180 / n * x[i], NULL);
		LineTo(hdc, 200 + 1024 / N * (i + 1), 250 - 180 / n * myFunc(i + 1, arrA, arrQ));
	}

	for (int i = 0; i < N; i += 1) {
		M += myFunc(i + 1, arrA, arrQ);
	}
	M /= N;
	TextOut(hdc, 50, 50, "M", 1);
	TextOut(hdc, 70, 50, "=", 1);
	std::stringstream s1;
	s1 << M;
	TextOut(hdc, 85, 50, (s1.str()).c_str(), (s1.str()).size());

	for (int i = 0; i < N; i += 1) {
		D += pow(myFunc(i + 1, arrA, arrQ) - M, 2);
	}
	D /= (N-1);
	TextOut(hdc, 50, 100, "D", 1);
	TextOut(hdc, 70, 100, "=", 1);
	std::stringstream s2;
	s2 << D;
	TextOut(hdc, 85, 100, (s2.str()).c_str(), (s2.str()).size());

	clock_t start = 0;
	clock_t end = 0;
	for (int i = 256; i < 32768; i += 256) {
		float *x = new float[i];
		MoveToEx(hdc, 400 + (i-256) / 64, 620 + 80 / n * (start - end),  NULL);
		
		start = clock();
		for (int j = 0; j < i; j += 1) {
			x[j] = myFunc(j, arrA, arrQ);
		}
		end = clock();
		
		LineTo(hdc, 400 + i / 64, 620 + 80 / n * (start - end));
	}
}