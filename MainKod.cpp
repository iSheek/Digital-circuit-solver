/**

@file MainKod.cpp
@author Igor Szyk
@brief Program tworzacy uklady cyfrowe i liczacy wartosci
@version 0.1
@date 2024-01-28
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "DeklaracjaFunkcji.h"
#include "TypyiStructy.h"


/**
* @brief Glowna funkcja
* @param argc podany argument
* @param argv[] nazwa pliku argumentu
*/

int main(int argc, char* argv[]) {
	
	CheckParameters(argc, argv);
	PARAM parameters;
	ReadParameters(argc, argv, parameters);

	std::vector<int> OUTPUTS, INPUTS;

	std::vector<struct GATE> VectorGates;
	ReadCircuit(parameters.u, VectorGates, OUTPUTS, INPUTS);
	
	ReadInputsAndWrite(parameters.i, parameters.o, VectorGates, OUTPUTS, INPUTS);

	std::cout << "Program poprawnie sie wykonal" << std::endl;
	
	return 0;
}


