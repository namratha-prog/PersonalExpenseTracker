#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Transaction {
    string type;
    string description;
    float amount;
};

vector<Transaction> transactions;

void loadTransactions() {
    ifstream file("transactions.txt");
    Transaction t;
    while (file >> t.type >> t.amount) {
        file.ignore(); // ignore space
        getline(file, t.description);
        transactions.push_back(t);
    }
    file.close();
}

void saveTransaction(const Transaction& t) {
    ofstream file("transactions.txt", ios::app);
    file << t.type << " " << t.amount << " " << t.description << endl;
    file.close();
}

void addTransaction() {
    Transaction t;
    cout << "Enter type (Income/Expense): ";
    cin >> t.type;
    cout << "Enter amount: ";
    cin >> t.amount;
    cin.ignore();
    cout << "Enter description: ";
    getline(cin, t.description);

    transactions.push_back(t);
    saveTransaction(t);

    cout << "Transaction added successfully.\n";
}

void viewTransactions() {
    float balance = 0;
    cout << "\n--- Transaction History ---\n";
    for (const auto& t : transactions) {
        cout << t.type << " - Rs." << t.amount << " - " << t.description << endl;
        if (t.type == "Income") balance += t.amount;
        else if (t.type == "Expense") balance -= t.amount;
    }
    cout << "\nCurrent Balance: Rs." << balance << "\n";
}

int main() {
    loadTransactions();
    int choice;

    do {
        cout << "\n====== Personal Expense Tracker ======\n";
        cout << "1. Add Transaction\n";
        cout << "2. View All Transactions\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTransaction(); break;
            case 2: viewTransactions(); break;
            case 3: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}