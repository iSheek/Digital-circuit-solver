/**

@file TypyiStructy.h
@author Igor Szyk
@brief Header zawierajacy struktury i typy wyliczeniowe
@version 0.1
@date 2024-01-28
*/

#pragma once
/**
* @brief Enum opisujacy typ bramki
*/
enum class GateType { AND, NAND, OR, NOR, XOR, XNOR, NEG, IN };

/**
* @brief Enum opisujacy wartosc na wyjsciu bramki
*/

enum class GateValue { OFF = 0, ON = 1, UNIND = -1 };

/**
* @brief Struktura odzwierciedlajaca bramki
*/

struct GATE {
	GateType Name; /**< Typ bramki */
	std::vector<int> inputNodes; /**< Numery wezlow wchodzacych do danej bramki */
	GateValue out = GateValue::UNIND; /**< Aktualna wartosc na wyjsciu bramki */
};


/**
* @brief Struktura zawierajaca w sobie argumenty
*/

struct PARAM {
	std::string u, /**< Plik wejscia z obwodem */
		i, /**< Plik wejscia z wartosciami na wejsciach */
		o; /**< Plik wyjsciowy z wartosciami na wejsciach i wyjsciach */
};


