////////////////////////////////////////////////////////////////////////////////
// Queries.cpp: To query the databse                                          //
// Application: Key Value DataBase, Spring 2017                               //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                       //
// Author:      Manasa Malali Nagabhushana, CSE687 - OOD,Spring 2017          //
// Source:      James W Fawcett                                              //
////////////////////////////////////////////////////////////////////////////////

#include "../Utilities/StrHelper.h"
#include <iostream>
#include "Queries.h"
#include <ostream>
#include <regex>
#include "../NoSqlDb/NoSqlDb.h"
#include <set>
#include "../Convert/Convert.h"

using StrData = std::string;
using intData = int;

//Query 7.1
//template<typename Data>
void Queries::FindValueOfKey(NoSqlDb<Data> db, std::string key)
{
	Keys list1 = db.keys();
	for (Key k1 : list1)
	{
		if (k1.find(key) != std::string::npos)
			std::cout << db.value(k1).show();
	}
}

//Query 7.2
void Queries::RetrieveChildren(NoSqlDb<StrData> db, Key k)
{
	std::cout << "\n";
	std::vector<std::string> list2 = db.value(k).children;

	for (int i = 0; i < (int)list2.size(); i++) {
		std::cout << "\nChildren of " << k << " are: " << list2[i] << " \n";
	}
	if (list2.size() == 0)
	{
		std::cout << "\nNo children present\n";
	}
}

//Query 7.3
std::vector<std::string> Queries::KeysMatchingPattern(NoSqlDb<StrData>& db, std::string typeOfList, std::string givenName, std::vector<std::string> vector3) {
	std::vector<std::string> resultVector;
	std::regex matchKeyName("[A-Za-z1-9]*(" + givenName + ")[A-Za-z1-9]*");
	Keys list3 = db.keys();
	if (typeOfList == "InitialList") {
		for (Key k3 : list3) {
			Element<Data> res = db.value(k3);
			std::string matchPattern = res.desc;
			if (regex_match(matchPattern, matchKeyName)) {
				resultVector.push_back(k3);
			}
		}
	}
	else if (typeOfList == "PreviousList")
	{
		for (Key k3 : vector3) {
			Element<Data> res = db.value(k3);
			std::string matchPattern = res.desc;
			if (regex_match(matchPattern, matchKeyName)) {
				resultVector.push_back(k3);
			}
		}
	}
	if (resultVector.size() == 0) {
		std::cout << "\nGiven pattern was not found, thus defaulting to all keys\n";
		return list3;
	}		
	//else
		return resultVector;
}

//Query 7.4
std::vector<std::string> Queries::KeysWithSpecifiedItemName(NoSqlDb<StrData>& db, std::string typeOfList, std::string givenName, std::vector<std::string> vector4)
{
	std::vector<std::string> resultVector;
	std::regex matchKeyName("[A-Za-z1-9]*(" + givenName + ")[A-Za-z1-9]*");
	if (typeOfList == "InitialList") {
		Keys list4 = db.keys();
		for (Key k4 : list4) {
			Element<Data> res = db.value(k4);
			std::string name = res.name;
			if (regex_match(name, matchKeyName)) {
				resultVector.push_back(k4);
			}
		}
	}
	else if (typeOfList == "PreviousList")
	{
		for (Key k4 : vector4) {
			Element<Data> res = db.value(k4);
			std::string name = res.name;
			if (regex_match(name, matchKeyName)) {
				resultVector.push_back(k4);
			}
		}
	}
	if (resultVector.size() == 0)
		std::cout << "\nThere is no record with the given the given string in its item name\n";
	return resultVector;
}

//Query 7.5
std::vector<std::string> Queries::KeysWithSpecifiedCategory(NoSqlDb<StrData>& db, std::string typeOfList, std::string givenName, std::vector<std::string> vector5)
{	
	std::vector<std::string> resultVector;
	std::regex matchKeyName("[A-Za-z1-9]*(" + givenName + ")[A-Za-z1-9]*");
	if (typeOfList == "InitialList") {
		Keys list5 = db.keys();
		for (Key k5 : list5) {
			Element<Data> res = db.value(k5);
			std::string name = res.category;
			if (regex_match(name, matchKeyName)) {
				resultVector.push_back(k5);
			}
		}
	}
	else if (typeOfList == "PreviousList") {
		for (Key k5 : vector5) {
			Element<Data> res = db.value(k5);
			std::string name = res.category;
			if (regex_match(name, matchKeyName)) {
				resultVector.push_back(k5);
			}
		}
	}
	if (resultVector.size() == 0)
		std::cout << "No element with similar patern in Category";
	return resultVector;
}

