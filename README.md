# Digital Circuit Solver (Symulator Układów Cyfrowych)

## 📌 O projekcie
Ten projekt to program napisany w języku C++, który służy do symulacji i rozwiązywania cyfrowych układów logicznych. Narzędzie potrafi odczytać schemat układu z pliku tekstowego, przyjąć zdefiniowane stany wejściowe, a następnie obliczyć i zapisać do pliku wynikowego wartości na wyjściach układu. Obliczenia dokonywane są na grafie z użyciem algorytmu rekurencyjnego.

**Kontekst powstania:** Projekt został zrealizowany w ramach zaliczenia przedmiotu *Programowanie Komputerów* na moim 1. semestrze studiów (semestr zimowy, październik 2023 – luty 2024). Program został ukończony i oddany do sprawdzenia pod koniec stycznia 2024 roku.

## 🚀 Funkcjonalności
* Obsługa podstawowych bramek logicznych: **AND, NAND, OR, NOR, XOR, XNOR, NEG**.
* Reprezentacja sygnałów jako stany binarne (ON = 1, OFF = 0, UNIND = wartość nieokreślona).
* Dynamiczne budowanie struktury układu (grafu węzłów) na podstawie prostego pliku tekstowego.
* Obsługa z poziomu wiersza poleceń z walidacją dostarczonych argumentów.
* Rekurencyjne wyliczanie wartości logicznych układu (silnik oceniający stan od wyjść do wejść).

## 🛠️ Jak uruchomić program?
Program obsługuje się z poziomu terminala/konsoli. Wymaga on podania trzech flag określających ścieżki do odpowiednich plików tekstowych.

**Składnia polecenia:**
```bash
./nazwa_programu -u <plik_ukladu> -i <plik_wejsc> -o <plik_wyjsciowy>
```

Opis parametrów:

-u — plik tekstowy zawierający budowę układu (definicje wejść, wyjść i połączeń bramek).

-i — plik tekstowy z wartościami logicznymi przypisanymi do wejść.

-o — plik tekstowy (zostanie wygenerowany lub nadpisany), w którym program zapisze wyniki na końcowych wyjściach układu.

## 📁 Format plików wejściowych
Plik opisujący układ (argument -u): Plik powinien definiować numery węzłów wejściowych (IN:), węzłów wyjściowych (OUT:) oraz relacje między nimi.

Przykład (zawartość pliku w1.txt):
```
IN: 1 6
OUT: 3
NAND: 1 6 5
NAND: 1 5 2
NAND: 5 6 4
NAND: 2 4 3
```

Interpretacja np. NAND: 1 6 5: Sygnał z węzłów 1 i 6 wchodzi do bramki NAND, a sygnał wychodzi na węzeł 5.

Plik ze stanami wejściowymi (argument -i): Każda linia reprezentuje stan testowy. Definiuje się numer węzła, dwukropek i wartość binarną.
Przykład (dla węzłów 1 i 6):
```
1:0 6:1
1:1 6:0
```

## ⚙️ Struktura projektu
MainKod.cpp – punkt wejścia aplikacji, wczytywanie parametrów i wywoływanie głównych procedur.

Funkcje.cpp – implementacja silnika programu, walidacji wejść, parsowania plików oraz rekurencyjnego obliczania stanu obwodu.

DeklaracjaFunkcji.h – plik nagłówkowy z sygnaturami funkcji używanych w projekcie.

TypyiStructy.h – plik nagłówkowy zawierający typy wyliczeniowe (GateType, GateValue) oraz główne struktury danych układu (GATE, PARAM).
