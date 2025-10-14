// Dataanalys_IOT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>   // F�r att skriva ut text och l�sa input
#include <vector>     // F�r att anv�nda en lista (vector) f�r att lagra v�rden
#include <algorithm>  // F�r funktioner som att sortera listan
#include <cmath>      // F�r matematiska ber�kningar som sqrt
#include <cstdlib>    // F�r enkel slumpgenerering (rand)
#include <ctime>      // F�r att seeda slumpen med tiden
#include <iomanip>    // F�r att formatera utskrifter, t.ex. decimaler
#include <windows.h>  // F�r svenska tecken i konsolen
#include <locale>     // F�r att st�lla in lokalisering

using namespace std;  
// Funktion f�r att l�gga till nya m�tv�rden manuellt
void addValues(vector<double>& number) {  // Ta emot vektorn som referens
    int numValues;  // Variabel f�r att lagra hur m�nga v�rden anv�ndaren vill l�gga till
    cout << "Hur m�nga temperatur vill du l�gga till? ";
    if (!(cin >> numValues) || numValues < 1) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ogiltig input! M�ste vara ett positivt heltal. Inget lagts till." << endl;
        return;  // Avsluta funktionen
    }
    cin.ignore(10000, '\n');  // Rensa extra tecken

    for (int i = 0; i < numValues; i++) {  // Loop f�r att l�gga till varje v�rde
        double value;  // Variabel f�r att lagra v�rdet
        cout << "Ange m�tv�rde " << (i + 1) << " (t.ex. 10.5): ";
        if (!(cin >> value)) {  // Kontrollera om inputen �r ett tal
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ogiltig input! Hoppar �ver detta v�rde." << endl;
            i--;  // F�rs�k igen med samma nummer
            continue;  // G� till n�sta loop
        }
        number.push_back(value);  // L�gg till v�rdet i listan
        cout << "temperatur " << value << " lagts till." << endl;
    }
    cin.ignore(10000, '\n');  // Rensa efter loopen
}

// Funktion f�r att simulera sensorstr�m 
void simulateSensor(vector<double>& number) {  // Ta emot vektorn som referens
    int numSimulations;  // Hur m�nga v�rden att simulera
    cout << "Hur m�nga slumpm�ssiga v�rden vill du simulera (10-30 �C)? ";
    if (!(cin >> numSimulations) || numSimulations < 1) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ogiltig input! Inget simulerat." << endl;
        return;
    }

    srand(time(0));
    cout << "Temperaturv�rden:" << endl;
    for (int i = 0; i < numSimulations; i++) {
        double simValue = 10.0 + static_cast<double>(rand()) / (RAND_MAX / 20.0);
        number.push_back(simValue);  // L�gg till i listan
        cout << "Simulerat v�rde " << (i + 1) << ": " << fixed << setprecision(1) << simValue << " �C" << endl;
    }
    cout << "Simulering klar! " << numSimulations << " v�rden tillagda." << endl;
}

