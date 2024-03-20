#include <iostream>										 // Uzywa cout/cin
#include <conio.h>										 // Uzywa funkcje getch()
#include <windows.h>					 				 // Uzywa funkcji windows
#include <ctime>						 				 // Uzywa funkcji czas
#include <fstream>									     // Uzywa funkcji do wysokiego wyniku
#include <string>
#include <cstdlib>
#include <chrono>									     // Uzywa funkcji czasu do konca gry

using namespace std;

void Menu(); //Menu gry
void fioletowy(); //zmienia kolor na fioletowy
void bialy();	  //zmienia kolor na bialy
void Tworca();	  //pokazuje tworce
void Graj();	  //przechodzi do wyboru gry
void Jak_grac();  //ekran z informacjami jak grac
void GameOver();  //ekran konca gry
void Mlotki_jak_grac();
void Test_reakcji_jak_grac();
void Lampki_jak_grac();
//LOGOWANIE
void Login();//glowna funkcja logowania
void rejestracja();//wczytywanie danych do pliku
void logowanie();//odczyt danych z pliku
//GRA MLOTKI
void mlotki(); //GLOWNA FUNKCJA GRY SZYBKIE UDERZENIE
void mlotki_grafika(); //CZÊŒÆ WIZUALNA
void mlotki_instrukcja_do_gry(); //INFORMACJE PRZED ROZPOCZECIEM GRY
void mlotki_start(); //FUNKCJA ROZPOCZYNAJACE GRE PO WCISNIECIU DOWOLNEGO PRZYCISKU
void mlotki_GameOver(); //FUNKCJA ZAPYTANIA CZY KONTYNUOWAC GRE W PRZYPADKU ZAKONCZENIA ROZGRYWKI
//GRA TEST REAKCJI
void Test_reakcji();
//GRA LAMPKI
void Lampki();

