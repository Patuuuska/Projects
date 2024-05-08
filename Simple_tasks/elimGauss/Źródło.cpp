#include <iostream>
#include <cmath>

using namespace std;

const int N = 5; // liczba niewiadomych

void printMatrix(float A[][N + 1]) //wyswietlanie macierzy
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= N; j++)
            cout << A[i][j] << " ";

        cout << endl;
    }
}

float* ElimGauss(float A[][N + 1])
//funkcja eliminacji Gaussa przyjmuje macierz A jako argument i zwraca wska?nik na wektor solution
{
    float x[N]; //przechowywania wyników rozwi?zania równania

    for (int i = 0; i < N; i++)
    {
        //szukamy maksymalnej warto?ci w kolumnie i
        int maxRow = i;
        for (int j = i + 1; j < N; j++)
            if (abs(A[j][i]) > abs(A[maxRow][i]))
                maxRow = j;

        //zamieniamy wiersze, aby najwi?kszy element znalaz? si? na przek?tnej
        for (int j = i; j <= N; j++)
            swap(A[maxRow][j], A[i][j]);

        //eliminacja Gaussa
        for (int j = i + 1; j < N; j++)
        {
            float factor = A[j][i] / A[i][i];
            for (int k = i; k <= N; k++)
                A[j][k] -= factor * A[i][k];
        }
    }

    //obliczamy wyniki dla niewiadomych
    for (int i = N - 1; i >= 0; i--)
    {
        x[i] = A[i][N];
        for (int j = i + 1; j < N; j++)
            x[i] -= A[i][j] * x[j];

        x[i] /= A[i][i];
    }

    //tworzymy dynamicznie wektor solution i zwracamy go
    float* solution = new float[N];
    for (int i = 0; i < N; i++)
    {
        solution[i] = x[i];
    }

    return solution;

    
}


int main()
{
    float A[N][N + 1] = { //tworzymy macierz A
            {1, -3, 4, 6.8, 9, 74.64},
            {-3, 2, 4.6, 6.3, -10, -40.26},
            {2, -1, 2.8, -8.4, -5, -2.32},
            {-6, 2, 7, -0.5, -0.9, 12.6},
            {5, -2, -0.5, 12,-4, -8.9}
    };
    printMatrix(A); //wyswietlanie macierzy

    float* solution = ElimGauss(A); 
    //rozwi?zujemy równanie za pomoc? funkcji ElimGauss i zapisujemy wyniki w wektorze solution

  //wy?wietlamy wyniki dla niewiadomych
    
    cout << endl<< "Rozwiazanie:" << endl;
    for (int i = 0; i < N; i++)
        cout << "x" << i + 1 << " = " << solution[i] << endl;

    delete[] solution; //zwalnianie pami?ci

    return 0;
}

