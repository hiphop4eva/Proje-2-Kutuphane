#pragma once

#include <vector>
#include <string>
#include <fstream>

class ClassBook {
public:
	ClassBook(int ID, std::string title, int ownerID = 0, int timeBorrow = 0);
	~ClassBook(){}

	std::string GetTitle() { return title; }
	int GetID() { return ID; }

	int GetOwnerID() { return ownerID; }
	int GetTimeBorrow() { return timeBorrow; }

protected:
	int ID;
	std::string title;

	int ownerID;
	int timeBorrow;
};

class ClassUser {
public:
	ClassUser(int ID, std::string name);

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

bool saveDatabase() {
	//std::string stringBuffer;
	//std::ifstream fileBuffer;
	//if (fileBuffer.is_open()) {
	//	fileBuffer.read((char*)(stringBuffer.c_str()), fileBuffer.gcount());
	//	fileBuffer.close();
	//}
	//else { 
	//	fileBuffer.close();
	//	return 0; 
	//}

	//stringBuffer.replace(stringBuffer.size() - 7, 7, "");

	std::ofstream fileDatabase;
	fileDatabase.open("Database.txt");

	if (fileDatabase.is_open()) {
		//fileDatabase.write(stringBuffer.c_str(), stringBuffer.size());

		for (int i = 0; i < bookList.size(); i++) {

			fileDatabase << "Start book\n";
			fileDatabase << bookList[i].GetID()         << "\n";
			fileDatabase << bookList[i].GetTitle()      << "\n";
			fileDatabase << bookList[i].GetOwnerID()    << "\n";
			fileDatabase << bookList[i].GetTimeBorrow() << "\n";
			fileDatabase << "End book\n";
			fileDatabase << "Final\n";
		}

		fileDatabase.close();
	}
	else {
		fileDatabase.close();
		return 0;
	}

	return 1;
}

bool loadDatabase() {
	std::ifstream fileDatabase;
	fileDatabase.open("Database.txt");

	fileDatabase.close();

	return 1;
}