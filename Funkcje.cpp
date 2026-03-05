/**

@file Funkcje.cpp
@author Igor Szyk
@brief Funkcje potrzebne do programu
@version 0.1
@date 2024-01-28
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "DeklaracjaFunkcji.h"
#include "TypyiStructy.h"


void CheckParameters(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cerr << "Dzialanie programu - Lista przelacznikow \n -u plik wejsciowy z ukladem \n -i plik wejsciowy ze stanami wejsc \n -o plik wyjsciowy ze stanami wyjsc" << std::endl;
		exit(0);
	}
	if (argc < 7) {
		std::cerr << "Uwaga! Nie wprowadzono wszystkich przelacznikow!" << std::endl;
		exit(1);
	}

}

void ReadParameters(int argc, char* argv[], PARAM &parameters) {
	std::string compare;
	for (int i = 1; i < argc - 1; ++i) {
		compare = argv[i];

		if (compare == "-u") {
			parameters.u = argv[++i];
		}

		if (compare == "-i") {
			parameters.i = argv[++i];
		}

		if (compare == "-o") {
			parameters.o = argv[++i];
		} 
	}
	
}

void ReadCircuit(std::string input, std::vector<struct GATE> &VectorGates, std::vector<int> &OUTPUTS, std::vector<int> &INPUTS) {

	std::ifstream plik1;
	plik1.open(input);
	if (!(plik1))
	{
		std::cerr << "Blad! Nie otwarto pliku!!";
		exit(1);
	}
	
	std::string line1, gatename;

	int PreviousNode = 0;

	while (std::getline(plik1, line1))
	{	GATE Bramka;
		std::istringstream iss(line1);
		iss >> gatename;
		std::vector<int> NodesNOW;			
		int Node, Last;
		gatename.erase(std::find(gatename.begin(), gatename.end(), ':'));
		enum class GateType Egatename;
		Egatename = TranslateStringToEnum(gatename);
		Bramka.Name = Egatename;
		
		
		if (!(gatename == "IN") && !(gatename == "OUT"))
		{
			while (iss >> Node) {
				NodesNOW.push_back(Node);
			}
			Last = NodesNOW.back();
			NodesNOW.pop_back();
			int i;
			while(!NodesNOW.empty())
			{	
				i = NodesNOW.back();
				NodesNOW.pop_back();
				Bramka.inputNodes.push_back(i);

			} 

			if (PreviousNode < Last + 1) {
			VectorGates.resize(Last + 1);
			PreviousNode = Last;
			}

		VectorGates[Last] = Bramka;
		
		}

		else if (gatename == "OUT") {
			while (iss >> Last) {
					OUTPUTS.push_back(Last);
			}
		}

		else if (gatename == "IN") {
			while (iss >> Last) {
				if (PreviousNode < Last + 1)
				{
					VectorGates.resize(Last + 1);
					PreviousNode = Last;
				}
				VectorGates[Last] = Bramka;
				INPUTS.push_back(Last);
			}
		}

	}

	plik1.close();
}

void ReadInputsAndWrite(std::string input2, std::string output, std::vector<struct GATE> &VectorGates, std::vector<int> OUTPUTS, std::vector<int> INPUTS) {

	std::ifstream plik2;
	plik2.open(input2);

	std::ofstream plik3;
	plik3.open(output);
	if (!(plik2) && !(plik3))
	{
		std::cerr << "Blad! Nie otwarto pliku!!";
		exit(1);
	}
	int nodeID, Value;
	std::string line;
	char colon;
	enum class GateValue EValue;


	while (std::getline(plik2, line))
	{
		
		std::istringstream iss2(line);
		std::vector<int> Evaluated;

		std::vector<int> CheckAmount1, CheckAmount2;

		plik3 << "IN: ";

		while (iss2 >> nodeID) {
			iss2 >> colon;
			iss2 >> Value;
			EValue = static_cast<GateValue>(Value);
			VectorGates[nodeID].out = EValue;
			Evaluated.push_back(nodeID);
			CheckAmount1.push_back(nodeID);
			CheckAmount2.push_back(Value);

			plik3 << nodeID << ':' << Value << ' ';
			}
		
		
		if (!(CheckAmount1.size() == CheckAmount2.size())) // Sprawdzamy czy zgadza sie ilosc wypisanych numerow wezlow do wypisanych wartosci
		{
			std::cerr << "Cos sie nie zgadza, sprawdz czy poprawnie wpisales wszystkie wartosci w pliku o argumencie -i";
			exit(1);
		}
		if (!(CheckAmount1.size() == INPUTS.size())) // Sprawdzamy czy zgadza sie ilosc wezlow w parametrze -u i -i
		{
			std::cerr << "Nie zgadza sie ilosc wejsc podanych w parametrach -u i -i";
			exit(1);
		}
		
		

		for (int m : OUTPUTS)
		{
			EvaluateOut(m, VectorGates);
		}

		plik3 << " " << "OUT: ";

		for (int i = 0; i < OUTPUTS.size(); i++)
		{
			plik3 << OUTPUTS[i] << ':' << static_cast<int>(VectorGates[OUTPUTS[i]].out) << ' ';
		}
		plik3 << "\n";

		for (int i = 0; i < VectorGates.size(); i++) // Czyszczenie wyliczonych wartosci po wpisaniu wartosci wyjsc
		{
			if (!(std::count(Evaluated.begin(), Evaluated.end(), i)))
			{
				VectorGates[i].out = GateValue::UNIND;
			}
		}
		
	}

	plik2.close();
	plik3.close();
}


enum class GateType TranslateStringToEnum(std::string original) {
	if (original == "AND")
	{
		return GateType::AND;
	}
	else if (original == "NAND")
	{
		return GateType::NAND;
	}
	else if (original == "OR")
	{
		return GateType::OR;
	}
	else if (original == "NOR")
	{
		return GateType::NOR;
	}
	else if (original == "XOR")
	{
		return GateType::XOR;
	}
	else if (original == "XNOR")
	{
		return GateType::XNOR;
	}
	else if (original == "NEG")
	{
		return GateType::NEG;
	}
	else if (original == "IN")
	{
		return GateType::IN;
	}
}

void EvaluateOut(int nodeID, std::vector<struct GATE> &VectorGates) {
		
	if (!(VectorGates[nodeID].out == GateValue::UNIND) )
	{
		return;
	}

	std::vector<GateValue> EvaluateFrom;

	for (int n = 0; n < VectorGates[nodeID].inputNodes.size(); n++)
		{
		int node = VectorGates[nodeID].inputNodes[n];
		EvaluateFrom.push_back(VectorGates[node].out);
		}
	std::vector<int> EvaluateFromINT;
	if (std::any_of(EvaluateFrom.begin(), EvaluateFrom.end(), [](enum class GateValue i) { return i == GateValue::UNIND; }))
		{
		for (int n : VectorGates[nodeID].inputNodes)
			{
			EvaluateOut(n, VectorGates);
			} 
		}
	EvaluateFrom.clear();
	for (int n = 0; n < VectorGates[nodeID].inputNodes.size(); n++)
	{
		int node = VectorGates[nodeID].inputNodes[n];
		EvaluateFrom.push_back(VectorGates[node].out);
	}
		switch (VectorGates[nodeID].Name)
		{

		case GateType::AND:
			if (std::all_of(EvaluateFrom.begin(), EvaluateFrom.end(), [](enum class GateValue i) {return i == GateValue::ON; }))
			{
				VectorGates[nodeID].out = GateValue::ON;
			}
			else {
				VectorGates[nodeID].out = GateValue::OFF;
			}
			break;

		case GateType::NAND:
			if (std::all_of(EvaluateFrom.begin(), EvaluateFrom.end(), [](enum class GateValue i) {return i == GateValue::ON; }))
			{
				VectorGates[nodeID].out = GateValue::OFF;
			}
			else {
				VectorGates[nodeID].out = GateValue::ON;
			}
			break;

		case GateType::OR:
			if (std::any_of(EvaluateFrom.begin(), EvaluateFrom.end(), [](enum class GateValue i) { return i == GateValue::ON; }))
			{
				VectorGates[nodeID].out = GateValue::ON;
			}
			else {
				VectorGates[nodeID].out = GateValue::OFF;
			}
			break;

		case GateType::NOR:
			if (std::any_of(EvaluateFrom.begin(), EvaluateFrom.end(), [](enum class GateValue i) { return i == GateValue::ON; }))
			{
				VectorGates[nodeID].out = GateValue::OFF;
			}
			else {
				VectorGates[nodeID].out = GateValue::ON;
			}

			break;

		case GateType::XOR:

			for (int i = 0; i < EvaluateFrom.size(); i++)
			{
				EvaluateFromINT.push_back(static_cast<int>(EvaluateFrom[i]));
			}
			if (count(EvaluateFromINT.begin(), EvaluateFromINT.end(), 1) % 2 == 1)
			{
				VectorGates[nodeID].out = GateValue::ON;
			}
			else
			{
				VectorGates[nodeID].out = GateValue::OFF;
			}

			break;

		case GateType::XNOR:
			for (int i = 0; i < EvaluateFrom.size(); i++)
			{
				EvaluateFromINT.push_back(static_cast<int>(EvaluateFrom[i]));
			}
			if (count(EvaluateFromINT.begin(), EvaluateFromINT.end(), 1) % 2 == 1)
			{
				VectorGates[nodeID].out = GateValue::OFF;
			}
			else
			{
				VectorGates[nodeID].out = GateValue::ON;
			}
			break;

		case GateType::NEG:
			if (std::all_of(EvaluateFrom.begin(), EvaluateFrom.end(), [](enum class GateValue i) {return i == GateValue::ON; }))
			{
				VectorGates[nodeID].out = GateValue::OFF;
			}
			else {
				VectorGates[nodeID].out = GateValue::ON;
			}
			break;

		case GateType::IN:
			VectorGates[nodeID].out = VectorGates[nodeID].out;
			break;

		default:
			break;
		}
	
}
