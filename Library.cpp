
       //comments
        inFile.ignore();
        getline(inFile, book.title, '|');
        getline(inFile, book.author, '|');
        inFile >> book.issued;
        inFile.ignore();
        book.displayBook();
        cout << "----------------------\n";
    }
    inFile.close(); //Closing the file after witing to it
}

//Function to search for book
void searchBook(string id) {
    ifstream inFile("library.txt"); //Opening the file
    if (!inFile) {
        cout << "No books found!\n";
        return;
    }

    Book book;
    bool found = false;
    while (inFile >> book.bookID) {  //Iteration in the file to check the searched book
        
        getline(inFile, book.title, '|');
        getline(inFile, book.author, '|');
        inFile >> book.issued;
        inFile.ignore();

        if (book.bookID == id) { //Condition that measures the resembelence betwwen each line in the file and the entered boook ID
        
            book.displayBook(); //If book is found the it will invoke function displayBook(), so as to display it
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) cout << "Book not found!\n";
}

//Function to Issue book from library
void issueBook(string id) {
    ifstream inFile("library.txt"); //Opening and Reading file library.txt where book details stored
    ofstream outFile("temp.txt"); //Opening and writing to the temoporay file (temp.txt) for the isssued book
    Book book;
    bool found = false;

    //Loop to find the book that a user want to be issued by it.
    while (inFile >> book.bookID) {
        inFile.ignore();
        getline(inFile, book.title, '|');
        getline(inFile, book.author, '|');
        inFile >> book.issued;
        inFile.ignore();

        //Check if the book is available to be issued as it is not issued
        if (book.bookID == id && !book.issued) {
            book.issued = true;
            cout << "Book issued successfully!\n";
            found = true;
        }
        outFile << book.bookID << "|" << book.title << "|" << book.author << "|" << book.issued << "\n";
    }

    inFile.close();//Closing the file lirary.txt
    outFile.close(); //Closing the file, temp.txt
    remove("library.txt"); //The file is removed as the updates are done in another file so it removed so as to be replaced by the updated file
    rename("temp.txt", "library.txt"); //Renaming the file temp.txt as thhe new library.txt file

    if (!found) cout << "Book not available for issuing!\n";
}


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


    return 0;
}
