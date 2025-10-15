# Dataanalys_IOT

Ett C++-program som samlar in och analyserar mätvärden, till exempel temperaturer.  
Programmet är gjort som en del av uppgiften *“Datainsamlare och analysverktyg för mätvärden”*.

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
   g++ -std=c++17 -o Dataanalys_IOT Dataanalys_IOT.cpp
   ./Dataanalys_IOT

   eller 
   
 Visual Studio (rekommenderas)
1. Öppna projektet i Visual Studio.  
2. Tryck Ctrl + Shift + B för att bygga programmet.  
3. Tryck F5 för att köra det.

# Avslutning

Tack för att du har tittat på mitt program!
Din feedback är alltid välkommen. 😊

