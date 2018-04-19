/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: GIAconditionNodeClass.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3e10a 15-January-2018
 *
 *******************************************************************************/


#ifndef HEADER_GIA_CONDITION_NODE_CLASS
#define HEADER_GIA_CONDITION_NODE_CLASS

#include "GIAglobalDefs.hpp"
#include "SHAREDvars.hpp"


//class GIAtimeConditionNode;


#define CONDITION_NODE_NUMBER_OF_TYPES (4)
#define CONDITION_NODE_TYPE_UNDEFINED (0)
#define CONDITION_NODE_TYPE_TIME (1)
#define CONDITION_NODE_TYPE_LOCATION (2)
#define CONDITION_NODE_TYPE_REASON (3)
#define CONDITION_NODE_TYPE_UNDEFINED_STRING "0"
#define CONDITION_NODE_TYPE_TIME_STRING "1"
#define CONDITION_NODE_TYPE_LOCATION_STRING "2"
#define CONDITION_NODE_TYPE_REASON_STRING "3"

#define TIME_MONTH_JANUARY "January"
#define TIME_MONTH_FEBRUARY "February"
#define TIME_MONTH_MARCH "March"
#define TIME_MONTH_APRIL "April"
#define TIME_MONTH_MAY "May"
#define TIME_MONTH_JUNE "June"
#define TIME_MONTH_JULY "July"
#define TIME_MONTH_AUGUST "August"
#define TIME_MONTH_SEPTEMBER "September"
#define TIME_MONTH_OCTOBER "October"
#define TIME_MONTH_NOVEMBER "November"
#define TIME_MONTH_DECEMBER "December"
#define TIME_MONTH_NUMBER_OF_TYPES (12)

#define MONDAY (0)
#define TUESDAY (1)
#define WEDNESDAY (2)
#define THURSDAY (3)
#define FRIDAY (4)
#define SATURDAY (5)
#define SUNDAY (6)
#define TIME_DAY_OF_WEEK_UNDEFINED (7)

#define GRAMMATICAL_TENSE_UNDEFINED (0)

#define TIME_YEAR_UNDEFINED (-15000000000)	//before start of universe
#define TIME_DAY_OF_MONTH_UNDEFINED (INT_DEFAULT_VALUE)
#define TIME_MONTH_UNDEFINED (INT_DEFAULT_VALUE)	//OLD: 13th month


class GIAtimeConditionNode
{
public:

	GIAtimeConditionNode(void);
	~GIAtimeConditionNode(void);

	string conditionName;

	//temporal coordinate system here - this needs to be replaced with a system time (or added to)
	int tense;
	/*
	enum tense {tenseundefined=GRAMMATICAL_TENSE_UNDEFINED, present=GRAMMATICAL_TENSE_PRESENT, past=GRAMMATICAL_TENSE_PAST, future=GRAMMATICAL_TENSE_FUTURE};
	*/
	/*
	enum
	{
		tenseundefined, present, past, future
	}tense;
	*/
	double second;
	int hour;
	int dayOfWeek;
	/*
	enum
	{
		monday, tuesday, wednesday, thursday, friday, saturday, sunday, dayundefined
	}dayOfWeek;
	*/
	/*
	enum
	{
		january, february, march, april, may, june, july, august, september, october, november, december, monthundefined
	}month;
	*/
	int month;
	int dayOfMonth;
	long year;	//in years < 0AD is negative
	double period;	//in seconds
	long totalTimeInSeconds;

	bool tenseOnlyTimeCondition;
	bool isProgressive;

	long idActiveListReorderdIDforXMLsave;	//for CXL output only
	int printX;			//for CXL output only
	int printY;			//for CXL output only
	bool printCoordsAlreadyDefined;
};

#define TIME_DATE_DISPLAY_FORMAT_AMERICAN (1)
#define TIME_DATE_DISPLAY_FORMAT_STANDARD (2)
#define TIME_DATE_DISPLAY_FORMAT_AUSTRALIAN (3)
#define TIME_DATE_DISPLAY_FORMAT (TIME_DATE_DISPLAY_FORMAT_AUSTRALIAN)
class GIAconditionNodeClassClass
{
	private: SHAREDvarsClass SHAREDvars;
	public: string generateDateTimeConditionName(const int dayOfMonth, const int month, const long year);
};


#endif

