#include<iostream>
#include<math.h>
#include<cmath>

#define MathPI atan(1.) * 4 //M_PI
#define f(x) ( exp( -1. * pow(x, 2) / 2) / sqrt(2. * MathPI) )

double met_trapezow(int n, double r[]) {
	//Pi= (f(xi-1)+f(xi)) / 2 * dx
	double S = 0., f2;
	//dx=(xk-xp)/n - szerokosc n rownych czesci
	double xp = r[0], xk = r[1];
	double dx = (xk - xp) / (double) n;
	double xi = f(xp), _xi;

	int i = 1;
	while ( i <= n ) {
		//xi=xp+i*dx for 1,2,...,n
		//f(xi-1) and f(xi) - wysokości
		_xi = xp + i * dx;
		f2 = f(_xi);
		//_xi = f2;

		S += xi + f2;
		xi = f2;

		++i;
	}
	return S * .5 * dx;
}

double trapez(double e, int n, double range[]) {
	double t,t2;
	int i = 0;
	do {
		t = met_trapezow(n, range);
		n = 2 * n;
		t2 = met_trapezow(n, range);

		++i;
	} while (abs(t2 - t) / t > e );
	std::cout << "iteracje: \t" << i << "\nl. podzialow: \t" << n << '\n';
	return t;
}

double met_simpsona(int n, double r[]) {

	double xp = r[0], xk = r[1];

	double dx = (xk - xp) / (double)n;
	double S = 0., ti = 0.;

	double xi, _ti;

	int i = 1;
	while (i <= n) {
		xi = xp + i * dx;

		_ti = xi - dx / 2.;
		ti += f(_ti);			// sum n
		if (i < n) S += f(xi);  // sum n-1

		++i;
	}
	return dx / 6. * (f(xp) + f(xk) + 2 * S + 4 * ti); 
}

double simpson(double e, int n, double range[]) {
	double t, t2;
	int i = 0;
	do {
		t = met_simpsona(n, range);
		n = 2 * n;
		t2 = met_simpsona(n, range);

		++i;
	} while (abs(t2 - t) / t > e);
	std::cout << "iteracje: \t" << i << "\nl. podzialow: \t" << n << '\n';
	return t;
}

double met_milnea(int n, double r[]) {

	int i = 1;

	double xp = r[0], xk = r[1];
	double f1, x;
	double dx = (xk - xp) / (double)n;
	double S = 0.;

	while (i < n) {
		x = xp + dx;
		f1 = f(x);
		
		if ((i+2) % 2 == 0) {
			S -= f1;
		}
		else {
			S += 2 * f1;
		};

		++i;
	}
	return (double)n / n-1 * dx * S;
}

double milne(double e, int n, double range[]) {
	double t, t2;
	int i = 0;
	do {
		t = met_milnea(n, range);
		n = 2 * n;
		t2 = met_milnea(n, range);

		++i;
	} while (abs(t2 - t) / t > e);
	std::cout << "iteracje: \t" << i << "\nl. podzialow: \t" << n << '\n';
	return t;
}

int main()
{
	double e = 1.e-5; // precyzja

	int n;

	double range[] = { -3, 3 };

	n = 2; // liczba podziałów pola pod funkcją
	std::cout << "==========\n";
	std::cout << "Met. trapezow \n\n";
	double t = trapez(e, n, range);
	std::cout << "wart. calki: \t" << t << '\n';
	std::cout << '\n';

	n = 3;
	std::cout << "==========\n";
	std::cout << "Met. Simpsona \n\n";
	double s = simpson(e, n, range);
	std::cout << "wart. calki: \t" << s << '\n';
	std::cout << '\n';

	n = 4;
	std::cout << "==========\n";
	std::cout << "Met. Milne'a \n\n";
	double m = milne(e, n, range);
	std::cout << "wart. calki: \t" << m << '\n';
	std::cout << '\n';

	return 0;
}