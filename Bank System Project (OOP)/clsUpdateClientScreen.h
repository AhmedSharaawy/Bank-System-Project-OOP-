#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsClientListScreen.h"
#include <iomanip>
#include "clsUser.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

public:

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRithts(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }

        _DrawScreenHeader("Update Client Screen");

        string AccountNumber = "";

        cout << "Please enter Client Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is Not Found , Choose Another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nUpdate Client Inf :-" << endl;
        cout << "------------------------------------" << endl;

        _ReadClientInfo(Client);

        clsBankClient::enSaveResult SaveResult;

        SaveResult = Client.Save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResult::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintClient(Client);
            break;
        }
        case clsBankClient::enSaveResult::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
        }
    }



};

