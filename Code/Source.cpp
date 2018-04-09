#include<iostream>
#include<vector>

using namespace std;

typedef long long lint;

lint gcd(lint a, lint b)
{
	if (b == 0) return a;
	return gcd(b, a%b);
}

// Multiplication of polynomials
vector<lint> multiplication(int s1, int s2, const vector<lint> &A, const vector<lint> &B)
{
	vector<lint> buf(s1 + s2 + 1, 0);
	for (int i = 0; i <= s1 + s2; i++)
	{
		for (int j = 0; j <= i; j++)
			if (A.size() > j)
				buf[i] += A[j] * B[i - j];
	}
	return buf;
}

// The derivative of a polynomial
void derivative(int n, vector<lint> &A)
{
	for (int i = 0; i < n; i++)
		A[i] = A[i + 1] * (i + 1);
	A[n] = 0;
}

//Calculation of integral and formula
lint integral(int n, vector<lint> &A)
{
	lint pr = 1;
	A.resize(n + 2);
	for (int i = 2; i <= n + 1; i++)
		pr *= i;
	for (int i = n + 1; i > 0; i--)
	{
		A[i] = A[i - 1] * (pr / i);
	}
	return pr;
}

// pow() for long long
lint lintPow(lint x, lint y)
{
	lint a = 1;

	for (int i = 1; i <= y; i++)
		a *= x;
	return a;
}

int main()
{
	int n;
	lint numerator = 0, denominator = 1;
	cin >> n;
	vector<lint> T(n + 1);
	cin >> T[0];
	lint max = T[0];
	denominator *= T[0];
	vector<lint> A(n + 1, 0), B(n + 1, 0);
	A[0] = T[0];
	A[1] = -1;
	for (int i = 1; i < n; i++)
	{
		cin >> T[i];
		if (T[i] < max) max = T[i];
		denominator *= T[i];
		B[0] = T[i];
		B[1] = -1;
		A = multiplication(i, 1, A, B);
	}
	for (int i = 0; i <= n; i++)
		A[i] = -A[i];
	derivative(n, A);
	for (int i = n; i>0; i--)
		A[i] = A[i - 1];
	A[0] = 0;
	denominator *= integral(n, A);
	for (int i = 0; i <= n + 1; i++)
		numerator += A[i] * lintPow(max, i);
	lint g = gcd(numerator, denominator);
	cout << numerator / g << "/" << denominator / g;
	return 0;
}