#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <codecvt>

struct DatabaseStruct {
	std::stringstream stream;
	std::vector<int> bookIDList;
	std::vector<int> userIDList;
};

class ClassBook {
public:
	ClassBook(
		int           ID, //1
		std::string   title, //2
		int           ownerID = 0, //3
		int           timeBorrow = 0, //4
		std::string   placeNumber = "0", //5
		std::string   copy = "", //6
		std::string   library = "", //7
		std::string   section = "", //8
		std::string   collection = "", //9
		std::string   subsection = "", //10
		std::string   shape = "", //11
		std::string   enviroment = "", //12
		std::string   lang = "", //13
		std::string   author = "", //14
		std::string   responsible = "", //15
		std::string   year = "", //16
		std::string isbn = 0, //17
		std::string   info = "", //18
		std::string   publisher = "", //19
		std::string   edition = "", //20
		std::string   physAttrib = "", //21
		std::string   serialRec = "", //22
		std::string   subject = "", //23
		std::string   notes = "" //24
	);
	~ClassBook(){}

	int           getID() { return ID; }
	std::string   getTitle() { return title; }
	int           getOwnerID() { return ownerID; }
	int           getTimeBorrow() { return timeBorrow; }
	std::string   GetPlaceNumber() { return placeNumber; }
	std::string   GetCopy() { return copy; }
	std::string   GetLibrary() { return library; }
	std::string   GetSection() { return section; }
	std::string   GetCollection() { return collection; }
	std::string   GetSubSection() { return subsection; }
	std::string   GetShape() { return shape; }
	std::string   GetEnviroment() { return enviroment; }
	std::string   GetLang() { return lang; }
	std::string   GetAuthor() { return author; }
	std::string   GetResponsible() { return responsible; }
	std::string   GetYear() { return year; }
	std::string GetISBN() { return isbn; }
	std::string   GetInfo() { return info; }
	std::string   GetPublisher() { return publisher; }
	std::string   GetEdition() { return edition; }
	std::string   GetPhysAttrib() { return physAttrib; }
	std::string   GetSerialRec() { return serialRec; }
	std::string   GetSubject() { return subject; }
	std::string   GetNotes() { return notes; }

	void SetID(int newID) { ID = newID; }
	void SetTitle(const std::string& newTitle) { title = newTitle; }
	void SetOwnerID(int newOwnerID) { ownerID = newOwnerID; }
	void SetTimeBorrow(int newTimeBorrow) { timeBorrow = newTimeBorrow; }
	void SetPlaceNumber(const std::string& newPlaceNumber) { placeNumber = newPlaceNumber; }
	void SetCopy(const std::string& newCopy) { copy = newCopy; }
	void SetLibrary(const std::string& newLibrary) { library = newLibrary; }
	void SetSection(const std::string& newSection) { section = newSection; }
	void SetCollection(const std::string& newCollection) { collection = newCollection; }
	void SetSubSection(const std::string& newSubSection) { subsection = newSubSection; }
	void SetShape(const std::string& newShape) { shape = newShape; }
	void SetEnviroment(const std::string& newEnviroment) { enviroment = newEnviroment; }
	void SetLang(const std::string& newLang) { lang = newLang; }
	void SetAuthor(const std::string& newAuthor) { author = newAuthor; }
	void SetResponsible(const std::string& newResponsible) { responsible = newResponsible; }
	void SetYear(const std::string& newYear) { year = newYear; }
	void SetISBN(const std::string& newISBN) { isbn = newISBN; }
	void SetInfo(const std::string& newInfo) { info = newInfo; }
	void SetPublisher(const std::string& newPublisher) { publisher = newPublisher; }
	void SetEdition(const std::string& newEdition) { edition = newEdition; }
	void SetPhysAttrib(const std::string& newPhysAttrib) { physAttrib = newPhysAttrib; }
	void SetSerialRec(const std::string& newSerialRec) { serialRec = newSerialRec; }
	void SetSubject(const std::string& newSubject) { subject = newSubject; }
	void SetNotes(const std::string& newNotes) { notes = newNotes; }

protected:

