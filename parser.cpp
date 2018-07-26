#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include "scanner.h"
using namespace std;
//=================================================
// File parser.cpp written by Group Number: 9
//=================================================
/*

1	<story> ::= <s> { <s> }
2	<s> :: = [CONNECTOR] <noun> SUBJECT <postsub>
3	<postsub> ::= <verb> <tense> PERIOD | <noun> <afternoun>
4	<afternoun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <postobject>
5	<postobject> ::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
6	<noun> ::= WORD1 | PRONOUN
7	<verb> ::= WORD2
8	<be> ::= IS | WAS
9	<tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG

*/
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)

// ** Need the updated match and next_token (with 2 global vars)
 
// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function		[Done]


//Global declarations...
//ifstream fin; --> declared in scanner.cpp [Note here to remind self.]
tokentype curToken;
string inWord;
string curWord;

//Function declartions...
void story();
void s();
void postsub();
void afternoun();
void postobject();
void noun();
void verb();
void be();
void tense();
bool match(tokentype, string);
tokentype next_token();
void endStory(tokentype);
void syntaxerror1(string, string);
void syntaxerror2(string, string);



//Done by: Jose Lopez
//<story> :: = <s>{ <s> }
void story()
{
	cout << "Processing story() " << endl << endl; // Trace Message

	cout << "Processing s()" << endl; //Trace Message
	next_token(); //First Loaded Token
	s(); //story number one

	while (curToken != EOFM) //if story isn't over
	{
		switch (next_token())
		{
			case CONNECTOR:
				cout << "Processing s(CONNECTOR)" << endl; //Trace Message
				s();
				break;

			default:
				cout << "Processing s(DEFAULT)" << endl; //Trace Message
				s();
				break;
		}
	}
}

//Done by: Jose Lopez
//<s> :: = [CONNECTOR] <noun> SUBJECT <postsub>
void s()
{

	if (curToken == CONNECTOR)
	{
		match(CONNECTOR, "CONNECTOR");
		next_token();
	}
	
	noun();

	if (next_token() == SUBJECT)
	{
		match(SUBJECT, "SUBJECT");
	}
	else
	{
		syntaxerror1("SUBJECT", curWord);
	}
	postsub();

}

//Done by: Jose Lopez
//<postsub> ::= <verb> <tense> PERIOD | <noun> <afternoun>
void postsub()
{

	cout << "Processing postsub()" << endl; //Trace Message
	switch (next_token())
	{
	case WORD2:
		verb();
		tense();

		if (next_token() == PERIOD)
		{
			match(PERIOD, "PERIOD");
		}
		else
		{
			syntaxerror1("PERIOD", curWord);
		}
		break;

	case WORD1:
		noun();
		afternoun();
		break;
	default:
		syntaxerror2(curWord, "postsub");
		break;
	}
}

//Done by: Jose Lopez
//<afternoun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <postobject>
void afternoun()
{
	cout << "Processing afternoun()" << endl; //Trace Message
	switch (next_token())
	{
	case IS:
		be();

		if (next_token() == PERIOD)
		{
			match(PERIOD, "PERIOD");
		}
		else
		{
			syntaxerror1("PERIOD", curWord);
		}
		break;

	case WAS:
		be();

		if (next_token() == PERIOD)
		{
			match(PERIOD, "PERIOD");
		}
		else
		{
			syntaxerror1("PERIOD", curWord);
		}
		break;

	case DESTINATION:
		match(DESTINATION, "DESTINATION");
		next_token();
		verb();
		tense();

		if (next_token() == PERIOD)
		{
			match(PERIOD, "PERIOD");
		}
		else
		{
			syntaxerror1("PERIOD", curWord);
		}
		break;

	case OBJECT:
		match(OBJECT, "OBJECT");
		postobject();
		break;

	default:
		syntaxerror2(curWord, "afternoun");
		break;
	}
}