// Funktion f�r att visa statistik
void showStats(const vector<double>& number) {  // Ta emot vektorn som const-referens (endast l�sning)
    if (number.empty()) {  // Kontrollera om listan �r tom
        cout << "Fel: Ingen data att analysera! L�gg till v�rden f�rst." << endl;
        return;
    }

    int count = number.size();  // Antal v�rden
    double sum = 0.0;  // Summa av v�rdena
    double minVal = number[0];  // Minsta v�rde
    double maxVal = number[0];  // St�rsta v�rde

    for (double val : number) {  // Loopa genom listan
        sum += val;  // L�gg till v�rdet i summan
        if (val < minVal) minVal = val;  // Uppdatera minsta v�rde
        if (val > maxVal) maxVal = val;  // Uppdatera st�rsta v�rde
    }

    double mean = sum / count;  // Medelv�rde

    double variance = 0.0;  // Varians
    for (double val : number) {
        variance += (val - mean) * (val - mean);  // Ber�kna differensen
    }
    variance /= count;  // Dela med antalet

    double stdDev = sqrt(variance);  // Standardavvikelse

    cout << fixed << setprecision(2);  // Formatera utskrifter med 2 decimaler
    cout << "\n--- Statistik ---" << endl;
    cout << "Antal temperatur: " << count << endl;
    cout << "Summa: " << sum << endl;
    cout << "Medelv�rde: " << mean << endl;
    cout << "Min-v�rde: " << minVal << endl;
    cout << "Max-v�rde: " << maxVal << endl;
    cout << "Varians: " << variance << endl;
    cout << "Standardavvikelse: " << stdDev << endl;

    // Tr�skelanalys
    double threshold;
    cout << "\nAnge en tr�skelv�rde (t.ex. 25 �C): ";
    if (cin >> threshold) {
        int above = 0, below = 0;
        for (double val : number) {
            if (val > threshold) above++;
            else if (val < threshold) below++;
        }
        cout << "Antal v�rden �ver " << threshold << ": " << above << endl;
        cout << "Antal v�rden under " << threshold << ": " << below << endl;
    }
    else {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ogiltig tr�skel! Hoppar �ver analys." << endl;
    }
}

// Funktion f�r att s�ka v�rde
void searchValue(const vector<double>& number) {  // Ta emot vektorn som const-referens
    if (number.empty()) {
        cout << "Fel: Ingen data att s�ka i!" << endl;
        return;
    }
    double searchVal;
    cout << "Ange v�rde att s�ka efter: ";
    if (cin >> searchVal) {
        auto it = find(number.begin(), number.end(), searchVal);
        if (it != number.end()) cout << "V�rdet hittades!" << endl;
        else cout << "V�rdet hittades inte." << endl;
    }
    else {
        cout << "Ogiltig input!" << endl;
    }
}

void sortList(vector<double>& number) {  // Ta emot vektorn som referens
    if (number.empty()) {
        cout << "Fel: Ingen data att sortera!" << endl;
        return;
    }
    int choice;
    cout << "Sortera: 1 f�r stigande, 2 f�r fallande: ";
    if (cin >> choice && (choice == 1 || choice == 2)) {
        if (choice == 1) sort(number.begin(), number.end());
        else sort(number.rbegin(), number.rend());
        cout << "Listan sorterad. Sorterad lista: ";
        for (double val : number) cout << fixed << setprecision(1) << val << " ";
        cout << endl;
    }
    else {
        cout << "Ogiltig input!" << endl;
    }
}

int main() {
    SetConsoleOutputCP(65001);  // F�r svenska tecken
    setlocale(LC_ALL, "sv_SE");  // R�ttat till "sv_SE" f�r svenska (du hade "SV_se", som kan vara ett stavfel)
    vector<double> number;  // Deklarera vektorn lokalt i main()

    cout << "V�lkommen till Dataanalys_ IOT program!" << endl;
    int choice;
    while (true) {
        cout << "\n--- Meny ---" << endl;
        cout << "1. L�gg till temperatur" << endl;
        cout << "2. Visa statistik" << endl;
        cout << "3. S�k v�rde" << endl;
        cout << "4. Sortera lista" << endl;
        cout << "5. Simulera sensor" << endl;
        cout << "6. Avsluta" << endl;
        cout << "V�lj (1-6): ";
        if (cin >> choice) {
            switch (choice) {
            case 1: addValues(number); break;  // Skicka vektorn
            case 2: showStats(number); break;  // Skicka vektorn
            case 3: searchValue(number); break;  // Skicka vektorn
            case 4: sortList(number); break;  // Skicka vektorn
            case 5: simulateSensor(number); break;  // Skicka vektorn
            case 6: cout << "Avslutar. Hej d�!"; return 0;
            default: cout << "Ogiltigt val!";
            }
        }
        else {
            cout << "Ogiltig input!";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
