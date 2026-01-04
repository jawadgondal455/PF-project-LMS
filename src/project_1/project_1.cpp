#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


struct Book {
    int id;
    string name;
    int quantity;
};
//-------signup-------
void signUp() {
    string username, password;
    bool found = false;

    cout << "\n--- SIGN UP ---\n";
    cout << "Enter username: ";
    cin >> username;

    cin.ignore();
    cout << "Enter password: ";
    getline(cin, password);

    ifstream read("users.txt");
    string line, u, p;

    while (getline(read, line)) {
        stringstream ss(line);
        ss >> u;
        getline(ss, p);

        if (u == username) {
            found = true;
            break;
        }
    }
    read.close();

    if (found==true) {
        cout << "User already exists!\n Try another username\n";
    } else {
        ofstream write("users.txt", ios::app);
        write << username << " " << password << endl;
        write.close();
        cout << "Sign Up Successful\n";
    }
}
//--------signin-------
bool signIn() {
    string username, password;

    cout << "\n--- SIGN IN ---\n";
    cout << "Enter username: ";
    cin >> username;

    cin.ignore();
    cout << "Enter password: ";
    getline(cin, password);

    ifstream read("users.txt");
    string line, u, p;

    while (getline(read, line)) {
        stringstream ss(line);
        ss >> u;
        getline(ss, p);

        if (u == username && p.substr(1) == password) {
            cout << "Login Successful! Welcome " << username << endl;
            return true;
        }
    }

    cout << "Invalid username or password!\n";
    return false;
}

// ------- ADD BOOK -------
void addbook() {
    Book b;

    cout << "\n--- ADD BOOK ---\n";
    cout << "Enter Book ID: ";
    cin >> b.id;

    cin.ignore();
    cout << "Enter Book Name: ";
    getline(cin, b.name);

    cout << "Enter Quantity: ";
    cin >> b.quantity;

    ofstream write("books.txt", ios::app);
    write << b.id << " " << b.name << " " << b.quantity << endl;
    write.close();

    cout << "Book added successfully\n";
}

// ------- VIEW BOOKS -------
void viewbooks() {
    ifstream read("books.txt");
    Book b;

    cout << "\nID\tName\t\tQuantity\n";
    cout << "--------------------------------\n";

    while (read >> b.id >> b.name >> b.quantity) {
        cout << b.id << "\t" << b.name << "\t\t" << b.quantity << endl;
    }
    read.close();
}

// ------- UPDATE bOOK -------
void updatebook() {
    int searchID;
    bool found = false;

    cout << "\nEnter Book ID to update: ";
    cin >> searchID;

    ifstream read("books.txt");
    ofstream write("temp.txt");

    Book b;

    while (read >> b.id >> b.name >> b.quantity) {
        if (b.id == searchID) {
            int newQty;
            cout << "Enter new quantity: ";
            cin >> newQty;

            write << b.id << " " << b.name << " " << newQty << endl;
            found = true;
        } else {
            write << b.id << " " << b.name << " " << b.quantity << endl;
        }
    }

    read.close();
    write.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        cout << "Book updated successfully!\n";
    else
        cout << "Book not found!\n";
}

// ------- DELETE BOOK -------
void deletebook() {
    int searchID;
    bool found = false;

    cout << "\nEnter Book ID to delete: ";
    cin >> searchID;

    ifstream read("books.txt");
    ofstream write("temp.txt");

    Book b;

    while (read >> b.id >> b.name >> b.quantity) {
        if (b.id == searchID) {
            found = true;   
        } else {
            write << b.id << " " << b.name << " " << b.quantity << endl;
        }
    }

    read.close();
    write.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        cout << "Book deleted successfully!\n";
    else
        cout << "Book not found!\n";
}
// ------- issuebook  -------
void issuebook() {
    int issueID;
    bool found = false;

    cout << "\nEnter Book ID to Issue: ";
    cin >> issueID;

    ifstream read("books.txt");
    ofstream write("temp.txt");

    Book b;

    while (read >> b.id >> b.name >> b.quantity) {
        if (b.id == issueID) {
            found = true;

            if (b.quantity > 0) {
                b.quantity--;
                cout << "Book Issued Successfully!\n";
                cout << "Remaining Quantity: " << b.quantity << endl;
            } else {
                cout << "Book Out of Stock!\n";
            }
        }
        write << b.id << " " << b.name << " " << b.quantity << endl;
    }

    read.close();
    write.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "Book Not Found!\n";
}
//------- returnbook  -------
void returnbook() {
    int returnID;
    bool found = false;

    cout << "\nEnter Book ID to Return: ";
    cin >> returnID;

    ifstream read("books.txt");
    ofstream write("temp.txt");

    Book b;

    while (read >> b.id >> b.name >> b.quantity) {
        if (b.id == returnID) {
            found = true;
            b.quantity++;
            cout << "Book Returned Successfully!\n";
            cout << "Updated Quantity: " << b.quantity << endl;
        }
        write << b.id << " " << b.name << " " << b.quantity << endl;
    }

    read.close();
    write.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "Book Not Found!\n";
}

// ------- LIBRARY MENU -------
void librarymenu() {
    int choice;

    do {
        cout << "\n--- LIBRARY MENU ---\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Update Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            addbook();
        else if (choice == 2)
            viewbooks();
        else if (choice == 3)
            updatebook();
        else if (choice == 4)
            deletebook();
        else if (choice == 5)
            issuebook();
        else if (choice == 6)
            returnbook();
        else if (choice == 7)
            cout << "Logged out successfully.\n";
        else
            cout << "Invalid choice!\n";

    } while (choice != 7);
}

int main() {
    int choice;
    bool exitProgram = false;

    do {
        cout << "\n-------LIBRARY MANAGEMENT SYSTEM ------\n";
        cout << "1. Sign Up\n";
        cout << "2. Sign In\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            signUp();
        }
        else if (choice == 2) {
            if (signIn()) {
                // agr too signin true huwa too hi librarymenu wala function chala ga 
                librarymenu();
            }
        }
        else if (choice == 3) {
            cout << "Program exit ho raha hai...\n";
            exitProgram = true;
        }
        else {
            cout << "Invalid choice! Dobara try karo.\n";
        }

    } while (!exitProgram);

    return 0;

}




