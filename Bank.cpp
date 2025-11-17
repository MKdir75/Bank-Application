#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Account {
    int accountNumber;
    string name;
    double balance;

public:
    Account(int accNo, string accName, double bal = 0.0) {
        accountNumber = accNo;
        name = accName;
        balance = bal;
    }

    int getAccountNumber() const { return accountNumber; }
    string getName() const { return name; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited " << amount << " successfully.\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            cout << "Withdrawn " << amount << " successfully.\n";
        }
    }

    void display() const {
        cout << "Account No: " << accountNumber
             << " | Name: " << name
             << " | Balance: " << balance << endl;
    }

    // Save account to file
    void save(ofstream &out) const {
        out << accountNumber << "," << name << "," << balance << endl;
    }

    // Load account from file
    static Account load(const string &line) {
        int accNo;
        string accName;
        double bal;
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);

        accNo = stoi(line.substr(0, pos1));
        accName = line.substr(pos1 + 1, pos2 - pos1 - 1);
        bal = stod(line.substr(pos2 + 1));

        return Account(accNo, accName, bal);
    }
};

vector<Account> accounts;

// Save all accounts to file
void saveAccounts() {
    ofstream out("accounts.txt");
    for (const auto &acc : accounts) {
        acc.save(out);
    }
    out.close();
}

// Load accounts from file
void loadAccounts() {
    ifstream in("accounts.txt");
    string line;
    while (getline(in, line)) {
        accounts.push_back(Account::load(line));
    }
    in.close();
}

Account* findAccount(int accNo) {
    for (auto &acc : accounts) {
        if (acc.getAccountNumber() == accNo) return &acc;
    }
    return nullptr;
}

int main() {
    loadAccounts();
    int choice;
    do {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int accNo;
            string name;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            accounts.push_back(Account(accNo, name));
            cout << "Account created successfully!\n";
            saveAccounts();
        }
        else if (choice == 2) {
            int accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;
            Account* acc = findAccount(accNo);
            if (acc) {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                acc->deposit(amount);
                saveAccounts();
            } else {
                cout << "Account not found!\n";
            }
        }
        else if (choice == 3) {
            int accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;
            Account* acc = findAccount(accNo);
            if (acc) {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                acc->withdraw(amount);
                saveAccounts();
            } else {
                cout << "Account not found!\n";
            }
        }
        else if (choice == 4) {
            int accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;
            Account* acc = findAccount(accNo);
            if (acc) {
                acc->display();
            } else {
                cout << "Account not found!\n";
            }
        }
        else if (choice == 5) {
            for (const auto &acc : accounts) {
                acc.display();
            }
        }
    } while (choice != 6);

    cout << "Exiting... Accounts saved.\n";
    saveAccounts();
    return 0;
}

