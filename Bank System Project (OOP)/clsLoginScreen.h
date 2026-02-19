#pragma once

#include <iostream>
#include "clsScreen.h"
#include "Gloabal.h"
#include "clsMainScreen.h"



class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
        bool LoginFaild = false;
        short CounterTrials = 2;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n";

                cout << "You have " << CounterTrials-- << " Trials to Login\n" << endl;
            }

            if (CounterTrials < 0)
            {
                cout << "You are Locked after 3 faild Trails" << endl;
                return false;
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

           CurrentUser.RegisterLogin();
           clsMainScreen::ShowMainMenue();
           return true;  
	}

public:

    static bool ShowLoginScreen()
    {
        while (true)
        {
            system("cls");
            _DrawScreenHeader("Login Screen");
            
            if (_Login() == false)
            {
                break;
            }
        }
        return false;
    }
};

