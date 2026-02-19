#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;

	bool _MarkForDelete = false;

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientsDate;
		vClientsDate = clsString::split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vClientsDate[0], vClientsDate[1], vClientsDate[2],
			vClientsDate[3], vClientsDate[4],clsUtil::DecryptText(vClientsDate[5]), stod(vClientsDate[6]));

	}

	struct stLoginRegisterRecord;
	
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector<string> LoginRegisterDateLine = clsString::split(Line, seperator);

		LoginRegisterRecord.DateTime = LoginRegisterDateLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDateLine[1];
		LoginRegisterRecord.Password = LoginRegisterDateLine[2];
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDateLine[3]);

		return LoginRegisterRecord;
	}

	static vector<clsUser> _LoadUsersDataFromFile()
	{
		vector<clsUser> vUsers;

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				vUsers.push_back(User);

			}
			MyFile.close();
		}

		return vUsers;
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperetor = "#//#")
	{
		string UserRecord = "";
		UserRecord += User.FirstName + Seperetor;
		UserRecord += User.LastName + Seperetor;
		UserRecord += User.Email + Seperetor;
		UserRecord += User.Phone + Seperetor;
		UserRecord += User.UserName + Seperetor;
		UserRecord += clsUtil::EncryptText(User.Password) + Seperetor;   // Enctypt Password
		UserRecord += to_string(User.Permissions);

		return UserRecord;

	}

	static void _SaveDataLineToFile(vector<clsUser> vUsers)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);  // Over Write

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsUser U : vUsers)
			{
				if (U._MarkForDelete == false)
				{
					DataLine = _ConvertUserObjectToLine(U);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}

	}

	string _PrapareLoginInRecord(string Seperetor = "#//#")
	{
		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Seperetor;
		LoginRecord += UserName + Seperetor;
		LoginRecord += clsUtil::EncryptText(Password) + Seperetor;      // Encrypt Password
		LoginRecord += to_string(Permissions);

		return LoginRecord;

	}
	void _Update()
	{
		vector<clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				U = *this;
				break;
			}
		}
		_SaveDataLineToFile(vUsers);
	}

	void _AddDateLineToFile(string DataLine)
	{

		fstream MyFile;

		MyFile.open("Users.txt", ios::out | ios::app);
		{
			if (MyFile.is_open())
			{
				MyFile << DataLine << endl;

				MyFile.close();
			}
		}
	}

	void _AddNew()
	{
		_AddDateLineToFile(_ConvertUserObjectToLine(*this));
	}

public:

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
		, pLoginRegister = 128
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName,
		string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;


	static clsUser Find(string UserName)
	{
		vector<clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		vector<clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());
	}

	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExist = 2 };

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return enSaveResult::svFaildEmptyObject;
		}

		case enMode::UpdateMode:
		{

			_Update();
			return enSaveResult::svSucceeded;
		}

		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResult::svFaildUserExist;
			}
			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}
		}

		}
	}

	static clsUser GetAddNewUser(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete()
	{
		vector<clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkForDelete = true;
				break;
			}
		}

		_SaveDataLineToFile(vUsers);
		*this = _GetEmptyUserObject();

		return true;
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;
		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;	
	}

	void RegisterLogin()
	{
		string stDateLine = _PrapareLoginInRecord();

		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDateLine << endl;

			MyFile.close();
		}
	}

	static vector<stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector<stLoginRegisterRecord> vLoginRegisteRecord;

		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile,Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisteRecord.push_back(LoginRegisterRecord);
			}
			MyFile.close();
		}

		return vLoginRegisteRecord;
	}
};

