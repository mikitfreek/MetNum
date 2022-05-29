#include <iostream>
#include <math.h>

float fn(float x) {
    float z = atan(x + 1);
    return z;
}

float modu(float a) {
    float mod;
    if (a < 0)
        mod = -a;
    else
        mod = a;
    return mod;
}

float falsi(float a, float b, int it)
{
    double e = 10e-5;
    
    float fa = fn(a),
        fb = fn(b);
    if (fa * fb > 0)
    {
        return -1;
    }

    float x = a - fa * (a - b) / (fa - fb);
    float f = fn(x);

    if (it < 0 || modu(f) <= e || modu(b - a) <= e)  
    {
        std::cout << "\tx = " << x << ";\t f(x) = " << f << '\n';
        return x;
    }

    if (fa * f < 0)         b = x;
    else if (fb * f < 0)    a = x;

    return falsi(a, b, --it);
}

float muller(float a, float b, float c, int it)
{
    double e = 10e-5;

    float fa = fn(a),
        fb = fn(b),
        fc = fn(c);

    float q = (c - b) / (b - a),
        _c = (1 + q) * fc,
        _b = (2 * q + 1) * fc - pow(1 + q, 2) * fb + (double)q * q * fa,
        _a = q * fc - q * (1 + q) * fb + q * q * fa;

    float d,
        delta = sqrt(_b * _b - 4 * _a * _c);
    if (delta < 0) return -1;

    float d0 = (_b + modu(sqrt(_b * _b - 4 * _a * _c))),
        d1 = (_b - modu(sqrt(_b * _b - 4 * _a * _c)));

    //delta max
    if (d0 >= d1)   d = d0;
    else            d = d1;

    float x = c - (c - b) * (2 * c) / d,
        f = fn(x);

    if (it < 0 || modu(f) <= e || modu(b - a) <= e)
    {

        std::cout << "\tdla punktow x0, x1, x2 = {" << a << ", " << b << ", " << c << "};" << '\n';
        std::cout << "\tx = " << x << ";\t f(x) = " << f << '\n';
        return x;
    }

    _a = _b;
    _b = _c;
    _c = x;

    return muller(a, b, c, --it);
}

int main()
{
    std::cout << '\n' << "Metoda Falsi: " << '\n';
    float f = falsi(-2, 2, 10);
    
    std::cout << '\n' << "Metoda Mullera: " << '\n';
    float m = muller(-2, 0, 2, 10);
    
    return 0;
}

