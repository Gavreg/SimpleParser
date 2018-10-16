#include "parser.h"
#include <algorithm>
#include <functional>
#include  <math.h>

#define SYMBOLS
#define SIGNS "+-*/"

#ifdef WSTRING
STRING letters = L"abcdefghigklmnopqrtsuvwxyzABCDEFGHIGKLMNOPQRSTUVWXYZ";
STRING symbols = L"+-*/";
STRING digits = L"0123456789.";
CHAR space = L' ';
#else
STRING letters = "abcdefghigklmnopqrtsuvwxyzABCDEFGHIGKLMNOPQRSTUVWXYZ";
STRING symbols = "+-*/";
STRING digits = "0123456789.";
CHAR space = ' ';
#endif

class Math_uni_function
{
public:
	std::function<double(double)> func;
	STRING name;
	
};

class Math_uni_cos : public Math_uni_function
{
public:
	Math_uni_cos()
	{
		func = [](double value)
		{
			return cos(value);
		};
	}
};

class Math_uni_sin : public Math_uni_function
{
public:
	Math_uni_sin()
	{
		func = [](double value)
		{
			return sin(value);
		};
	}
};

bool is_letter(CHAR &c)
{
	return std::find(letters.begin(), letters.end(), c) != letters.end();
}

bool is_digit(CHAR &c)
{
	return std::find(digits.begin(), digits.end(), c) != digits.end();
}

bool is_symbol (CHAR &c)
{
	return std::find(symbols.begin(), symbols.end(), c) != symbols.end();
}

enum CharType
{
	_NULL, SYMBOL, LETTER, DIGIT, SPACE
};

CharType get_char_type(CHAR &c)
{
	if (is_letter(c))
		return CharType::LETTER;
	else if (is_digit(c))
		return CharType::DIGIT;
	else if (is_symbol(c))
		return CharType::SYMBOL;
	else if (c == space)
		return CharType::SPACE;


	
	return CharType::_NULL;
}

using namespace std;
void Parser::lexical()
{  	



}

void Parser::syntaxis()
{ 
	STRING buf;

	//STRING symbols = L"+-*/";
	auto str_length = str.length();
	CharType curType = _NULL;
	CharType lastType = _NULL;
	for (decltype(str_length) i = 0; i < str_length; i++)
	{
		CHAR c;
		c = str[i];
		curType = get_char_type(c);


		if (i > 0)
		{

			if ( (lastType == CharType::SYMBOL || lastType != curType || curType==SPACE) && buf.size()>0)
			{
				Token new_token;
				new_token.text = buf;
				switch (lastType)
				{
				case CharType::DIGIT: new_token.type = TokenType::VAL; new_token.value = stod(buf);	  break;
				case CharType::LETTER: new_token.type = TokenType::STR; break;
				case CharType::SYMBOL: new_token.type = TokenType::OPER; break;
				default:;
				}
				tokens.push_back(new_token);
				buf.clear();
			}

		}

		if (curType != CharType::SPACE)
			buf.push_back(c);

		lastType = curType;

	}
}

void Parser::setString(const STRING & str)
{
	this->str = str;
	this->str.push_back(space);
	syntaxis();
	lexical();
	
}
