////////////////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp: key/value pair in-memory database                             //
// Application: Key Value DataBase, Spring 2017                               //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                       //
// Author:      Manasa Malali Nagabhushana, CSE687 - OOD,Spring 2017          //
// Source:      James W Fawcett                                              //
////////////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package acts as a test Executive and demeonstrates the requirements 
*
* Required Files:
* ---------------
*   - CppProperties.h,CppProperties.cpp
*   - XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp
*   - persist.cpp,Queries.h

* Build Process:
* --------------
*   devenv XmlParser.sln /debug rebuild
*
* Maintenance History:
* --------------------
* Ver 1.0 : 7 February 2017
* - first release
*
*/

#include "NoSqlDb.h"
#include <iostream>
#include "../DbToXml/persist.cpp"
#include "../Queries/Queries.h"

using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;
using namespace std;

std::ostream& operator<<(std::ostream& out, Property<std::string>& p)
{
	std::string temp = p;
	try {
		out << (temp).c_str();
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  exception:\n  " << ex.what() << "\n";
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, Property<const std::string>& p)
{
	std::string temp = p;
	try {
		out << (temp).c_str();
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  exception:\n  " << ex.what() << "\n";
	}
	return out;
}

void InsertIntoIntDb()
{  
  std::cout << "\n  Demonstrating NoSql Helper Code";
  std::cout << "\n =================================\n";
  std::cout << "\n  Creating and saving NoSqlDb elements with Integer data";
  std::cout << "\n -------------------------------------------------------\n";
  NoSqlDb<intData> idb;
  Element<intData> ielem1;
  ielem1.name = "elem1";
  ielem1.category = "test";
  ielem1.data = 1;
  ielem1.desc = "Integer 1";
  ielem1.timeDate = __TIMESTAMP__;

  idb.save(ielem1.name, ielem1);

  Element<intData> ielem2;
  ielem2.name = "elem2";
  ielem2.category = "test";
  ielem2.data = 2;
  ielem2.desc = "Integer 2";
  ielem2.timeDate = __TIMESTAMP__;

  idb.save(ielem2.name, ielem2);

  Element<intData> ielem3;
  ielem3.name = "elem3";
  ielem3.category = "test";
  ielem3.data = 3;
  ielem3.desc = "Integer 3";
  ielem3.timeDate = __TIMESTAMP__;

  idb.save(ielem3.name, ielem3);

  std::cout << "\n  Retrieving elements from NoSqlDb<int>";
  std::cout << "\n ---------------------------------------\n";

  std::cout << "\n  size of idb = " << idb.count() << "\n";
  Keys ikeys = idb.keys();
  for (Key key : ikeys)
  {
    std::cout << "\n  " << key << ":";
    std::cout << idb.value(key).show();
  }
  std::cout << "\n\n";
}

int main() {

	NoSqlDb<StrData> db;
	Element<StrData> child;	
	std::cout << "\n Test Executive that demonstrates queries 2 to 9\n";
	std::cout << "\n  Demonstrating NoSql Helper Code";
	std::cout << "\n =================================\n";
	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 2\n";
	std::cout << "\n Inserting elements into the database\n";
	std::cout << "\n -------------------------------------------------------\n";

	time_t now = time(0);
	char* dt = ctime(&now);	

	Element<StrData> Barney;
	Barney.name = "Barney";
	Barney.category = "Student";
	Barney.data = "Barney Stinson! yes he is awesome";
	Barney.desc = "Male";
	Barney.timeDate = dt;
	Barney.children = { "" };
	db.save(Barney.name, Barney);

	Element<StrData> Ted;
	Ted.name = "Ted";
	Ted.category = "Professor";
	Ted.data = "Ted is an Architect";
	Ted.desc = "Male";
	Ted.timeDate = dt;
	Ted.children = { "Lily" };
	db.save(Ted.name, Ted);

	Element<StrData> Robin;
	Robin.name = "Robin";
	Robin.category = "Student";
	Robin.data = "Robin is a Journalist";
	Robin.desc = "Female";
	Robin.timeDate = dt;
	Robin.children = { "Marshall","Ross" };
	db.save(Robin.name, Robin);

	Element<StrData> Lily;
	Lily.name = "Lily";
	Lily.category = "Professor";
	Lily.data = "Lily is a Professor";
	Lily.desc = "Female";
	Lily.timeDate = dt;
	Barney.children = { "" };
	db.save(Lily.name, Lily);

	Element<StrData> Marshall;
	Marshall.name = "Marshall";
	Marshall.category = "Student";
	Marshall.data = "Marshall's son is Marvin";
	Marshall.desc = "Male";
	Marshall.children = { "" };
	db.save(Marshall.name, Marshall);

	Element<StrData> Tracy;
	Tracy.name = "Tracy";
	Tracy.category = "Receptionist";
	Tracy.data = "Tracy is Ted's wife";
	Tracy.desc = "Female";
	Tracy.children = { "Rachel" };
	db.save(Tracy.name, Tracy);	

	Keys key2 = db.keys();
	for (Key key : key2)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
		std::cout << "\n";
	}

	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";
	std::cout << "\n  size of db = " << db.count() << "\n";

	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirements 3 and 4\n";
	std::cout << "\n -------------------------------------------------------\n";

	std::cout << "\n Delete element 'Marshall' from the database\n";
	db.Delete("Marshall");
	std::cout << "\n After deleting a record - Marshall\n";
	Keys key1 = db.keys();
	for (Key key : key1)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
		std::cout << "\n";
	}
	
	std::cout << "\n Demonstrating edtition for record - Tracy\n";
	std::cout << "\n Before editing record - Tracy\n";
	std::cout << db.value("Tracy").show();	
	db.EditName("Tracy", "TracyMosby");
	db.EditCategory("Tracy", "OfficeAssistant");
	db.EditChildren("Tracy", "Joey");
	std::cout << "\n After editing record - Tracy\n";
	std::cout << db.value("Tracy").show();
	
	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";

	Keys keys = db.keys();
	for (Key key : keys) {
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}

	Barney.data = "Barney's updated data";
	Barney.category = "updated test";

	db.Update(Barney.name, Barney);	
	Keys ke = db.keys();
	for (Key key : ke)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
		std::cout << "\n";

	}

	std::cout << "\n ---------------------------------------\n";
	std::cout << " XML Persist\n";
	std::cout << " Requirement 5\n";
	std::cout << "---------------------------------------\n";
	std::string toString = db.toXml();
	std::cout << "Data from the databse was sent to XML file and its contents are:";
	std::cout << toString;

	std::ofstream xmlFile("XmlFile.xml");
	xmlFile << toString;
	xmlFile.close();
	std::cout << "\n---------------------------------------\n";
	std::cout << "Requirement 6\n";
	std::cout << "\n---------------------------------------\n";
	std::cout << "The contents of the XML file were retrieved and sent back to the database, and are as follows: \n";
	NoSqlDb<StrData> fromDB;
	fromDB.fromXml("XmlFile.xml");
	std::cout << toString;
	Keys ikeys = fromDB.keys();
	for (Key key : ikeys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << fromDB.value(key).show();
	}
	std::cout << "\n\n";

	std::cout << "\n ---------------------------------------\n";
	std::cout << "\n Demonstrating Queries\n";
	std::cout << "\n Requirement 7\n";
	std::cout << "\n ---------------------------------------\n";
	Queries q;
	std::vector<std::string> nu;
	std::cout << "\n ------------------Query 1---------------------\n";
	q.FindValueOfKey(db, Barney.name);
	std::cout << "\n -------------------Query 2--------------------\n";
	q.RetrieveChildren(db, Robin.name);
	std::cout << "\n --------------------Query 3-------------------\n";
	std::vector<std::string> result3 = q.KeysMatchingPattern(db, "InitialList", "Male", nu);
	std::cout << "\n Records with pattern Male in their description are: \n";
	for (int i = 0; i < (int)result3.size(); i++) {
		std::cout << result3[i] << "\n";
	}
	std::cout << "\n -------------------Query 3--------------------\n";
	std::vector<std::string> result3a = q.KeysMatchingPattern(db, "InitialList", "Female", nu);
	std::cout << "\n Records with pattern Female in their description are: \n";
	for (int i = 0; i < (int)result3a.size(); i++) {
		std::cout << result3a[i] << "\n";
	}
	std::cout << "\n --------------------Query 4-------------------\n";
	std::vector<std::string> result4a = q.KeysWithSpecifiedItemName(db, "InitialList", "Ted", nu);
	std::cout << "\n Records with item name Ted are\n";
	if (result4a.size() == 0)
		std::cout << "\n No records match the given item name\n";
	for (int i = 0; i < (int)result4a.size(); i++) {
		std::cout << result4a[i] << "\n";
	}
	std::cout << "\n ------------------Query 5---------------------\n";
	std::vector<std::string> result5 = q.KeysWithSpecifiedCategory(db, "InitialList", "Professor", nu);
	std::cout << "\n Records with category Professor are: \n";
	for (int i = 0; i < (int)result5.size(); i++) {
		std::cout << result5[i] << "\n";
	}
	
	std::cout << "\n --------------------Query 6-------------------\n";
	std::vector<std::string> result6 = q.KeysWithSpecifiedTemplateData(db, "InitialList", "husband", nu);
	std::cout << "\n Records with 'husband' in template data are: \n";
	for (int i = 0; i < (int)result6.size(); i++) {
		std::cout << result6[i] << "\n";
	}

	std::cout << "\n --------------------Query 7-------------------\n";	
	std::cout << "\n Keys that were inserted/ modified within the given time interval are:\n";
	std::vector<std::string> result7 = q.RetrieveKeysbetweenTimeInterval(db, result7, "2017-02-10T08:26:50");
	for (int i = 0; i < (int)result7.size(); i++) {
		std::cout << result7[i] << "\n";
	}	

	std::cout << "\n ---------------------------------------\n";
	std::cout << " Subsequent queries\n";
	std::cout << "\n Requirement 8\n";
	std::cout << "---------------------------------------\n";
	std::vector<std::string> result8 = q.SubsequentQuery(db, "ItemNameQuery");
	std::cout << "\n Result of subsequent queries: \n\n";
	for (int i = 0; i < (int)result8.size(); i++) {
		std::cout << result8[i] << "\n";
	}

	std::cout << "\n ---------------------------------------\n";
	std::cout << "\n Union of keys\n";
	std::cout << "\n Requirement 9\n";
	std::cout << "\n ---------------------------------------\n";
	std::vector<std::string> result9 = q.UnionOfKeys(db, result4a, result5, "Female");
	std::cout << "\n Result of Union of keys: \n";
	for (int i = 0; i < (int)result9.size(); i++) {
		std::cout << result9[i] << "\n";
	}

	std::cout << "\n ---------------------------------------\n";
	std::cout << "\n Project structure and dependencies\n";
	std::cout << "\n Requirement 10\n";
	std::cout << "\n ---------------------------------------\n";
	std::string toString1 = db.ProjectStructure();
	std::cout << "Contents:";
	std::cout << toString1;

	std::ofstream xmlFile1("XmlFile1.xml");
	xmlFile1 << toString1;
	xmlFile1.close();

}





	


