#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class User
{
protected:
    string username;
    string password;

public:
    User(const string &_username, const string &_password) : username(_username), password(_password) {}

    bool isLoggedIn()
    {
        string username, password, un, pw;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password:";
        cin >> password;

        ifstream read("username.txt");
        getline(read, un);
        getline(read, pw);
        if (un == username && pw == password)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Account;  

void displayAccountInfo(const Account &account);

class Account : public User
{
private:
    int Etheral, balance;
    int bitcoin;
    int deposit, withdraw;
    int total_equity = 100;
    int predict;
    int Etheral_value;
    int bitcoin_value;
    int crypto_invest;
    int crypto_return;
    vector<pair<string, int>> transactions;

public:
    Account(const string &_username, const string &_password)
        : User(_username, _password), crypto_invest(0), crypto_return(0), balance(50000),
          Etheral(0), bitcoin(0), withdraw(0), deposit(0), Etheral_value(100), bitcoin_value(500) {}
    bool Deposit(int money)
    {
        deposit += money;
        balance += money;
        transactions.push_back({"Deposit:", money});
        return true;
    }

    void Get_account_information()
    {
        cout << "Money Details:\n";
        cout << "Bank Balance:" << balance << endl;
        cout << "Etheral:" << Etheral << endl;
        cout << "Bitcoin:" << bitcoin << endl;
    }

    bool Withdraw(int money)
    {
        if (money > balance)
        {
            return false;
        }

        withdraw += money;
        balance -= money;
        transactions.push_back({"Withdraw:", money});
        return true;
    }

    bool buy_crypto()
    {
        int option;
        cout << "Want to purchase Etheral press 1 else "
                "for bitcoin press 2\n";
        cin >> option;

                if (option == 1)
                {
                    Etheral += 1;
                    balance -= Etheral_value;
                    crypto_invest += (Etheral)*Etheral_value;
                }
                else
                {
                    bitcoin += 1;
                    balance -= bitcoin_value;
                   crypto_invest += bitcoin_value;
                }
    }

    bool sell_crypto()
    {
        int option;
        cout << "Want to sell Etheral press 1 else for "
                "bitcoin press 2\n";
        cin >> option;

        if (option == 2)
        {
            if (bitcoin == 0)
                return false;
           crypto_return += bitcoin_value;
            balance += bitcoin_value;
            transactions.push_back({"Bitcoin Sold:", bitcoin_value});
            bitcoin -= 1;
        }
        else
        {
            if (Etheral == 0)
                return false;
            crypto_return += Etheral_value;
            balance += Etheral_value;
            transactions.push_back({"Etheral Sold:", Etheral_value});
            Etheral -= 1;
        }

        return true;
    }

    void History()
    {
        cout << "Displaying All transactions\n";
        for (auto it : transactions)
        {
            cout << it.first << " " << it.second << endl;
        }

        char temp;
        cout << "Do you want to clear all transactions:";
        cin >> temp;

        int no = transactions.size();

        if (temp == 'Y' || temp=='y')
        {
            transactions.clear();
            cout << "Total transactions cleared:" << no << endl;
        }
        else
        {
            cout << "Total transaction:" << no << endl;
        }
    }

    void saveToFile()
    {
        ofstream file("account.txt");
        file << "Balance: " << balance << endl;
        file << "Etheral: " << Etheral << endl;
        file << "Bitcoin: " << bitcoin << endl;
        file.close();

        ofstream transFile("transactions.txt");
        for (auto it : transactions)
        {
            transFile << it.first << " " << it.second << endl;
        }
        transFile.close();
    }


    friend void displayAccountInfo(const Account &account);
};

void displayAccountInfo(const Account &account)
{
    cout << "Account Information (Friend Function):\n";
    cout << "Username: " << account.username << endl;
    cout << "Balance: " << account.balance << endl;
    cout << "Etheral: " << account.Etheral << endl;
    cout << "Bitcoin: " << account.bitcoin << endl;
}

int main()
{
        int amount, choice;

    string username, password;
    int c;

    cout << "1. Register\n2. Login\nYour choice: ";
    cin >> c;
    if (c == 1)
    {
        string username, password;
        cout << "select a username: ";
        cin >> username;
        cout << "select a password: ";
        cin >> password;

        ofstream file("username.txt");
        file << username << endl
             << password;
        file.close();
    }
    else if (c == 2)
    {

        Account person(username, password);
        bool status = person.isLoggedIn();

        if (!status)
        {
            cout << "Invalid username or password" << endl;
            return 0;
        }
        else
        {
            cout << "Successfully logged in" << endl;

            while (1)
            {
                cout << " "
                        ""
                        "***************************** \n";

                cout << "1. Account Info "
                     << endl;
                cout << "2. Deposit"
                     << endl;
                cout << "3. Withdraw"
                     << endl;
                cout << "4. History "
                     << endl;
                cout << "5. Buy Crypto "
                     << endl;
                cout << "6. Sell Crypto "
                     << endl;
                cout << "Else press any invalid key for exit \n"
                     << endl;

                cin >> choice;
                int ans;

                switch (choice)
                {
                case 1:
                    person.Get_account_information();
                    break;

                case 2:
                    cout << "Enter amount to deposit : ";
                    cin >> amount;
                    ans = person.Deposit(amount);
                    if (ans)
                        cout << "Successfully deposited money" << endl;
                    else
                        cout << "Failed\n";

                    break;

                case 3:
                    cout << "Enter amount to withdrawn : ";
                    cin >> amount;
                    ans = person.Withdraw(amount);

                    if (ans)
                        cout << "Successfully withdrawn Amount" << endl;
                    else
                        cout << "Not Enough Balance\n";

                    break;

                case 4:
                    person.History();
                    break;

                case 5:
                    ans = person.buy_crypto();
                    if (ans)
                    cout << "Successful Transaction" << endl;
                    break;

                case 6:
                    ans = person.sell_crypto();
                    if (ans)
                        cout << "Successful Transaction" << endl;
                    else
                        cout << "Not Enough Cryptocoins\n";
                    break;

                default:
                    person.saveToFile(); 
                    exit(0);
                    break;
                }
            }
            return 1;
        }
    }

    return 0;
}