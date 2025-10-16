# Dataanalys_IOT

Ett C++-program som samlar in och analyserar mätvärden, till exempel temperaturer.  
Programmet är gjort för uppgiften *“Datainsamlare och analysverktyg för mätvärden”*.

# Funktioner
- Lägg till egna temperaturvärden manuellt  
- Visa statistik (antal, summa, medelvärde, min, max, varians, standardavvikelse)  
- Sök efter ett specifikt värde  
- Sortera värden (stigande eller fallande)  
- Simulera sensordata (slumpmässiga värden mellan 10–30 °C)  
- Tröskelvärdesanalys – räkna hur många mätningar som ligger över eller under en gräns  

# Teknik och struktur
- Skrivet i C++  
- Använder std::vector  för att lagra data  
- Uppdelat i flera tydliga funktioner för läsbarhet  
- Felhantering vid ogiltig inmatning  
- Körs i konsolen med en enkel meny  

# Så kör du programmet
  Visual Studio 
1. Öppna projektet i Visual Studio.  
2. Tryck Ctrl + Shift + B för att bygga programmet.  
3. Tryck F5 för att köra det.
   elller
   g++ -std=c++17 -o Dataanalys_IOT Dataanalys_IOT.cpp
   ./Dataanalys_IOT
   
# Användning

Vid start visas menyn:
Välkommen till Dataanalys_ IOT program!

--- Meny ---
1. Lägg till temperatur
2. Visa statistik
3. Sök värde
4. Sortera lista
5. Simulera sensor
6. Avsluta
Välj (1-6):

Välj ett alternativ (1–6) och följ instruktionerna i konsolen.

# Exempel på körning
Välkommen till Dataanalys_ IOT program!

--- Meny ---
1. Lägg till temperatur
2. Visa statistik
3. Sök värde
4. Sortera lista
5. Simulera sensor
6. Avsluta
Välj (1-6): 5
Hur många slumpmässiga värden vill du simulera (10-30 °C)? 5
Temperaturvärden:
Simulerat värde 1: 17.3 °C
Simulerat värde 2: 22.1 °C
Simulerat värde 3: 28.6 °C
Simulerat värde 4: 19.4 °C
Simulerat värde 5: 25.0 °C
Simulering klar! 5 värden tillagda.

Välj (1-6): 2
--- Statistik ---
Antal temperatur: 5
Summa: 112.40
Medelvärde: 22.48
Min-värde: 17.30
Max-värde: 28.60
Varians: 14.53
Standardavvikelse: 3.81

Ange en tröskelvärde (t.ex. 25 °C): 25
Antal värden över 25.00: 1
Antal värden under 25.00: 4

# Projektstruktur
.
├── Dataanalys_IOT.cpp   # Huvudprogram med meny och alla funktioner
└── README.md            # Denna fil

# Avslutning

Tack för att du har tittat på mitt program! 
Din feedback är alltid välkommen. 😊

