#pragma once
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
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../NoSqlDb/NoSqlDb.h"
#include "../Queries/Queries.h"

template<typename Data>
class XMLDBConversion
{
	bool toXml(const std::string& xml);
	void fromXml(const std::string& xml);


};

