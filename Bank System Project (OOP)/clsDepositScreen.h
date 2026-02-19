#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDepositScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "--------------------------------\n";
        cout << "Client Card" << endl;
        cout << "--------------------------------\n";

        cout << "First Name      : " << Client.FirstName << endl;
        cout << "Last Name       : " << Client.LastName << endl;
        cout << "Full Name       : " << Client.FullName() << endl;
        cout << "Email           : " << Client.Email << endl;
        cout << "Phone           : " << Client.Phone << endl;
        cout << "Account Number  : " << Client.AccountNumber() << endl;
        cout << "Pin Code        : " << Client.PinCode << endl;
        cout << "Account Balance : " << Client.AcccountBalance << endl;
        cout << "--------------------------------\n";
    }
    static string _ReadAccountNumber()
    {
        string AccountNumber;

        cout << "Please enter Account Number : ";
        cin >> AccountNumber;

        return AccountNumber;
    }


public:

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("Deposit Screen");

        string AccountNumber;

        AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client Whith [" << AccountNumber << "] does Not Exist : " << endl;
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;

        cout << "Please enter Deposit Amount : ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\n\nAre you sure you want Perform This Transaction ? y/n ? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Client.Deposit(Amount);
            cout << "\nAmount Deposited Successfully " << endl;
            cout << "New Balance is : " << Client.AcccountBalance;
        }
        else
        {
            cout << "\nOpration was Cancelled\n";
        }


    }





};

