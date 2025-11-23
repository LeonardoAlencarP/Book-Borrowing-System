#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ===== Base class =====
class Book {
protected:
    string title;
    string author;
    string isbn;
    bool available;
    string dateAdded;

public:
    Book(string t, string a, string i, bool av, string date)
        : title(t), author(a), isbn(i), available(av), dateAdded(date) {
    }

    virtual ~Book() {}

    string getIsbn() const {
        return isbn;
    }

    bool isAvailable() const {
        return available;
    }

    virtual void display() const {
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "ISBN: " << isbn << "\n";
        cout << "Available: " << (available ? "Yes" : "No") << "\n";
        cout << "Date added: " << dateAdded << "\n";
    }

    void borrow() {
        if (available) {
            available = false;
            cout << "You borrowed \"" << title << "\".\n";
        }
        else {
            cout << "The book \"" << title << "\" is not available.\n";
        }
    }

    void giveBack() {
        available = true;
        cout << "You returned \"" << title << "\".\n";
    }
};

// ===== Derived class: HardcopyBook =====
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
        cout << "Shelf number: " << shelfNumber << "\n";
    }
};

// ===== Derived class: EBook =====
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
        cout << "License end date: " << licenseEndDate << "\n";
    }
};

// ===== LibraryManager =====
class LibraryManager {
private:
    vector<Book*> items;   // stores pointers to Book / HardcopyBook / EBook

public:
    ~LibraryManager() {
        // Clean up dynamic memory
        for (Book* b : items) {
            delete b;
        }
    }

    void addItem(Book* book) {
        items.push_back(book);
    }

    Book* findItem(const string& isbn) {
        for (Book* b : items) {
            if (b->getIsbn() == isbn) {
                return b;
            }
        }
        return nullptr;
    }

    void listAllAvailable() const {
        cout << "\nAvailable books:\n";
        for (Book* b : items) {
            if (b->isAvailable()) {
                b->display();
                cout << "---------------------\n";
            }
        }
    }
};

int main() {
    LibraryManager manager;

    // Hardcopy versions
    manager.addItem(new HardcopyBook(
        "I'm Glad My Mom Died", "Jennette McCurdy",
        "9781668022849", true, "2025-11-01", "A1"));

    manager.addItem(new HardcopyBook(
        "One of Us Is Lying", "Karen M. McManus",
        "9780141375632", true, "2025-11-01", "B3"));

    // EBook versions
    manager.addItem(new EBook(
        "The Handmaid's Tale", "Margaret Atwood",
        "9780099740919", true, "2025-11-01", "2026-12-31"));

    manager.addItem(new EBook(
        "One of Us Is Back", "Karen M. McManus",
        "9780241739501", true, "2025-11-01", "2027-01-15"));

    manager.addItem(new EBook(
        "The Holy Bible", "Various",
        "9780005331941", true, "2025-11-01", "2030-01-01"));

    cout << "Library Manager Task 3";

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
            manager.listAllAvailable();
        }
        else if (option == "2") {
            cout << "Enter ISBN to borrow: ";
            getline(cin, isbnInput);
            Book* b = manager.findItem(isbnInput);
            if (b == nullptr) {
                cout << "Book not found.\n";
            }
            else {
                b->borrow();
            }
        }
        else if (option == "3") {
            cout << "Enter ISBN to return: ";
            getline(cin, isbnInput);
            Book* b = manager.findItem(isbnInput);
            if (b == nullptr) {
                cout << "Book not found.\n";
            }
            else {
                b->giveBack();
            }
        }
        else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
