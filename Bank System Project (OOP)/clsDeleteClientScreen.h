#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsClientListScreen.h"
#include <iomanip>
#include "clsUser.h"


class clsDeleteClientScreen : protected clsScreen
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

public:

	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRithts(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}

		_DrawScreenHeader("Delete Client Screen");

		string AccountNumber;

		cout << "Please enter AccountNumber : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account Number Not Found , Enter Another One : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer = 'n';

		cout << "Are You Sure You Want To Delete This Client ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted Successfuly\n" << endl;
				_PrintClient(Client);
			}
			else
			{
				cout << "Error Client Was Not Deleted" << endl;
			}
		}
	}
};

