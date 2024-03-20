#include"user_funs.h"

matrix ff0T(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	y = pow(x(0) - ud1(0), 2) + pow(x(1) - ud1(1), 2);
	return y;
}

matrix ff0R(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	matrix Y0 = matrix(2, 1), MT = matrix(2, new double[2]{ m2d(x),0.5 });
	matrix* Y = solve_ode(df0, 0, 0.1, 10, Y0, ud1, MT);
	int n = get_len(Y[0]);
	double teta_max = Y[1](0, 0);
	for (int i = 1; i < n; ++i)
		if (teta_max < Y[1](i, 0))
			teta_max = Y[1](i, 0);
	y = abs(teta_max - m2d(ud1));
	Y[0].~matrix();
	Y[1].~matrix();
	return y;
}

matrix df0(double t, matrix Y, matrix ud1, matrix ud2)
{
	matrix dY(2, 1);
	double m = 1, l = 0.5, b = 0.5, g = 9.81;
	double I = m*pow(l, 2);
	dY(0) = Y(1);
	dY(1) = ((t <= ud2(1))*ud2(0) - m*g*l*sin(Y(0)) - b*Y(1)) / I;
	return dY;
}


matrix df1(double t, matrix Y, matrix ud1, matrix ud2)
{
	double a = 0.98;
	double b = 0.63;
	double g = 9.81;
	double Pa = 0.75;
	double Db = 0.00365665;
	double Fin = 0.01;
	double Tin = 10;
	double Ta = 90;
	double Pb = 1;

	matrix dY(3, 1);
	double Fa_out = a * b * m2d(ud2) * sqrt(2 * g * (Y(0) / Pa));
	double Fb_out = a * b * Db * sqrt(2 * g * (Y(1) / Pb));

	dY(0) = -Fa_out;
	dY(1) = Fa_out + Fin - Fb_out;
	dY(2) = Fin / Y(1) * (Tin - Y(2)) + Fa_out / Y(1) * (Ta - Y(2));
	cout << dY << endl;
	return dY;
}

matrix func2(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	int i;
	matrix Y0 = matrix(3, new double[3] {5, 1, 10});
	matrix* Y = solve_ode(df1, 0, 1, 1000, Y0, ud1, x);
	int n = get_len(Y[0]);
	double max = Y[1](0, 2);
	for (i = 1; i < n; i++) {
		if (max < Y[1](i, 2)) {
			max = Y[1](i, 2);
		}
	}
	y = abs(max - 50);
	cout << y << endl;
	return y;
}

matrix ff1T(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	y = -cos(0.1 * x()) * exp(-pow(0.1 * x() - 2 * 3.14, 2)) + 0.002 * pow(0.1 * x(), 2);
	return y;
}