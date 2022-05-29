#define _USE_MATH_DEFINES
#include<iostream>
#include<math.h>
#include<cmath>

#define f(y, x) ( (double)1 - 2 * (y * x) * std::tan(x)  )

void met_RungegoKutty(int n, double r[]) {

	double x, yn, k1, k2, k3, k4, h, a, b, y, xi, yi;
	a = r[0];
	b = r[1];
	int i = (int) a;
	yn = 1; //y(a)
	h = (b - a) / n;
	
	do {

		xi = a + (long)(i + 1) * h;
		x = xi;

		k1 = f( x, yn);
		k2 = f((x + h) / 2, yn + h * k1 / 2);
		k3 = f((x + h) / 2, yn + h * k2 / 2);
		k4 = f(x + h, yn + h * k3);

		yn = yn + h * ((k1 / 6) + (2 * k2 / 6) + (2 * k3 / 6) + (k4 / 6));

		++i;

		std::cout << "x "<<i<< ": "<<xi<<'\n';
		std::cout << "y "<<i<<": "<<yn << '\n';
	} while (i < n);

	
}

int main()
{
	double range[] = { 0, M_PI / 3 };
	int n = 6;

	std::cout << "==========\n";
	//std::cout << "Met. RungegoKutty \n\n";
	met_RungegoKutty(n, range);
	//std::cout << "wart.: \t" << t << '\n';
	std::cout << '\n';

	return 0;
}