#include <iostream>
 
#include <fstream>
#include <string>

using namespace std;

class Book {
public:
    string bookID, title, author;
    bool issued;

    void getBookDetails() {
        cout << "Enter Book ID: ";
        cin >> bookID;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        issued = false;
    }

    void displayBook() {
        cout << "Book ID: " << bookID << "\nTitle: " << title << "\nAuthor: " << author;
        cout << "\nStatus: " << (issued ? "Issued" : "Available") << "\n";
    }
};
// Function to display all books

void addBook() {
    Book book;
    book.getBookDetails();
    ofstream outFile("library.txt", ios::app);
    outFile << book.bookID << "|" << book.title << "|" << book.author << "|" << book.issued << "\n";
    outFile.close();
    cout << "Book added successfully!\n";
}


void displayBooks() {
    ifstream inFile("library.txt");
    if (!inFile) {
        cout << "No books found!\n";
        return;
    }

    Book book;
    while (inFile >> book.bookID) {
        inFile.ignore();
        getline(inFile, book.title, '|');
        getline(inFile, book.author, '|');
        inFile >> book.issued;
        inFile.ignore();
        book.displayBook();
        cout << "-------------------------\n";
    }
    inFile.close();
}

// Function to search a book
void searchBook(string id) {
    ifstream inFile("library.txt");
    if (!inFile) {
        cout << "No books found!\n";
        return;
    }

    Book book;
    bool found = false;
    while (inFile >> book.bookID) {
        inFile.ignore();
        getline(inFile, book.title, '|');
        getline(inFile, book.author, '|');
        inFile >> book.issued;
        inFile.ignore();

        if (book.bookID == id) {
            cout << "Book Found:\n";
            book.displayBook();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) cout << "Book not found!\n";
}

// Function to issue a book
void issueBook(string id) {
    ifstream inFile("library.txt");
    ofstream outFile("temp.txt");
    Book book;
    bool found = false;

    while (inFile >> book.bookID) {
        inFile.ignore();
        getline(inFile, book.title, '|');
        getline(inFile, book.author, '|');
        inFile >> book.issued;
        inFile.ignore();

        if (book.bookID == id && !book.issued) {
            book.issued = true;
            cout << "Book issued successfully!\n";
            found = true;
        }
        outFile << book.bookID << "|" << book.title << "|" << book.author << "|" << book.issued << "\n";
    }

    inFile.close();
    outFile.close();
    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found) cout << "Book not available for issuing!\n";
}

// Function to return a book
void returnBook(string id) {
    ifstream inFile("library.txt");
    ofstream outFile("temp.txt");
    Book book;
    bool found = false;

    while (inFile >> book.bookID) {
        inFile.ignore();
        getline(inFile, book.title, '|');
        getline(inFile, book.author, '|');
        inFile >> book.issued;
        inFile.ignore();

        if (book.bookID == id && book.issued) {
            book.issued = false;
            cout << "Book returned successfully!\n";
            found = true;
        }
        outFile << book.bookID << "|" << book.title << "|" << book.author << "|" << book.issued << "\n";
    }

    inFile.close();
    outFile.close();
    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found) cout << "Book not found or not issued!\n";
}

// Main function
int main() {
    int choice;
    string bookID;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Display Books\n3. Search Book\n4. Issue Book\n5. Return Book\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                cout << "Enter Book ID to search: ";
                cin >> bookID;
                searchBook(bookID);
                break;
            case 4:
                cout << "Enter Book ID to issue: ";
                cin >> bookID;
                issueBook(bookID);
                break;
            case 5:
                cout << "Enter Book ID to return: ";
                cin >> bookID;
                returnBook(bookID);
                break;
            case 6:
                cout << "Exiting... Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
