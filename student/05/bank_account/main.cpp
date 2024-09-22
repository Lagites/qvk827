#include "account.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Prints accounts stored in the given vector
void print_accounts(const vector<Account*>& accs)
{
    cout << endl;
    cout << "Printing all accounts:" << endl;
    for(auto acc : accs)
    {
        acc->print();
    }
    cout << endl;
}

int main()
{
    cout << "1: Creating three accounts" << endl;
    Account current_account("Tupu");
    Account savings_account ("Hupu");
    Account credit_card_account("Lupu", true);

    // Collecting accounts into a vector to be able to print them
    // by just going through the vector.
    // Actually pointers (the memory addresses of the accounts) are stored in
    // the vector to enable changes to be targeted also at the vector elements.
    vector<Account*> accounts;
    accounts.push_back(&current_account);
    accounts.push_back(&savings_account);
    accounts.push_back(&credit_card_account);

    // Setting credit limit for a credit card account
    credit_card_account.set_credit_limit(100);

    // Trying to set credit limit for a non-credit card account
    current_account.set_credit_limit(100);

    // Saving money in all three accounts
    current_account.save_money(100);
    savings_account.save_money(200);
    credit_card_account.save_money(300);

    print_accounts(accounts);

    cout << "2: Taking money succesfully:" << endl;
    current_account.take_money(50);
    print_accounts(accounts);

    cout << "3: Taking money unsuccesfully:" << endl;
    current_account.take_money(100);
    print_accounts(accounts);

    cout << "4: Taking money succesfully from a credit card account:" << endl;
    credit_card_account.take_money(310);
    print_accounts(accounts);

    cout << "5: Taking money unsuccesfully from a credit card account:" << endl;
    credit_card_account.take_money(100);
    print_accounts(accounts);

    cout << "6: Transferring money succesfully: " << endl;
    savings_account.transfer_to(credit_card_account, 50);
    print_accounts(accounts);

    cout << "7: Transferring money unsuccesfully: " << endl;
    savings_account.transfer_to(current_account, 200);
    print_accounts(accounts);

    cout << "8: Transferring money succesfully from a credit card account:" << endl;
    credit_card_account.transfer_to(savings_account, 60);
    print_accounts(accounts);

    cout << "9: Transferring money unsuccesfully from a credit card account:" << endl;
    credit_card_account.transfer_to(savings_account, 100);
    print_accounts(accounts);

    return 0;
}
