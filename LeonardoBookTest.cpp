#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// ===== Base class with validation =====
class Book {
protected:
    string title;
    string author;
    string isbn;
    bool available;
    string dateAdded;
    bool valid;

public:
    Book(string t, string a, string i, bool av, string date)
        : title(t), author(a), isbn(i), available(av), dateAdded(date), valid(true) {
        validateBook();
    }

    virtual ~Book() {}

    string getIsbn() const {
        return isbn;
    }

    string getTitle() const {
        return title;
    }

    bool isAvailable() const {
        return available && valid;
    }

    bool isValid() const {
        return valid;
    }

    void validateBook() {
        valid = true;
        string errors = "";

        // Title check
        if (title.empty()) {
            errors += "Title Error: empty; ";
            valid = false;
        }

        // Author check
        if (author.empty()) {
            errors += "Author Error: empty; ";
            valid = false;
        }

        // ISBN numeric check
        bool isbnNumeric = !isbn.empty();
        for (char c : isbn) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                isbnNumeric = false;
                break;
            }
        }
        if (!isbnNumeric) {
            errors += "ISBN Error: not numeric; ";
            valid = false;
        }

        // Date format YYYY-MM-DD check
        if (dateAdded.length() != 10 ||
            dateAdded[4] != '-' ||
            dateAdded[7] != '-') {
            errors += "Date Error: wrong format; ";
            valid = false;
        }

        if (!errors.empty()) {
            cout << "Book validation errors - " << (title.empty() ? "No title" : title)
                 << ": " << errors << "\n";
        }
    }

    virtual void display() const {
        if (!valid) {
            cout << "INVALID BOOK: " << (title.empty() ? "No title" : title) << "\n";
            return;
        }
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "ISBN: " << isbn << "\n";
        cout << "Available: " << (available ? "Yes" : "No") << "\n";
        cout << "Date added: " << dateAdded << "\n";
    }

    void borrowBook() {
        if (!valid) {
            cout << "Cannot borrow \"" << (title.empty() ? "No title" : title)
                 << "\" because data is invalid.\n";
            return;
        }
        if (available) {
            available = false;
            cout << "You borrowed \"" << title << "\".\n";
        } else {
            cout << "The book \"" << title << "\" is not available.\n";
        }
    }

    void returnBook() {
        if (!valid) {
            cout << "Cannot return \"" << (title.empty() ? "No title" : title)
                 << "\" because data is invalid.\n";
            return;
        }
        available = true;
        cout << "You returned \"" << title << "\".\n";
    }
};

// ===== HardcopyBook =====
class HardcopyBook : public Book {
private:
    string shelfNumber;

public:
    HardcopyBook(string t, string a, string i, bool av,
                 string date, string shelf)
        : Book(t, a, i, av, date), shelfNumber(shelf) {
    }

    void display() const override {
        Book::display();
        if (valid) {
            cout << "Shelf number: " << shelfNumber << "\n";
        }
    }
};

// ===== EBook =====
class EBook : public Book {
private:
    string licenseEndDate;

public:
    EBook(string t, string a, string i, bool av,
          string date, string licenseEnd)
        : Book(t, a, i, av, date), licenseEndDate(licenseEnd) {
    }

    void display() const override {
        Book::display();
        if (valid) {
            cout << "License end date: " << licenseEndDate << "\n";
        }
    }
};

