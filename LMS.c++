// Project: Simple Library Management System
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>
using namespace std;
// Book structure definition
struct Book {
    int id;
    string title;
    string author;
    bool available;
    string borrower;

    // Constructor to initialize a book
    Book(int id, string title, string author) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->available = true;   // Initially all books are available
        this->borrower = "";      // No borrower initially
    }
};

// Library class definition
class Library {
private:
    vector<Book> books;  // Vector to store books

public:
    // Function to add a new book to the library
    void addBook(int id, string title, string author) {
        Book newBook(id, title, author);    // Create a new book object
        books.push_back(newBook);           // Add the new book to the vector
        cout << "Book added successfully.\n";
    }

    // Function to search for a book by its title
    void searchByTitle(string title) {
        bool found = false;
        for (const auto& book : books) {
            if (book.title == title) {      // Check if the title matches
                displayBookDetails(book);   // Display book details if found
                found = true;
            }
        }
        if (!found) {
            cout << "Book with title '" << title << "' not found.\n";
        }
    }

    // Function to search for a book by its ID
    void searchById(int id) {
        bool found = false;
        for (const auto& book : books) {
            if (book.id == id) {            // Check if the ID matches
                displayBookDetails(book);   // Display book details if found
                found = true;
            }
        }
        if (!found) {
            cout << "Book with ID '" << id << "' not found.\n";
        }
    }

    // Function to issue a book to a student
    void issueBook(int id, string studentName) {
        for (auto& book : books) {
            if (book.id == id && book.available) {
                book.available = false;     // Mark the book as issued
                book.borrower = studentName; // Record the borrower's name
                cout << "Book '" << book.title << "' issued to " << studentName << ".\n";
                return;
            }
        }
        cout << "Book with ID '" << id << "' is either not available or does not exist.\n";
    }

    // Function to return a book to the library
    void returnBook(int id) {
        for (auto& book : books) {
            if (book.id == id && !book.available) {
                book.available = true;      // Mark the book as available
                book.borrower = "";         // Clear borrower information
                cout << "Book '" << book.title << "' returned successfully.\n";
                return;
            }
        }
        cout << "Book with ID '" << id << "' is either already available or does not exist.\n";
    }

    // Function to list all books in the library
    void listAllBooks() {
        if (books.empty()) {
            cout << "Library is empty.\n";
            return;
        }

        cout << "List of all books in the library:\n";
        for (const auto& book : books) {
            displayBookDetails(book);   // Display details of each book
        }
    }

    // Function to delete a book from the library
    void deleteBook(int id) {
        auto it = remove_if(books.begin(), books.end(), [id](const Book& book) {
            return book.id == id;       // Predicate to remove book with matching ID
        });
        if (it != books.end()) {
            books.erase(it, books.end());   // Erase the book from the vector
            cout << "Book with ID '" << id << "' deleted successfully.\n";
        } else {
            cout << "Book with ID '" << id << "' not found.\n";
        }
    }

private:
    // Helper function to display details of a book
    void displayBookDetails(const Book& book) {
        cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author;
        if (book.available) {
            cout << ", Status: Available\n";
        } else {
            cout << ", Status: Issued to " << book.borrower << "\n";
        }
    }
};

// Function to display menu and get user choice
int displayMenuAndGetChoice() {
    int choice;
    cout << "\n------ Library Management System Menu ------\n";
    cout << "1. Add a new book\n";
    cout << "2. Search for a book by title\n";
    cout << "3. Search for a book by ID\n";
    cout << "4. Issue a book\n";
    cout << "5. Return a book\n";
    cout << "6. List all books\n";
    cout << "7. Delete a book\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main() {
    Library library;
    int choice;
    string title, author, studentName;
    int id;

    do {
        choice = displayMenuAndGetChoice();    // Display menu and get user choice

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                library.addBook(id, title, author);
                break;

            case 2:
                cout << "Enter book title to search: ";
                getline(cin, title);
                library.searchByTitle(title);
                break;

            case 3:
                cout << "Enter book ID to search: ";
                cin >> id;
                library.searchById(id);
                break;

            case 4:
                cout << "Enter book ID to issue: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter student name: ";
                getline(cin, studentName);
                library.issueBook(id, studentName);
                break;

            case 5:
                cout << "Enter book ID to return: ";
                cin >> id;
                library.returnBook(id);
                break;

            case 6:
                library.listAllBooks();
                break;

            case 7:
                cout << "Enter book ID to delete: ";
                cin >> id;
                library.deleteBook(id);
                break;

            case 8:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number from 1 to 8.\n";
                break;
        }

        #ifdef _WIN32
        system("pause");    // Pause screen on Windows
        #else
        system("clear");    // Clear screen on other systems
        #endif

    } while (choice != 8);   // Repeat until user chooses to exit

    return 0;
}