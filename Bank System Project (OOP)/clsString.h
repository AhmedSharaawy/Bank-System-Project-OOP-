#pragma once

#include <iostream>
#include <vector>
using namespace std;

class clsString
{
private:
	string _Value;

public:
	clsString()
	{
		_Value = "";
	}
	clsString(string Value)
	{
		_Value = Value;
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}
	string GetValue()
	{
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static short Length(string S1)
	{
		return S1.length();
	}
	short Length()
	{
		return _Value.length();
	}

	static short CountWords(string St)
	{

		string delim = " ";
		short Pos = 0;
		string sWord;
		short Counter = 0;

		cout << "\nThe number of words in your string is : ";
		while ((Pos = St.find(delim)) != std::string::npos)
		{
			sWord = St.substr(0, Pos);
			if (sWord != "")
			{
				Counter++;

			}

			St.erase(0, Pos + delim.length());

		}

		if (St != "")
		{
			Counter++;
		}

		return Counter;
	}
	short CountWords()
	{
		return CountWords(_Value);
	}

	static void PrintFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;


		cout << "\nFirst Letter Of Strings " << endl;

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				cout << S1[i] << endl;


			}

			IsFirstLetter = (S1[i] == ' ' ? true : false);

		}

	}
	void PrintFirstLetterOfEachWord()
	{
		PrintFirstLetterOfEachWord(_Value);
	}

	static string UpperFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				S1[i] = toupper(S1[i]);


			}

			IsFirstLetter = (S1[i] == ' ' ? true : false);

		}

		return S1;
	}
	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				S1[i] = tolower(S1[i]);


			}

			IsFirstLetter = (S1[i] == ' ' ? true : false);

		}

		return S1;
	}
	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllLetterOfEachWord(string S1)
	{

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				S1[i] = toupper(S1[i]);


			}

		}

		return S1;
	}
	void UpperAllLetterOfEachWord()
	{
		_Value = UpperAllLetterOfEachWord(_Value);
	}

	static string LowerAllLetterOfEachWord(string S1)
	{

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				S1[i] = tolower(S1[i]);


			}

		}

		return S1;
	}
	void LowerAllLetterOfEachWord()
	{
		_Value = LowerAllLetterOfEachWord(_Value);
	}

	static char InvertLatterCase(char ch1)
	{
		return isupper(ch1) ? tolower(ch1) : toupper(ch1);
	}

	static string InvertAllStringLettersCase(string st)
	{
		for (short i = 0; i < st.length(); i++)
		{
			st[i] = InvertLatterCase(st[i]);
		}

		return st;
	}
	void InvertAllStringLettersCase()
	{
		_Value = InvertAllStringLettersCase(_Value);
	}

	static short CountLetters(string st)
	{
		short Counter = 0;

		for (short i = 0; i < st.length(); i++)
		{
			Counter++;
		}

		return Counter;
	}
	short CountLetters()
	{
		return CountLetters(_Value);
	}

	static short CountCapitalLetters(string st)
	{
		short Counter = 0;

		for (short i = 0; i < st.length(); i++)
		{
			if (isupper(st[i]))
				Counter++;
		}

		return Counter;
	}
	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetters(string st)
	{
		short Counter = 0;

		for (short i = 0; i < st.length(); i++)
		{
			if (islower(st[i]))
				Counter++;
		}

		return Counter;
	}
	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	static short CountSpecificLetter(string st, char ch)
	{

		short Counter = 0;

		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] == ch)
				Counter++;
		}

		return Counter;
	}
	short CountSpecificLetter(char ch)
	{
		return CountSpecificLetter(_Value, ch);
	}

	static short CountSmallAndCapitalLetter(string st, char ch)
	{

		short Counter = 0;

		for (short i = 0; i < st.length(); i++)
		{
			if (tolower(st[i]) == tolower(ch))
				Counter++;
		}

		return Counter;
	}
	short CountSmallAndCapitalLetter(char ch)
	{
		return CountSmallAndCapitalLetter(_Value, ch);
	}

	static bool IsVowel(char Ch)
	{
		Ch = tolower(Ch);

		return((Ch == 'a') || (Ch == 'e') || (Ch == 'i') || (Ch == 'o') || (Ch == 'u'));
	}

	static short CountVowels(string st)
	{
		short Counter = 0;

		for (short i = 0; i < st.length(); i++)
		{
			if (IsVowel(st[i]))
				Counter++;
		}

		return Counter;
	}
	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static vector<string> split(string St, string delim)
	{
		vector<string> vstring;

		short Pos = 0;
		string sWord;


		while ((Pos = St.find(delim)) != std::string::npos)
		{
			sWord = St.substr(0, Pos);
			
			St.erase(0, Pos + delim.length());

			vstring.push_back(sWord);
		}

		if (St != "")
		{
			vstring.push_back(St);
		}

		return vstring;
	}
	vector<string> split(string delim)
	{
		return split(_Value, delim);
	}

	static string TrimLeft(string st)
	{
		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] != ' ')
			{
				return st.substr(i, st.length() - i);
			}
		}
		return "";
	}
	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string st)
	{
		for (short i = st.length(); i >= 0; i--)
		{

			if (st[i] != ' ')
			{
				return st.substr(0, i + 1);
			}

		}

		return "";
	}
	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(string st)
	{
		return (TrimLeft(TrimRight(st)));
	}
	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string JoinString(vector<string> vstring, string Delim)
	{
		string st = "";

		for (string& s : vstring)
		{
			st = st + s + Delim;
		}

		return st.substr(0, st.length() - Delim.length());
	}

	static string JoinString(string arrstring[], short Length, string Delim)
	{
		string st = "";

		for (short i = 0; i < Length; i++)
		{
			st = st + arrstring[i] + Delim;
		}

		return st.substr(0, st.length() - Delim.length());
	}

	static string ReverseWordsInString(string st)
	{
		vector<string> vstring;

		string st2 = "";

		vstring = split(st, " ");

		vector<string>::iterator iter = vstring.end();   // declare iterator

		while (iter != vstring.begin())
		{
			--iter;

			st2 += *iter + " ";

		}

		st2 = st2.substr(0, st2.length() - 1);  // Remove Last Space " "

		return st2;

	}
	void ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}

	static string ReplaceWordInString(string st, string StringToReplace, string ReplaceTo)
	{
		short pos = st.find(StringToReplace);

		while (pos != std::string::npos)
		{
			st = st.replace(pos, StringToReplace.length(), ReplaceTo);

			pos = st.find(StringToReplace);
		}
		return st;

	}
	string ReplaceWordInString(string StringToReplace, string ReplaceTo)
	{
		return ReplaceWordInString(_Value, StringToReplace, ReplaceTo);
	}

	static string RemovePunctuatinsFromString(string st)
	{
		string st2;

		for (short i = 0; i < st.length(); i++)
		{
			if (!ispunct(st[i]))
			{
				st2 = st2 + st[i];
			}
		}

		return st2;
	}
	void RemovePunctuatinsFromString()
	{
		_Value = RemovePunctuatinsFromString(_Value);
	}
};