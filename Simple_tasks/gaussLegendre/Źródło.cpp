#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

using namespace std;

const double x2[] = { -0.577350, 0.577350 };
const double weight2[] = { 1.0, 1.0 };

const double x3[] = { -0.774597, 0, 0.774597 };
const double weight3[] = { 0.5555555556, 0.8888888889, 0.5555555556 };

const double x4[] = { -0.861136, -0.339981, 0.339981, 0.861136 };
const double weight4[] = { 0.347855, 0.652145, 0.652145, 0.347855 };

const double x5[] = { -0.906180, -0.538469, 0, 0.538469, 0.906180 };
const double weight5[] = { 0.236927, 0.478629, 0.568889, 0.478629, 0.236927 };

const double x6[] = { -0.93247,-0.661209,-0.238619,0.238619,0.661209,0.93247 };
const double weight6[] = { 0.171325,0.360762,0.467914,0.467914,0.36076,0.17132 };

const double x7[] = { -0.949108,-0.741531,-0.405845,0,0.405845,0.741531,0.949108 };
const double weight7[] = { 0.129485,0.279705,0.38183,0.417959,0.38183,0.27971,0.129485 };

const double x8[] = { -0.96029,-0.796667,-0.525532,-0.183435,0.183435,0.525532,0.796667,0.96029 };
const double weight8[] = { 0.101229,0.222381,0.313707,0.362684, 0.362684,0.313707,0.222381,0.10123 };

const double x10[] = { -0.973907, -0.865063, -0.67941, -0.433395, -0.148874, 0.148874, 0.433395, 0.67941, 0.865063, 0.973907 };
const double weight10[] = { 0.066671, 0.149451, 0.219086, 0.26927, 0.295524, 0.29552, 0.26927, 0.21909, 0.149451, 0.066671 };


const double x15[] = { -0.987992 ,-0.937273 , -0.848206 ,-0.724417, -0.570972, -0.394151, -0.2011940, 0, 0.201194, 0.394151, 0.570972, 0.724417, 0.848206,  0.937273 , 0.987992 };
const double weight15[] = { 0.030753, 0.070366, 0.107159, 0.139570, 0.166269, 0.186161, 0.198431, 0.202578, 0.198431, 0.186161, 0.1662692, 0.139570, 0.1071592, 0.070366, 0.030753 };

double f_1(double x) {
    return 55 - 2 * x - 6 * pow(x, 2) + 5 * pow(x, 3) + 0.4 * pow(x, 4);
}
double f_2(double x) {
    return 1 - 2 * exp(x) - 6 * cos(x);
}
double f_3(double x) {
    return pow(x, 2) * pow(sin(x), 3);
};
double f_4(double x) {
    return exp(pow(x, 2)) * (x - 1);
}
double f_5(double x) {
    return sin(1 - x) / (1 - x);
}
double f_6(double x) {
    return sin(1 / (1 - x));
}
double f_7(double x) {
    return sin(x) / x;
}



double gaussLegendre(double (*f)(double), double a, double b, int n) {
    double* x = new double[n];
    double* weight2 = new double[n];
    if (n == 2) {
        for (int i = 0; i < n; i++) {
            x[i] = (b - a) / 2.0 * x2[i] + (b + a) / 2.0;
            weight2[i] = (b - a) * weight2[i] / 2;
        }
    }
    else if (n == 3) {
        for (int i = 0; i < n; i++) {
            x[i] = (b - a) / 2.0 * x3[i] + (b + a) / 2.0;
            weight2[i] = (b - a) * weight3[i] / 2;
        }
    }
    else if (n == 4) {
        for (int i = 0; i < n; i++) {
            x[i] = (b - a) / 2.0 * x4[i] + (b + a) / 2.0;
            weight2[i] = (b - a) * weight4[i] / 2;
        }
    }
    else if (n == 5) {
        for (int i = 0; i < n; i++) {
            x[i] = (b - a) / 2.0 * x5[i] + (b + a) / 2.0;
            weight2[i] = (b - a) * weight5[i] / 2;
        }
    }
    else if (n == 6) {
        for (int i = 0; i < n; i++) {
            x[i] = (b - a) / 2.0 * x6[i] + (b + a) / 2.0;
            weight2[i] = (b - a) * weight6[i] / 2;
        }
    }
    else if (n == 7) {
        for (int i = 0; i < n; i++) {
            x[i] = (b - a) / 2.0 * x7[i] + (b + a) / 2.0;
            weight2[i] = (b - a) * weight7[i] / 2;
        }
    }
    else if (n == 8) {
        for (int i = 0; i < n; i++) {
            x[i] = (b - a) / 2.0 * x8[i] + (b + a) / 2.0;
            weight2[i] = (b - a) * weight8[i] / 2;
        }
    }
    else if (n == 10) {
        for (int i = 0; i < n; i++) {
            x[i] = (b - a) / 2.0 * x10[i] + (b + a) / 2.0;
            weight2[i] = (b - a) * weight10[i] / 2;
        }
    }
    else if (n == 15) {
        for (int i = 0; i < n; i++) {
            x[i] = (b - a) / 2.0 * x15[i] + (b + a) / 2.0;
            weight2[i] = (b - a) * weight15[i] / 2;
        }
    }
    else {
        cout << "Nieprawidlowa liczba wezlow" << endl;
        return 0;
    }


    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += weight2[i] * f(x[i]);
    }

    return result;
}



int main() {

    cout << "podpunkt1 a " << endl;
    cout << "GaussLegendre dla f_3 n = 2: " << gaussLegendre(f_3, 0., 4.5, 2) << endl;
    cout << "GaussLegendre dla f_3 n = 3: " << gaussLegendre(f_3, 0., 4.5, 3) << endl;
    cout << "GaussLegendre dla f_3 n = 4: " << gaussLegendre(f_3, 0., 4.5, 4) << endl;
    cout << "GaussLegendre dla f_3 n = 5: " << gaussLegendre(f_3, 0., 4.5, 5) << endl;
    cout << endl;
    cout << "podpunkt1 b" << endl;
    cout << "GaussLegendre dla f_4 n = 2: " << gaussLegendre(f_4, -2., 2., 2) << endl;
    cout << "GaussLegendre dla f_4 n = 3: " << gaussLegendre(f_4, -2., 2., 3) << endl;
    cout << "GaussLegendre dla f_4 n = 4: " << gaussLegendre(f_4, -2., 2., 4) << endl;
    cout << "GaussLegendre dla f_4 n = 5: " << gaussLegendre(f_4, -2., 2., 5) << endl;
    cout << endl;
    cout << "GaussLegendre dla f_1: " << gaussLegendre(f_1, -2, 2, 6) << endl;
    cout << "GaussLegendre dla f_2: " << gaussLegendre(f_2, -2, 2, 5) << endl;
    cout << "GaussLegendre dla f3: " << gaussLegendre(f_3, 0, 4.5, 8) << endl;
    cout << "GaussLegendre dla f4: " << gaussLegendre(f_4, -2, 2, 15) << endl;
    cout << "GaussLegendre dla f5: " << gaussLegendre(f_5, 0, 1, 10) << endl;
    cout << "GaussLegendre dla f6: " << gaussLegendre(f_6, 0, 1 - 1e-4, 8) << endl;
    cout << "GaussLegendre dla f7: " << gaussLegendre(f_7, 0, 1, 6) << endl;

    return 0;

}