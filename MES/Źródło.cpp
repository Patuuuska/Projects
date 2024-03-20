#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip> 
#include <vector>

using namespace std;

const double eps = 1e-12; // stała przybliżenia zera

bool eliminategauss(int n, double** AB, double* X)// za pomocą tej funkcji wykonuje się cały algorytm eliminacji gaussa
{
    double m, s;

    // przy pomocy poniższych forów eliminuje współczynniki 
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(AB[i][i]) < eps)
            {
                return false;
            }
            m = -AB[j][i] / AB[i][i];
            AB[j][i] = 0;
            for (int k = i + 1; k <= n; k++)
            {
                AB[j][k] += m * AB[i][k];
            }
        }
    }

    // przy pomocy poniższych forów wyliczam niewiadome

    for (int i = n - 1; i >= 0; i--)
    {
        s = AB[i][n];

        for (int j = n - 1; j >= i + 1; j--)
        {
            s -= AB[i][j] * X[j];
        }
        if (fabs(AB[i][i]) < eps)
        {
            return false;
        }

        X[i] = s / AB[i][i];
    }

    return true;
}

struct GlobalData {
    int sim_time;
    int sim_step_time;
    int con;
    int alfa;
    int tot;
    int in_temp;
    int den;
    int spec_heat;
    int nn;
    int en;

    void read() {
      // ifstream file("Test1_4_4.txt");
       ifstream file("Test2_4_4_MixGrid.txt");
        // ifstream file("Test3_31_31_kwadrat.txt");
        // ifstream file("Test4_31_31_trapez.txt");


        if (!file.is_open()) {
            cerr << "File can't be read" << endl;
            return;
        }

        string line;

        while (getline(file, line)) {
            istringstream iss(line); //strumien gdzie zdanie przechowywane jest w line
            string word;
            iss >> word; // 1 slowo

            if (word == "SimulationTime") iss >> sim_time; //kolejne slowo do zmiennej
            else if (word == "SimulationStepTime") iss >> sim_step_time;
            else if (word == "Conductivity") iss >> con;
            else if (word == "Alfa") iss >> alfa;
            else if (word == "Tot") iss >> tot;
            else if (word == "InitialTemp") iss >> in_temp;
            else if (word == "Density") iss >> den;
            else if (word == "SpecificHeat") iss >> spec_heat;
            else if (word == "Nodes") {
                string pom;
                iss >> pom;
                if (pom == "number") iss >> nn;
            }
            else if (word == "Elements") {
                string pom;
                iss >> pom;
                if (pom == "number") iss >> en;
            }
        }
    }

    void print() {
        cout << "SimulationTime: " << sim_time << endl;
        cout << "SimulationStepTime: " << sim_step_time << endl;
        cout << "Conductivity: " << con << endl;
        cout << "Alfa: " << alfa << endl;
        cout << "Tot: " << tot << endl;
        cout << "InitialTemp: " << in_temp << endl;
        cout << "Density: " << den << endl;
        cout << "SpecificHeat: " << spec_heat << endl;
        cout << "Nodes number: " << nn << endl;
        cout << "Elements number: " << en << endl;
    }
};

class Node {
public:
    double x;
    double y;
    int BC;

    double get_x() {
        return x;
    }

    double get_y() {
        return y;
    }

    int get_bc() {
        return BC;
    }


};

struct Element {
    int nodes[4];
    double H[4][4];
    double H_bc[4][4];
    double P[4];
    double H_sum[4][4];
    double C[4][4];
public:
    Element() {
        for (int a = 0; a < 4; a++)
        {
            for (int b = 0; b < 4; b++) {
                H[a][b] = 0.0;
                H_bc[a][b] = 0.0;
                H_sum[a][b] = 0.0;
                C[a][b] = 0.0;
            }
        }
        for (int a = 0; a < 4; a++) {
            P[a] = 0;
        }
    }

    int get_nodes(int index) {
        return nodes[index];
    }

    void set_H(int i, int j, double h) {
        H[i][j] += h;
    }
    double get_H(int i, int j) {
        return H[i][j];
    }

