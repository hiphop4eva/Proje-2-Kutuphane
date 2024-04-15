#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::wstring widen(std::string narrow) {
	wchar_t* buffer = new wchar_t[narrow.length() + 1];
	std::copy(narrow.begin(), narrow.end(), buffer);
	buffer[narrow.length()] = 0;

	std::wstring wide;
	wide.append(buffer);

	delete[] buffer;
	return wide;
}

std::wstring widen(int narrowInt) {
	std::string narrow = std::to_string(narrowInt);
	wchar_t* buffer = new wchar_t[narrow.length() + 1];
	std::copy(narrow.begin(), narrow.end(), buffer);
	buffer[narrow.length()] = 0;

	std::wstring wide;
	wide.append(buffer);

	delete[] buffer;
	return wide;
}

struct DatabaseStruct {
	std::stringstream stream;
	std::vector<int> bookIDList;
	std::vector<int> userIDList;
};

class ClassBook {
public:
	ClassBook(int ID, std::string title, int ownerID = 0, int timeBorrow = 0);
	~ClassBook(){}

	std::string getTitle() { return title; }
	int getID() { return ID; }

	int getOwnerID() { return ownerID; }
	int getTimeBorrow() { return timeBorrow; }

protected:
	int ID;
	std::string title;

	int ownerID;
	int timeBorrow;
};

class ClassUser {
public:
	ClassUser(int ID, std::string name);

	int getID() { return ID; }
	std::string getName() { return name; }

protected:
	int ID;
	std::string name;

};

std::vector<ClassBook> bookList;
std::vector<ClassUser> userList;

ClassBook::ClassBook(int ID, std::string title, int ownerID, int timeBorrow) : ID(ID), title(title), ownerID(ownerID), timeBorrow(timeBorrow) {
	bookList.push_back(*this);
}

ClassUser::ClassUser(int ID, std::string name) : ID(ID), name(name) {
	userList.push_back(*this);
}

DatabaseStruct readDatabase();

bool saveDatabase() {
	DatabaseStruct database = readDatabase();
	{
		std::string inter = database.stream.str();
		inter.erase(inter.end() - 6, inter.end());
		database.stream.str(inter);
	}
	database.stream.seekp(0, std::ios_base::end);

	bool cont = true;

	for (int i = 0; i < bookList.size(); i++) {
		for (int k = 0; k < database.bookIDList.size(); k++) {
			if (bookList[i].getID() == database.bookIDList[k]) { cont = false; break; }
		}

		if (cont == false) { cont = true; continue; }
		database.stream << "Start book\n";
		database.stream << bookList[i].getID() << "\n";
		database.stream << bookList[i].getTitle() << "\n";
		database.stream << bookList[i].getOwnerID() << "\n";
		database.stream << bookList[i].getTimeBorrow() << "\n";
		database.stream << "End book\n";
	}
	cont = true;
	for (int i = 0; i < userList.size(); i++) {
		for (int k = 0; k < database.userIDList.size(); k++) {
			if (userList[i].getID() == database.userIDList[k]) { cont = false; break; }
		}

		if (cont == false) { cont = true; continue; }
		database.stream << "Start user\n";
		database.stream << userList[i].getID() << "\n";
		database.stream << userList[i].getName() << "\n";
		database.stream << "End user\n";
	}

	database.stream << "Final\n";

	std::ofstream fileDatabase;
	fileDatabase.open("Database.txt");

	if (fileDatabase.is_open()) {
		fileDatabase << database.stream.str();
		
		fileDatabase.close();
	}
	else {
		fileDatabase.close();
		return 0;
	}

	return 1;
}

void readDataBook(std::ifstream &file, std::string &input, DatabaseStruct &database) {
	int id;
	std::string title;
	int ownerID;
	int timeBorrow;

	int readOrder = 1;
	bool duplBreak = false;

	while (file) {
		getline(file, input);
		database.stream << input << "\n";

		if (duplBreak == true) {
			break;
		}

		if (input == "End book") {
			ClassBook(id, title, ownerID, timeBorrow);
			readOrder = 0;
			break;
		}
		else if (readOrder == 1) {
			id = atoi(input.c_str());;
			database.bookIDList.push_back(id);
			readOrder++;

			for (int i = 0; i < bookList.size(); i++) {
				if (id == bookList[i].getID()) {
					duplBreak = true;
				}
			}
		}
		else if (readOrder == 2) {
			title = input;
			readOrder++;
		}
		else if (readOrder == 3) {
			ownerID = atoi(input.c_str());
			readOrder++;
		}
		else if (readOrder == 4) {
			timeBorrow = atoi(input.c_str());
			readOrder++;
		}
	}
}

void readDataUser(std::ifstream& file, std::string &input, DatabaseStruct &database) {
	int id;
	std::string name;

	int readOrder = 1;
	bool duplBreak = false;

	while (file) {
		getline(file, input);
		database.stream << input << "\n";

		if (duplBreak == true) {
			break;
		}

		if (input == "End user") {
			ClassUser(id, name);
			readOrder = 0;
			break;
		}
		else if (readOrder == 1) {
			id = atoi(input.c_str());;
			database.userIDList.push_back(id);
			readOrder++;

			for (int i = 0; i < userList.size(); i++) {
				if (id == userList[i].getID()) {
					duplBreak = true;
				}
			}
		}
		else if (readOrder == 2) {
			name = input;
			readOrder++;
		}
	}
}

DatabaseStruct readDatabase() {
	std::ifstream file;
	std::string input;
	DatabaseStruct database;

	file.open("Database.txt");

	while (file) {
		getline(file, input);
		database.stream << input << "\n";

		if (input == "Start book") {
			readDataBook(file, input, database);
		}
		else if (input == "Start user") {
			readDataUser(file, input, database);
		}
		
		if (input == "Final") {
			break;
		}
	}
	file.close();

	return database;
}