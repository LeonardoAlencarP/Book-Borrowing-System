#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
protected:
    std::string title;
    std::string author;
    std::string isbn;
    bool available;
    std::string dateAdded;
    bool valid;

public:
    Book(std::string t, std::string a, std::string i, bool av, std::string date);
    virtual ~Book();

    std::string getIsbn() const;
    std::string getTitle() const;
    bool isAvailable() const;
    bool isValid() const;

    void validateBook();
    virtual void display() const;
    void borrowBook();
    void returnBook();
};

class HardcopyBook : public Book {
private:
    std::string shelfNumber;

public:
    HardcopyBook(std::string t, std::string a, std::string i, bool av,
                 std::string date, std::string shelf);

    void display() const override;
};

class EBook : public Book {
private:
    std::string licenseEndDate;

public:
    EBook(std::string t, std::string a, std::string i, bool av,
          std::string date, std::string licenseEnd);

    void display() const override;
};

void sortBooks(Book* books[], int size);

#endif
