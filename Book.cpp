#include "Book.h"
#include <cctype>

Book::Book(std::string t, std::string a, std::string i, bool av, std::string date)
    : title(t), author(a), isbn(i), available(av), dateAdded(date), valid(true) {
    validateBook();
}

Book::~Book() {
}

std::string Book::getIsbn() const {
    return isbn;
}

std::string Book::getTitle() const {
    return title;
}

bool Book::isAvailable() const {
    return available && valid;
}

bool Book::isValid() const {
    return valid;
}

void Book::validateBook() {
    valid = true;
    std::string errors = "";

    if (title.empty()) {
        errors += "Title Error: empty; ";
        valid = false;
    }

    if (author.empty()) {
        errors += "Author Error: empty; ";
        valid = false;
    }

    bool isbnNumeric = !isbn.empty();
    for (char c : isbn) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            isbnNumeric = false;
            break;
        }
    }
    if (!isbnNumeric) {
        errors += "ISBN Error: not numeric; ";
        valid = false;
    }

    if (dateAdded.length() != 10 ||
        dateAdded[4] != '-' ||
        dateAdded[7] != '-') {
        errors += "Date Error: wrong format; ";
        valid = false;
    }

    if (!errors.empty()) {
        std::cout << "Book validation errors - "
                  << (title.empty() ? "No title" : title)
                  << ": " << errors << "\n";
    }
}

void Book::display() const {
    if (!valid) {
        std::cout << "INVALID BOOK: "
                  << (title.empty() ? "No title" : title) << "\n";
        return;
    }
    std::cout << "Title: " << title << "\n";
    std::cout << "Author: " << author << "\n";
    std::cout << "ISBN: " << isbn << "\n";
    std::cout << "Available: " << (available ? "Yes" : "No") << "\n";
    std::cout << "Date added: " << dateAdded << "\n";
}

void Book::borrowBook() {
    if (!valid) {
        std::cout << "Cannot borrow \""
                  << (title.empty() ? "No title" : title)
                  << "\" because data is invalid.\n";
        return;
    }
    if (available) {
        available = false;
        std::cout << "You borrowed \"" << title << "\".\n";
    } else {
        std::cout << "The book \"" << title << "\" is not available.\n";
    }
}

void Book::returnBook() {
    if (!valid) {
        std::cout << "Cannot return \""
                  << (title.empty() ? "No title" : title)
                  << "\" because data is invalid.\n";
        return;
    }
    available = true;
    std::cout << "You returned \"" << title << "\".\n";
}

HardcopyBook::HardcopyBook(std::string t, std::string a, std::string i, bool av,
                           std::string date, std::string shelf)
    : Book(t, a, i, av, date), shelfNumber(shelf) {
}

void HardcopyBook::display() const {
    Book::display();
    if (valid) {
        std::cout << "Shelf number: " << shelfNumber << "\n";
    }
}

EBook::EBook(std::string t, std::string a, std::string i,
bool av, std::string date, std::string licenseEnd)
    : Book(t, a, i, av, date), licenseEndDate(licenseEnd) {
}

void EBook::display() const {
    Book::display();
    if (valid) {
        std::cout << "License end date: " << licenseEndDate << "\n";
    }
}

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
