/*Questa e' la console eseguibile, che usa la classe BullCow

*/
#pragma once
#include <thread>         
#include <chrono>  
#include <iostream>
#include <string>
#include<stdlib.h>
#include "FBullCowGame.h"


using namespace std::chrono;
// sintassi di unreal engine 4
using FText = std::string;
using int32 = int;


// funzioni esterne alla classe
void Printintro();
void Difficolty();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // istanza del gioco
int32 MaxTries = BCGame.GetMaxTries();
// Inizio gioco
int main()
{
	
	bool bPlayAgain = false;
	do {
		Printintro();
		while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
			auto start = high_resolution_clock::now();
			PlayGame();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop - start);
			std::cout << "Ci hai messo: "<<duration.count()<<" secondi!" << std::endl;
		}
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	

	return 0; // uscita applicazione
}


void Printintro()
{
	BCGame.Reset();
	std::cout << "Benvenuto in Bulls and Cows.\n";
	std::cout << "Bull = lettera nel posto giusto;\nCow= lettera esatta ma nel posto sbagliato;\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Riesci ad indovinare le " << BCGame.GetHiddenWordLenght();
	std::cout << " lettere dell'isogramma che sto pensando?\n";
	std::cout << std::endl;
	return;
}

void Difficolty() {
	
}

void PlayGame()
{
	BCGame.Reset();



	//Numero dei cicli che chiedono l'ipotesi finche' il gioco non e' vinto
	// e se ci sono ancora dei tentativi
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//stampare numero cows e bulls
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";

		}

	PrintGameSummary();
	return;
}


// Loop infinito finche' l'utente non da' un'ipotesi valida
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {
		
		// Ottieni l'ipotesi dal giocatore
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Tentativo " << CurrentTry << " di " << BCGame.GetMaxTries();
		std::cout << ". Inserisci la tua ipotesi: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Per favore inserisci " << BCGame.GetHiddenWordLenght() << " parole.\n\n";
			break;
		/*case EGuessStatus::Not_Isogram:
			std::cout << "Per favore inserisci una parola senza ripetere le lettere.\n\n";
			break; */
		case EGuessStatus::Not_Lowercase:
			std::cout << "Per favore inserisci solo lettere minuscole\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::Ok); // Continuare il ciclo finche' non otteniamo un'ipotesi valida o nessun errore
	return Guess;
}

bool AskToPlayAgain() {

	std::cout << "Vuoi giocare di nuovo? (y/n)\n";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	if (Response[0] == 'y') {
		system("CLS");
		return true;
	}
	else exit(1);
	
}

void PrintGameSummary() {
	if (BCGame.IsGameWon())
	{
		std::cout << "Complimenti hai vinto!\n\n";
	}
	else
	{
		std::cout << "Mi dispiace, hai perso :(\n";
		std::cout << "Soluzione = " << BCGame.GetHiddenWord() << ".\n";
	}

}


