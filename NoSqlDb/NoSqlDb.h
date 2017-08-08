#pragma once
#pragma warning (disable : 4996)
////////////////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp: key/value pair in-memory database                             //
// Application: Key Value DataBase, Spring 2017                               //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                       //
// Author:      Manasa Malali Nagabhushana, CSE687 - OOD,Spring 2017          //
// Source:		James W Fawcett                                               //
////////////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package provides template class called element containing data elements in NoSql DataBase
* It contains Interface and Implementation of Save,Delete,Updation,Display functionalities of DataBase
*
* Required Files:
* ---------------
*   - CppProperties.h,CppProperties.cpp
*   - XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp

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

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../CppProperties/CppProperties.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../Convert/Convert.h"
#include "../Utilities/StrHelper.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include <ctime>
#include <fstream>


/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair
template<typename Data>
class Element
{
public:
  using Name = std::string;
  using Category = std::string;
  using TimeDate = std::string;
  using ChildRelation = std::vector<std::string>;
  using Desc = std::string;

  Property<Name> name;                // metadata
  Property<Category> category;        // metadata
  Property<TimeDate> timeDate;        // metadata
  Property<Data> data;                // data
  Property<Desc> desc;				  // metadata 
  Property<ChildRelation> children;   //metadata 
  std::string show();
};

//show function displays all the elements in the database
template<typename Data>
std::string Element<Data>::show()
{
  std::ostringstream out;
  out.setf(std::ios::adjustfield, std::ios::left);
  out << "\n    " << std::setw(16) << "name"     << " : " << name;
  out << "\n    " << std::setw(16) << "category" << " : " << category;
  out << "\n    " << std::setw(16) << "timeDate" << " : " << timeDate;
  out << "    " << std::setw(16) << "description" << " : " << desc;
  out << "\n    " << std::setw(16) << "data"     << " : " << data;
  out << "\n    " << std::setw(16) << "children" << " : ";

  //children keys being displayed 
std::vector<std::string> temp = children;
  for (int i = 0; i < (int)temp.size(); i++) {
	  out << temp[i]<<" ";
  }
  return out.str();
}
/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements
template<typename Data>
class NoSqlDb
{
public:
  using Key = std::string;
  using Keys = std::vector<Key>;
  Keys keys();
  bool save(Key key, Element<Data> elem);
  bool Delete(Key key);
  void DeleteChildren(Key key1);
  void EditName(Key key, std::string newName);
  void EditCategory(Key key, std::string newCategory);
  void EditData(Key key, std::string newData);
  void EditDescription(Key key, std::string newDescription);
  void EditChildren(Key key, std::string newChildren);
  void Update(Key key, Element<Data> elem);
  Element<Data> value(Key key);
  size_t count();
  void set_timedate(Key &key, Element<Data> &elem);
  std::string toXml();  
  std::string Req10toXml();
  std::string ProjectStructure();
  void fromXml(const std::string& xml); 

private:
	using Item = std::pair<Key, Element<Data>>;
	std::unordered_map<Key, Element<Data>> store;	
};

//Function to save the time and date of record
template<typename Data>
void NoSqlDb<Data>::set_timedate(Key& key, Element<Data>& elem)
{
	Queries q1;
	elem.timeDate = q1.getTime(time(NULL));	
}

//keys of dataBase are stored in a collection 
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
  Keys keys;
  for (Item item : store)
  {
    keys.push_back(item.first);
  }
  return keys;
}

//Elements are saved into DataBase using save function 
template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{

  if(store.find(key) != store.end())
    return false;
  set_timedate(key, elem);
  store[key] = elem;
  return true;
}

//Elements metadata or data can be updated in to the database using update function
template<typename Data>
void NoSqlDb<Data>::Update(Key key, Element<Data> elem)
{
	if(store.find(key)!=store.end())
	store[key] = elem;		
}