    void set_H_bc(int i, int j, double hbc) {
        H_bc[i][j] += hbc;
    }
    double get_H_bc(int i, int j) {
        return H_bc[i][j];
    }
    void set_H_sum(int i, int j, double hsum) {
        H_sum[i][j] += hsum;
    }
    double get_H_sum(int i, int j) {
        return H_sum[i][j];
    }
    void set_P(int i, double p) {
        P[i] += p;
    }
    double get_P(int i) {
        return P[i];
    }
    void set_C(int i, int j, double c) {
        C[i][j] += c;
    }
    double get_C(int i, int j) {
        return C[i][j];
    }

};

class Gauss {
    int number_pc;
    double* points;
    double* weights;

public:
    Gauss() {
        number_pc = 0;
        points = nullptr;
        weights = nullptr;
    }

    Gauss(int pc, double* array_points, double* array_weights) {
        number_pc = pc;
        points = array_points;
        weights = array_weights;
    }

    int get_number_pc() {
        return number_pc;
    }

    double get_point(int index) {
        return points[index];
    }

    double get_weight(int index) {
        return weights[index];
    }
};

class Surface {
public:
    double* ksi;
    double* eta;
    double* weights;
    double** shapes_function_values;
};
class UniversalElement {
public:
    Gauss gauss;
    double** dN_dKsi;
    double** dN_dEta;
    double** shapes_function_values;
    Surface* surface = new Surface[4];

