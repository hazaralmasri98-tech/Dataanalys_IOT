// Dataanalys_IOT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>   
#include <vector>     
#include <algorithm>  
#include <cmath>      
#include <cstdlib>    
#include <ctime>     
#include <iomanip>    
#include <windows.h>  
#include <locale>     

using namespace std;  

void addValues(vector<double>& number) {  // Ta emot vektorn som referens
    int numValues; 
    cout << "Hur många temperatur vill du lägga till? ";
    if (!(cin >> numValues) || numValues < 1) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ogiltig input! Måste vara ett positivt heltal. Inget lagts till." << endl;
        return;  // Avsluta funktionen
    }
    cin.ignore(10000, '\n');  // Rensa extra tecken

    for (int i = 0; i < numValues; i++) {  
        double value; 
        cout << "Ange mätvärde " << (i + 1) << " (t.ex. 10.5): ";
        if (!(cin >> value)) {  
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ogiltig input! Hoppar över detta värde." << endl;
            i--;  // Försök igen med samma nummer
            continue; 
        }
        number.push_back(value);  
        cout << "temperatur " << value << " lagts till." << endl;
    }
    cin.ignore(10000, '\n');  
}

// Funktion för att simulera sensorström 
void simulateSensor(vector<double>& number) {  
    int numSimulations; 
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
void showStats(const vector<double>& number) {  
    if (number.empty()) {  
        cout << "Fel: Ingen data att analysera! Lägg till värden först." << endl;
        return;
    }

    int count = number.size();  // Antal värden
    double sum = 0.0;  // Summa av värdena
    double minVal = number[0];  // Minsta värde
    double maxVal = number[0];  // Största värde

    for (double val : number) { 
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

    cout << fixed << setprecision(2); 
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
void searchValue(const vector<double>& number) { 
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

void sortList(vector<double>& number) {  
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
    setlocale(LC_ALL, "sv_SE");  
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
            case 1: addValues(number); break;  
            case 2: showStats(number); break;  
            case 3: searchValue(number); break; 
            case 4: sortList(number); break;  
            case 5: simulateSensor(number); break;  
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