//Done by: Jose Lopez
//<postobject> ::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
void postobject()
{
	cout << "Processing postobject()" << endl; //Trace Message
	switch (next_token())
	{
		case WORD2:
			verb();
			tense();

			if (next_token() == PERIOD)
			{
				match(PERIOD, "PERIOD");
			}
			else
			{
				syntaxerror1("PERIOD", curWord);
			}
			break;

		case WORD1:
			noun();
			next_token();
			match(DESTINATION, "DESTINATION");
			next_token();
			verb();
			tense();

			if (next_token() == PERIOD)
			{
				match(PERIOD, "PERIOD");
			}
			else
			{
				syntaxerror1("PERIOD", curWord);
			}
			break;

		default:
			syntaxerror2(curWord, "postobject");
			break;

	}
}

//Done by: Jose Lopez
//<noun> ::= WORD1 | PRONOUN
void noun()
{
	cout << "Processing noun()" << endl; //Trace Message
	switch (curToken)
	{
		case WORD1:
			match(WORD1, "WORD1");
			break;

		case PRONOUN:
			match(PRONOUN, "PRONOUN");
			break;

		default:
			syntaxerror2(curWord, "noun");
			break;
	}
}

//Done by: Jose Lopez
//<verb> ::= WORD2
void verb()
{
	cout << "Processing verb()" << endl; //Trace Message
	switch (curToken)
	{
		case WORD2:
			match(WORD2, "WORD2");
			break;
		
		default:
			syntaxerror2(curWord, "verb");
			break;
	}
}

//Done by: Jose Lopez
//<be> ::= IS | WAS
void be()
{
	cout << "Processing be()" << endl; //Trace Message

	switch (curToken)
	{
		cout << "TEST CURRENT WORD: " << curWord << endl;

		case IS:
			match(IS, "IS");
			break;
		
		case WAS:
			match(WAS, "WAS");
			break;

		default:
			syntaxerror2(curWord, "be");
			break;
	}
}

//Done by: Jose Lopez
//<tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
void tense()
{
	cout << "Processing tense()" << endl; //Trace Message
	switch (next_token())
	{
		case VERBPAST:
			match(VERBPAST, "VERBPAST");
			break;

		case VERBPASTNEG:
			match(VERBPASTNEG, "VERBPASTNEG");
			break;

		case VERB:
			match(VERB, "VERB");
			break;

		case VERBNEG:
			match(VERBNEG, "VERBNEG");
			break;

		default:
			syntaxerror2(curWord, "tense");
			break;

	}
}

//Done by: Jose Lopez
tokentype next_token()
{

	scanner(curToken, inWord);

	cout << "Scanner called with word: " << inWord << endl;

	//cout << "Next word is " << inWord << endl;
	curWord = inWord;

	if (curToken == ERROR)
	{
		cout << "Word: " << inWord << " does not exist in language. " << endl;
	}

	endStory(curToken);
	return curToken;
}

//Done by: Jose Lopez
bool match(tokentype tType, string sType)
{
	if(curToken != tType)
	{
		syntaxerror1(sType, curWord);
	}
	
	cout << "Matched: " << sType << endl;

	return true;
}

//Done by: Jose Lopez
void endStory(tokentype endToken)
{
	if (endToken == EOFM)
	{
		cout << "This story has ended..." << endl;
		cin >> inWord; //Placeholder to see text.
		exit(-1);
	}
}
//Done by: Jose Lopez
void syntaxerror1(string tType, string errType)
{
	cout << "SYNTAX: Error expected " << tType << " found " << errType << " . " << endl;

	exit(-1);
}

//Done by: Jose Lopez
void syntaxerror2(string errWord, string expWord)
{
	cout << "SYNTAX: Error expected " << expWord << " found " << errWord << " . " << endl;

	exit(-1);
}



// The test driver to start the parser
// Done by:  **Jose Lopez
int main()
{

  //- opens the input file
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());
  
  cout << "Story begins..." << endl;

  //- calls the <story> to start parsing
  story();


  //- closes the input file 
  fin.close();


}// end
//** should require no other input files!


