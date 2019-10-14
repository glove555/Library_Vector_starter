#include "../includes_usr/fileIO.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 *             NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 *             SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char *filename) {
    //open file
    ifstream myfile;
    myfile.open(filename);

    //bad cases
    if (!myfile.is_open())
        return COULD_NOT_OPEN_FILE;

    std::string line;
    book myBook;
    std::string token;

    //get rid of old values
    books.clear();

    //when file isn't at end
    while (!myfile.eof()) {
        //get line from file
        getline(myfile, line);
        stringstream ss(line);
        int count = 1;
        while (getline(ss, token, ',')) {
            switch (count) {
            //    int book_id;  //order!
            //    std::string title;
            //    std::string author;
            //    book_checkout_state state;
            //    int loaned_to_patron_id;
            case 1: { //bookid
                myBook.book_id = stoi(token);
                break;
            }
            case 2: { //title
                myBook.title = token;
                break;
            }
            case 3: { //author
                myBook.author = token;
                break;
            }
            case 4: { //state
                if (token == "1")
                    myBook.state = book_checkout_state::IN;
                break;
            }
            case 5: { //patronid
                myBook.loaned_to_patron_id = stoi(token);
                break;
            }
            }
            //add to count
            count++;
            books.push_back(myBook);
            ss.clear();
        }
    }
    if (myfile.is_open())
        myfile.close();
    if (books.size() <= 0)
        return NO_BOOKS_IN_LIBRARY;
    return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 *             NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 *             SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char *filename) {
    //open file
    ofstream myfile;
    myfile.open(BOOKFILE);

    //bad cases
    if (!myfile.is_open())
        return COULD_NOT_OPEN_FILE;
    if (books.size() <= 0)
        return NO_PATRONS_IN_LIBRARY;

    string mydata;
//    int book_id;  //order!
//    std::string title;
//    std::string author;
//    book_checkout_state state;
//    int loaned_to_patron_id;

    for (int i = 0; i < (signed) books.size(); i++) {
        mydata = to_string(books[i].book_id) + "," + books[i].title + ","
                + books[i].author + "," + to_string(books[i].state) + ","
                + to_string(books[i].loaned_to_patron_id);
        myfile << mydata << endl;
    }
    return SUCCESS;
}
/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 *             NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 *             SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char *filename) {
    ifstream myfile;
    myfile.open(filename);
    patrons.clear();
    //bad cases
    if (!myfile.is_open())
        return COULD_NOT_OPEN_FILE;
    std::string line;
    std::string token;
    patron myPat;
    while (!myfile.eof()) {
        //get line from file
        getline(myfile, line);
        stringstream ss(line);
        int count = 1;
        while (getline(ss, token, ',')) {
            switch (count) {
            //    int patron_id;
            //    std::string name;
            //    int number_books_checked_out;
            case 1: { //patronid
                myPat.patron_id = stoi(token);
                break;
            }
            case 2: { //title
                myPat.name = token;
                break;
            }
            case 3: { //author
                myPat.number_books_checked_out = stoi(token);
                break;
            }
            }
            count++;
            patrons.push_back(myPat);
            ss.clear();
        }
    }
    if (patrons.size() <= 0)
        return NO_PATRONS_IN_LIBRARY;

    return SUCCESS;
}
/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 *             NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 *             SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char *filename) {
    ofstream myfile;
    myfile.open(PATRONFILE);
    //bad cases
    if (!myfile.is_open())
        return COULD_NOT_OPEN_FILE;
    if (patrons.size() <= 0)
        return NO_PATRONS_IN_LIBRARY;
    string mydata;
//    int patron_id; //order!
//    std::string name;
//    int number_books_checked_out;
    for (int i = 0; i < (signed) patrons.size(); i++) {
        mydata = to_string(patrons[i].patron_id) + "," + patrons[i].name + ","
                + to_string(patrons[i].number_books_checked_out);
        myfile << mydata << endl;
    }

    return SUCCESS;
}