//zmienne
int z;											// Poruszanie sie klawiatura
int m = 1;
int o = 1;
int zm1 = 1, zm2 = 1, zm4 = 1, zm5 = 1;
//zmienne - logowanie
string login_wczyt, haslo_wczyt;
string login_odczyt, haslo_odczyt;
//zmienne - GRA MLOTKI
int wybor, gracz;
char znak;
char oznaczenie_pola[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char square[10] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

int main()
{
	while (1)
	{
		system("cls");

		cout << "\n\n\n\n";
		cout << "\t\t\tWitaj na WyspaGierNaReflex!";
		cout << "\n\n\n\n\n";
		cout << "";
		cout << "";
		cout << "\t\t\t\tCzy posiadasz konto na WyspaGierNaReflex?\n";
		if (zm5 == 1) fioletowy();  cout << "\t\t\t tak, Zaloguj \n"; bialy();
		if (zm5 == 2) fioletowy();  cout << "\t\t\t nie, Przejdz do Rejestracji \n";	bialy();
		if (zm5 == 3) fioletowy();  cout << "\t\t\t Wyjscie \n"; bialy();
		z = _getch();

		if (z == 72) { zm5--; }
		if (z == 80) zm5++;
		if (zm5 == 0) { zm5 += 3; }
		if (zm5 == 4) { zm5 -= 3; }

		if ((z == 13) && (zm5 == 3)) exit(1);			// Wyjscie z programu
		if ((z == 13) && (zm5 == 2)) rejestracja();				// Menu opcji
		if ((z == 13) && (zm5 == 1)) logowanie();			// Rozpoczecie Gry


	}
}

//Menu gry
void Menu()
{
	while (1)
	{
		system("cls");
		cout << "\n\tUzytkownik: " << login_wczyt << "\n";
		cout << "\n\n\n\n\n\n";


		if (m == 1) fioletowy();  cout << "\t\t\t\t Graj \n"; bialy();
		if (m == 2) fioletowy();  cout << "\t\t\t\t Jak grac \n";	bialy();
		if (m == 3) fioletowy();  cout << "\t\t\t\t Tworca \n"; bialy();
		if (m == 4) fioletowy();  cout << "\t\t\t\t Wyjscie \n"; bialy();
		z = _getch();

		if (z == 72) { m--; }
		if (z == 80) m++;
		if (m == 0) { m += 4; }
		if (m == 5) { m -= 4; }
		//if (z == 80) { if (m < 4) { m++; } }						// Ograniczenie z dolu
		if ((z == 13) && (m == 4)) exit(1);				// Wyjscie z programu
		if ((z == 13) && (m == 2)) Jak_grac();
		if ((z == 13) && (m == 3)) Tworca();				// Menu opcji
		if ((z == 13) && (m == 1)) Graj();			// Rozpoczecie Gry
	}
}




void rejestracja()//wczytywanie danych do pliku
{
	system("cls");
	cout << "\n\n\n\t\t\t\t      \n\n\n";
	cout << "\t\t\t-------------------------\n";
	cout << "\t\t\t| R E J E S T R A C J A |\n";
	cout << "\t\t\t-------------------------\n\n\n";
	cout << "\t\t\t P o d a j   l o g i n : ";
	cin >> login_wczyt;
	cout << "\n\t\t\t P o d a j   h a s l o : ";
	cin >> haslo_wczyt;
	cout << "\n\n\t\t\tAby utworzyc konto nacisnij ENTER... ";
	char zarejestruj = _getch();

	fstream plik;
	plik.open("logowanie.txt", ios::out);
	plik << login_wczyt << endl;
	plik << haslo_wczyt << endl;

	plik.close();
}

void logowanie()//odczyt danych z pliku
{
	system("cls");
	string linia;
	int nr_linii = 1;
	fstream plik;
	plik.open("logowanie.txt", ios::in);
	if (plik.good() == false) cout << "Blad bazy danych!";
	while (getline(plik, linia))
	{
		switch (nr_linii)
		{
		case 1: login_wczyt = linia;
			break;
		case 2: haslo_wczyt = linia;
			break;
		}
		nr_linii++;
	}
	plik.close();
	cout << "\n\t\t\t\t      \n\n\n";
	cout << "\t\t\t---------------------\n";
	cout << "\t\t\t| L O G O W A N I E |\n";
	cout << "\t\t\t---------------------\n\n\n";
	cout << "\t\t\t P o d a j   l o g i n : ";
	cin >> login_odczyt;
	cout << "\n\t\t\t P o d a j   h a s l o : ";
	cin >> haslo_odczyt;

	if ((login_odczyt == login_wczyt) && (haslo_odczyt == haslo_wczyt))
	{
		cout << "\n\n\t\t\tLogowanie przeszlo pomyslnie! Zapraszamy.... ";
		cout << "\n\n\t\t\tnacisnij dowolny przycisk... ";
		_getch();
		Menu();
	}
	else
	{
		system("cls");
		cout << "\n\n\t\t\tPodano zle dane! Wpisz poprawny login i haslo.";
		cout << "\n\n\t\t\tnacisnij dowolny przycisk... ";
		_getch();
		logowanie();
	}
}


///ekrany
//
//zm1 - obsluguje funkcje
void Graj()
{
	while (1)
	{
		system("cls");									// Czyszczenie Ekranu
		bialy();
		cout << "\n\n\n\t\t\t\t      \n\n\n";
		if (zm1 == 1) { fioletowy(); }cout << "\t\t\t Szybkie uderzenie \n"; bialy();
		if (zm1 == 2) { fioletowy(); }cout << "\t\t\t League of Reflex \n"; bialy();
		if (zm1 == 3) { fioletowy(); }cout << "\t\t\t Lampki i Sandaly \n"; bialy();
		if (zm1 == 4) { fioletowy(); }cout << "\t\t\t Powrot \n"; bialy();
		z = _getch();

		if (z == 72) { zm1--; }
		if (z == 80) { zm1++; }
		if (zm1 == 0) zm1 += 4;
		if (zm1 == 5) zm1 -= 4;

		if ((z == 13) && (zm1 == 1))  mlotki();
		if ((z == 13) && (zm1 == 2))  Test_reakcji();
		if ((z == 13) && (zm1 == 3))  Lampki();
		if ((z == 13) && (zm1 == 4)) Menu();
	}
}

//zm2 - obsluga funkcji
void Jak_grac() {
	while (1)
	{
		system("cls");									// Czyszczenie Ekranu
		bialy();
		cout << "\n\n\n\t\t\t\t      \n\n\n";
		if (zm2 == 1) { fioletowy(); }cout << "\t\t\t Szybkie uderzenie \n"; bialy();
		if (zm2 == 2) { fioletowy(); }cout << "\t\t\t League of Reflex \n"; bialy();
		if (zm2 == 3) { fioletowy(); }cout << "\t\t\t Lampki i Sandaly \n"; bialy();
		if (zm2 == 4) { fioletowy(); }cout << "\t\t\t Powrot \n"; bialy();
		z = _getch();

		if (z == 72)  zm2--;
		if (z == 80)  zm2++;
		if (zm2 == 0) zm2 += 4;
		if (zm2 == 5) zm2 -= 4;

		if ((z == 13) && (zm2 == 1))  Mlotki_jak_grac();
		if ((z == 13) && (zm2 == 2))  Test_reakcji_jak_grac();
		if ((z == 13) && (zm2 == 3))  Lampki_jak_grac();
		if ((z == 13) && (zm2 == 4)) Menu();
	}
}

void Tworca() {
	int zm3 = 1;
	while (1)
	{
		system("cls");									// Czyszczenie Ekranu

		cout << "\n\n\n\t\t\t\t      \n\n\n";
		cout << "\t\t\t Szybkie uderzenie       *****\n";
		cout << "\t\t\t League of Reflex            ***** Patrycja Jablonska\n";
		cout << "\t\t\t Lampki i Sandaly        *****\n\n";

		if (zm3 == 1) { fioletowy(); }cout << "\t\t\t Powrot \n"; bialy();
		z = _getch();


		if ((z == 13) && (zm3 == 1))  Menu();
	}
}


///Gry

/// Szybkie uderzenie ********************************************************************************************************************
void mlotki()
{
	mlotki_instrukcja_do_gry();
	mlotki_start();
	int licznik = 0;

	gracz = 1; // gracz 1 - Mysz, gracz 2 - M³otek
	//FUNKCJA ODLICZAJACA 1 MIN DO ZAKONCZENIA GRY
	chrono::steady_clock::time_point tend = std::chrono::steady_clock::now() + chrono::milliseconds(30000);
	do
	{
		system("cls");
		mlotki_grafika();

		// zmien kolej gracza
		gracz = (gracz % 2) ? 1 : 2;

		// wybierz pole do wstawienia znaku
		srand(time(NULL));
		if (gracz == 1) //mysz
		{
			wybor = (1 + rand() % 8);
		}

		else //mlotek
		{
			cout << "\n\t\t\t\t\t\tUDERZ W MYSZ: ";
			cin >> wybor;
			cout << "\n" << endl;
		}

		// przypisanie znaku do gracza( 'o' dla myszy, puste pole ' ' dla mlotka)
		znak = (gracz == 1) ? 'O' : ' ';

		//licznik punktow
		if (gracz == 2 && square[wybor] == 'O')
		{
			licznik++;
		}

		// wstaw znak w dan¹ kafelkê
		square[wybor] = znak;

		gracz++;

	} while (chrono::steady_clock::now() < tend);

	system("cls");
	cout << "\n\n\n\t\t\t\t\t\t      KONIEC CZASU! \n\n";
	cout << "\t\t\t\t\t\tTwoj wynik: | " << licznik << " | punktow \n\n\n";
	cout << "\t\t\t\t\tAby przejsc dalej nacisnij dowolny klawisz ... \n";
	_getch();
	mlotki_GameOver();
	licznik == 0;
}

//CZÊŒÆ WIZUALNA
void mlotki_grafika()
{
	cout << "\n\t\t\t\t\t     ****************************" << endl;
	cout << "\t\t\t\t\t     |  GRA: SZYBKIE UDERZENIE  |\n";
	cout << "\t\t\t\t\t     ****************************\n" << endl;
	cout << "\t\t\t\t\t        CZAS: | 30 | sekund   \n" << endl;
	cout << "\t\t\t\t\t    _________ _________ _________             _____________________\n";
	cout << "\t\t\t\t\t   |" << oznaczenie_pola[1] << "        |" << oznaczenie_pola[2] << "        |" << oznaczenie_pola[3] << "        |           /                     \\\n";
	cout << "\t\t\t\t\t   |         |         |         |           |                      \\\n";
	cout << "\t\t\t\t\t   |    " << square[1] << "    |    " << square[2] << "    |    " << square[3] << "    |           \\_______     __________ \\\n";
	cout << "\t\t\t\t\t   |         |         |         |                   |   |          \\_\\\n";
	cout << "\t\t\t\t\t   |_________|_________|_________|                   |   |\n";
	cout << "\t\t\t\t\t   |" << oznaczenie_pola[4] << "        |" << oznaczenie_pola[5] << "        |" << oznaczenie_pola[6] << "        |                   |   |\n";
	cout << "\t\t\t\t\t   |         |         |         |                   |   |\n";
	cout << "\t\t\t\t\t   |    " << square[4] << "    |    " << square[5] << "    |    " << square[6] << "    |                   |   |\n";
	cout << "\t\t\t\t\t   |         |         |         |                   |   |\n";
	cout << "\t\t\t\t\t   |_________|_________|_________|                   |   |\n";
	cout << "\t\t\t\t\t   |" << oznaczenie_pola[7] << "        |" << oznaczenie_pola[8] << "        |" << oznaczenie_pola[9] << "        |                   |   |\n";
	cout << "\t\t\t\t\t   |         |         |         |                   |   |\n";
	cout << "\t\t\t\t\t   |    " << square[7] << "    |    " << square[8] << "    |    " << square[9] << "    |                   |   |\n";
	cout << "\t\t\t\t\t   |         |         |         |                  /_____\\\n";
	cout << "\t\t\t\t\t   |_________|_________|_________|\n\n";
}

//INFORMACJE PRZED ROZPOCZECIEM GRY
void mlotki_instrukcja_do_gry()
{
	system("cls");
	cout << "\n\n\tZASADY GRY: Masz 30 sekund, aby trafic mlotkiem jak najwiecej myszy, ktore pojawiaja sie w kafelkach\n";
	cout << "\n\t\t\t\t\t STEROWANIE:  klawisze: 1-9 + ENTER \n\n\n";
	cout << "\t\t\t\t Aby wejsc do gry nacisnij dowolny klawisz ...\n\n\t\t\t\t\t\tMilej gry! :-)";
	_getch(); // Oczekiwanie na klawisz
}

//FUNKCJA ROZPOCZYNAJACE GRE PO WCISNIECIU DOWOLNEGO PRZYCISKU
void mlotki_start()
{
	system("cls");
	mlotki_grafika();
	cout << "\n\t\t\t\tAby rozpoczac gre nacisnij dowolny klawisz ...";
	_getch();
}

//FUNKCJA ZAPYTANIA CZY KONTYNUOWAC GRE W PRZYPADKU ZAKONCZENIA ROZGRYWKI
void mlotki_GameOver()
{
	char c;
	cout << "\n\n\n\t\t\t\t\t   GRASZ JESZCZE?(wybierz cyfre)\n";
	cout << "\t\t\t\t\t\t  1.Tak\n";
	cout << "\t\t\t\t\t\t  2.Nie\n";
	c = _getch();
	if (c == '1')
	{
		mlotki();
	}
	else if (c == '2')
	{
		Menu();
	}
	else
	{
		cout << "Prosze wybrac wlasciwa cyfre po wcisnieciu dowolnego przycisku: " << endl;
		_getch();
		mlotki_GameOver();
	}
}

/// L A M P K I  i   S A N D A L Y  ********************************************************************************************************************
//Lampki
void Lampki() {

	//srand(time(NULL));
	int losowa;
	losowa = rand() % 10 + 3;
	unsigned int start = clock();

	bialy();
	system("cls");
	cout << "gdy zmieni sie kolor wcisnij enter\n";
	cout << "\t\t\t\t\t\t        OOO      \n";
	cout << "\t\t\t\t\t\t       OOOOO       \n";
	cout << "\t\t\t\t\t\t      OOOOOOO       \n";
	cout << "\t\t\t\t\t\t       OOOOO       \n";
	cout << "\t\t\t\t\t\t        OOO     \n";
	Sleep(losowa * 1000);
	system("cls");

	start = clock();


	cout << "gdy zmieni sie kolor wcisnij enter\n";
	fioletowy();
	cout << "\t\t\t\t\t\t        OOO      \n";
	cout << "\t\t\t\t\t\t       OOOOO       \n";
	cout << "\t\t\t\t\t\t      OOOOOOO       \n";
	cout << "\t\t\t\t\t\t       OOOOO       \n";
	cout << "\t\t\t\t\t\t        OOO     \n";


	_getch();
	system("cls");
	bialy();
	cout << "Twoj czas reakcji: " << 0.001 * (clock() - start);
	_getch();

	GameOver();

}


/// L E A G U E   O F   R E F L E X *****************************************************************************************************************
void Test_reakcji()

{
	system("cls");
	int punkty = 0;


	fioletowy();
	cout << "\t\t\t\t\t         ******************\n";

	cout << "\t\t\t\t\t         |  "; bialy(); cout << "TEST REAKCJI"; fioletowy(); cout << "  |\n";
	cout << "\t\t\t\t\t         ******************\n";
	bialy();
	cout << "\n\n\t  ZASADY GRY:Wybierz odpowiedni klawisz z klawiatury, po tym jak zobaczysz go na ekranie!\n";

	cout << "\t\t\t\t\t        Masz tylko 10 sekund!\n";
	cout << "\t\t\t\t\t   Liczy sie szybkosc! POWODZENIA!\n";
	fioletowy();
	cout << "\n\t\t\t\t     Jesli chcesz rozpoczac gre wcisnij spacje... ";
	bialy();
	char przycisk = _getch();
	if (przycisk == ' ')
	{
		system("cls");


		chrono::steady_clock::time_point tend = std::chrono::steady_clock::now()
			+ chrono::milliseconds(10000);
		while (chrono::steady_clock::now() < tend)
		{


			fioletowy();
			char wylosowana;
			char wybrana;
			static const int ilosc_liter = 'z' - 'a';
			srand(time(NULL));
			wylosowana = rand() % (ilosc_liter + 1) + 'a';
			cout << "\t\t\t\t\t          *******************\n";
			cout << "\t\t\t\t\t          |  "; bialy(); cout << "TEST  REAKCJI"; fioletowy(); cout << "  |\n";
			cout << "\t\t\t\t\t          *******************\n";
			cout << "\n\n\n\n\n\n";
			cout << "        *                               *         * * * * * * * * * *         *                               *      \n";
			cout << "      *   *                           *   *       *                 *       *   *                           *   *    \n";
			cout << "    *       *                       *       *     *                 *     *       *                       *       *  \n";
			cout << "  *           *                   *           *   *                 *   *           *                   *           *\n";
			cout << "*               *               *               * *        "; bialy(); cout << wylosowana; fioletowy(); cout << "        * *               *               *               *\n";
			cout << "                  *           *                   *                 *                   *           *                 \n";
			cout << "                    *       *                     *                 *                     *       *                   \n";
			cout << "                      *   *                       *                 *                       *   *                     \n";
			cout << "                        *                         * * * * * * * * * *                         *                       \n\n";
			cout << "\t\t\t\t\t\t\t   ";
			wybrana = _getch();
			if (wybrana == wylosowana) punkty++;

			else punkty--;

			system("cls");
		}
		fioletowy();

		cout << "\n\n\n\t\t\t\t\tIlosc zdobytych punktow w tej grze to: " << punkty << "\n\n";

		if (punkty <= 0)
			cout << "\t\t\t\t\tChyba musisz jeszcze pocwiczyc... -_-\n";
		else if (punkty > 0 && punkty < 8)
			cout << "\t\t\t\t\tTo przecietny wynik, sprobuj jeszcze raz! ";
		else if (punkty >= 8 && punkty < 14)
			cout << "\t\t\t\t\tPoszlo ci calkiem niezle! Dobra robota! ";
		else
			cout << "\t\t\t\t\tWow!! Super wynik! Gratulacje! :)";
		bialy();
		cout << endl << endl;
		system("pause");
	}
	else
	{
		cout << "\n\n\t\t\t\t  Wyglada na to, ze nie chcesz zagrac w ta gre.. :(";
		Sleep(3000);
	}

	GameOver();
}



//zm4
void GameOver() {
	while (1)
	{
		system("cls");
		bialy();
		cout << "\n\n\n\n\t\t\t      Koniec Gry\n\n\n\t\t\t   Moze jeszcze jedna rundka?\n";
		if (zm4 == 1) { fioletowy(); cout << "\t\t\t\t Tak "; }
		if (zm4 == 1) { bialy(); cout << "\t\t\t\t  Nie"; }
		if (zm4 == 2) { bialy(); cout << "\t\t\t\t  Tak"; }
		if (zm4 == 2) { fioletowy(); cout << "\t\t\t\t Nie "; }
		z = _getch();

		if (z == 75) zm4--;
		if (z == 77) zm4++;
		if (zm4 == 0) zm4 += 2;
		if (zm4 == 3) zm4 -= 2;
		if ((z == 13) && (zm4 == 2))  Menu();
		if ((z == 13) && (zm4 == 1))  Graj();
	}
}

//Graficzne
void fioletowy()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED);
}

