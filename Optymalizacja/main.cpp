
#include"opt_alg.h"

void lab0();
void lab1();


int main()
{
	try
	{
		lab1();
	}
	catch (string EX_INFO)
	{
		cerr << "ERROR:\n";
		cerr << EX_INFO << endl << endl;
	}
	system("pause");
	return 0;
}

void lab0()
{
	//Funkcja testowa
	double epsilon = 1e-2;
	int Nmax = 10000;
	matrix lb(2, 1, -5), ub(2, 1, 5), a(2, 1);
	solution opt;
	a(0) = -1;
	a(1) = 2;
	opt = MC(func2, 2, lb, ub, epsilon, Nmax, a);
	cout << opt << endl << endl;
	solution::clear_calls();

	//Wahadlo
	Nmax = 1000;
	epsilon = 1e-2;
	lb = 0;
	ub = 5;
	double teta_opt = 1;
	opt = MC(ff0R, 1, lb, ub, epsilon, Nmax, teta_opt);
	cout << opt << endl << endl;
	solution::clear_calls();

	//Zapis symulacji do pliku csv
	matrix Y0 = matrix(2, 1), MT = matrix(2, new double[2]{ m2d(opt.x),0.5 });
	matrix* Y = solve_ode(df0, 0, 0.1, 10, Y0, NAN, MT);
	ofstream Sout("symulacja_lab0.csv");
	Sout << hcat(Y[0], Y[1]);
	Sout.close();
	Y[0].~matrix();
	Y[1].~matrix();
}

void lab1()
{
	
	cout << "\n\nLab1:\n\n";
	//double* c = new double[2];
	int liczba = 0;

	//c = expansion(ff1T, -100.0, 1.0, 2.0, 1000);
	double* Xop;
	Xop = expansion(&ff1T, 10, 1.0, 2.0, 1000);
	solution d;

	solution a =lag(ff1T, 40, 80.0, 0.01, 0.0001, 10000);
	solution b = fib(ff1T, -100.0, 100.0, 0.01, NULL, NULL);
	cout << a.x << endl;
	cout << a.y << endl;
	//cout << c[0] << endl;
	//cout << c[1] << endl;
	cout << liczba;
	
	cout << "Ekspansja" << endl;
	double* wynik;
	wynik = expansion(&func2, 10, 1.0, 2.0, 1000);
	cout << wynik[0] << ";" << wynik[1] << ";" << solution::f_calls << "\n";
	solution::clear_calls();

	double epsilon = 1e-5;
	solution ffib = fib(func2, wynik[0], wynik[1], epsilon);
	cout << m2d(ffib.x) << ";" << m2d(ffib.y) << ";" << solution::f_calls << ";" << m2d(ffib.x) << "\n";
	solution::clear_calls();
	cout << "testowa funkcja celu" << endl;
	ofstream expansionfile("expansion.txt");
	ofstream fibonaccifile("fibonacci.txt");
	ofstream lagrangefile("lagrange.txt");
	double x0;
	double epsilon = 1e-5;
	for (int i = -10; i < 10; i++)
	{
		x0 = i;
		double* wynik = expansion(func2, x0, 1.0, 1.0, 15000);
		expansionfile << x0 << ";" << wynik[0] << ";" << wynik[1] << ";" << solution::f_calls << "\n";
		solution::clear_calls();

		solution ffib = fib(func2, wynik[0], wynik[1], epsilon);
		fibonaccifile << m2d(ffib.x) << ";" << m2d(ffib.y) << ";" << solution::f_calls << ";" << m2d(ffib.x) << "\n";
		solution::clear_calls();

		solution wynik_lag = lag(func2, wynik[0], wynik[1], epsilon, 0.0001, 1000);
		lagrangefile << m2d(wynik_lag.x) << ";" << m2d(wynik_lag.y) << ";" << solution::f_calls << ";" << m2d(wynik_lag.x) << "\n";
		solution::clear_calls();
	}
	
	
	double epsilon1 = 1e-5;
	double gamma = 1e-200;
	double Nmax = 50;

	ofstream expansionfile("expansion.txt");
	ofstream fibonaccifile("fibonacci.txt");
	ofstream lagrangefile("lagrange.txt");

	double* wynik = expansion(&func2, 3, 1, 5, 1000);
	solution wynik_fib = fib(func2, wynik[0], wynik[1], epsilon1);
	fibonaccifile << m2d(wynik_fib.x)<<";" << m2d(wynik_fib.y) << ";" << solution::f_calls << ";" << m2d(wynik_fib.y) << "\n";
	solution::clear_calls();
	solution wynik_lag = lag(func2, wynik[0], wynik[1], epsilon1, 0.0001, 1000);
	lagrangefile << m2d(wynik_lag.x) << ";" << m2d(wynik_lag.y) << ";" << solution::f_calls << ";" << m2d(wynik_lag.y) << "\n";

	for (int i = -2; i < 20; i++)
	{
		double x0 = i;
		double* wynik = expansion(&func2, x0, 1, 5, 1000);
		expansionfile << x0 << ";" << wynik[0] << ";" << wynik[1] << ";" << solution::f_calls << "\n";
		solution::clear_calls();

		solution wynik_fib = fib(func2, wynik[0], wynik[1], epsilon1);
		fibonaccifile << m2d(wynik_fib.x) << ";" << m2d(wynik_fib.y) << ";" << solution::f_calls << ";" << m2d(wynik_fib.y) << "\n";
		solution::clear_calls();

		solution wynik_lag = lag(func2, wynik[0], wynik[1], epsilon1, 0.0001, 1000);
		lagrangefile<< m2d(wynik_lag.x) << ";" << m2d(wynik_lag.y) << ";" << solution::f_calls << ";" << m2d(wynik_lag.y) << "\n";

	}
	 
	
	solution x_fibtest = fib(func2, 1e-4, 1e-2, 1e-7);
	cout << "fib" << endl << x_fibtest << endl;
	solution::clear_calls();
	solution x_lagtest = lag(func2, 1e-4, 1e-2, 1e-7, 1e-200, 1000);
	
	//cout << "lag" << endl << x_lagtest << endl;
	//solution::clear_calls();

	//solution x_fibtest = fib(func2, -100, 100, 1e-5);
	//solution x_lagtest = lag(func2, 1e-4, 1e-2, 1e-7, 1e-200, 1000);
	

}

