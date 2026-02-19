#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsClientListScreen.h"
#include <iomanip>
#include "clsUser.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
        cout << "\nEnter FirsName : ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "Enter LastName : ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "Enter Email : ";
        Client.Email = clsInputValidate::ReadString();

        cout << "Enter Phone : ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "Enter PinCode : ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Enter AccountBalance : ";
        Client.AcccountBalance = clsInputValidate::ReadFloatNumber();
	}
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


public:

    static void ShowAddNewClientScreen()
    {
        if (!CheckAccessRithts(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
        _DrawScreenHeader("Add New Client Screen");

        string AccountNumber;

        cout << "Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number is Already Used , Choose anthor One : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClient(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResult SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svSucceeded:
        {
            cout << "\nAccount Add Successfuly\n" << endl;
            _PrintClient(NewClient);
            break;
        }

        case clsBankClient::enSaveResult::svFaildEmptyObject:
        {
            cout << "\nError Account Not Save because it is Empty" << endl;
            break;
        }

        case clsBankClient::enSaveResult::svFaildAccountNumberExist:
        {
            cout << "\nFaild Account Number is Used " << endl;
            break;
        }
        }

    }


};