	int         ID; //1
	std::string title; //2
	int         ownerID; //3
	int         timeBorrow; //4
	std::string placeNumber; //5
	std::string copy; //6
	std::string library; //7
	std::string section; //8
	std::string collection; //9
	std::string subsection; //10
	std::string shape; //11
	std::string enviroment; //12
	std::string lang; //13
	std::string author; //14
	std::string responsible; //15
	std::string year; //16
	std::string isbn; //17
	std::string info; //18
	std::string publisher; //19
	std::string edition; //20
	std::string physAttrib; //21
	std::string serialRec; //22
	std::string subject; //23
	std::string notes; //24

};

class ClassUser {
public:
	ClassUser(int ID, std::string name, std::string password, bool isMod);

	int getID() { return ID; }
	std::string getName() { return name; }
	std::string getPassword() { return password; }
	bool getMod() { return isMod; }
	bool getLogin() { return loggedIn; }

	void SetID(int newID) { ID = newID; }
	void SetMod(bool newMod) { isMod = newMod; }

	void login() { loggedIn = true; }
	void logout() { loggedIn = false; }

protected:
	int ID;
	std::string name;
	std::string password;
	bool loggedIn = false;
	bool isMod = false;

};

std::vector<ClassBook> bookList;
std::vector<ClassUser> userList;

ClassBook::ClassBook(
	int         ID, //1
	std::string title, //2
	int         ownerID, //3
	int         timeBorrow, //4
	std::string placeNumber, //5
	std::string copy, //6
	std::string library, //7
	std::string section, //8
	std::string collection, //9
	std::string subsection, //10
	std::string shape, //11
	std::string enviroment,//12
	std::string lang, //13
	std::string author, //14
	std::string responsible, //15
	std::string year, //16
	std::string isbn, //17
	std::string info, //18
	std::string publisher, //19
	std::string edition, //20
	std::string physAttrib, //21
	std::string serialRec, //22
	std::string subject, //23
	std::string notes //24
		) : 
	ID(ID), //1
	title(title), //2
	ownerID(ownerID), //3
	timeBorrow(timeBorrow), //4
	placeNumber(placeNumber), //5
	copy(copy), //6
	library(library), //7
	section(section), //8
	collection(collection), //9
	subsection(subsection), //10
	shape(shape), //11
	enviroment(enviroment), //12
	lang(lang), //13
	author(author), //14
	responsible(responsible), //15
	year(year), //16
	isbn(isbn), //17
	info(info), //18
	publisher(publisher), //19
	edition(edition), //20
	physAttrib(physAttrib), //21
	serialRec(serialRec), //22
	subject(subject), //23
	notes(notes) //24
{
	bookList.push_back(*this);
}

