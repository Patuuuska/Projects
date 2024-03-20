#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
class Game {
    int losowaLiczba;
    vector<int> gameHistory;
    
    public:
        Game() {
            losowaLiczba = 0;
        }

        void history() {
            cout << "\nHistoria wygranych gier:" << endl;
            for (const auto& result : gameHistory) {
                cout << result << " ";
            }
            cout << endl;
        }

    void play() {
        do {
            losowaLiczba = rand() % 100 + 1;
            cout << "------------------" << endl;
            cout << "|  WITAJ W GRZE  |" << endl;
            cout << "------------------" << endl;

            cout << "Program losuje liczbe od 1 do 100 - sprobuj ja zgadnac!" << endl << endl;
            int liczba = 0;
            while (liczba != losowaLiczba) {
                cout << "Podaj liczbe: " << endl;
                cin >> liczba;

                if (cin.fail()) { // Sprawdzenie czy poprzednia operacja wejścia to niepowodzenie
                    cin.clear();  // Resetowanie flagi błędu
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Usunięcie błędnych danych z bufora
                    cout << "Podaj poprawna liczbe" << endl;
                }
                else {
                    if (liczba < 1 || liczba > 100) {
                        cout << "Podaj liczbe z zakresu 1 do 100" << endl;
                    }
                    else {
                    

                        if (liczba < losowaLiczba) {
                            cout << "Liczba musi byc wieksza." << endl;
                        }
                        else if (liczba > losowaLiczba) {
                            cout << "Liczba musi byc mniejsza." << endl;
                        }
                        else {
                            gameHistory.push_back(liczba);
                            cout << "------------------------------" << endl;
                            cout << "| Udalo sie! WYGRALES!!!     |" << endl;
                            cout << "| Wylosowana liczba to : " << losowaLiczba << "  |" << endl;
                            cout << "------------------------------" << endl;

                        }
                    }
                }
            }
            cout << "Koniec gry." << endl;
            history();
            char odp;
            cout << "Czy chcesz zagrac ponownie? (Wpisz 'T' jesli chcesz zagrac lub jakikolwiek inny znak zeby zakonczyc): ";
            cin >> odp;
            if (odp != 'T' && odp != 't') {
                break;
            }

        } while (true);
    }

    
};
int main() {

    
    Game game;
    game.play();
    game.history();

    return 0;
}
