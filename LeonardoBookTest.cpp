#include <iostream>
#include <string>
#include "Book.h"
using namespace std;

int main() {
    cout << "=== ICT0008 A3 Test Application (Leonardo) ===\n\n";

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

    cout << "TEST 2 - INCORRECT BOOKS\n\n";

    HardcopyBook* bad1 = new HardcopyBook(
        "I'm Glad My Mom Died", "Jennette McCurdy",
        "ABC123", true, "11-01-2025", "X1");

    HardcopyBook* bad2 = new HardcopyBook(
        "One of Us Is Lying", "",
        "9780141375632", true, "2025/11/01", "B3");

    EBook* bad3 = new EBook(
        "The Handmaid's Tale", "Margaret Atwood",
        "978X9740919", true, "2025-11", "2026-12");

    Book* badBooks[3] = { bad1, bad2, bad3 };

    for (int i = 0; i < 3; i++) {
        cout << "Bad Book " << (i + 1) << ":\n";
        badBooks[i]->display();
        cout << "---------------------\n";
    }
    cout << "\n";

    cout << "TEST 3 - SORTING BY TITLE (A-Z)\n\n";

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
            found = false;
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

    for (int i = 0; i < 6; i++) {
        delete allBooks[i];
    }

    return 0;
}
