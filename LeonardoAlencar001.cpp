// Leonardo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

class LibraryBook {
private:
    string title;
    string author;
    string isbn;
    bool available;
    string dateAdded;

public:
    LibraryBook() {}

    LibraryBook(string t, string a, string i, bool av, string date)
        : title(t), author(a), isbn(i), available(av), dateAdded(date) {
    }

    string getIsbn() const {
        return isbn;
    }

    bool isAvailable() const {
        return available;
    }

    void borrowBook() {
        if (available) {
            available = false;
            cout << "You borrowed: \"" << title << "\"\n";
        }
        else {
            cout << "The book \"" << title << "\" is not available.\n";
        }
    }

    void showInfo() const {
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "ISBN: " << isbn << "\n";
        cout << "Available: " << (available ? "Yes" : "No") << "\n";
        cout << "Date added: " << dateAdded << "\n";
    }
};

int findBookByIsbn(LibraryBook books[], int count, const string& targetIsbn) {
    for (int i = 0; i < count; i++) {
        if (books[i].getIsbn() == targetIsbn) {
            return i;
        }
    }
    return -1;
}

int main() {
    const int TOTAL_BOOKS = 5;

    LibraryBook books[TOTAL_BOOKS] = {
        LibraryBook("I'm Glad My Mom Died", "Jennette McCurdy", "9781668022849", true, "2025-11-01"),
        LibraryBook("One of Us Is Lying", "Karen M. McManus", "9780141375632", true, "2025-11-01"),
        LibraryBook("The Handmaid's Tale", "Margaret Atwood", "9780099740919", true, "2025-11-01"),
        LibraryBook("One of Us Is Back", "Karen M. McManus", "9780241739501", true, "2025-11-01"),
        LibraryBook("The Holy Bible", "Various", "9780005331941", true, "2025-11-01")
    };

    cout << "Book Borrowing System";

    string inputIsbn;

    while (true) {
        cout << "\nType ISBN to borrow a book (0 to exit): ";
        getline(cin, inputIsbn);

        if (inputIsbn == "0") {
            cout << "Closing the program. Goodbye!\n";
            break;
        }

        int position = findBookByIsbn(books, TOTAL_BOOKS, inputIsbn);

        if (position == -1) {
            cout << "Book with ISBN " << inputIsbn << " was not found.\n";
        }
        else {
            books[position].borrowBook();
        }
    }

    return 0;
}