//Query 7.6
std::vector<std::string> Queries::KeysWithSpecifiedTemplateData(NoSqlDb<StrData>& db, std::string typeOfList, std::string givenName, std::vector<std::string> vector6)
{
	std::vector<std::string> resultVector;
	Keys list6 = db.keys();
	std::regex matchKeyName("[A-Za-z1-9]*(" + givenName + ")[A-Za-z1-9]*");
	if (typeOfList == "InitialList") {
		for (Key k : list6) {
			Element<Data> res = db.value(k);
			std::string data = res.data;
			if (regex_match(data, matchKeyName)) {
				resultVector.push_back(k);
			}
		}
	}
	else if (typeOfList == "PreviousList") {
		for (Key k : vector6) {
			Element<Data> res = db.value(k);
			std::string data = res.category;
			if (regex_match(data, matchKeyName)) {
				resultVector.push_back(k);
			}
		}
	}
	if (resultVector.size() == 0)
		std::cout << "No element with similar pattern in Template Data";
	return resultVector;
}

std::string Queries::getTime(time_t dateTime) {
	struct tm buf;
	char cStr[100];
	localtime_s(&buf, &dateTime);
	strftime(cStr, sizeof(cStr), "%Y-%m-%dT%X", &buf);
	std::string str(cStr);
	return str;
}

static std::time_t takeTime(std::string dateTime) {
	time_t time;
	struct tm buf;
	sscanf_s(dateTime.c_str(), "%d-%d-%dT%d:%d:%d", &buf.tm_year, &buf.tm_mon, &buf.tm_mday, &buf.tm_hour, &buf.tm_min, &buf.tm_sec);
	buf.tm_year -= 1900;
	buf.tm_mon -= 1;
	time = mktime(&buf);
	return time;
}

//Query 7.7 

Keys Queries::RetrieveKeysbetweenTimeInterval(NoSqlDb<StrData>& db, Keys _keys, std::string time1, std::string time2)
{
	//if keys not provided query on all keys present in the database if else query on the provided keys only
	if (_keys.empty())
		_keys = db.keys();

	Keys results;

	for (Key key : _keys) {
		Element<Data> currEle = db.value(key);
		time_t data = takeTime(currEle.timeDate);
		if (data >= takeTime(time1) && data <= takeTime(time2))
			results.push_back(key);
	}

	return results;
}

Keys Queries::RetrieveKeysbetweenTimeInterval(NoSqlDb<StrData>& db, Keys _keys, std::string time_t)
{
	return RetrieveKeysbetweenTimeInterval(db, _keys, time_t, getTime(time(NULL)));
}

//Requirement 8 
std::vector<std::string> Queries::SubsequentQuery(NoSqlDb<StrData>& db, std::string nextQuery)
{	
	std::vector<std::string> result1, temp;
	std::vector<std::string> result2;	
	temp = db.keys();
	result1 = KeysWithSpecifiedCategory(db, "PreviousList", "Student", temp);

	if (nextQuery == "ItemNameQuery") {		
		std::string substr = "Robin";
		result2 = KeysWithSpecifiedItemName(db, "PreviousList", substr, result1);
	}
	else if (nextQuery == "TemplateDataQuery") {		
		std::string substr = "Syracuse";
		result2 = KeysWithSpecifiedTemplateData(db, "PreviousList", substr, result1);
	}
	else if (nextQuery == "PatternMatching") {		
		std::string substr = "Male";
		result2 = KeysMatchingPattern(db, "PreviousList", substr, result1);
	}
	return result2;
}

// Requirement 9
std::vector<std::string> Queries::UnionOfKeys(NoSqlDb<StrData> db, std::vector<std::string> UnionVector1, std::vector<std::string> UnionVector2, std::string s)
{
	std::vector<std::string> Result;
	for (Key k : UnionVector2)
	{
		Result.push_back(k);
	}
	for (Key k1 : UnionVector1)
	{
		Result.push_back(k1);
	}
	std::vector<std::string> resultVector;	
	std::regex matchKeyName("[a-zA-Z1-9]*(" + s + ")[a-zA-Z1-9]*");
	for (Key k : Result) {
		Element<Data> resultant = db.value(k);
		std::string name = resultant.desc;
		if (regex_match(name, matchKeyName)) {
			resultVector.push_back(resultant.name);
		}
	}
	if (resultVector.size() == 0)
		std::cout << "No element with specified name";
	return resultVector;
}


