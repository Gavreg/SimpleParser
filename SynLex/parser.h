#ifndef PARSER_H
#define PARSER_H

//#define WSTRING

#ifdef WSTRING
#define STRING std::wstring
#define TO_STRING std::to_wstring
#define CHAR wchar_t

#else
#define	STRING std::string
#define TO_STRING std::to_string
#define CHAR char

#endif

#include <string>
#include <vector>


using namespace std;

enum TokenType { STR, VAL, OPER };

class Token
{

public:
	TokenType type = TokenType::STR;
	STRING text;
	double value = 0;
};



class Parser
{
	STRING str;

	void lexical();
	void syntaxis();

	std::vector<Token>	tokens;

public:
	void setString(const STRING &str);

	
};


#endif





