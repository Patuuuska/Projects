#include <iostream>
#include <string>
#include <queue>

using namespace std;

//Podaj liczbe k
//liczby szukane sa kolejno z cyfr 5 i 6
//wynik to k-ta z kolei liczba szukana
string func(int k) {
	queue<string> q;
	q.push("5");
	q.push("6");


	string current;
	int count = 0;
	while (!q.empty()) {
		current = q.front(); 
		q.pop(); 
		count++;

		if (count == k) {
			return current;
		}

		q.push(current + "5");
		q.push(current + "6");

	}
}

int main() {
	int k;
	cout << "Podaj liczbe k: ";
	cin >> k;
	string result = func(k);
	cout << result;
	return 0;
}
