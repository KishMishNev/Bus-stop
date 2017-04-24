#include<iostream>

using namespace std;

typedef long long lint;

lint A[10], B[10], C[10];

lint gcd(lint a, lint b)
{
	if (b == 0) return a;
	return gcd(b, a%b);
}

void multi(lint s1, lint s2)
{
	for (int i = 0; i <= s1 + s2; i++)
		C[i] = 0;
	for (lint i = 0; i <= s1 + s2; i++)
	{
		for (lint j = 0; j <= i; j++)
			C[i] += A[j] * B[i - j];
	}
	for (lint i = 0; i <= s1 + s2; i++)
		A[i] = C[i];
}

void derivative(lint n)
{
	for (lint i = 0; i < n; i++)
		A[i] = A[i + 1] * (i + 1);
	A[n] = 0;
}

lint integral(lint n)
{
	lint pr = 1;
	for (lint i = 2; i <= n + 1; i++)
		pr *= i;
	for (lint i = n + 1; i > 0; i--)
	{
		A[i] = A[i - 1] * (pr / i);
	}
	return pr;
}

lint mpow(lint x, lint y)
{
	lint a = 1;

	for (int i = 1; i <= y; i++)
		a *= x;
	return a;
}

int main()
{
	lint n;
	lint numerator = 0, denominator = 1;
	lint T[6];
	cin >> n;
	cin >> T[0];
	lint max = T[0];
	denominator *= T[0];
	A[0] = T[0];
	A[1] = -1;
	for (lint i = 1; i < n; i++)
	{
		cin >> T[i];
		if (T[i] < max) max = T[i];
		denominator *= T[i];
		B[0] = T[i];
		B[1] = -1;
		multi(i, 1);
	}
	for (int i = 0; i <= n; i++)
		A[i] = -A[i];
	derivative(n);
	for (int i = n; i>0; i--)
		A[i] = A[i - 1];
	A[0] = 0;
	denominator *= integral(n);

	for (int i = 0; i <= n + 1; i++)
		numerator += A[i] * (lint)mpow(max, i);
	lint g = gcd(numerator, denominator);
	cout << numerator / g << "/" << denominator / g;
	return 0;
}