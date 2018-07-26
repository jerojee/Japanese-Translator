#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: 9 [Is now a .h File]
//=====================================================

// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by: Jeremy Ojeda
// ** RE: (vowel | vowel n | cons vowel | cons vowel n | cons pair vowel | cons pair vowel n)^+
bool mytoken(string s)
{
	string state = "QV";
	int charpos = 0;

	while (s[charpos] != '\0')
	{
		if (state == "QV" && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
			state = "QV";
		else if (state == "QV" && s[charpos] == 'n')
			state = "QN";
		else if (state == "QV" && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'p' || s[charpos] == 'r'))
			state = "QC2";
		else if (state == "QV" && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
			state = "QC1";
		else if (state == "QV" && s[charpos] == 's')
			state = "QS";
		else if (state == "QV" && s[charpos] == 'c')
			state = "QC";
		else if (state == "QV" && s[charpos] == 't')
			state = "QT";

		else if (state == "QN" && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
			state = "QV";
		else if (state == "QN" && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r'))
			state = "QC2";
		else if (state == "QN" && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
			state = "QC1";
		else if (state == "QN" && s[charpos] == 's')
			state == "QS";
		else if (state == "QN" && s[charpos] == 't')
			state == "QT";
		else if (state == "QN" && s[charpos] == 'c')
			state == "QC";

		else if (state == "QC2" && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
			state = "QV";
		else if (state == "QC2" && s[charpos] == 'y')
			state == "QC1";

		else if (state == "QC1" && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
			state = "QV";

		else if (state == "QT" && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
			state = "QV";
		else if (state == "QT" && s[charpos] == 's')
			state = "QC1";

		else if (state == "QC" && s[charpos] == 'h')
			state = "QC1";

		else if (state == "QS" && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
			state = "QV";
		else if (state == "QS" && s[charpos] == 'h')
			state = "QC1";

		else
			return(false);
		charpos++;
	}//end of while

	 // where did I end up????
	if (state == "QV" || state == "QN") return(true);  // end in a final state
	else return(false);
}

// ** Add the PERIOD DFA here
// ** Done by: Jeremy Ojeda
// ** RE: (.)
bool periodToken(string s)
{
	int state = 0;
	int charpos = 0;

	while (s[charpos] != '\0')
	{
		if (state == 0 && s[charpos] == '.') //check if character is a period
			state = 1;
		else
			return(false);
		charpos++;
	}//end of while

	if (state == 1) return(true);  // end in a final state
	else return(false);
}


// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, etc.
enum tokentype {VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM, ERROR, WORD1, WORD2, PERIOD};

// ** string tokenName[30] = { }; for the display names of tokens
string tokenName[30] = {"VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM","ERROR", "WORD1", "WORD2", "PERIOD" };

// ** Need the reservedwords table to be set up here. English will be
// ** used in Part C but it should be stored now.
// ** Do not require any file input for this.
// ** a.out should work without any additional files.
string reservedWord [19][2] = {{"masu", "VERB"},{"masen", "VERBNEG"},{"mashita", "VERBPAST"},{"masendeshita", "VERBPASTNEG"},{"desu", "IS"},{"deshita","WAS"},{"o", "OBJECT"},{"wa", "SUBJECT"},{"ni","DESTINATION"},{"watashi", "PRONOUN"},{"anata", "PRONOUN"},{"kare", "PRONOUN"},{"kanojo", "PRONOUN"},{"sore", "PRONOUN"},{"mata", "CONNECTOR"},{"soshite", "CONNECTOR"},{"shikashi","CONNECTOR"},{"dakara", "CONNECTOR"}, {"eofm", "EOFM"}};

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// ** Done by: Jeremy Ojeda, Lauren Carr, Jose Lopez 
int scanner(tokentype& a, string& w)
{

	// ** Grab the next word from the file via fin
	fin >> w;

	//2. Call the token functions one after another (if-then-else)
	//   And generate a lexical error message if both DFAs failed.
	//   Let the token_type be ERROR in that case.
	bool result = mytoken(w);

	if (periodToken(w) == true) //if character is a period
	{
		a = PERIOD; //type is period
		return 1; //return
	}

	//3. Make sure WORDs are checked against the reservedwords list
	// If not reserved, token_type is WORD1 or WORD2.

	for (int i = 0; i < 19; i++)
	{
		if (w == reservedWord[i][0])
		{
			if (i == 0)
			{
				a = VERB;
				return 1;
			}
			if (i == 1)
			{
				a = VERBNEG;
				return 1;
			}
			if (i == 2)
			{
				a = VERBPAST;
				return 1;
			}
			if (i == 3)
			{
				a = VERBPASTNEG;
				return 1;
			}
			if (i == 4)
			{
				a = IS;
				return 1;
			}
			if (i == 5)
			{
				a = WAS;
				return 1;
			}
			if (i == 6)
			{
				a = OBJECT;
				return 1;
			}
			if (i == 7)
			{
				a = SUBJECT;
				return 1;
			}
			if (i == 8)
			{
				a = DESTINATION;
				return 1;
			}
			if (i == 9 || i == 10 || i == 11 || i == 12 || i == 13)
			{
				a = PRONOUN;
				return 1;
			}
			if (i == 14 || i == 15 || i == 16 || i == 17)
			{
				a = CONNECTOR;
				return 1;
			}
			if (i == 18)
			{
				a = EOFM;
				return 1;
			}
		}
	}


	if (result == true && (w[w.length() - 1] == 'I' || w[w.length() - 1] == 'E')) //check if word is of type WORD2
	{
		a = WORD2;
		return 1;
	}
	if (result == true) //if word DFA returned true
	{
		a = WORD1;
		return 1;
	}

	//4. Return the token type & string  (pass by reference)
	if (result == false)
	{
		a = ERROR;
		cout << "\nLexical error: " << w << " is not a valid token" << endl;
		return 1;
	}
	return 0;
}//the end