    void set_Element(Gauss gauss) {
        this->gauss = gauss;
        int points_number = gauss.get_number_pc() * gauss.get_number_pc();

        // Alokacja pamięci dla tablic dynamicznych
        dN_dKsi = new double* [points_number];
        dN_dEta = new double* [points_number];
        shapes_function_values = new double* [points_number];

        for (int i = 0; i < points_number; i++) {
            dN_dKsi[i] = new double[4];
            dN_dEta[i] = new double[4];
            shapes_function_values[i] = new double[4]; // ilość funkcji kształtu to zawsze 4
        }

        // Pętle iterujące przez punkty całkowania w kierunku ksi i eta
        for (int i = 0; i < gauss.get_number_pc(); i++) {
            for (int j = 0; j < gauss.get_number_pc(); j++) {
                // Obliczenia dla dN_deta
                int index = i * gauss.get_number_pc() + j;
                if (index < points_number) {
                    dN_dEta[index][0] = -(1.0 / 4.0) * (1 - gauss.get_point(i));
                    dN_dEta[index][1] = (1.0 / 4.0) * (1 - gauss.get_point(i));
                    dN_dEta[index][2] = (1.0 / 4.0) * (1 + gauss.get_point(i));
                    dN_dEta[index][3] = -(1.0 / 4.0) * (1 + gauss.get_point(i));
                }

                // Obliczenia dla dN_dksi
                if (index < points_number) {
                    dN_dKsi[index][0] = -(1.0 / 4.0) * (1 - gauss.get_point(j));
                    dN_dKsi[index][1] = -(1.0 / 4.0) * (1 + gauss.get_point(j));
                    dN_dKsi[index][2] = (1.0 / 4.0) * (1 + gauss.get_point(j));
                    dN_dKsi[index][3] = (1.0 / 4.0) * (1 - gauss.get_point(j));
                }

                // Obliczenia dla shapes_function_values potrzebne do c
                if (index < points_number) {
                    shapes_function_values[index][0] = (1.0 / 4.0) * (1 - gauss.get_point(j)) * (1 - gauss.get_point(i));
                    shapes_function_values[index][1] = (1.0 / 4.0) * (1 + gauss.get_point(j)) * (1 - gauss.get_point(i));
                    shapes_function_values[index][2] = (1.0 / 4.0) * (1 + gauss.get_point(j)) * (1 + gauss.get_point(i));
                    shapes_function_values[index][3] = (1.0 / 4.0) * (1 - gauss.get_point(j)) * (1 + gauss.get_point(i));

                }
                cout << "N: ksi:" << gauss.get_point(j) << "\t";
                cout << "eta:" << gauss.get_point(i) << endl;

            }
        }
        /*cout << "funkcje ksztaltu:" << endl;
         for (int j = 0; j < 4; j++) {
             for (int i = 0; i < 4; i++) {

                 cout << shapes_function_values[j][i] << "\t";

             }
             cout << endl;
         }*/

        for (int i = 0; i < 4; i++) {
            surface[i].ksi = new double[gauss.get_number_pc()];
            surface[i].eta = new double[gauss.get_number_pc()];
            surface[i].weights = new double[gauss.get_number_pc()];
            surface[i].shapes_function_values = new double* [gauss.get_number_pc()];
            for (int j = 0; j < gauss.get_number_pc(); j++) {
                surface[i].shapes_function_values[j] = new double[4];
            }
        }

        for (int i = 0; i < gauss.get_number_pc(); i++) {
            surface[0].ksi[i] = gauss.get_point(i);
            surface[0].eta[i] = -1;
            surface[0].weights[i] = gauss.get_weight(i);
        }

        for (int i = 0; i < gauss.get_number_pc(); i++) {
            surface[1].ksi[i] = 1;
            surface[1].eta[i] = gauss.get_point(i);
            surface[1].weights[i] = gauss.get_weight(i);
        }

        for (int i = 0; i < gauss.get_number_pc(); i++) {
            surface[2].ksi[i] = -gauss.get_point(i);
            surface[2].eta[i] = 1;
            surface[2].weights[i] = gauss.get_weight(i);
        }

        for (int i = 0; i < gauss.get_number_pc(); i++) {
            surface[3].ksi[i] = -1;
            surface[3].eta[i] = -gauss.get_point(i);
            surface[3].weights[i] = gauss.get_weight(i);
        }

        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < gauss.get_number_pc(); i++) {
                surface[j].shapes_function_values[i][0] = (1.0 / 4.0) * (1.0 - surface[j].ksi[i]) * (1.0 - surface[j].eta[i]);
                surface[j].shapes_function_values[i][1] = (1.0 / 4.0) * (1.0 + surface[j].ksi[i]) * (1.0 - surface[j].eta[i]);
                surface[j].shapes_function_values[i][2] = (1.0 / 4.0) * (1.0 + surface[j].ksi[i]) * (1.0 + surface[j].eta[i]);
                surface[j].shapes_function_values[i][3] = (1.0 / 4.0) * (1.0 - surface[j].ksi[i]) * (1.0 + surface[j].eta[i]);
            }
        }
    }

    void show_ksi_eta() {
        int points_number = gauss.get_number_pc() * gauss.get_number_pc();

        cout << "\n* * * dN_dKsi * * *\n";
        cout << "\tN1 \t\tN2 \t\tN3 \t\tN4\n";
        for (int i = 0; i < points_number; i++) {
            cout << i + 1 << " | ";
            cout << "\t" << dN_dKsi[i][0] << " | ";
            cout << "\t" << dN_dKsi[i][1] << " | ";
            cout << "\t" << dN_dKsi[i][2] << " | ";
            cout << "\t" << dN_dKsi[i][3] << endl;
        }
        cout << "\n* * * dN_dEta * * *\n";
        cout << "\tN1 \t\tN2 \t\tN3 \t\tN4\n";
        for (int i = 0; i < points_number; i++) {
            cout << i + 1 << " | ";
            cout << "\t" << dN_dEta[i][0] << " | ";
            cout << "\t" << dN_dEta[i][1] << " | ";
            cout << "\t" << dN_dEta[i][2] << " | ";
            cout << "\t" << dN_dEta[i][3] << endl;
        }

    }

    ~UniversalElement() {
        for (int i = 0; i < gauss.get_number_pc() * gauss.get_number_pc(); i++) {
            delete[] dN_dKsi[i];
            delete[] dN_dEta[i];
            delete[] shapes_function_values[i];
        }
        delete[] dN_dKsi;
        delete[] dN_dEta;
        delete[] shapes_function_values;
    }

};


