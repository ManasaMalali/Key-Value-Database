#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <iostream>
#include <memory>
#include <iostream>
#include <fstream>
#include "../Convert/Convert.h"
#include "../CppProperties/CppProperties.h"
#include "../NoSqlDb/NoSqlDb.h"
#include "../Queries/Queries.h"
#include "XMLDBConversion.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"

using sPtr = std::shared_ptr < XmlProcessing::AbstractXmlElement >;

bool toXml(NoSqlDb<StrData>& db,const std::string& xml) {
	sPtr pRoot = XmlProcessing::makeTaggedElement("Database");
	XmlProcessing::XmlDocument doc(XmlProcessing::makeDocElement(pRoot));

	for (auto i = store.begin(); i != store.end(); ++i) {
		
		sPtr pEntry = XmlProcessing::makeTaggedElement("Entry");
		Key currentKey = i->first;
		Element<Data> currentData = i->second;

		sPtr pKeyElement = XmlProcessing::makeTaggedElementNText("Key", currentKey);
		sPtr pNameElement = XmlProcessing::makeTaggedElementNText("Name", currentData.name);
		sPtr pCategoryElement = XmlProcessing::makeTaggedElementNText("Category", currentData.category);
		sPtr pDescriptionElement = XmlProcessing::makeTaggedElementNText("Description", currentData.description);
		sPtr pDateTimeElement = XmlProcessing::makeTaggedElementNText("DateTime", currentData.timeDate);

		std::vector<Key> children = currentData.children;
		sPtr pChildrenElement = XmlProcessing::makeTaggedElement("Children");
		for (Key child : children) {
			sPtr pChildElement = XmlProcessing::makeTaggedElementNText("Child", child);
			pChildrenElement->addChild(pChildElement);
		}

		sPtr pDataElement = XmlProcessing::makeTaggedElementNText("Data", Convert<Data>::toString(currentData.data));

		pEntry->addChild(pKeyElement);
		pEntry->addChild(pNameElement);
		pEntry->addChild(pCategoryElement);
		pEntry->addChild(pDescriptionElement);
		pEntry->addChild(pDateTimeElement);
		pEntry->addChild(pChildrenElement);
		pEntry->addChild(pDataElement);

		pRoot->addChild(pEntry);
	}
	std::ofstream xmlFile(xml);
	if (xmlFile.is_open())
		xmlFile << doc.toString();
	xmlFile.close();
	return true;
}

//Loads entries to DB from the given path of the XML file

void fromXml(const std::string& xml) {
	try
	{
		XmlProcessing::XmlDocument doc(xml, XmlProcessing::XmlDocument::file);
		//std::cout << doc.toString();

		std::vector<sPtr> entries = doc.descendents("Entry").select();
		for (sPtr entry : entries) {
			Element<Data> data;
			std::string key = trim(entry->children()[0]->children()[0]->value());
			data.name = trim(entry->children()[1]->children()[0]->value());
			data.category = trim(entry->children()[2]->children()[0]->value());
			data.description = trim(entry->children()[3]->children()[0]->value());
			data.timeDate = trim(entry->children()[4]->children()[0]->value());

			std::vector<sPtr> children = entry->children()[5]->children();
			std::vector<Key> _children;
			for (sPtr child : children) {
				_children.push_back(trim(child->children()[0]->value()));
			}
			data.children = _children;
			//data.data = entry->children()[6]->children()[0]->value();
			data.data = Convert<Data>::fromString(trim(entry->children()[6]->children()[0]->value()));

			if (store.find(key) != store.end())
				continue;

			store[key] = data;
		}
		updateWriteCount();
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n  " << ex.what();
	}

}