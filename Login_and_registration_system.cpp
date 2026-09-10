#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool usernameExists(string username)
{
    ifstream file("users.txt");

    string storedUsername, storedPassword;

    while (file >> storedUsername >> storedPassword)
    {
        if (storedUsername == username)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void registerUser()
{
    string username, password;

    cout << "\n===== Registration =====\n";
    cout << "Enter username: ";
    cin >> username;

    if (usernameExists(username))
    {
        cout << "Username already exists.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    if (username.length() < 3)
    {
        cout << "Username must contain at least 3 characters.\n";
        return;
    }

    if (password.length() < 6)
    {
        cout << "Password must contain at least 6 characters.\n";
        return;
    }

    ofstream file("users.txt", ios::app);

    file << username << " " << password << endl;

    file.close();

    cout << "Registration successful.\n";
}

void loginUser()
{
    string username, password;

    cout << "\n===== Login =====\n";
    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");

    string storedUsername, storedPassword;
    bool loginSuccess = false;

    while (file >> storedUsername >> storedPassword)
    {
        if (storedUsername == username &&
            storedPassword == password)
        {
            loginSuccess = true;
            break;
        }
    }

    file.close();

    if (loginSuccess)
        cout << "Login successful. Welcome, " << username << "!\n";
    else
        cout << "Invalid username or password.\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n================================\n";
        cout << "     LOGIN & REGISTRATION\n";
        cout << "================================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            registerUser();
            break;

        case 2:
            loginUser();
            break;

        case 3:
            cout << "\nThank you for using the system.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}