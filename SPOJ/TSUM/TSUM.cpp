#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 41000, DMAX = 140000, ZERO = 20000;
const double PI = 3.141592653589793, delta = 0.4824584828252467;

struct Complex
{
	double re, im;
	Complex operator+(const Complex &y)
	{
		return (Complex){re + y.re, im + y.im};
	}
	Complex operator-(const Complex &y)
	{
		return (Complex){re - y.re, im - y.im};
	}
	Complex operator*(const Complex &y)
	{
		return (Complex){re * y.re - im * y.im, re * y.im + y.re * im};
	}
	Complex operator/(const double y)
	{
		return (Complex){re / y, im / y};
	}
};

Complex operator*(double x, Complex y)
{
	return (Complex){x * y.re, x * y.im};
}

int N;
Complex X[DMAX], Y[DMAX], Z[DMAX], tmp[DMAX];

void DFT(Complex A[], Complex B[], int l, int level, double dir)
{
	int i;
	if(!level)
	{
		B[l] = A[l];
		return;
	}
	int limit = 1<<(level - 1), mid = l + limit;
	Complex unit = (Complex){cos(dir * 2 * PI / (1<<level)), sin(dir * 2 * PI / (1<<level))}, omega = (Complex){1.0, 0.0};
	for(i = 0;i < limit;i += 1)
	{
		B[l + i] = A[l + 2 * i];
		B[mid + i] = A[l + 2 * i + 1];
	}
	DFT(B, A, l, level - 1, dir);
	DFT(B, A, mid, level - 1, dir);
	for(i = 0;i < limit;i += 1, omega = omega * unit)
	{
		B[l + i] = A[l + i] + omega * A[mid + i];
		B[mid + i] = A[l + i] - omega * A[mid + i];
	}
}

int main()
{
	int i, x, maximum = 0, limit, level;
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
	{
		scanf("%d", &x);
		x += ZERO;
		Z[3 * x] = Y[2 * x] = X[x] = (Complex){1.0, 0.0};
		maximum = max(maximum, 3 * x);
	};
	for(level = 1;(1<<level) < maximum;level += 1);
	limit = 1<<level;
	DFT(X, tmp, 0, level, 1.0);
	memcpy(X, tmp, sizeof(X));
	DFT(Y, tmp, 0, level, 1.0);
	memcpy(Y, tmp, sizeof(Y));
	DFT(Z, tmp, 0, level, 1.0);
	memcpy(Z, tmp, sizeof(Z));
	for(i = 0;i < limit;i += 1)
		X[i] = (X[i] * X[i] * X[i] - 3 * Y[i] * X[i] + 2 * Z[i]) / 6 / limit;
	DFT(X, tmp, 0, level, -1.0);
	memcpy(X, tmp, sizeof(X));
	for(i = 0;i < limit;i += 1)
	{
		x = int(X[i].re + delta);
		if(x)
			printf("%d : %d\n", i - 3 * ZERO, x);
	}
	exit(0);
}
