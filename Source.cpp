#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;
using std::right;
const int MAX_NUM = 100;
string multiplication(string origin);
string plusAndMinus(string origin);
bool incorrectformat(string origin);

int main()
{
	system("COLOR 70");
	
	string input;
	string TempNum = "";
	float result = 0;
	string temp = "";
	string replace = "";
	string bracketEq = "";
	char command = ' ';


	while (command != 'q')
	{
		cout << "Enter your equation here: " << endl;
		cin >> input;

		replace = "";
		TempNum = "";
		result = 0;
		temp = "";


		if (incorrectformat(input) == true)
		{
			cout << "The format of equation is not correct!!!" << endl;
			system("CLS");
			continue;
		}

		for (int i = 0; i < input.length(); i++)
		{
			if (input.at(i) == ')')
			{
				for (int j = 0; j <= i; j++)
				{
					if (input.at(i - j) == '(')
					{
						bracketEq = input.substr(i - j + 1, j - 1);

						bracketEq = multiplication(bracketEq);

						bracketEq = plusAndMinus(bracketEq);

						input.replace(i - j, j + 1, bracketEq);

						i = 0;
						break;
					}
				}
			}
		}

		input = multiplication(input);
		input = plusAndMinus(input);
		for (int i = 0; i < input.length(); i++)
		{
			if (input.at(i) != '=')
			{
				TempNum += input.at(i);
			}
		}

		result = stof(TempNum);
		cout << "The result is: " << result << endl;
		cout << "what to do next\n q to quit \n c to continue" << endl << endl;;
		cin >> command;
		system("CLS");
	}


	
	return 0;
}
/*
Caculate the multiplication and division part of the equation first, then replace the result of multiplication/division to the original equation.
*/
string multiplication(string origin)
{
	int begin = 0;
	int finish = 0;
	string temp = "";
	string replace = "";
	float resultTemp = 0;
	string TempNum = "";
	float first = 0;
	float second = 0;

	for (int i = 0; i < origin.length(); i++)
	{
		if (origin.at(i) != '*' && origin.at(i) != '/')
		{
			first = 0;
			TempNum = "";
		}
		if (origin.at(i) == '*' || origin.at(i) == '/')
		{
			int j = 1;
			while ((origin.at(i - j) >= '0' && origin.at(i - j) <= '9') || origin.at(i - j) == '.')
			{
				j++;
				if (i - j < 0)
				{
					break;
				}
			}
			begin = i + 1 - j;

			int k = 1;
			while ((origin.at(i + k) >= '0' && origin.at(i + k) <= '9') || origin.at(i + k) == '.')
			{
				k++;
				if (i + k >= origin.length())
				{
					break;
				}
			}
			finish = k + j - 1;

			temp = origin.substr(begin, finish);

			for (int l = 0; l < temp.length(); l++)
			{
					if ((temp.at(l) >= '0' && temp.at(l) <= '9') || temp.at(l) == '.')
					{
						TempNum += temp.at(l);
					}
					else
					{
						if (first == 0)
						{
							first = stof(TempNum);
							TempNum = "";
						}
						TempNum = "";
						for (int m = l + 1; m < temp.length(); m++)
						{
							TempNum += temp.at(m);

						}
						second = stof(TempNum);
						TempNum = "";
						switch (temp.at(l))
						{
						case '*':
							resultTemp = first * second;
							break;
						case '/':
							resultTemp = first / second;
							break;
						default:
							break;
						}
						first = resultTemp;
					}
					
			}
			replace = to_string(resultTemp);
			origin.replace(begin, finish, replace);
			i = 0;
		}


	}
	return origin;
}

string plusAndMinus(string origin)
{
	int begin = 0;
	int finish = 0;
	string temp = "";
	string replace = "";
	float resultTemp = 0;
	string TempNum = "";
	float first = 0;
	float second = 0;

	for (int i = 0; i < origin.length(); i++)
	{
		if (origin.at(i) == '+' || origin.at(i) == '-')
		{
			int j = 1;
			while ((origin.at(i - j) >= '0' && origin.at(i - j) <= '9') || origin.at(i - j) == '.')
			{
				j++;
				if (i - j < 0)
				{
					break;
				}
			}
			begin = i - j + 1;

			int k = 1;
			while ((origin.at(i + k) >= '0' && origin.at(i + k) <= '9') || origin.at(i + k) == '.')
			{
				k++;
				if (i + k >= origin.length())
				{
					break;
				}
			}
			finish = k + j - 1;

			temp = origin.substr(begin, finish);

			for (int l = 0; l < temp.length(); l++)
			{
					if ((temp.at(l) >= '0' && temp.at(l) <= '9') || temp.at(l) == '.')
					{
						TempNum += temp.at(l);
					}
					else
					{
						if (first == 0)
						{
							first = stof(TempNum);
							TempNum = "";
						}
						TempNum = "";
						for (int m = l + 1; m < temp.length(); m++)
						{
							TempNum += temp.at(m);

						}
						second = stof(TempNum);
						TempNum = "";
						switch (temp.at(l))
						{
						case '+':
							resultTemp = first + second;
							break;
						case '-':
							resultTemp = first - second;
							break;
						default:
							break;
						}
						first = resultTemp;
						second = 0;
					}


			}
			replace = to_string(resultTemp);
			origin.replace(begin, finish, replace);
			i = 0;
		}


	}
	return origin;
}

bool incorrectformat(string origin)
{
	int bracketNum = 0;
	for (int i = 0; i < origin.length(); i++)
	{
		if (i + 1 < origin.length())
		{
			if (!(origin.at(i) >= '0' && origin.at(i) <= '9') && (origin.at(i) != '(' && origin.at(i) != ')'))
			{
				if (!(origin.at(i + 1) >= '0' && origin.at(i + 1) <= '9') && (origin.at(i + 1) != '(' && origin.at(i + 1) != ')'))
				{
					cout << "Problem with sign" << endl; 
					return true;
				}
			}
		}

		if (origin.at(i) == '(')
		{
			bracketNum++;
		}
		if (origin.at(i) == ')')
		{
			bracketNum--;
		}
	}

	if (bracketNum != 0)
	{
		return true;
	}

	return false;
}