#pragma once

#include"ode_solver.h"

matrix ff0T(matrix, matrix = NAN, matrix = NAN);
matrix ff0R(matrix, matrix = NAN, matrix = NAN);
matrix df0(double, matrix, matrix = NAN, matrix = NAN);
matrix df1(double t, matrix Y, matrix ud1, matrix ud2);
matrix func2(matrix x , matrix , matrix);
matrix ff1T(matrix x, matrix ud1, matrix ud2);