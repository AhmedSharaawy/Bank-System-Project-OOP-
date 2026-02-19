#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{
private:

    static void PrintClientRecordLine(clsBankClient Client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AcccountBalance;
    }

public:

   static void ShowClientsList()
   {
       if (!CheckAccessRithts(clsUser::enPermissions::pListClients))
       {
           return;
       }
        vector<clsBankClient> vClients = clsBankClient::GetClientList();
       
        string Title = "client List Screen";
        string SubTitle = "\t   (" + to_string(vClients.size()) + ") Client(s)";

        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << setw(15) << left << "Account Number";
        cout << "| " << left << setw(20) << left << "Client Name";
        cout << "| " << left << setw(12) << left << "Phone";
        cout << "| " << left << setw(20) << left << "Email";
        cout << "| " << left << setw(10) << left << "PinCode";
        cout << "| " << left << setw(12) << left << "AccountBalance";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "________________________________________________\n" << endl;

        if (vClients.size() == 0)
        {
            cout << "Not Clients Available in the System" << endl;
        }
        else
        {
            for (clsBankClient Client : vClients)
            {
                PrintClientRecordLine(Client);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________\n" << endl;


   }
};