//An element can be removed from database using Delete function
template<typename Data>
bool NoSqlDb<Data>::Delete(Key key)
{
	if (store.find(key) == store.end()) {
		cout << "\n Given key does not exist in the database. \n";
		return false;
	}
	else {
		store.erase(key);
		cout << "\n Record with the given key was deleted\n";
		DeleteChildren(key);
		return true;
	}
}
// Function to delete the children
template<typename Data>
void NoSqlDb<Data>::DeleteChildren(Key key1)
{
	for (Item s : store)
	{
		Key givenKey;
		std::vector<std::string> list1 = s.second.children;
		for (int i = 0; i < (int)list1.size(); i++)
		{
			if (list1[i] == key1)
				list1.erase(list1.begin() + i);
		}
		s.second.children = list1;		
		givenKey = s.first;
		store[givenKey].children = s.second.children;
	}	
}
// Function to edit metadata - name
template<typename Data>
void NoSqlDb<Data>::EditName(Key key, std::string newName)
{
	Element<Data> result;
	result = store[key];
	result.name = newName;
	set_timedate(key, result);
	store[key] = result;	
	return;
}
// Function to edit metadata - category
template<typename Data>
void NoSqlDb<Data>::EditCategory(Key key, std::string newCategory)
{
	Element<Data> result1;
	result1 = store[key];
	result1.category = newCategory;
	set_timedate(key, result1);
	store[key] = result1;	
	return;
}
// Function to edit metadata - data
template<typename Data>
void NoSqlDb<Data>::EditData(Key key, std::string newData)
{
	Element<Data> result2;
	result2 = store[key];
	result2.data = newData;
	set_timedate(key, result2);
	store[key] = result2;	
	return;
}
// Function to edit metadata - description
template<typename Data>
void NoSqlDb<Data>::EditDescription(Key key, std::string newDescription)
{
	Element<Data> result3;
	result3 = store[key];
	result3.desc = newDescription;
	set_timedate(key, result3);
	store[key] = result3;	
	return;
}
// Function to edit metadata - children
template<typename Data>
void NoSqlDb<Data>::EditChildren(Key key, std::string newChildren)
{	
	Element<Data> result4;
	result4 = store[key];
	std::vector<std::string> temp = result4.children.getValue();
	temp.push_back(newChildren);
	result4.children = temp;
	store[key] = result4;	
	return;
}
// Function that returns all the metadata value
template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
  if (store.find(key) != store.end())
    return store[key];
  return Element<Data>();
}

//count function returns the number of elements in the database
template<typename Data>
size_t NoSqlDb<Data>::count()
{
  return store.size();
}

