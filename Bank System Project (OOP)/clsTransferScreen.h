#pragma once

#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private :
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card : ";
        cout << "\n______________________________" << endl;
		cout << "Full Name : " << Client.FullName() << endl;
		cout << "Account Number : " << Client.AccountNumber() << endl;
		cout << "Total Balance : " << Client.AcccountBalance << endl;
		cout << "________________________________" << endl;
	}

    static string _ReadAccountNumber()
    {
        string AccountNumber;

        cout << "\nPlease Enter Account Number to Transfer From : ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static double ReadAmount(clsBankClient SourceClient)
    {
        double Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadDblNumber();

        while (Amount > SourceClient.AcccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }

public:

    static void ShowTransferScreen()
    {
        _DrawScreenHeader("Transfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(DestinationClient);

        double Amount = ReadAmount(SourceClient);

        cout << "\nAre you Sure you want to Perform this Opration ? Y/n ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient))
            {
                cout << "\nTransfer Done Successfully\n";
            }
            else
            {
                cout << "\nTranfer Faild\n";
            }
        }
        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);


    }
};

