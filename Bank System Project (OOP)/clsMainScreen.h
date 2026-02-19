#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsMangeUsers.h"
#include <iomanip>
#include "Gloabal.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginRegister = 8 , eCurrencyExchange = 9,  eExit = 10
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << " " << "Choose What do you want to do ? [1 To 9] : ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter Number berween 1 To 10 ? ");
        return Choice;
    }

    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList();

    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();

    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();

    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();

    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();

    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();

    }

    static void _ShowManageUsersMenue()
    {
        clsMangeUsers::ShowManageUsersMenue();

    }

    static void _ShowLoginRegister()
    {
        clsLoginRegisterScreen::ShowLoinRegisteScreen();

    }

    static void _ShowCurrencyExchangeMainScreen()
    {
        clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");

    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eLoginRegister:
            system("cls");
            _ShowLoginRegister();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eCurrencyExchange:
            system("cls");
            _ShowCurrencyExchangeMainScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _Logout();
            //Login();

            break;
        }

    }

public:


    static void ShowMainMenue()
    {
        system("cls");

        clsScreen::_DrawScreenHeader("Main Screen");

        cout << setw(37) << left << "" << "====================================" << endl;
        cout << setw(37) << left << "" << "\t\t Main Menue Screen " << endl;
        cout << setw(37) << left << "" << "====================================" << endl;

        cout << setw(37) << left << "" << "\t [1] Show Client List" << endl;
        cout << setw(37) << left << "" << "\t [2] Add New Client" << endl;
        cout << setw(37) << left << "" << "\t [3] Delete Client" << endl;
        cout << setw(37) << left << "" << "\t [4] Update Client Info" << endl;
        cout << setw(37) << left << "" << "\t [5] Find Client" << endl;
        cout << setw(37) << left << "" << "\t [6] Transactions" << endl;
        cout << setw(37) << left << "" << "\t [7] Mange Users" << endl;
        cout << setw(37) << left << "" << "\t [8] Login Register" << endl;
        cout << setw(37) << left << "" << "\t [9] Currency Exchange" << endl;
        cout << setw(37) << left << "" << "\t [10] Logout" << endl;

        cout << setw(37) << left << "" << "====================================" << endl;

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }


};



