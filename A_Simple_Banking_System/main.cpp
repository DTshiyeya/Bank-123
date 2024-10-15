#include <iostream>
#include <unordered_map>
#include <string>
#include <limits> // For numeric limits

using namespace std;

class bankAccount {
public:
    string username;
    string password;
    int accountNumber;
    double balance;

    bankAccount(string user, string pass, int accNum)
        : username(user), password(pass), accountNumber(accNum), balance(0.0) {}

    bankAccount() : username(""), password(""), accountNumber(0), balance(0.0) {}
};

unordered_map<int, bankAccount>accounts; // Stores account numbers and account details
int accountCounter = 100; // Unique account number generator
int loggedInAccountNumber = -1; // Track logged-in account

void createAccount() {
    string username, password;
    cout<<"Enter a new username: ";
    cin>>username;
    cout<<"Enter a new password: ";
    cin>>password;
    int accountNumber = accountCounter++; // Increment account number for each new account
    accounts[accountNumber] = bankAccount(username, password, accountNumber);
    cout<<endl;
    cout<<"Account created successfully! "<<endl;
    cout<<"Your account number is: "<<accountNumber<<endl;
}

void login() {
    if (accounts.empty()) {
        cout<<"No accounts available. Please create an account first.\n";
        return;
    }

    string username, password;
    cout<<"Enter your username: ";
    cin>>username;
    cout<<"Enter your password: ";
    cin>>password;

    // Check if the username and password match
    for (const auto& account : accounts) {
        if (account.second.username == username && account.second.password == password) {
            loggedInAccountNumber = account.first; // Set the logged-in account number
            cout<<"Login successful! "<<endl;
            cout<<endl;
            cout<<"Welcome, "<<username<<"!!!";
            return;
        }
    }
    cout<<"Invalid username or password. Try again.\n";
}

void depositMoney() {
    if (loggedInAccountNumber == -1) {
        cout<<"You must be logged in to perform this operation.\n";
        return;
    }

    double amount;
    cout<<"Enter the amount to deposit: R";
    cin>>amount;

    // Check for valid input
    if (cin.fail() || amount <= 0) {
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout<<"Invalid amount. Please enter a positive value.\n";
        return;
    }

    accounts[loggedInAccountNumber].balance += amount;
    cout<<"Deposit successful. Your new balance is: R"<<accounts[loggedInAccountNumber].balance<<"\n";
}

void withdrawMoney() {
    if (loggedInAccountNumber == -1) {
        cout << "You must be logged in to perform this operation.\n";
        return;
    }

    double amount;
    cout<<"Enter the amount to withdraw: R";
    cin>>amount;

    // Check for valid input
    if (cin.fail() || amount <= 0) {
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout<<"Invalid amount. Please enter a positive value.\n";
        return;
    }

    if (amount>accounts[loggedInAccountNumber].balance) {
        cout<<"Insufficient funds. Your current balance is: "<<accounts[loggedInAccountNumber].balance<<"\n";
    }
    else {
        accounts[loggedInAccountNumber].balance -= amount;
        cout<<"Withdrawal successful. Your new balance is: R"<<accounts[loggedInAccountNumber].balance<<"\n";
    }
}

void checkBalance() {
    if (loggedInAccountNumber == -1) {
        cout<<"You must be logged in to check your balance.\n";
        return;
    }

    cout<<"Your current balance is: R"<<accounts[loggedInAccountNumber].balance<<"\n";
}

void logout() {
    loggedInAccountNumber = -1;
    cout<<"Logged out successfully.\n";
}

int main() {
    int choice;

    while (true) {
        if (loggedInAccountNumber == -1) {
            // Main menu (when no user is logged in)
            cout<<"\n---Simple Bank System---\n";
            cout<<"1. Create Account\n";
            cout<<"2. Login\n";
            cout<<"3. Exit\n";
            cout<<"Enter your choice: ";
            cin>>choice;

            // Check for valid input
            if (cin.fail()) {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout<<"Invalid choice. Please enter a number.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    login();
                    break;
                case 3:
                    cout<<"Exiting...\n";
                    return 0;
                default:
                    cout<<"Invalid choice. Please try again.\n";
            }
        }
        else {
            // Transaction menu (when a user is logged in)
            cout<<"\n---Transaction Menu---\n";
            cout<<"1. Deposit Money\n";
            cout<<"2. Withdraw Money\n";
            cout<<"3. Check Balance\n";
            cout<<"4. Logout\n";
            cout<<"Enter your choice: ";
            cin>>choice;

            // Check for valid input
            if (cin.fail()) {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout<<"Invalid choice. Please enter a number.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    depositMoney();
                    break;
                case 2:
                    withdrawMoney();
                    break;
                case 3:
                    checkBalance();
                    break;
                case 4:
                    logout();
                    break;
                default:
                    cout<<"Invalid choice. Please try again.\n";
            }
        }
    }

    return 0;
}