class Jakobian {
    UniversalElement ele;
    double jakobian[2][2];
    double reverse_jakobian[2][2];
    double det;
    double** dN_dx;
    double** dN_dy;
    Element element;
    GlobalData global;


public:

    double get_reverse_jakobian(int i, int j) {
        return reverse_jakobian[i][j];
    }

    double get_det() {
        return det;
    }



    void calculate_jakobian(Node* nodes, Element* elements, UniversalElement& universalElement, int index, int indexi) {
        double* dN_dKsi = universalElement.dN_dKsi[index];
        double* dN_dEta = universalElement.dN_dEta[index];

        double x0 = nodes[elements[indexi].nodes[0]].get_x();
        double x1 = nodes[elements[indexi].nodes[1]].get_x();
        double x2 = nodes[elements[indexi].nodes[2]].get_x();
        double x3 = nodes[elements[indexi].nodes[3]].get_x();

        double y0 = nodes[elements[indexi].nodes[0]].get_y();
        double y1 = nodes[elements[indexi].nodes[1]].get_y();
        double y2 = nodes[elements[indexi].nodes[2]].get_y();
        double y3 = nodes[elements[indexi].nodes[3]].get_y();

        jakobian[0][0] = dN_dKsi[0] * y0 + dN_dKsi[1] * y1 + dN_dKsi[2] * y2 + dN_dKsi[3] * y3;
        jakobian[0][1] = dN_dEta[0] * y0 + dN_dEta[1] * y1 + dN_dEta[2] * y2 + dN_dEta[3] * y3;
        jakobian[1][0] = dN_dKsi[0] * x0 + dN_dKsi[1] * x1 + dN_dKsi[2] * x2 + dN_dKsi[3] * x3;
        jakobian[1][1] = dN_dEta[0] * x0 + dN_dEta[1] * x1 + dN_dEta[2] * x2 + dN_dEta[3] * x3;

        det = (jakobian[1][1] * jakobian[0][0]) - (jakobian[1][0] * jakobian[0][1]);

        reverse_jakobian[0][0] = jakobian[0][0] / det;
        reverse_jakobian[0][1] = -jakobian[0][1] / det;
        reverse_jakobian[1][0] = -jakobian[1][0] / det;
        reverse_jakobian[1][1] = jakobian[1][1] / det;
    }

    void show_jakobian() {
        cout << "jakobian:\n";
        cout << endl << jakobian[0][0] << "\t\t";
        cout << jakobian[0][1] << endl;
        cout << jakobian[1][0] << "\t\t";
        cout << jakobian[1][1] << endl;

        cout << endl << "det:" << det << endl;
    }

    double calculate_detJ(Node node1, Node node2) {
        return sqrt(pow(node1.get_x() - node2.get_x(), 2) + pow(node1.get_y() - node2.get_y(), 2));
    }


};



class Grid {

    Element* elements;
    Node* nodes;
    Gauss gauss;
    UniversalElement element;
    string linebc;
    GlobalData global;

    void readne(const GlobalData& globalData) {
        //ifstream file("Test1_4_4.txt");
        ifstream file("Test2_4_4_MixGrid.txt");
         // ifstream file("Test3_31_31_kwadrat.txt");
          //  ifstream file("Test4_31_31_trapez.txt");
        if (!file.is_open()) {
            cerr << "File can't be read" << endl;
            return;
        }

        string line;

        while (getline(file, line)) {
            if (line == "*Node") {
                nodes = new Node[globalData.nn + 1];
                for (int i = 1; i <= globalData.nn; i++) {
                    getline(file, line);
                    istringstream iss(line);
                    int n;
                    double x, y;
                    char c;
                    iss >> n >> c >> x >> c >> y;
                    nodes[i].x = x;
                    nodes[i].y = y;
                    nodes[i].BC = 0;
                }
            }
            else if (line.find("*Element") != string::npos) {
                elements = new Element[globalData.en];
                for (int i = 0; i < globalData.en; i++) {
                    getline(file, line);
                    istringstream iss(line);
                    int n;
                    int a, b, c, d;
                    char ch;
                    iss >> n >> ch >> a >> ch >> b >> ch >> c >> ch >> d;
                    elements[i].nodes[0] = a;
                    elements[i].nodes[1] = b;
                    elements[i].nodes[2] = c;
                    elements[i].nodes[3] = d;
                }
            }
            else if (line == "*BC") {
                getline(file, linebc);
                // Zamień przecinki na spacje
                for (char& c : linebc) {
                    if (c == ',') {
                        c = ' ';
                    }
                }
                // Utwórz strumień wejścia ze zmienionej linii
                istringstream stream(linebc);

                // Wczytaj liczby do wektora
                vector<int> numbers;
                int num;
                while (stream >> num) {
                    numbers.push_back(num);
                }
                // Przypisanie 1 do bc prez wektor liczb
                for (int n : numbers) {
                    nodes[n].BC = 1;
                }


            }

        }
    }