// ===== Bubble sort by title (A–Z) =====
void sortBooks(Book* books[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (books[j]->getTitle() > books[j + 1]->getTitle()) {
                Book* temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

int main() {
    cout << "=== ICT0008 A3 Test Application (Leonardo) ===\n\n";

    // ===== Correct books =====
    cout << "TEST 1 - CORRECT BOOKS\n\n";

    HardcopyBook* correct1 = new HardcopyBook(
        "I'm Glad My Mom Died", "Jennette McCurdy",
        "9781668022849", true, "2025-11-01", "A1");

    HardcopyBook* correct2 = new HardcopyBook(
        "One of Us Is Lying", "Karen M. McManus",
        "9780141375632", true, "2025-11-01", "B3");

    EBook* correct3 = new EBook(
        "The Handmaid's Tale", "Margaret Atwood",
        "9780099740919", true, "2025-11-01", "2026-12-31");

    Book* correctBooks[3] = { correct1, correct2, correct3 };

    for (int i = 0; i < 3; i++) {
        cout << "Book " << (i + 1) << ":\n";
        correctBooks[i]->display();
        cout << "---------------------\n";
    }
    cout << "\n";

    // ===== Incorrect books =====
    cout << "TEST 2 - INCORRECT BOOKS\n\n";

    HardcopyBook* bad1 = new HardcopyBook(
        "I'm Glad My Mom Died", "Jennette McCurdy",
        "ABC123", true, "11-01-2025", "X1");   // bad ISBN and date

    HardcopyBook* bad2 = new HardcopyBook(
        "One of Us Is Lying", "",
        "9780141375632", true, "2025/11/01", "B3"); // empty author, wrong date

    EBook* bad3 = new EBook(
        "The Handmaid's Tale", "Margaret Atwood",
        "978X9740919", true, "2025-11", "2026-12"); // bad ISBN, bad date

    Book* badBooks[3] = { bad1, bad2, bad3 };

    for (int i = 0; i < 3; i++) {
        cout << "Bad Book " << (i + 1) << ":\n";
        badBooks[i]->display();
        cout << "---------------------\n";
    }
    cout << "\n";

    // ===== Sorting tests =====
    cout << "TEST 3 - SORTING BY TITLE (A-Z)\n\n";

    // a) Ascending (already sorted)
    Book* asc[3] = { correct1, correct2, correct3 };
    cout << "Array A - Ascending BEFORE sort:\n";
    for (int i = 0; i < 3; i++) {
        cout << asc[i]->getTitle() << " | ";
    }
    cout << "\n";
    sortBooks(asc, 3);
    cout << "Array A - Ascending AFTER sort:\n";
    for (int i = 0; i < 3; i++) {
        cout << asc[i]->getTitle() << " | ";
    }
    cout << "\n\n";

    // b) Descending
    Book* desc[3] = { correct3, correct2, correct1 };
    cout << "Array B - Descending BEFORE sort:\n";
    for (int i = 0; i < 3; i++) {
        cout << desc[i]->getTitle() << " | ";
    }
    cout << "\n";
    sortBooks(desc, 3);
    cout << "Array B - Descending AFTER sort:\n";
    for (int i = 0; i < 3; i++) {
        cout << desc[i]->getTitle() << " | ";
    }
    cout << "\n\n";

    // c) Mixed
    Book* mixed[3] = { correct2, correct3, correct1 };
    cout << "Array C - Mixed BEFORE sort:\n";
    for (int i = 0; i < 3; i++) {
        cout << mixed[i]->getTitle() << " | ";
    }
    cout << "\n";
    sortBooks(mixed, 3);
    cout << "Array C - Mixed AFTER sort:\n";
    for (int i = 0; i < 3; i++) {
        cout << mixed[i]->getTitle() << " | ";
    }
    cout << "\n\n";

    // ===== Interactive menu =====
    cout << "INTERACTIVE LIBRARY MENU\n";

    Book* allBooks[6] = {
        correct1, correct2, correct3,
        static_cast<Book*>(bad1),
        static_cast<Book*>(bad2),
        static_cast<Book*>(bad3)
    };

    string option;
    string isbnInput;

    while (true) {
        cout << "\n1 - List available books\n";
        cout << "2 - Borrow by ISBN\n";
        cout << "3 - Return by ISBN\n";
        cout << "0 - Exit\n";
        cout << "Choose an option: ";
        getline(cin, option);

        if (option == "0") {
            cout << "Exiting program.\n";
            break;
        }
        else if (option == "1") {
            cout << "\nAvailable books:\n";
            for (int i = 0; i < 6; i++) {
                if (allBooks[i]->isAvailable()) {
                    allBooks[i]->display();
                    cout << "---------------------\n";
                }
            }
        }
        else if (option == "2") {
            cout << "Enter ISBN to borrow: ";
            getline(cin, isbnInput);
            bool found = false;
            for (int i = 0; i < 6; i++) {
                if (allBooks[i]->getIsbn() == isbnInput) {
                    allBooks[i]->borrowBook();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Book not found.\n";
            }
        }
        else if (option == "3") {
            cout << "Enter ISBN to return: ";
            getline(cin, isbnInput);
            bool found = false;
            for (int i = 0; i < 6; i++) {
                if (allBooks[i]->getIsbn() == isbnInput) {
                    allBooks[i]->returnBook();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Book not found.\n";
            }
        }
        else {
            cout << "Invalid option.\n";
        }
    }

    // Clean up
    for (int i = 0; i < 6; i++) {
        delete allBooks[i];
    }

    return 0;
}