void bialy()
{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}
//Zasady gry
void Mlotki_jak_grac()
{
	int zm = 1;
	while (1)
	{
		system("cls");									// Czyszczenie Ekranu

		cout << "\n\n\t\t\t\t\tZlikwiduj wszystkie pojawiajace sie myszy!\n";
		cout << "\n\n\tZASADY GRY: Masz 30 sekund, aby trafic mlotkiem jak najwiecej myszy, ktore pojawiaja sie w kafelkach\n";
		cout << "\n\t\t\t\t\t STEROWANIE:  klawisze: 1-9 + ENTER \n\n\n";

		if (zm == 1) { fioletowy(); }printf("\t\t\t\t\t\t\t Powrot \n"); bialy();
		z = _getch();

		if ((z == 13) && (zm == 1))  Jak_grac();
	}
}

void Test_reakcji_jak_grac()
{
	int zm = 1;
	while (1)
	{
		system("cls");									// Czyszczenie Ekranu

		cout << "\n\n\t\t\t\t\t\tSprawdz swoj refleks!\n";
		cout << "\n\n\t\t\tZASADY GRY: gdy na ekranie pojawi sie dany znak wcisnij go na klawiaturze\n";
		cout << "\n\t\t\t\t\t STEROWANIE:  znaki z klawiatury \n\n\n";

		if (zm == 1) { fioletowy(); }printf("\t\t\t\t\t\t\t Powrot \n"); bialy();
		z = _getch();

		if ((z == 13) && (zm == 1))  Jak_grac();
	}
}

void Lampki_jak_grac()
{
	int zm = 1;
	while (1)
	{
		system("cls");									// Czyszczenie Ekranu

		cout << "\n\n\t\t\t\t\t\tSprawdz swoj refleks!\n";
		cout << "\n\n\t\t\tZASADY GRY: gdy zmieni sie kolor z bialego na fioletowy wcisnij enter\n";
		cout << "\n\t\t\t\t\t   Obok wyswietli sie czas reakcji\n";
		cout << "\n\t\t\t\t\t\t STEROWANIE:  ENTER \n\n\n";

		if (zm == 1) { fioletowy(); }printf("\t\t\t\t\t\t\t Powrot \n"); bialy();
		z = _getch();

		if ((z == 13) && (zm == 1))  Jak_grac();
	}
}
