// Include necessary header files
#include <iostream> // for input and output streams
#include <fstream>  // for file streams
#include <vector>   // for using the vector container
#include <sstream>  // for string stream operations
#include <string>   // for string operations

// Use the standard namespace to avoid prefixing with std::
using namespace std;

// Define a User class to store user details and perform user-related operations
class User {
public:
    string name;    // Stores the user's name
    double balance; // Stores the user's account balance

    // Reads all users from the "users.txt" file and returns them as a vector of User objects
    vector<User> readAllUsers() {
        vector<User> users; // A vector to hold all users
        ifstream inFile("users.txt"); // Input file stream to read from the users file
        string line; // Variable to hold each line from the file
        // Read the file line by line
        while (getline(inFile, line)) {
            istringstream iss(line); // Use string stream to parse the line
            User user; // Create a temporary User object
            // Parse the line into name and balance and add to the vector if successful
            if (iss >> user.name >> user.balance) {
                users.push_back(user);
            }
        }
        inFile.close(); // Close the file stream
        return users; // Return the vector of users
    }

    // Saves the current user to the "users.txt" file
    void saveToFile() {
        vector<User> users = readAllUsers(); // Read the existing users
        bool userExists = false; // Flag to check if the current user exists in the file

        // Check if the current user already exists in the list
        for (User& user : users) {
            if (user.name == this->name) {
                user.balance = this->balance; // Update the existing user's balance
                userExists = true; // Set the flag
                break;
            }
        }

        // If the user does not exist, add them to the list
        if (!userExists) {
            users.push_back(*this);
        }

        // Open the file in truncate mode to overwrite and save all users
        ofstream outFile("users.txt", ios::trunc); 
        if (outFile.is_open()) {
            // Write each user's name and balance to the file
            for (const User& user : users) {
                outFile << user.name << " " << user.balance << endl;
            }
            outFile.close(); // Close the file stream
        } else {
            // Error handling if the file cannot be opened
            cout << "Unable to open file for writing." << endl;
        }
    }

    // Allows a new user to create an account
    void makeUser() {
        // Prompt the user for their name and starting balance
        cout << "Please enter Name and starting balance: " << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Balance: ";
        cin >> balance;
        saveToFile(); // Save the new user to file
        accountMenu(); // Show the account menu
    }

    // Allows a user to log in to their account
    void login() {
        string username; // Variable to store the username entered by the user
        cout << "Login to account" << endl;
        cout << "Username: ";
        cin >> username; // Input the username
        ifstream inFile("users.txt"); // Open the file stream for reading
        if (inFile.is_open()) {
            string line; // Variable to hold each line from the file
            // Read the file line by line
            while (getline(inFile, line)) {
                istringstream iss(line); // Use string stream to parse the line
                string extractedName; // Variable to hold the extracted name
                double extractedBalance; // Variable to hold the extracted balance
                // Check if the line contains the entered username and its balance
                if (iss >> extractedName >> extractedBalance && extractedName == username) {
                    cout << "Login successful" << endl;
                    name = extractedName; // Set the current user's name
                    balance = extractedBalance; // Set the current user's balance
                    inFile.close(); // Close the file stream
                    accountMenu(); // Show the account menu
                    return;
                }
            }
            // If the user is not found, display an error message
            cout << "Login failed: User not found." << endl;
            inFile.close(); // Close the file stream
        } else {
            // Error handling if the file cannot be opened
            cout << "Unable to open file for reading." << endl;
        }
    }

    // Allows a user to deposit money into their account
    void deposit() {
        double newAmount; // Variable to hold the deposit amount
        cout << "Add money to account balance" << endl;
        cin >> newAmount; // Input the deposit amount
        balance += newAmount; // Update the balance
        cout << "New balance is " << balance << endl; // Display the new balance
        saveToFile(); // Save the updated balance to file
        accountMenu(); // Show the account menu
    }

    // Allows a user to withdraw money from their account
    void withdraw() {
        double newAmount; // Variable to hold the withdrawal amount
        cout << "Remove money from account balance" << endl;
        cin >> newAmount; // Input the withdrawal amount
        // Check if the withdrawal amount is less than or equal to the balance
        if(newAmount <= balance) {
            balance -= newAmount; // Update the balance
            cout << "New balance is " << balance << endl; // Display the new balance
        } else {
            // Display an error message if there is insufficient balance
            cout << "Insufficient balance." << endl;
        }
        saveToFile(); // Save the updated balance to file
        accountMenu(); // Show the account menu
    }

    // Displays the account menu and allows the user to select an option
    void accountMenu() {
        int menu; // Variable to hold the menu choice
        // Display the user's balance and menu options
        cout << name << " Balance: " << balance << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Logout" << endl;
        cin >> menu; // Input the menu choice
        // Switch statement to handle the menu choice
        switch (menu) {
            case 1: // Deposit
                deposit();
                break;
            case 2: // Withdraw
                withdraw();
                break;
            case 3: // Logout
                cout << "Logging out." << endl;
                break;
            default: // Invalid option
                cout << "Invalid option. Please try again." << endl;
                accountMenu(); // Show the account menu again
                break;
        }
    }

    // Displays the main menu and allows the user to select an option
    void mainMenu() {
        int mm; // Variable to hold the main menu choice
        // Display the main menu options
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cin >> mm; // Input the main menu choice
        // Switch statement to handle the main menu choice
        switch (mm) {
            case 1: // Login
                login();
                break;
            case 2: // Register
                makeUser();
                break;
            case 3: // Exit
                cout << "Exiting program." << endl;
                break;
            default: // Invalid option
                cout << "Invalid option. Please try again." << endl;
                mainMenu(); // Show the main menu again
                break;
        }
    }
};

// The main function - entry point of the program
int main() {
    User user; // Create a User object
    user.mainMenu(); // Display the main menu
    return 0; // Return success status
}
