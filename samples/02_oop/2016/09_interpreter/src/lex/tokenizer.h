#ifndef __TOKENIZER_H
#define __TOKENIZER_H

#include <string>

using namespace std;


struct Token
{
	static const int ERROR = -1;
	static const int NUMBER = 0;
	static const int UNKNOWN = 1;
	static const int KW_START = 2;
	static const int KW_END = 3;
	static const int KW_IF = 4;
	static const int KW_THEN = 5;
	static const int KW_ELSE = 6;
	static const int KW_ASSIGN = 7;
	static const int ARITH_OPER = 8;


	Token ();
	Token (int _type, string _val_str, double _val_double);

	int type;
	string val_str;
	double val_double;

};

class Tokenizer
{
private:
	istream &in;
	bool token_peeked;
	Token peeked_token;
public:
	Tokenizer (istream &_in);

	Token peekToken ();
	Token getToken ();
	bool moreTokens ();

};


#endif