// Dataanalys_IOT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>   // För att skriva ut text och läsa input
#include <vector>     // För att använda en lista (vector) för att lagra värden
#include <algorithm>  // För funktioner som att sortera listan
#include <cmath>      // För matematiska beräkningar som sqrt
#include <cstdlib>    // För enkel slumpgenerering (rand)
#include <ctime>      // För att seeda slumpen med tiden
#include <iomanip>    // För att formatera utskrifter, t.ex. decimaler
#include <windows.h>  // För svenska tecken i konsolen
#include <locale>     // För att ställa in lokalisering

using namespace std;  
// Funktion för att lägga till nya mätvärden manuellt
void addValues(vector<double>& number) {  // Ta emot vektorn som referens
    int numValues;  // Variabel för att lagra hur många värden användaren vill lägga till
    cout << "Hur många temperatur vill du lägga till? ";
    if (!(cin >> numValues) || numValues < 1) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ogiltig input! Måste vara ett positivt heltal. Inget lagts till." << endl;
        return;  // Avsluta funktionen
    }
    cin.ignore(10000, '\n');  // Rensa extra tecken

    for (int i = 0; i < numValues; i++) {  // Loop för att lägga till varje värde
        double value;  // Variabel för att lagra värdet
        cout << "Ange mätvärde " << (i + 1) << " (t.ex. 10.5): ";
        if (!(cin >> value)) {  // Kontrollera om inputen är ett tal
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ogiltig input! Hoppar över detta värde." << endl;
            i--;  // Försök igen med samma nummer
            continue;  // Gå till nästa loop
        }
        number.push_back(value);  // Lägg till värdet i listan
        cout << "temperatur " << value << " lagts till." << endl;
    }
    cin.ignore(10000, '\n');  // Rensa efter loopen
}

// Funktion för att simulera sensorström 
void simulateSensor(vector<double>& number) {  // Ta emot vektorn som referens
    int numSimulations;  // Hur många värden att simulera
    cout << "Hur många slumpmässiga värden vill du simulera (10-30 °C)? ";
    if (!(cin >> numSimulations) || numSimulations < 1) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ogiltig input! Inget simulerat." << endl;
        return;
    }

    srand(time(0));
    cout << "Temperaturvärden:" << endl;
    for (int i = 0; i < numSimulations; i++) {
        double simValue = 10.0 + static_cast<double>(rand()) / (RAND_MAX / 20.0);
        number.push_back(simValue);  // Lägg till i listan
        cout << "Simulerat värde " << (i + 1) << ": " << fixed << setprecision(1) << simValue << " °C" << endl;
    }
    cout << "Simulering klar! " << numSimulations << " värden tillagda." << endl;
}

// Funktion för att visa statistik
void showStats(const vector<double>& number) {  // Ta emot vektorn som const-referens (endast läsning)
    if (number.empty()) {  // Kontrollera om listan är tom
        cout << "Fel: Ingen data att analysera! Lägg till värden först." << endl;
        return;
    }

    int count = number.size();  // Antal värden
    double sum = 0.0;  // Summa av värdena
    double minVal = number[0];  // Minsta värde
    double maxVal = number[0];  // Största värde

    for (double val : number) {  // Loopa genom listan
        sum += val;  // Lägg till värdet i summan
        if (val < minVal) minVal = val;  // Uppdatera minsta värde
        if (val > maxVal) maxVal = val;  // Uppdatera största värde
    }

    double mean = sum / count;  // Medelvärde

    double variance = 0.0;  // Varians
    for (double val : number) {
        variance += (val - mean) * (val - mean);  // Beräkna differensen
    }
    variance /= count;  // Dela med antalet

    double stdDev = sqrt(variance);  // Standardavvikelse

    cout << fixed << setprecision(2);  // Formatera utskrifter med 2 decimaler
    cout << "\n--- Statistik ---" << endl;
    cout << "Antal temperatur: " << count << endl;
    cout << "Summa: " << sum << endl;
    cout << "Medelvärde: " << mean << endl;
    cout << "Min-värde: " << minVal << endl;
    cout << "Max-värde: " << maxVal << endl;
    cout << "Varians: " << variance << endl;
    cout << "Standardavvikelse: " << stdDev << endl;

    // Tröskelanalys
    double threshold;
    cout << "\nAnge en tröskelvärde (t.ex. 25 °C): ";
    if (cin >> threshold) {
        int above = 0, below = 0;
        for (double val : number) {
            if (val > threshold) above++;
            else if (val < threshold) below++;
        }
        cout << "Antal värden över " << threshold << ": " << above << endl;
        cout << "Antal värden under " << threshold << ": " << below << endl;
    }
    else {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ogiltig tröskel! Hoppar över analys." << endl;
    }
}

// Funktion för att söka värde
void searchValue(const vector<double>& number) {  // Ta emot vektorn som const-referens
    if (number.empty()) {
        cout << "Fel: Ingen data att söka i!" << endl;
        return;
    }
    double searchVal;
    cout << "Ange värde att söka efter: ";
    if (cin >> searchVal) {
        auto it = find(number.begin(), number.end(), searchVal);
        if (it != number.end()) cout << "Värdet hittades!" << endl;
        else cout << "Värdet hittades inte." << endl;
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
    cout << "Sortera: 1 för stigande, 2 för fallande: ";
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
    SetConsoleOutputCP(65001);  // För svenska tecken
    setlocale(LC_ALL, "sv_SE");  // Rättat till "sv_SE" för svenska (du hade "SV_se", som kan vara ett stavfel)
    vector<double> number;  // Deklarera vektorn lokalt i main()

    cout << "Välkommen till Dataanalys_ IOT program!" << endl;
    int choice;
    while (true) {
        cout << "\n--- Meny ---" << endl;
        cout << "1. Lägg till temperatur" << endl;
        cout << "2. Visa statistik" << endl;
        cout << "3. Sök värde" << endl;
        cout << "4. Sortera lista" << endl;
        cout << "5. Simulera sensor" << endl;
        cout << "6. Avsluta" << endl;
        cout << "Välj (1-6): ";
        if (cin >> choice) {
            switch (choice) {
            case 1: addValues(number); break;  // Skicka vektorn
            case 2: showStats(number); break;  // Skicka vektorn
            case 3: searchValue(number); break;  // Skicka vektorn
            case 4: sortList(number); break;  // Skicka vektorn
            case 5: simulateSensor(number); break;  // Skicka vektorn
            case 6: cout << "Avslutar. Hej då!"; return 0;
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
