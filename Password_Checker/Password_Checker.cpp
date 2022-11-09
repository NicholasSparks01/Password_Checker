/*


*/

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include <regex>

using namespace std;


bool Char_Checker(string str) {

	//Regex to check if the string has all character requirements

	bool check = false;
	const regex Special_Char("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[-+_!@#$%^&*.,?]).+$");

	if (regex_match(str, Special_Char)) { return true; }

	else { check = false; }

	return check;
}

bool Dictionary_Test(string str) {
	ifstream DictPasswords;
	string dictPassword;
	bool checking;

	DictPasswords.open("OneThousand.txt");

	if (!DictPasswords.is_open()) { cout << "Not opening a .txt file correctly. ERROR.\n"; }

	while (!DictPasswords.eof()) {
		getline(DictPasswords, dictPassword);
		if (dictPassword == str) {
			return true;
		}
	}
	DictPasswords.close();

	return false;
}

bool CheckLength(string str) {

	bool check;

	if (str.length() >= 8) {
		check = true;
	}
	else {
		check = false;
	}
	return check;
}

int main(){
	ifstream InputPasswords;
	int vectorSize = 0;
	vector<string> Test_Passwords;
	string password;
	bool characterCheck = false;
	string CurrPassword;

	InputPasswords.open("Test_Words.txt");

	if (!InputPasswords.is_open()) {
		cout << "Not opening a .txt file correctly. ERROR.\n";
	}

	//Loads all test passwords into a vector
	while (!InputPasswords.eof()) {	
		getline(InputPasswords, password);
		Test_Passwords.push_back(password);
		++vectorSize;
	}
	InputPasswords.close();
	
	ofstream OutputPasswords;
	OutputPasswords.open("Result.txt");

	if (!OutputPasswords.is_open()) { cout << "Not opening a .txt file correctly. ERROR.\n"; }

	for (int i = 0; i < vectorSize; ++i) {

		characterCheck = Char_Checker(Test_Passwords.at(i));
		CurrPassword = Test_Passwords.at(i);
		cout << "----------------------------\n";
		if (characterCheck == true) {	// Checks password's needed characters

			cout << CurrPassword << " HAS all characters needed || ";

			if (Dictionary_Test(CurrPassword) == false) {	// Checks if password is in dictionary 
				cout << "WASN'T in Dictonary Scan || ";
				if (CheckLength(CurrPassword) == true) {	// Checks if passwords length is long enough
					cout << "IS long enough || ";
					cout << "GOOD PASSWORD\n";
					OutputPasswords << "Good\n";
				}
				else {	// Password isn't long enough
					cout << "password is < 8 characters\n";
					OutputPasswords << "Bad\n";

				}
			}

			else {	// Password was in the Dictionary Scan
				cout << CurrPassword << "WAS in Dictronary Scan.\n";
				OutputPasswords << "Bad\n";
			}
		}

		else {	// Password doesn't have all special characters needed
			cout << CurrPassword << " DOESN'T contain all special charaters.\n";
			OutputPasswords << "Bad\n";
		}
		

	}
	
	OutputPasswords.close();

	return 0;
}

