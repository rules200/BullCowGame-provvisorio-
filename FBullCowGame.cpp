#pragma once

#include "FBullCowGame.h"
#include <map>
#include <time.h>

// sintassi di unreal engine 4
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // costruttore di default

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

/*void FBullCowGame::SetWordByLength(int32 WordLength)
{
	TMap <int32, FString> WordsByLenght { {1,"ape"}, {2,"dvd"}, {3,"bio"}, {4,"ego"}, {5,"ente"}, {6,"rete"}, {7,"casa"}, {8,"pane"}, {9,"pelle"}, {10,"pesto"}, {11,"aborto"}, {12,"banana"}, {13, "abbazia"} };
	MyHiddenWord = WordsByLenght[WordLength];
} */

FString FBullCowGame::GetHiddenWord() { return MyHiddenWord; }

int32 FBullCowGame::GetMaxTries() const {
	TMap <int32, int32> WordLenghtToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString Vocabulary[] = { "pianeta", "pane", "pineta", "pasta", "ape", "sedia" };
	srand(time(NULL));
	int i = (rand() % 6) + 1;
/*	const FString HIDDEN_WORD = "plane"; */
	MyHiddenWord = Vocabulary[i];

    MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	/* (!IsIsogram(Guess)) { // Se l'ipotesi non e' un isogramma
		return EGuessStatus::Not_Isogram;
	}
	else*/ if (!IsLowercase(Guess)) { // Se l'ipotesi non e' in minuscolo
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght()) { // Se la lunghezza dell'ipotesi e' sbagliata
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::Ok;
	}
}

// Ottieni una VALIDA ipotesi, incrementare i turni e ritorna un count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//Ritornare il numero dei turni
	MyCurrentTry++;

	//Creare una variabile di ritorno (conteggio mucca e toro)
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length(); // assume la stessa lunghezza di guess
    //Creare un loop per esaminare tutte le lettere dell'ipotesi
	for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++) //MHWChar = MyHiddenWordChar e' la i
	{

		//Confrontare le lettere dell'ipotesi con la parola nascosta
		for (int32 GChar = 0; GChar < WordLenght; GChar++) { //GChar = GuessChar e' la j

			//se corrispondono allora:
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
                if (MHWChar == GChar) { 	// if sono nel posto giusto
					BullCowCount.Bulls++; // incremento tori  
				}
				else {
					BullCowCount.Cows++; // incremento mucche se non lo sono
				}
			
			}
		}
	}if (BullCowCount.Bulls == WordLenght) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

/*bool FBullCowGame::IsIsogram(FString Word) const

	//trattare le parole con 0 e 1 lettera come isogramma
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // settare la mappa
	for (auto Letter : Word) // per tutte le lettere della parola
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { // se la lettera e' nella map
			return false; // non abbiamo un isogramma
		}
		else
		{
			LetterSeen[Letter] = true; // aggiungi la lettera alla map
		}
    }

	return true; // per esempio nel caso in cui sia stato inserito /0 
} */

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // se non e' un caso in minuscolo
		{
			return false;
		}
	}
	return true;
}