    void printne(const GlobalData& globalData) {
        int pom = elements[0].nodes[0];

        cout << "Nodes: \n";

        for (int i = 1; i <= globalData.nn; i++) {

            cout << i << ". = [ " << nodes[i].x << ", " << nodes[i].y << " ] " << "BC = " << nodes[i].BC << "\n";
        }
        cout << "Elements: \n";
        for (int i = 0; i < globalData.en; i++) {
            int j = i + 1;
            cout << j << ". = [ " << elements[i].nodes[0] << ", " << elements[i].nodes[1] << ", " << elements[i].nodes[2] << ", " << elements[i].nodes[3] << " ]\n";
        }
        cout << "BC: \n";
        cout << linebc << endl;
    }

public:
    Grid(Gauss g) {
        gauss = g;

        GlobalData global;
        global.read();
        global.print();
        readne(global);
        printne(global);
        UniversalElement element;
        element.set_Element(gauss);
        element.show_ksi_eta();
        int points_number = gauss.get_number_pc() * gauss.get_number_pc();
        Jakobian jakob;
        double** dN_dx = new double* [points_number];  // 4x tablica dla dN_dx
        double** dN_dy = new double* [points_number];// 4xpktcalk^2 tablica dla dN_dy
        for (int d = 0; d < points_number; d++) {
            dN_dx[d] = new double[4];
            dN_dy[d] = new double[4];
        }


        double H[4][4] = { 0 };

        for (int i = 0; i < global.en; i++) {//po elemnetach jedziemy

            cout << "***************Dla nowego elementu:***************:" << i + 1 << endl;



            double* pom_det = new double[points_number];
            for (int j = 0; j < points_number; j++) {//po pkt calkowania
                cout << "\n***Dla punku calkowania:***:" << j + 1 << endl;
                jakob.calculate_jakobian(nodes, elements, element, j, i);
                jakob.show_jakobian();
                pom_det[j] = jakob.get_det();

                double* dN_dKsi = element.dN_dKsi[j];
                double* dN_dEta = element.dN_dEta[j];
                for (int k = 0; k < 4; k++) {

                    dN_dx[j][k] = jakob.get_reverse_jakobian(0, 0) * dN_dEta[k]
                        + jakob.get_reverse_jakobian(0, 1) * dN_dKsi[k];
                    dN_dy[j][k] = jakob.get_reverse_jakobian(1, 0) * dN_dEta[k]
                        + jakob.get_reverse_jakobian(1, 1) * dN_dKsi[k];

                }

            }

            //do liczenia  dN//dN_dx i dN/dN_dy trzeba wykorzystac dN/dKsi i dN/dEta i jakobian przeksztalcenia
           /*cout << endl << "dN_dx:\n";
            for (int i = 0; i < points_number; i++) {
                for (int j = 0; j < 4; j++) {
                    cout << dN_dx[i][j] << "\t";
                }
                cout << endl;
            }

            cout << endl << "dN_dy:\n";
            for (int i = 0; i < points_number; i++) {
                for (int j = 0; j < 4; j++) {
                    cout << dN_dy[i][j] << "\t";
                }
                cout << endl;
            }*/ 

            for (int punkty_c = 0; punkty_c < points_number; punkty_c++) {

                double resultX[4][4];
                // Mnożenie  wiersza x przez transponowany  wiersz x
                for (int a = 0; a < 4; ++a) {
                    for (int j = 0; j < 4; ++j) {
                        resultX[a][j] = dN_dx[punkty_c][a] * dN_dx[punkty_c][j];
                    }
                }
                // Mnożenie wiersza y przez transponowany  wiersz y
                double resultY[4][4];
                for (int a = 0; a < 4; ++a) {
                    for (int j = 0; j < 4; ++j) {
                        resultY[a][j] = dN_dy[punkty_c][a] * dN_dy[punkty_c][j];
                    }
                }
                double resultSum[4][4];
                for (int a = 0; a < 4; a++) {
                    for (int j = 0; j < 4; j++) {
                        resultSum[a][j] = global.con * (resultX[a][j] + resultY[a][j]) * pom_det[punkty_c];
                        //calkowanie H to mnozenie przez pom_det
                    }
                }
                //Macierz H reprezentuje równanie Fouriera. Mówi o przewodzeniu ciepla wewnatrz elementu
                //macierz h
                for (int a = 0; a < 4; ++a) {
                    for (int j = 0; j < 4; ++j) {
                        elements[i].set_H(a, j, (resultSum[a][j] * (gauss.get_weight(punkty_c / gauss.get_number_pc())) * gauss.get_weight(punkty_c % gauss.get_number_pc())));
                    }
                }

                //macierz c
//informuje ile ciepla moze zmagazynowac element skonczony
                for (int k = 0; k < 4; k++) {
                    for (int l = 0; l < 4; l++) {
                        //wykorzystuje sie (w odroznieniu od macierzy H) wartosci funkcji ksztaltu a nie ich pochodne
                        elements[i].set_C(k, l, (global.den * global.spec_heat * (element.shapes_function_values[punkty_c][k]) * (element.shapes_function_values[punkty_c][l]) * pom_det[punkty_c] * (gauss.get_weight(punkty_c / gauss.get_number_pc()) * gauss.get_weight(punkty_c % gauss.get_number_pc()))));
                    }
                }

            }
             cout << "\n****Glowna Macierz H:****\n";
            for (int a = 0; a < 4; a++) {
                for (int b = 0; b < 4; b++) {
                    cout << elements[i].get_H(a, b) << "\t";
                }
                cout << endl;
            }
           

            cout << endl;
            for (int n = 0; n < 4; n++) {
                int node1 = elements[i].get_nodes(n);
                int node2 = elements[i].get_nodes((n + 1) % 4); // ostatni zeby byl 0 a nie 4

                if (nodes[node1].get_bc() && nodes[node2].get_bc()) {
                    //jakobian H_bc mowi o stosunku powierzchni dla danego punktu calkowania w ukladzie globalnym (x i y) do powierzchni tego punktu w ukladzie lokalny 
                    double det_J = jakob.calculate_detJ(nodes[node1], nodes[node2]) / 2.0; //det to dlugosc odcinka miedzy nodami

                    for (int j = 0; j < element.gauss.get_number_pc(); j++) {
                        for (int k = 0; k < 4; k++) {
                            for (int l = 0; l < 4; l++) {
                                //macierz Hbc opisuje zachowanie materialu na brzegu, obliczana jest wartosc calki po powierzchni

                                elements[i].set_H_bc(k, l, (global.alfa * element.surface[n].weights[j] * (element.surface[n].shapes_function_values[j][k]) * (element.surface[n].shapes_function_values[j][l]) * det_J));
                            }
                            //wektor P odnosi sie do drugiego waruku brzegowego,jak wplywa otaczajaca temp. na sciany materialu
                                                       // wektor P to alfa * temp otoczenia
                            elements[i].set_P(k, (global.alfa * det_J * global.tot * element.surface[n].weights[j] * (element.surface[n].shapes_function_values[j][k])));

                        }

                    }
                }
            }
            cout << "\n**** Macierz H_bc:****\n";
            for (int a = 0; a < 4; a++) {
                for (int j = 0; j < 4; j++) {
                    cout << elements[i].get_H_bc(a, j) << "\t";
                }
                cout << endl;
            }
            cout << "\nWektor P:" << endl;
            for (int j = 0; j < 4; j++)
            {
                if (j < 3)
                    cout << elements[i].P[j] << ", ";
                else
                    cout << elements[i].P[j] << endl;
            }
            



            for (int n = 0; n < 4; n++) {
                for (int m = 0; m < 4; m++) {
                    elements[i].set_H_sum(n, m, (elements[i].get_H(n, m) + elements[i].get_H_bc(n, m)));
                }
            }
            cout << "\n**** Macierz H_sum:****\n";
            for (int a = 0; a < 4; a++) {
                for (int j = 0; j < 4; j++) {
                    cout << elements[i].get_H_sum(a, j) << "\t";
                }
                cout << endl;
            }

               cout << "\n**** Macierz C lokalnie:****\n";
            for (int a = 0; a < 4; a++) {
                for (int b = 0; b < 4; b++) {
                    cout << elements[i].get_C(a, b) << "\t";
                }
                cout << endl;
            }

        }
        //koniec petli elementow i zaczynamy globalnie liczyc
        double** H_global;
        int pom = global.nn;
        H_global = new double* [pom];
        for (int a = 0; a < pom; a++) {
            H_global[a] = new double[pom];
            for (int j = 0; j < pom; j++) {
                H_global[a][j] = 0.0; //inicjalizacja tab global_h i 0 wypelniamy
            }
        }
        for (int i = 0; i < global.en; i++)
        {
            //agregacja - H lokalne dodawane sa w miejsca wspolrzednych globalnych elementow
            for (int n = 0; n < 4; n++) {
                for (int m = 0; m < 4; m++) { //-1 bo elementy sa od 1 do 16 a ja chce wypelniac tablice od 0
                    H_global[elements[i].get_nodes(n) - 1][elements[i].get_nodes(m) - 1] += elements[i].get_H_sum(n, m);
                }
            }
        }
        cout << "\n**** Macierz H_global:****\n";
        for (int a = 0; a < pom; a++) {
            for (int j = 0; j < pom; j++) {
                cout << H_global[a][j] << " ";
            }
            cout << endl;
        }
        



        double* P_global;
        P_global = new double[pom];
        for (int i = 0; i < pom; i++) {
            P_global[i] = 0.0;
        }

        for (int i = 0; i < global.en; i++) {
            for (int j = 0; j < 4; j++) {
                P_global[elements[i].get_nodes(j) - 1] += elements[i].get_P(j);
            }
        }
        /* cout << "\n**** Macierz P_global:****\n";
        for (int a = 0; a < pom; a++) {

            if (a < pom - 1)
                cout << P_global[a] << ", ";
            else
                cout << P_global[a] << endl;

        }*/
       


        double** C_global;
        C_global = new double* [pom];
        for (int a = 0; a < pom; a++) {
            C_global[a] = new double[pom];
            for (int j = 0; j < pom; j++) {
                C_global[a][j] = 0.0;
            }
        }
        for (int i = 0; i < global.en; i++)
        {
            for (int n = 0; n < 4; n++) {
                for (int m = 0; m < 4; m++) { //-1 bo elementy sa od 1 do 16 a ja chce wypelniac tablice od 0
                    C_global[elements[i].get_nodes(n) - 1][elements[i].get_nodes(m) - 1] += elements[i].get_C(n, m);
                }
            }
        }


        double min, max;
        double* t1;
        t1 = new double[pom];
        for (int ilosc = 1; ilosc <= 10; ilosc++) {
            double** C_koniec;
            double** HC_koniec;
            double* C_dt;
            double* P_koniec;
            C_koniec = new double* [pom];
            HC_koniec = new double* [pom];
            P_koniec = new double[pom];
            C_dt = new double[pom];

            for (int a = 0; a < pom; a++) {
                C_koniec[a] = new double[pom];
                HC_koniec[a] = new double[pom];
                P_koniec[a] = 0.0;
                C_dt[a] = 0.0;
                for (int j = 0; j < pom; j++) {
                    C_koniec[a][j] = 0.0;
                    HC_koniec[a][j] = 0.0;
                }
            }

            for (int a = 0; a < pom; a++) {
                for (int b = 0; b < pom; b++) {
                    C_koniec[a][b] = C_global[a][b] / global.sim_step_time; ///c_global przez dettet
                }
            }

            for (int a = 0; a < pom; a++) {
                for (int b = 0; b < pom; b++) {
                    HC_koniec[a][b] = C_koniec[a][b] + H_global[a][b]; //pierwszy czlon rownania
                }
            }
             if (ilosc == 1) {
                cout << "\n**** Macierz [H] + [C]_dT:****\n";
                for (int a = 0; a < pom; a++) {
                    for (int j = 0; j < pom; j++) {
                        cout << HC_koniec[a][j] << " ";
                    }
                    cout << endl;
                }
            }
           

            for (int a = 0; a < pom; a++) {
                for (int b = 0; b < pom; b++) {
                    if (ilosc == 1)
                        C_koniec[a][b] *= global.in_temp;
                    else
                        C_koniec[a][b] *= t1[b];

                    C_dt[a] += C_koniec[a][b]; //suma wiersza c_koniec
                }
            }



            for (int a = 0; a < pom; a++)
            {
                P_koniec[a] = P_global[a] + C_dt[a];
            }
            if (ilosc == 1) {
                cout << "\n**** Macierz BC:****\n";
                for (int a = 0; a < pom; a++) {
                    cout << P_koniec[a] << " ";
                }
                cout << endl;
            }


            double* X;

            // tworzenie tablicy dynamicznej
            double** AB;
            AB = new double* [pom];
            for (int i = 0; i < pom; i++)
            {
                AB[i] = new double[pom + 1];
            }

            // Przypisywanie wartości z macierzy HC_koniec
            for (int x = 0; x < pom; x++) {
                for (int y = 0; y < pom; y++) {
                    AB[x][y] = HC_koniec[x][y];
                }
            }

            // Przypisywanie wartości z wektora P_koniec
            for (int x = 0; x < pom; x++) {
                AB[x][pom] = P_koniec[x];
            }

            X = new double[pom];

            eliminategauss(pom, AB, X); // uruchamiamy eliminację gaussa

            for (int i = 0; i < pom; i++)
            {
                t1[i] = 0.0;
            }

            for (int i = 0; i < pom; i++)
            {
                t1[i] = X[i];
                cout << X[i] << endl;
            }

            min = X[0];
            max = X[0];


            //szukanie max min
            for (int i = 1; i < pom; i++)
            {
                if (X[i] > max)
                {
                    max = X[i];
                }
                else if (X[i] < min)
                {
                    min = X[i];
                }
            }

            cout << endl;
            cout << "Time = " << global.sim_step_time * ilosc << ", Min_t = " << min << ", Max_t = " << max << endl;

            for (int i = 0; i < pom; i++)
            {
                delete[] AB[i];
            }
            delete[] X;
        }

    }
};


int main() {
    double points_2D[] = { (-1.0) / sqrt(3.0), (1.0) / sqrt(3.0) };
    double weights_2D[] = { 1.0, 1.0 };
    Gauss gauss_2D(2, points_2D, weights_2D);

    double points_3D[] = { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) };
    double weights_3D[] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
    Gauss gauss_3D(3, points_3D, weights_3D);

    double points_4D[] = { ((sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))) * -1.0), ((sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0))) * -1.0),
        (sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0))), (sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))) };

    double weights_4D[] = { ((18.0 - sqrt(30.0)) / 36) , ((18.0 + sqrt(30.0)) / 36),  (((18.0 + sqrt(30.0)) / 36)), (((18.0 - sqrt(30.0)) / 36)) };
    Gauss gauss_4D(4, points_4D, weights_4D);


    Grid Grid(gauss_4D);

    return 0;
}



