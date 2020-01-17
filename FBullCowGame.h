/* La logica del gioco ( non contiene il codice) */

#pragma once
#include <string>

// sintassi di unreal engine 4
using FString = std::string;
using int32 = int;

struct FBullCowCount {

	int32 Bulls = 0;
	int32 Cows = 0;

};

enum EGuessStatus {
	Invalid_Status,
	Ok, 
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase

};

class FBullCowGame {
public:
	FBullCowGame(); // costruttore 
	
	FString GetHiddenWord();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
    bool IsGameWon() const;
	void SetWordByLength(int32 WordLength);

	EGuessStatus CheckGuessValidity(FString) const; // restituirò il valore più tardi

	void Reset(); // restituirò il valore più tardi
	FBullCowCount SubmitValidGuess(FString);
	





private:
	//vedere il costruttore per i valori (inizializzazione); 
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};