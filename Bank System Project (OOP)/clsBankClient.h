#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "Gloabal.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientsDate;
		vClientsDate = clsString::split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientsDate[0], vClientsDate[1], vClientsDate[2],
			vClientsDate[3], vClientsDate[4], vClientsDate[5], stod(vClientsDate[6]));

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);

			}
			MyFile.close();
		}

		return vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperetor = "#//#")
	{
		string ClientRecord = "";

		ClientRecord += Client.FirstName + Seperetor;
		ClientRecord += Client.LastName + Seperetor;
		ClientRecord += Client.Email + Seperetor;
		ClientRecord += Client.Phone + Seperetor;
		ClientRecord += Client.AccountNumber() + Seperetor;
		ClientRecord += Client.PinCode + Seperetor;
		ClientRecord += to_string(Client.AcccountBalance);

		return ClientRecord;
	}

	static void _SaveDataLineToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);  // Over Write

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient C : vClients)
			{
				if (C.MarkForDelete == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}

	}

	void _Update()
	{
		vector<clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& c : vClients)
		{
			if (c.AccountNumber() == AccountNumber())
			{
				c = *this;
				break;
			}
		}
		_SaveDataLineToFile(vClients);
	}

	void _AddDateLineToFile(string DataLine)
	{

		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);
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
		_AddDateLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRecord(double Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#")
	{
		string TransferLogRecord = "";

		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AcccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AcccountBalance) + Seperator;
		TransferLogRecord += UserName;

		return TransferLogRecord;
	}

	void RegisterTransferLog(double Amount, clsBankClient DestinationClient, string UserName)
	{
		string stDateLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << stDateLine << endl;

			MyFile.close();
		}
	}

	struct stTrnsferLogRecord;

	static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTrnsferLogRecord TrnsferLogRecord;

		vector <string> vTrnsferLogRecordLine = clsString::split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;

	}


public:

	struct stTrnsferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;

	};


	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string Pincode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = Pincode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPincode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPincode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AcccountBalance;

	/*void Print()
	{
		cout << "--------------------------------\n";
		cout << "Client Card" << endl;
		cout << "--------------------------------\n";

		cout << "First Name      : " << FirstName << endl;
		cout << "Last Name       : " << LastName << endl;
		cout << "Full Name       : " << FullName() << endl;
		cout << "Email           : " << Email << endl;
		cout << "Phone           : " << Phone << endl;
		cout << "Account Number  : " << _AccountNumber << endl;
		cout << "Pin Code        : " << _PinCode << endl;
		cout << "Account Balance : " << _AccountBalance << endl;
		cout << "--------------------------------\n";
	}*/

	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExist = 2 };

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
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResult::svFaildAccountNumberExist;
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

	static clsBankClient GetAddNewClient(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& c : vClients)
		{
			if (c.AccountNumber() == _AccountNumber)
			{
				c.MarkForDelete = true;
				break;
			}
		}

		_SaveDataLineToFile(vClients);
		*this = _GetEmptyClientObject();

		return true;
	}

	static vector<clsBankClient> GetClientList()
	{
		return _LoadClientsDataFromFile();
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
		}

	}

	static double GetTotalBalance()
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		double TotalBalance = 0;

		for (clsBankClient Client : vClients)
		{
			TotalBalance += Client.AcccountBalance;
		}
		return TotalBalance;
	}

	bool Transfer(double Amount, clsBankClient& Destinationclient)
	{
		if (Amount > AcccountBalance)
		{
			return false;
		}

		Withdraw(Amount);

		Destinationclient.Deposit(Amount);

		RegisterTransferLog(Amount, Destinationclient, CurrentUser.UserName);

		return true;
	}

	static  vector <stTrnsferLogRecord> GetTransfersLogList()
	{
		vector <stTrnsferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);  //read Mode

		if (MyFile.is_open())
		{

			string Line;

			stTrnsferLogRecord TransferRecord;

			while (getline(MyFile, Line))
			{

				TransferRecord = _ConvertTransferLogLineToRecord(Line);

				vTransferLogRecord.push_back(TransferRecord);

			}

			MyFile.close();

		}

		return vTransferLogRecord;

	}
};




