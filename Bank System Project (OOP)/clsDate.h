#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
	short _Year = 1;
	short _Month = 1;
	short _Day = 1900;

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Year = now->tm_year + 1900;
		_Month= now->tm_mon + 1;
		_Day = now->tm_mday;
	}
	clsDate(string sDate)
	{
		vector<string> vDate;
		vDate = clsString::split(sDate, "/");

		_Year = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Day = stoi(vDate[2]);
	}
	clsDate(short Day, short Month, short Year)
	{
		_Year = Year;
		_Month = Month;
		_Day = Day;
	}
	clsDate(short DateOrderInYear, short Year)
	{
		//This will construct a date by date order in year
		clsDate Date1 = GetDayFromYearOrderInYear(DateOrderInYear, Year);
		_Day = Date1.Day;
		_Month = Date1.Month;
		_Year = Date1.Year;
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}
	short GetYear()
	{
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return clsDate(Day, Month, Year);
	}

	static string GetSystemDateTimeString()
	{
		//system datetime string
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));
	}

	void Print()
	{
		cout << DateToString() << endl;
	}

	static	bool IsValidDate(clsDate Date)
	{

		if (Date.Day < 1 || Date.Day>31)
			return false;

		if (Date.Month < 1 || Date.Month>12)
			return false;

		if (Date.Month == 2)
		{
			if (IsLeapYear(Date.Year))
			{
				if (Date.Day > 29)
					return false;
			}
			else
			{
				if (Date.Day > 28)
					return false;
			}
		}

		short DaysInMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > DaysInMonth)
			return false;

		return true;

	}

	bool IsValid()
	{
		return IsValidDate(*this);
	}

	static string DateToString(clsDate Date)
	{
		return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString()
	{
		return  DateToString(*this);
	}

	static bool IsLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 100) || (Year % 400 == 0);
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}
	short NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(_Year);
	}

	static int NumberOfHoursInYear(short Year)
	{
		return NumberOfDaysInYear(Year) * 24;
	}
	int NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(_Year);
	}

	static int NumberOfMunitesInYear(short Year)
	{
		return NumberOfHoursInYear(Year) * 60;
	}
	int NumberOfMunitesInYear()
	{
		return NumberOfMunitesInYear(_Year);
	}

	static int NumberOfSecondsInYear(short Year)
	{
		return NumberOfMunitesInYear(Year) * 60;
	}
	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear(_Year);
	}

	static short NumberOfDaysInMonth(short Year, short Month)
	{
		if (Month < 1 || Month > 12)
		{
			return 0;
		}

		int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[12 - 1];
	}
	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Year, _Month);
	}

	static int NumberOfHoursInMonth(short Year, short Month)
	{
		return NumberOfDaysInMonth(Year, Month) * 24;
	}
	int NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(_Year, _Month);
	}

	static int NumberOfMunitesInMonth(short Year, short Month)
	{
		return NumberOfHoursInMonth(Year, Month) * 60;
	}
	int NumberOfMunitesInMonth()
	{
		return NumberOfMunitesInMonth(_Year, _Month);
	}

	static int NumberOfSecondsInMonth(short Year, short Month)
	{
		return NumberOfMunitesInMonth(Year, Month) * 60;
	}
	int NumberOfSecondsInMonth()
	{
		return NumberOfSecondsInMonth(_Year, _Month);
	}

	static short DayOfWeekOrder(short Year, short Month, short Day)
	{
		short a = ((14 - Month) / 12);

		short y = Year - a;

		short m = Month + (12 * a) - 2;

		short d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

		return d;
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Year, _Month, _Day);
	}

	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder];
	}
	static string DayShortName(short Day , short Month , short Year)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
	}
	string DayShortName()
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];
	}

	static string MonthShortName(short MonthNumber)
	{
		string Months[12] = { "Jan", "Feb", "Mar",
		"Apr", "May", "Jun",
		"Jul", "Aug", "Sep",
		"Oct", "Nov", "Dec" };

		return (Months[MonthNumber - 1]);
	}
	string MonthShortName()
	{
		return MonthShortName(_Month);
	}

	static void PrintMonthCalender(short Year, short Month)
	{
		int current = DayOfWeekOrder(Year, Month, 1);

		int NumberOfDays = NumberOfDaysInMonth(Year, Month);

		printf("\n____________________%s____________________\n\n", MonthShortName(Month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i;
		for (i = 0; i < current; i++)
			printf("     ");  // اطبع خانة من 5 فراغات ليوم فاضى بنفس عهرض الايام وال هو 5 برضو

		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);    // علشان يبقا كدة كل رقم عرضه يساوى 5 ف كدة كل خانة ليها عرض معين وهو 5

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		cout << "\n____________________________________________\n";
	}
	void PrintMonthCalender()
	{
		PrintMonthCalender(_Year, _Month);
	}

	static void PrintCalenderForYear(short Year)
	{
		cout << "\n______________________________________________\n\n";
		cout << "            Calender - " << Year << endl;
		cout << "______________________________________________\n";

		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalender(Year, i);
		}
	}
	void PrintCalenderForYear()
	{
		PrintCalenderForYear(_Year);
	}

	static short DaysFromTheBeginingTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (short i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(Year, i);
		}

		TotalDays += Day;

		return TotalDays;
	}
	short DaysFromTheBeginingTheYear()
	{
		return DaysFromTheBeginingTheYear(_Day, _Month, _Year);
	}

	static clsDate GetDayFromYearOrderInYear(short DateOrderInYear, short Year)
	{
		clsDate Date;

		short ReminingDays = DateOrderInYear;
		short MonthDays;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Year, Date.Month);

			if (ReminingDays > MonthDays)
			{
				ReminingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = ReminingDays;
				break;
			}
		}

		return Date;
	}

	void AddDays(short AddDays)
	{
		short ReminingDays = AddDays + DaysFromTheBeginingTheYear(_Day , _Month , _Year);
		short MonthDays = 0;

		_Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(_Year , _Month);

			if (ReminingDays > MonthDays)
			{
				ReminingDays -= MonthDays;
				_Month++;

				if (_Month > 12)
				{
					_Month = 1;
					_Year++;
				}
			}
			else
			{
				_Day = ReminingDays;
				break;
			}

		}
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{

		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date1.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);


	}
	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1 , clsDate Date2)
	{

		return (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day) ? true : false;

	}
	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool LastDayInMonth(clsDate Date)
	{
		return  (Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month));
	}
	bool LastDayInMonth()
	{
		return LastDayInMonth(*this);
	}

	static bool LastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool LastMonthInYear()
	{
		return LastMonthInYear(_Month);
	}

	static clsDate AddOneDay(clsDate Date)
	{
		if (LastDayInMonth(Date))
		{
			if (LastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;

		}

		return Date;

	}
	clsDate AddOneDay()
	{
		return AddOneDay(*this);
	}

	static void  SwapDates(clsDate& Date1, clsDate& Date2)
	{

		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;

	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		//this will take care of negative diff
		int Days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			//Swap Dates 
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;

		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}
		return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
	}
	int GetDifferenceInDays(clsDate Date2 , bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this,Date2 , true);
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
	}



	static clsDate IncreaseDateByXDays(short Days, clsDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}
	void IncreaseDateByXDays(short Days)
	{
		 IncreaseDateByXDays( Days , *this);
	}

	static clsDate IncreaseDateByOneWeek(clsDate & Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}
	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate & Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}
	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate IncreaseDateByOneMonth(clsDate &Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		short NumberOfDaysInCurrntMonth = NumberOfDaysInMonth(Date.Year, Date.Month);

		if (Date.Day > NumberOfDaysInCurrntMonth)
		{
			Date.Day = NumberOfDaysInCurrntMonth;
		}
		return Date;
	}
	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonth(short Months, clsDate &Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}
	void IncreaseDateByXMonth(short Months)
	{
		IncreaseDateByXMonth(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;

		return Date;
	}
	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYear(short Years, clsDate& Date)
	{
		Date.Year += Years;

		return Date;
	}
	void IncreaseDateByXYear(short Years)
	{
		IncreaseDateByXYear(Years, *this);
	}

	static clsDate IncreaseDateByOneDecade(clsDate &Date)
	{
		Date.Year += 10;

		return Date;
	}
	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate Date)
	{
		Date.Year += (10 * 10);

		return Date;
	}
	void IncreaseDateByXDecades()
	{
		IncreaseDateByXDecades(*this);
	}

	static clsDate IncreaseDateByCentury(clsDate &Date)
	{
		Date.Year += 100;

		return Date;
	}
	void IncreaseDateByCentury()
	{
		IncreaseDateByCentury(*this);
	}

	static clsDate IncreaceDateByoneMillennium(clsDate &Date)
	{
		Date.Year += 1000;

		return Date;
	}
	void IncreaceDateByoneMillennium()
	{
		IncreaceDateByoneMillennium(*this);
	}



	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;
			}
			else
			{

				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
			}
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}
	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{

		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}
	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
	{

		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{

		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
			Date.Month--;

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}


		return Date;
	}
	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
	{

		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(Days, *this);
	}

	static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
	{

		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{

		Date.Year--;
		return Date;
	}
	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
	{

		Date.Year -= Years;
		return Date;
	}
	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(Years, *this);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		//Period of 10 years
		Date.Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
	{

		Date.Year -= Decades * 10;
		return Date;
	}
	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(Decades, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		//Period of 100 years
		Date.Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		//Period of 1000 years
		Date.Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}



	static short IsEndOfWeek(clsDate Date)
	{
		return  DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
	}
	short IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		//Weekends are Fri and Sat
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex == 5 || DayIndex == 6);
	}
	bool IsWeekEnd()
	{
		return  IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		//Weekends are Sun,Mon,Tue,Wed and Thur

	   /*
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex >= 5 && DayIndex <= 4);
	   */

	   //shorter method is to invert the IsWeekEnd: this will save updating code.
		return !IsWeekEnd(Date);

	}
	bool IsBusinessDay()
	{
		return  IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}
	short DaysUntilTheEndOfWeek()
	{
		return  DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date1)
	{

		clsDate EndOfMontDate;
		EndOfMontDate.Day = NumberOfDaysInMonth(Date1.Month, Date1.Year);
		EndOfMontDate.Month = Date1.Month;
		EndOfMontDate.Year = Date1.Year;

		return GetDifferenceInDays(Date1, EndOfMontDate, true);

	}
	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date1)
	{

		clsDate EndOfYearDate;
		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date1.Year;

		return GetDifferenceInDays(Date1, EndOfYearDate, true);

	}
	short DaysUntilTheEndOfYear()
	{
		return  DaysUntilTheEndOfYear(*this);
	}

	//i added this method to calculate business days between 2 days
	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{

		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;

	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		/*short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}*/

		return CalculateBusinessDays(DateFrom, DateTo);

	}
	//above method is eough , no need to have method for the object

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{

		short WeekEndCounter = 0;

		for (short i = 1; i <= VacationDays; i++)
		{

			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}
		//to add weekends 
		for (short i = 1; i <= WeekEndCounter; i++)
			DateFrom = AddOneDay(DateFrom);

		return DateFrom;
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));

	}
	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		/* if (IsDate1AfterDate2(Date1,Date2))
			 return enDateCompare::After;*/

			 //this is faster
		return enDateCompare::After;

	}

	enDateCompare CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}
};