// Function to write the contents of the database to an Xml file
template<typename Data>
std::string NoSqlDb<Data>::toXml()
{
	std::cout << "\nSends the data from database to xml\n";
	std::string xml;
	XmlDocument doc;
	SPtr pRoot = makeTaggedElement("Database");
	doc.docElement() = pRoot;

	for (Item item : store)
	{
		SPtr pElem = makeTaggedElement("Element");
		pRoot->addChild(pElem);
		SPtr pKey = makeTaggedElement("Key");
		pElem->addChild(pKey);
		SPtr pTextKey = makeTextElement(item.second.name);
		pKey->addChild(pTextKey);

		SPtr pValue = makeTaggedElement("Value");
		pElem->addChild(pValue);

		SPtr pName = makeTaggedElement("Name");
		pValue->addChild(pName);
		SPtr pTextName = makeTextElement(item.second.name);
		pName->addChild(pTextKey);

		SPtr pCategory = makeTaggedElement("Category");
		pValue->addChild(pCategory);
		SPtr pTextCategory = makeTextElement(item.second.category);
		pCategory->addChild(pTextCategory);

		SPtr pDescription = makeTaggedElement("Description");
		pValue->addChild(pDescription);
		SPtr pTextDescription = makeTextElement(item.second.desc);
		pDescription->addChild(pTextDescription);

		SPtr pTimeDate = makeTaggedElement("Timedate");
		pValue->addChild(pTimeDate);
		SPtr pTextTimeDate = makeTextElement(item.second.timeDate);
		pTimeDate->addChild(pTextTimeDate);

		SPtr pChildren = makeTaggedElement("Children");
		pValue->addChild(pChildren);

		for (unsigned int i = 0; i < item.second.children.getValue().size(); i++) {
			SPtr pChild = makeTaggedElement("Child");
			SPtr pTextChild = makeTextElement(item.second.children.getValue().at(i));
			pChild->addChild(pTextChild);
			pChildren->addChild(pChild);
		}
		SPtr pData = makeTaggedElement("Data");
		pValue->addChild(pData);
		SPtr ptextData = makeTextElement(item.second.data);
		pData->addChild(ptextData);
	}
	xml = doc.toString();
	return xml;
}
template<typename Data>
std::string NoSqlDb<Data>::ProjectStructure()
{
	std::ofstream ProjectStruc;
	ProjectStruc.open("../projectstruc.xml");
	std::string xml;
	XmlDocument doc;
	SPtr pRoot = makeTaggedElement("Project 1");
	doc.docElement() = pRoot;
	SPtr pTestExecElem = makeTaggedElement("Test Executive");
	pRoot->addChild(pTestExecElem);
	SPtr pDependentfiles = makeTaggedElement("Dependencies");
	SPtr pTextElem = makeTextElement("XmlDocument, NoSqlDb,Queries,CppProperties,XmlPersist");
	pDependentfiles->addChild(pTextElem);
	pTestExecElem->addChild(pDependentfiles);
	SPtr pNoSqlDb = makeTaggedElement("NoSqlDb");
	pRoot->addChild(pNoSqlDb);
	SPtr pDependent = makeTaggedElement("Dependencies");
	SPtr pTextElem1 = makeTextElement("XmlDocument, CppProperties");
	pDependent->addChild(pTextElem1);
	pNoSqlDb->addChild(pDependent);
	SPtr pQueries = makeTaggedElement("Queries");
	pRoot->addChild(pQueries);
	SPtr pDependent1 = makeTaggedElement("Dependencies");
	SPtr pTextElem11 = makeTextElement("NoSqlDb,CppProperties");
	pDependent1->addChild(pTextElem11);
	pQueries->addChild(pDependent1);	
	SPtr pDepend = makeTaggedElement("Dependencies");
	SPtr pText = makeTextElement("NoSqlDb,CppProperties");
	pDepend->addChild(pText);	
	xml = doc.toString();
	return xml;
	ProjectStruc << xml;
	ProjectStruc.close();
}

// Function to retrieve data from xml back to database
template<typename Data>
void NoSqlDb<Data>::fromXml(const std::string& xml)
{

	std::cout << "Send contents from XML file back to database \n";
	try {
		XmlDocument doc(xml, XmlDocument::file);

		std::vector<SPtr> s = doc.descendents("element").select();		

		for (int i = 0; i < int(s.size()); i++) {
			std::vector<SPtr> keyDesc = doc.descendents("key").select();
			std::vector<SPtr> valueDesc = doc.descendents("value").select();

			Element<Data> element;
			std::string name_value = valueDesc.at(i)->children()[0]->children()[0]->value();
			name_value = trim(name_value);
			element.name = name_value;

			std::string category_value = valueDesc.at(i)->children()[1]->children()[0]->value();
			category_value = trim(category_value);
			element.category = category_value;

			std::string textDescription_value = valueDesc.at(i)->children()[1]->children()[0]->value();
			textDescription_value = trim(textDescription_value);
			element.desc = textDescription_value;

			std::string timeDate_value = valueDesc.at(i)->children()[3]->children()[0]->value();
			timeDate_value = trim(timeDate_value);
			element.timeDate = timeDate_value;
			std::vector<std::string> children_value;
			children_value.clear();
			for (unsigned int j = 0; j < valueDesc.at(i)->children()[4]->children().size(); j++) {
			std::string childKey = trim(valueDesc.at(i)->children()[4]->children()[j]->children()[0]->value());
			children_value.push_back(childKey);
			}
			element.children = children_value;

			std::string data_value = valueDesc.at(i)->children()[2]->children()[0]->value();
			data_value = trim(data_value);
			element.data = Convert<Data>::fromString(data_value);

			std::string key_value = keyDesc.at(i)->children()[0]->value();
			key_value = trim(key_value);
			this->save(key_value, element);
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  xml error";
		std::cout << "\n  " << ex.what();
	}
}














