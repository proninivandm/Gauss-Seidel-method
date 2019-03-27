#include "stdafx.h"
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <iomanip>
const double l = 0.1;
const double a = 10;
using namespace std;
double Zolotoe(double l, double a, double b, double(*func)(double, double), int ji, double *ygr1, double *ygr2, double d1, double d2);
double F(double m, double n);
int main()
{
	double eps;
	double x1[3];
	double x2[3];
	double y1[4];
	double y2[4];
	double d[] = { 1, 0, 0, 1 };
	double de1, de2, lambd;
	double lmbd[3];
	int k = 1, j = 1;

	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите eps=";
	cin >> eps;
	cout << "Введите X1: " << endl << "x1=";
	cin >> x1[1];
	cout << endl << "x2=";
	cin >> x2[1];

	y1[1] = x1[1];
	y2[1] = x2[1];
	cout << "K"
		<< setw(15) << "Xk, F(Xk)"
		<< setw(28) << "J"
		<< setw(12) << "LMBDj"
		<< setw(20) << "Yj"
		<< setw(22) << "dj"
		<< setw(23) << "Yj+1"
		<< setw(25) << "de"
		<< setw(20) << "lambd"
		<< setw(17) << "Y1" << endl << endl;

	while (1)
	{
		cout << k << setw(8) << '(' << setprecision(4) << fixed << x1[1] << ',' << setprecision(4) << fixed << x2[1] << "), " << setprecision(4) << fixed << F(x1[1], x2[1]);
		while (j <= 2)
		{
			if (j == 2)
				cout << setw(44) << j << setw(10);
			else
				cout << setw(12) << j;
			lmbd[j] = Zolotoe(l, -a, a, F, j, y1, y2, d[j - 1], d[j + 1]);
			cout << setw(14) << setprecision(4) << fixed << lmbd[j] << setw(8)
				<< '(' << setprecision(4) << fixed << y1[j] << ',' << setprecision(4) << fixed << y2[j] << ')'
				<< setw(12) << '(' << d[j - 1] << ',' << d[j + 1] << ')';
			y1[j + 1] = y1[j] + d[j - 1] * lmbd[j];
			y2[j + 1] = y2[j] + d[j + 1] * lmbd[j];
			cout << setw(7) << '(' << setprecision(4) << y1[j + 1] << ',' << setprecision(4) << y2[j + 1] << ')';
			if (j == 1)
				cout << endl;
			j++;
		}
		x1[2] = y1[3];
		x2[2] = y2[3];
		if (sqrt(pow(abs(x1[2] - x1[1]), 2) + pow(abs(x2[2] - x2[1]), 2)) < eps)
			break;

		de1 = x1[2] - x1[1];
		de2 = x2[2] - x2[1];
		lambd = Zolotoe(l, -a, a, F, 2, x1, x2, de1, de2);
		y1[1] = x1[2] + lambd * de1;
		y2[1] = x2[2] + lambd * de2;
		cout << setw(10) << '(' << setprecision(4) << de1
			<< ',' << setprecision(4) << de2 << ')'
			<< setw(15) << setprecision(4) << lambd
			<< setw(10) << '('
			<< y1[1] << setprecision(4) << ','
			<< y2[1] << setprecision(4) << ')' << endl << endl;
		j = 1;
		k++;
		x1[1] = x1[2];
		x2[1] = x2[2];

	}
	cout << endl << "Оптимальный вектор: (" << x1[2] << "; "
		<< x2[2] << ')' << endl << "Количество итераций= " << k << endl << "Значение функции:  F= " << F(x1[2], x2[2]) << endl;

	system("pause");
	return 0;
}

double Zolotoe(double l, double a, double b, double(*func)(double, double), int ji, double *ygr1, double *ygr2, double d1, double d2)
{
	const double al = 0.618;
	int j = 0;
	int k = 1;
	double lmbd = a + (1 - al)*(b - a);
	double mu = a + al * (b - a);

	while (b - a >= l)
	{
		if (func(ygr1[ji] + lmbd * d1, ygr2[ji] + lmbd * d2) > func(ygr1[ji] + mu * d1, ygr2[ji] + mu * d2))
		{
			a = lmbd;
			lmbd = mu;
			mu = a + al * (b - a);

		}//if
		else
		{
			b = mu;
			mu = lmbd;
			lmbd = a + (1 - al)*(b - a);

		}//else

		k++;
	}//while
	return (b + a) / 2;
}

double F(double m, double n)
{
	double p = pow(m - n, 2) + pow(n - 2, 2);
	return p;
}