ClassUser::ClassUser(int ID, std::string name, std::string password, bool isMod) : ID(ID), name(name), password(password), isMod(isMod) {
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
		database.stream << bookList[i].GetPlaceNumber() << "\n";
		database.stream << bookList[i].GetCopy() << "\n";
		database.stream << bookList[i].GetLibrary() << "\n";
		database.stream << bookList[i].GetSection() << "\n";
		database.stream << bookList[i].GetCollection() << "\n";
		database.stream << bookList[i].GetSubSection() << "\n";
		database.stream << bookList[i].GetShape() << "\n";
		database.stream << bookList[i].GetEnviroment() << "\n";
		database.stream << bookList[i].GetLang() << "\n";
		database.stream << bookList[i].GetAuthor() << "\n";
		database.stream << bookList[i].GetResponsible() << "\n";
		database.stream << bookList[i].GetYear() << "\n";
		database.stream << bookList[i].GetISBN() << "\n";
		database.stream << bookList[i].GetInfo() << "\n";
		database.stream << bookList[i].GetPublisher() << "\n";
		database.stream << bookList[i].GetEdition() << "\n";
		database.stream << bookList[i].GetPhysAttrib() << "\n";
		database.stream << bookList[i].GetSerialRec() << "\n";
		database.stream << bookList[i].GetSubject() << "\n";
		database.stream << bookList[i].GetNotes() << "\n";
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
		database.stream << userList[i].getPassword() << "\n";
		database.stream << userList[i].getMod() << "\n";
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
	int         id; //1
	std::string title; //2
	int         ownerID = 0; //3
	int         timeBorrow = 0; //4
	std::string placeNumber = "0"; //5
	std::string copy = ""; //6
	std::string library = ""; //7
	std::string section = ""; //8
	std::string collection = ""; //9
	std::string subsection = ""; //10
	std::string shape = ""; //11
	std::string enviroment = ""; //12
	std::string lang = ""; //13
	std::string author = ""; //14
	std::string responsible = ""; //15
	std::string year = ""; //16
	std::string isbn = ""; //17
	std::string info = ""; //18
	std::string publisher = ""; //19
	std::string edition = ""; //20
	std::string physAttrib = ""; //21
	std::string serialRec = ""; //22
	std::string subject = ""; //23
	std::string notes = ""; //24

	int readOrder = 1;
	bool duplBreak = false;

	while (file) {
		getline(file, input);
		database.stream << input << "\n";

		if (duplBreak == true) {
			break;
		}

		if (input == "End book") {
			ClassBook(
				id,
				title,
				ownerID, 
				timeBorrow, 
				placeNumber, 
				copy, 
				library, 
				section, 
				collection, 
				subsection, 
				shape, 
				enviroment, 
				lang, 
				author, 
				responsible, 
				year, 
				isbn, 
				info, 
				publisher, 
				edition, 
				physAttrib, 
				serialRec, 
				subject,
				notes);

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
		else if (readOrder == 5) {
			placeNumber = input;
			readOrder++;
		}
		else if (readOrder == 6) {
			copy = input;
			readOrder++;
		}
		else if (readOrder == 7) {
			library = input;
			readOrder++;
		}
		else if (readOrder == 8) {
			section = input;
			readOrder++;
		}
		else if (readOrder == 9) {
			collection = input;
			readOrder++;
		}
		else if (readOrder == 10) {
			subsection = input;
			readOrder++;
		}
		else if (readOrder == 11) {
			shape = input;
			readOrder++;
		}
		else if (readOrder == 12) {
			enviroment = input;
			readOrder++;
		}
		else if (readOrder == 13) {
			lang = input;
			readOrder++;
		}
		else if (readOrder == 14) {
			author = input;
			readOrder++;
		}
		else if (readOrder == 15) {
			responsible = input;
			readOrder++;
		}
		else if (readOrder == 16) {
			year = input;
			readOrder++;
		}
		else if (readOrder == 17) {
			isbn = atoi(input.c_str());
			readOrder++;
		}
		else if (readOrder == 18) {
			info = input;
			readOrder++;
		}
		else if (readOrder == 19) {
			publisher= input;
			readOrder++;
		}
		else if (readOrder == 20) {
			edition = input;
			readOrder++;
		}
		else if (readOrder == 21) {
			physAttrib = input;
			readOrder++;
		}
		else if (readOrder == 22) {
			serialRec = input;
			readOrder++;
		}
		else if (readOrder == 23) {
			subject = input;
			readOrder++;
		}
		else if (readOrder == 24) {
			notes = input;
			readOrder++;
		}
	}
}

void readDataUser(std::ifstream& file, std::string &input, DatabaseStruct &database) {
	int id;
	std::string name;
	std::string password;
	bool mod;

	int readOrder = 1;
	bool duplBreak = false;

	while (file) {
		getline(file, input);
		database.stream << input << "\n";

		if (duplBreak == true) {
			break;
		}

		if (input == "End user") {
			ClassUser(id, name, password, mod);
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
		else if (readOrder == 3) {
			password = input;
			readOrder++;
		}
		else if (readOrder == 4) {
			if (input == "1") {
				mod = true;
			}
			else {
				mod = false;
			}
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

void MoveBookContents(const int& bookID, DatabaseStruct &database) {
	std::string input;
	int readOrder = 1;
	int id;
	std::streampos posStart;
	std::streampos posEnd;
	std::string inter;
	inter = database.stream.str();

	bookList.erase(bookList.begin() + (bookID));

	for (int i = 0; i < bookList.size(); i++) {
		if (i >= bookID) {
			bookList[i].SetID(i);
		}
	}
	
	database.stream.seekg(0, std::ios_base::beg);

	while (database.stream) {
		std::getline(database.stream, input);

		if (input == "Start book") {
			readOrder++;
		}
		else if (readOrder == 2) {
			id = atoi(input.c_str());
			if (id > bookID) {
				database.stream.seekg(-(int)(input.size() + 1), std::ios_base::cur);
				posStart = database.stream.tellg();
				database.stream.seekg(input.size(), std::ios_base::cur);
				posEnd = database.stream.tellg();
				
				inter.erase(posStart, posEnd - posStart);
				inter.insert(posStart, std::to_string(id - 1));
				database.stream.str(inter);

				database.stream.seekg(posEnd, std::ios_base::beg);

			}
			readOrder = 1;
		}
	}
}

void MoveUserContents(const int& userID, DatabaseStruct& database) {
	std::string input;
	int readOrder = 1;
	int id;
	std::streampos posStart;
	std::streampos posEnd;
	std::string inter;
	inter = database.stream.str();

	userList.erase(userList.begin() + (userID));

	for (int i = 0; i < userList.size(); i++) {
		if (i >= userID) {
			userList[i].SetID(i);
		}
	}

	database.stream.seekg(0, std::ios_base::beg);

	while (database.stream) {
		std::getline(database.stream, input);

		if (input == "Start user") {
			readOrder++;
		}
		else if (readOrder == 2) {
			id = atoi(input.c_str());
			if (id > userID) {
				database.stream.seekg(-(int)(input.size() + 1), std::ios_base::cur);
				posStart = database.stream.tellg();
				database.stream.seekg(input.size(), std::ios_base::cur);
				posEnd = database.stream.tellg();

				inter.erase(posStart, posEnd - posStart);
				inter.insert(posStart, std::to_string(id - 1));
				database.stream.str(inter);

				database.stream.seekg(posEnd, std::ios_base::beg);
			}
			readOrder = 1;
		}
	}
}

void DeleteBook(int bookID) {
	DatabaseStruct database = readDatabase();
	database.stream.seekg(0, std::ios_base::beg);
	std::fstream file;
	std::string input;
	int readOrder = 1;
	int id;
	std::streampos posStart;
	std::streampos posEnd;

	while (database.stream) {
		std::getline(database.stream, input);

		if (input == "Start book") {
			database.stream.seekg(-11, std::ios_base::cur);
			posStart = database.stream.tellg();
			database.stream.seekg(11, std::ios_base::cur);
			readOrder++;
		}
		else if (readOrder == 2) {
			id = atoi(input.c_str());
			if (id == bookID) {
				readOrder++;
			}
			else {
				readOrder = 1;
			}
		}
		else if (input == "End book" && readOrder != 1) {

			posEnd = database.stream.tellg();
			{
				std::string inter = database.stream.str();
				inter.erase(posStart, posEnd - posStart);
				database.stream.str(inter);
			}

			database.stream.seekg(0, std::ios_base::beg);

			MoveBookContents(bookID, database);

			readOrder = 1;
			break;
		}

		if (input == "Final") {
			break;
		}
	}

	file.open("Database.txt");
	file << database.stream.str();
	file.close();
}

void DeleteUser(int userID) {
	DatabaseStruct database = readDatabase();
	database.stream.seekg(0, std::ios_base::beg);
	std::fstream file;
	std::string input;
	int readOrder = 1;
	int id;
	std::streampos posStart;
	std::streampos posEnd;

	while (database.stream) {
		std::getline(database.stream, input);

		if (input == "Start user") {
			database.stream.seekg(-11, std::ios_base::cur);
			posStart = database.stream.tellg();
			database.stream.seekg(11, std::ios_base::cur);
			readOrder++;
		}
		else if (readOrder == 2) {
			id = atoi(input.c_str());
			if (id == userID) {
				readOrder++;
			}
			else {
				readOrder = 1;
			}
		}
		else if (input == "End user" && readOrder != 1) {

			posEnd = database.stream.tellg();
			{
				std::string inter = database.stream.str();
				inter.erase(posStart, posEnd - posStart);
				database.stream.str(inter);
			}

			database.stream.seekg(0, std::ios_base::beg);

			MoveUserContents(userID, database);

			readOrder = 1;
			break;
		}

		if (input == "Final") {
			break;
		}
	}

	file.open("Database.txt");
	file << database.stream.str();
	file.close();
}

void UpdateBook(int bookID) {
	DatabaseStruct database = readDatabase();
	database.stream.seekg(0, std::ios_base::beg);
	std::fstream file;
	std::string input;
	int readOrder = 1;
	int id;
	std::streampos posStart;
	std::streampos posEnd;
	std::string inter;
	std::string backup;

	while (database.stream) {
		std::getline(database.stream, input);

		if (input == "Start book") {
			database.stream.seekg(-11, std::ios_base::cur);
			posStart = database.stream.tellg();
			database.stream.seekg(11, std::ios_base::cur);
			readOrder++;
		}
		else if (readOrder == 2) {
			id = atoi(input.c_str());
			if (id == bookID) {
				readOrder++;
			}
			else {
				readOrder = 1;
			}
		}
		else if (input == "End book" && readOrder != 1) {

			posEnd = database.stream.tellg();
			
			inter = database.stream.str();
			inter.erase(posStart, posEnd - posStart);
			database.stream.str(inter);

			backup = database.stream.str();
			backup.erase(std::ios_base::beg, posStart);
			
			inter.erase(posStart, std::ios_base::end - posStart);
			database.stream.str(inter);
			
			readOrder = 1;
			break;
		}

		if (input == "Final") {
			break;
		}
	}

	database.stream.seekp(posStart, std::ios_base::beg);

	database.stream << "Start book\n";
	database.stream << bookList[bookID].getID() << "\n";
	database.stream << bookList[bookID].getTitle() << "\n";
	database.stream << bookList[bookID].getOwnerID() << "\n";
	database.stream << bookList[bookID].getTimeBorrow() << "\n";
	database.stream << bookList[bookID].GetPlaceNumber() << "\n";
	database.stream << bookList[bookID].GetCopy() << "\n";
	database.stream << bookList[bookID].GetLibrary() << "\n";
	database.stream << bookList[bookID].GetSection() << "\n";
	database.stream << bookList[bookID].GetCollection() << "\n";
	database.stream << bookList[bookID].GetSubSection() << "\n";
	database.stream << bookList[bookID].GetShape() << "\n";
	database.stream << bookList[bookID].GetEnviroment() << "\n";
	database.stream << bookList[bookID].GetLang() << "\n";
	database.stream << bookList[bookID].GetAuthor() << "\n";
	database.stream << bookList[bookID].GetResponsible() << "\n";
	database.stream << bookList[bookID].GetYear() << "\n";
	database.stream << bookList[bookID].GetISBN() << "\n";
	database.stream << bookList[bookID].GetInfo() << "\n";
	database.stream << bookList[bookID].GetPublisher() << "\n";
	database.stream << bookList[bookID].GetEdition() << "\n";
	database.stream << bookList[bookID].GetPhysAttrib() << "\n";
	database.stream << bookList[bookID].GetSerialRec() << "\n";
	database.stream << bookList[bookID].GetSubject() << "\n";
	database.stream << bookList[bookID].GetNotes() << "\n";
	database.stream << "End book\n";

	database.stream << backup;

	inter.clear();
	inter = database.stream.str();

	file.open("Database.txt");
	file << database.stream.str();
	file.close();
}

void UpdateUser(int userID) {
	DatabaseStruct database = readDatabase();
	database.stream.seekg(0, std::ios_base::beg);
	std::fstream file;
	std::string input;
	int readOrder = 1;
	int id;
	std::streampos posStart;
	std::streampos posEnd;
	std::string inter;
	std::string backup;

	while (database.stream) {
		std::getline(database.stream, input);

		if (input == "Start user") {
			database.stream.seekg(-11, std::ios_base::cur);
			posStart = database.stream.tellg();
			database.stream.seekg(11, std::ios_base::cur);
			readOrder++;
		}
		else if (readOrder == 2) {
			id = atoi(input.c_str());
			if (id == userID) {
				readOrder++;
			}
			else {
				readOrder = 1;
			}
		}
		else if (input == "End user" && readOrder != 1) {

			posEnd = database.stream.tellg();

			inter = database.stream.str();
			inter.erase(posStart, posEnd - posStart);
			database.stream.str(inter);

			backup = database.stream.str();
			backup.erase(std::ios_base::beg, posStart);

			inter.erase(posStart, std::ios_base::end - posStart);
			database.stream.str(inter);

			readOrder = 1;
			break;
		}

		if (input == "Final") {
			break;
		}
	}

	database.stream.seekp(posStart, std::ios_base::beg);

	database.stream << "Start user\n";
	database.stream << userList[userID].getID() << "\n";
	database.stream << userList[userID].getName() << "\n";
	database.stream << userList[userID].getPassword() << "\n";
	database.stream << userList[userID].getMod() << "\n";
	database.stream << "End user\n";

	database.stream << backup;

	inter.clear();
	inter = database.stream.str();

	file.open("Database.txt");
	file << database.stream.str();
	file.close();
}
