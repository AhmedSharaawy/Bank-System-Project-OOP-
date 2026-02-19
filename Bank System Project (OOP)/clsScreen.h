
#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include "clsUser.h"
#include "Gloabal.h"
#include "clsDate.h"
using namespace std;



class clsScreen
{
protected:

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t___________________________________";
        cout << "\n\n\t\t\t\t\t\t" << Title;
         if (SubTitle != "")
       {
            cout << "\n\t\t\t\t\t  " << SubTitle;
       }
          cout << "\n\t\t\t\t\t___________________________________\n\n";

          cout << "\t\t\t\t\tUser : " << CurrentUser.UserName << endl;
          cout << "\t\t\t\t\tDate : " << clsDate::DateToString(clsDate()) << "\n\n";
     }

    static bool CheckAccessRithts(clsUser::enPermissions  Permission)
    {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }
    }
};

