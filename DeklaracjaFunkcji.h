/**

@file DeklaracjaFunkcji.h
@author Igor Szyk
@brief Deklaracja funkcji zawartych w programie
@version 0.1
@date 2024-01-28
*/

#pragma once


/**
* @brief Funkcja sprawdzajaca czy zgadza sie liczba podanych argumentow
* @param argc parametr dla ilosci argumentow
* @param argv[] parametr tablicy dla nazw plikow uzywanych w programie
*/

void CheckParameters(int argc, char* argv[]); 

/**
* @brief Funkcja czytajaca argumenty i podajaca je do struktury z parametrami
* @param argc parametr dla ilosci argumentow
* @param argv[] parametr tablicy dla nazw plikow uzywanych w programie
* @param parameters parametr struktury do ktorej wstawia sie wyczytane argumenty
*/

void ReadParameters(int argc, char* argv[], struct PARAM& parameters);

/**
* @brief Funkcja czytajaca uklad z pliku i budujaca go
* @param input plik z ktorego czyta sie budowe ukladu
* @param VectorGates wektor do ktorego wpisuje sie wyczytany uklad z pliku
* @param OUTPUTS wektor do ktorego wypisuje sie numery bramek wyjscia
* @param INPUTS wektor do ktorego wypisuje sie numery bramek wejscia
*/

void ReadCircuit(std::string input, std::vector<struct GATE> &VectorGates, std::vector<int> &OUTPUTS, std::vector<int>& INPUTS);

/**
* @brief Funkcja czytajaca wartosci na wejsciach z pliku i wprowadzajaca wartosci wejsc do ukladu oraz wprowadzajaca wartosci do kazdej bramki i wypisujaca wartosci wyjsc 
* @param input2 plik z ktorego czyta sie wartosci na wejsciach
* @param output plik do ktorego wypisuje sie wartosci wejsc i wyjsc
* @param VectorGates wektor na ktorym czyta sie wartosci wyjsc potrzebnych bramek
* @param OUTPUTS wektor numerow wyjsc do ktorych szuka sie wartosci 
* @param INPUTS wektor numerow wejsc, ktore wykorzystuje sie do sprawdzenia czy zgadza sie ilosc wartosci z iloscia numerow wezlow
*/


void ReadInputsAndWrite(std::string input2, std::string output, std::vector<struct GATE>& VectorGates, std::vector<int> OUTPUTS, std::vector<int> INPUTS);

/**
* @brief Funkcja "tlumaczaca" stringi z pliku na enum
* @param original parametr zawierajacy oryginalny tekst w stringu
* @return typ bramki w enum
*/

enum class GateType TranslateStringToEnum(std::string original);

/**
* @brief Funkcja wyliczajaca wartosc wyjscia z wartosci znajdujacej sie na wejsciu bramki
* @param nodeID numer wezla z ktorego aktualnie bedzie wyznaczana wartosc na wyjsciu
* @param VectorGates wektor zawierajacy uklad, na ktorym bedzie sie operowac
*/

void EvaluateOut(int nodeID, std::vector<struct GATE> &VectorGates);


