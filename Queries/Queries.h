#pragma once
////////////////////////////////////////////////////////////////////////////////
// Queries.h:   To query the databse					                      //
// Application: Key Value DataBase, Spring 2017                               //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                       //
// Author:      Manasa Malali Nagabhushana, CSE687 - OOD,Spring 2017          //
// Source:      James W Fawcett                                              //
////////////////////////////////////////////////////////////////////////////////


#pragma once
#include  "../NoSqlDb/NoSqlDb.h"
using StrData = std::string;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;
using Data = std::string;

class Queries
{
public:
	Queries()  {}
	void FindValueOfKey(NoSqlDb<Data> db, std::string k);
	void RetrieveChildren(NoSqlDb<StrData> db, Key k);
	std::vector<std::string> KeysMatchingPattern(NoSqlDb<StrData>& db, std::string typeOfList, std::string givenName, std::vector<std::string> vector3);
	std::vector<std::string> KeysWithSpecifiedItemName(NoSqlDb<StrData>& db, std::string typeOfList, std::string givenName, std::vector<std::string> vector4);
	std::vector<std::string> KeysWithSpecifiedCategory(NoSqlDb<StrData>& db, std::string typeOfList, std::string givenName, std::vector<std::string> vector5);
	std::vector<std::string> KeysWithSpecifiedTemplateData(NoSqlDb<StrData>& db, std::string typeOfList, std::string givenName, std::vector<std::string> vector6);
	std::vector<std::string> UnionOfKeys(NoSqlDb<StrData> db, std::vector<std::string> UnionVector1, std::vector<std::string> UnionVector2, std::string s);
	std::vector<std::string> SubsequentQuery(NoSqlDb<StrData>& db, std::string nextQuery);
	std::vector<std::string> RetrieveKeysbetweenTimeInterval(NoSqlDb<StrData>& db, Keys k, std::string starttime, std::string endtime);
	Keys RetrieveKeysbetweenTimeInterval(NoSqlDb<StrData>& db, Keys _keys, std::string time_t);
	std::string getTime(time_t dateTime);
};