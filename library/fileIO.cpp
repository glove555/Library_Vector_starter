#include "../includes_usr/fileIO.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char *filename) {
	//open file
	ifstream myfile;
	myfile.open(filename);

	//bad cases
	if (!myfile.is_open())
		return COULD_NOT_OPEN_FILE;
	if (BOOKFILE_EMPTY)
		return NO_BOOKS_IN_LIBRARY;

	std::string line;
	book myBook;
	//when file isn't at end
	while (!myfile.eof()) {
		//get line from file
		getline(myfile, line);
		//adds to array
		books.push_back(myBook);
		//clear stream
		myfile.clear();
	}
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char *filename) {
	//open file
	ifstream myfile;
	myfile.open(BOOKFILE);

	//bad cases
	if (!myfile.is_open())
		return COULD_NOT_OPEN_FILE;
	if (BOOKFILE_EMPTY)
		return NO_PATRONS_IN_LIBRARY;

	string mydata;
	for (int i = 0; i < books.size(); i++) {
		mydata = books[i].title + " " + to_string(books[i].book_id) + " "
				+ books[i].author + " "
				+ to_string(books[i].loaned_to_patron_id) + " "
				+ books[i].state;
//		myfile<<mydata<<endl;
	}
	if (myfile.is_open())
		myfile.close();
	return SUCCESS;
}
/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char *filename) {
	ifstream PATRONFILE;
	PATRONFILE.open(filename);
	//bad cases
	if (!PATRONFILE.is_open())
		return COULD_NOT_OPEN_FILE;
	if (BOOKFILE_EMPTY)
		return NO_PATRONS_IN_LIBRARY;

	std::string line;
	patron myPat;
	stringstream ss;
	std::string id;
	std::string num;
	while (!PATRONFILE.eof()) {

		//get lines from file
		getline(PATRONFILE, line);
		ss(line);
		getline(ss, myPat.name);
		getline(ss, id);
		getline(ss, num);
		myPat.number_books_checked_out = int(num);
		myPat.patron_id = int(id);

		//adds to array
		patrons.push_back(myPat);

		//clear stream
		ss.clear();
	}
	return SUCCESS;
}
/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char *filename) {
	ifstream PATRONFILE;
	PATRONFILE.open(filename);
	//bad cases
	if (!PATRONFILE.is_open())
		return COULD_NOT_OPEN_FILE;
	if (BOOKFILE_EMPTY)
		return NO_PATRONS_IN_LIBRARY;

	string mydata;
	for (int i = 0; i < patrons.size(); i++) {
		mydata = patrons[i].name + "," + patrons[i].number_books_checked_out
				+ "," + patrons[i].patron_id;
//		PATRONFILE<<mydata<<endl;
	}
	return SUCCESS;
}
