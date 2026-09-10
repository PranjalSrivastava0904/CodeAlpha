#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Transaction
{
public:
    string type;
    double amount;
    string details;

    Transaction()
    {
        type = "";
        amount = 0;
        details = "";
    }

    Transaction(string t, double a, string d)
    {
        type = t;
        amount = a;
        details = d;
    }
};

class Account
{
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account()
    {
        accountNumber = 0;
        balance = 0;
    }

    Account(int accNo, double bal = 0)
    {
        accountNumber = accNo;
        balance = bal;
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    double getBalance()
    {
        return balance;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid amount.\n";
            return;
        }

        balance += amount;

        transactions.push_back(
            Transaction("Deposit", amount, "Money deposited")
        );

        cout << "Amount deposited successfully.\n";
    }

    bool withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid amount.\n";
            return false;
        }

        if (amount > balance)
        {
            cout << "Insufficient balance.\n";
            return false;
        }

        balance -= amount;

        transactions.push_back(
            Transaction("Withdrawal", amount, "Money withdrawn")
        );

        cout << "Amount withdrawn successfully.\n";
        return true;
    }

    bool transferTo(Account &receiver, double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid amount.\n";
            return false;
        }

        if (amount > balance)
        {
            cout << "Insufficient balance.\n";
            return false;
        }

        balance -= amount;
        receiver.balance += amount;

        transactions.push_back(
            Transaction(
                "Transfer",
                amount,
                "Transferred to account " +
                to_string(receiver.accountNumber)
            )
        );

        receiver.transactions.push_back(
            Transaction(
                "Received",
                amount,
                "Received from account " +
                to_string(accountNumber)
            )
        );

        cout << "Fund transferred successfully.\n";
        return true;
    }

    void showTransactions()
    {
        if (transactions.empty())
        {
            cout << "No transactions available.\n";
            return;
        }

        cout << "\nTransaction History\n";
        cout << "-------------------------------\n";

        for (auto &t : transactions)
        {
            cout << "Type    : " << t.type << endl;
            cout << "Amount  : Rs. " << fixed << setprecision(2)
                 << t.amount << endl;
            cout << "Details : " << t.details << endl;
            cout << "-------------------------------\n";
        }
    }

    void showAccountInfo()
    {
        cout << "\nAccount Information\n";
        cout << "-------------------------------\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Balance        : Rs. "
             << fixed << setprecision(2)
             << balance << endl;
    }
};

class Customer
{
private:
    int customerId;
    string name;
    string phone;
    Account account;

public:
    Customer()
    {
        customerId = 0;
        name = "";
        phone = "";
    }

    Customer(int id, string n, string p, int accNo)
    {
        customerId = id;
        name = n;
        phone = p;
        account = Account(accNo);
    }

    int getCustomerId()
    {
        return customerId;
    }

    int getAccountNumber()
    {
        return account.getAccountNumber();
    }

    Account &getAccount()
    {
        return account;
    }

    void showCustomerInfo()
    {
        cout << "\nCustomer Information\n";
        cout << "-------------------------------\n";
        cout << "Customer ID    : " << customerId << endl;
        cout << "Name           : " << name << endl;
        cout << "Phone          : " << phone << endl;
        cout << "Account Number : "
             << account.getAccountNumber() << endl;
        cout << "Balance        : Rs. "
             << fixed << setprecision(2)
             << account.getBalance() << endl;
    }
};

vector<Customer> customers;

void saveCustomers()
{
    ofstream file("customers.txt");

    for (auto &customer : customers)
    {
        file << customer.getCustomerId() << " "
             << customer.getAccountNumber() << " "
             << customer.getAccount().getBalance() << endl;
    }

    file.close();
}

void createCustomer()
{
    int id;
    int accountNumber;
    string name;
    string phone;

    cout << "\nEnter Customer ID: ";
    cin >> id;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Phone Number: ";
    cin >> phone;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    Customer customer(id, name, phone, accountNumber);

    customers.push_back(customer);

    saveCustomers();

    cout << "\nCustomer and account created successfully.\n";
}

Customer *findCustomerByAccount(int accountNumber)
{
    for (auto &customer : customers)
    {
        if (customer.getAccountNumber() == accountNumber)
            return &customer;
    }

    return nullptr;
}

void depositMoney()
{
    int accountNumber;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    Customer *customer = findCustomerByAccount(accountNumber);

    if (customer == nullptr)
    {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter Deposit Amount: ";
    cin >> amount;

    customer->getAccount().deposit(amount);

    saveCustomers();
}

void withdrawMoney()
{
    int accountNumber;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    Customer *customer = findCustomerByAccount(accountNumber);

    if (customer == nullptr)
    {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter Withdrawal Amount: ";
    cin >> amount;

    if (customer->getAccount().withdraw(amount))
        saveCustomers();
}

void transferMoney()
{
    int senderAccount;
    int receiverAccount;
    double amount;

    cout << "\nEnter Sender Account Number: ";
    cin >> senderAccount;

    cout << "Enter Receiver Account Number: ";
    cin >> receiverAccount;

    Customer *sender =
        findCustomerByAccount(senderAccount);

    Customer *receiver =
        findCustomerByAccount(receiverAccount);

    if (sender == nullptr || receiver == nullptr)
    {
        cout << "One or both accounts not found.\n";
        return;
    }

    if (sender == receiver)
    {
        cout << "Sender and receiver cannot be the same account.\n";
        return;
    }

    cout << "Enter Transfer Amount: ";
    cin >> amount;

    if (sender->getAccount().transferTo(
            receiver->getAccount(), amount))
    {
        saveCustomers();
    }
}

void showCustomer()
{
    int accountNumber;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    Customer *customer =
        findCustomerByAccount(accountNumber);

    if (customer == nullptr)
    {
        cout << "Account not found.\n";
        return;
    }

    customer->showCustomerInfo();
}

void showTransactions()
{
    int accountNumber;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    Customer *customer =
        findCustomerByAccount(accountNumber);

    if (customer == nullptr)
    {
        cout << "Account not found.\n";
        return;
    }

    customer->getAccount().showTransactions();
}

int main()
{
    int choice;

    do
    {
        cout << "\n=================================\n";
        cout << "       BANKING MANAGEMENT SYSTEM\n";
        cout << "=================================\n";
        cout << "1. Create Customer and Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Show Account Information\n";
        cout << "6. Show Transaction History\n";
        cout << "7. Exit\n";
        cout << "=================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createCustomer();
            break;

        case 2:
            depositMoney();
            break;

        case 3:
            withdrawMoney();
            break;

        case 4:
            transferMoney();
            break;

        case 5:
            showCustomer();
            break;

        case 6:
            showTransactions();
            break;

        case 7:
            cout << "\nThank you for using the Banking System.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}