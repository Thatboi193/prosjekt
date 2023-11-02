#include <iostream>
#include <fstream>

using namespace std;

class User {
public:
    string name;
    double balance;

    void saveToFile() {
        ofstream outFile("users.txt", ios::app);  // Open file in append mode
        if (outFile.is_open()) {
            outFile << name << " " << balance << endl;  // Write name and balance to file
            outFile.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
        fam();
    }

    void makeUser() {
        cout << "Please enter Name and starting balance: " << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Balance: ";
        cin >> balance;
        saveToFile();  // Save user info to file after creating
        fam();
    }

    void login() {
        string username;
        cout << "Login to account" << endl;
        cout << "Username: ";
        cin >> username;
        ifstream inFile("users.txt");  // Open file in read mode
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {  // Read file line by line
                if (line.find(username) != string::npos) {  // Check if username is found
                    cout << "Login successful" << endl;
                    name = username;  // Set name to the logged-in username
                    // please make work processing to extract and set balance
                    break;
                }
            }
            inFile.close();
        } else {
            cout << "Unable to open file for reading." << endl;
        }
        fam();
    }

    void deposit() {
        double newAmount;
        cout << "Add money to account balance" << endl;
        cin >> newAmount;
        balance += newAmount;
        cout << "New balance is " << balance << endl;
        fam();
    }

    void withdraw() {
        double newAmount;
        cout << "Remove money from account balance" << endl;
        cin >> newAmount;
        balance -= newAmount;  // Corrected to subtract newAmount from balance
        cout << "New balance is " << balance << endl;
        fam();
    }

    void fam() {
        int menu;
        cout << name << " Balance: " << balance << endl;  // Corrected to display name
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw"  << endl;
        cout << "3. Exit" << endl;
        cin >> menu;
        switch (menu) {
            case 1:
                deposit();
                break;
            case 2:
                withdraw();
                break;
            case 3:
                mainmenu();
                break;
        }
    }

    void mainmenu() {
      	cout << "1. Login" << endl;
       	cout << "2. Register" << endl;
      	cout << "3. Exit" << endl;
        int mm;
        cin >> mm;
        switch (mm) {
            case 1:
                login();
                break;
            case 2:
                makeUser();
                break;
            case 3:
                system("explorer.exe");
                break;
            default:
                cout << "Invalid option";
                break;
        }
    }

    void showBalance() {
        cout << balance;
        fam();
    }
};

int main() {
    User user1;
    user1.mainmenu();
    return 0;
}
