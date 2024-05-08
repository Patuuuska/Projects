#include <iostream>
#include <Windows.h>


using namespace std;

long double fib[1000];
int ile;

int main() {
	cout << "Podaj ile elementow ciagu Fib podac: ";
	cin >> ile;
	fib[0] = 1;
	fib[1] = 1;
	cout << endl;
	for (int i = 2; i < ile; i++) {

		fib[i] = fib[i - 1] + fib[i - 2];
		cout << "Element " << i + 1 << " ciagu Fib wynosi " << fib[i]<<endl;

	}
	Sleep(1000);
	return 0;
}