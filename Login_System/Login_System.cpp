// Login System with Registration and file storing
// Created by Rudra Sikri on 11-09-21


#include <iostream>
#include <map>
#include <fstream>
#include <string>
using namespace std;

//class to make objects with two attributes for username and password
class account {
private:
	string username;
	string password;
public:
	account() {
		this->username = "";
		this->password = "";
	}

	account(string un, string pass);

	string getUsername();
	string getPassword();

	//operator overloading for objects of account class
	friend ofstream& operator << (ofstream& ofs, account& ac);    
	friend ifstream& operator >> (ifstream& ifs, account& ac); 
};

//class to store all the credentials and and to provide login and registration facility
class LoginSystem {
private:
	map<string, account> data;       //stores all the credentials

public:
	LoginSystem();      //extracts the credentials from external data file and stores it in the map

	bool logIn();     //Provides login
	void registration();     //Provides registration

	~LoginSystem();     //stores all the data from the map into an external data file when the program is closed
};

int main() {
	LoginSystem D;     //creates an object of LoginSystem class when the program is started

	int choice = -1;

	while (choice != 0) {
		cout << "****************** Log In Interface ******************" << endl
			<< "1. Login" << endl
			<< "2. Registration" << endl
			<< "0. Exit" << endl
			<< "Your Choice: ";

		cin >> choice;
		cin.ignore();     //Flushing the input stream

		switch (choice) {
		case 1:
			if (D.logIn()) {     //fuction for login is called
				cout << "You are successfully Logged in!" << endl;
			}
			else {
				cout << "Login failed, Check username or password" << endl;
			}

			cout << "Enter \'0\' to exit" << endl;
			cin >> choice;
			break;

		case 2:
			D.registration();     //function for registration is called
			break;

		default:
			cout << "Please enter a valid choice" << endl;
			cout << "\n\n";
		}

	}
	return 0;
}

account::account(string un, string pass) {
	username = un;
	password = pass;
}

//returns username
string account::getUsername() {
	return username;
}

//returns password
string account::getPassword() {
	return password;
}

// operator overloading for objects of account class
ofstream& operator << (ofstream& ofs, account& ac) {
	ofs << ac.username << endl;
	ofs << ac.password << endl;
	return ofs;
}

// operator overloading for objects of account class
ifstream& operator >> (ifstream& ifs, account& ac) {
	ifs >> ac.username;
	ifs >> ac.password;
	return ifs;
}

//extracts the credentials from external data file and stores it in the map
LoginSystem::LoginSystem() {
	account ac;
	ifstream infile;

	infile.open("login.data");     //"login.data" file is opened for extract stored data
	if (!infile) {    //file not found or due to some error
		return;
	}
	while (!infile.eof()) {     //extracts data until the end of file
		infile >> ac;     //credentials are  stored  in object of account class
		data.insert(pair<string, account>(ac.getUsername(), ac));     //all the credentials are stored in the map with username as key and object of account class as the value
	}

	infile.close();
}

//Provides login
bool LoginSystem::logIn() {

	string un;
	string pass;

	cout << "\n\n";
	cout << "****************** Log In Interface ******************" << endl;
	cout << "Username: ";
	getline(cin, un);     //gets the username from the user

	cout << "Password: ";
	getline(cin, pass);     //gets the password from the user

	map<string, account>::iterator itr = data.find(un);     //Iterator to the element with key equal to the username provided by the user  

	if (itr != data.end()) {      //If username found
		if (itr->second.getPassword() == pass)     //if password of account object associated with the key matches the password provided by the user
			return true;
		else     //if password of account object associated with the key does not match the password provided by the user
			return false;
	}
	else      //If username not found
		return false;
}

//Provides registration
void LoginSystem::registration() {
	string un;
	string pass;

	cout << "\n\n";
	cout << "****************** Registration ******************" << endl << "Create username and password" << endl;
	cout << "Username: ";
	getline(cin, un);        //gets the username from the user

	if (data.find(un) != data.end()) {      //if username already exist in the database
		cout << "Username already exists, please try a different one" << endl;
		cout << "\n\n";
		registration();
		return;
	}

	cout << "Password: ";
	getline(cin, pass);      //gets the password from the user

	account ac(un, pass);

	data.insert(pair<string, account>(un, ac));      //credentials are stored in the map

	cout << "Registration successful!" << endl;
	cout << "\n\n";

	return;
}

//stores all the data from the map into an external data file when the program is closed
LoginSystem::~LoginSystem() {
	ofstream outfile;

	outfile.open("login.data");       //"login.data" file is opened to store data

	map<string, account>::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++) {
		outfile << itr->second;     //All the credentials are stored in the external data file from the map
	}
	outfile.close();
}