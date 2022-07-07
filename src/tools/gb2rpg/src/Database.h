#pragma once

#include <vector>

namespace tinyxml2 {
    class XMLDocument;
};

class Database {
public:
    Database() = delete;

    static void genDatabase();

private:
    static void genSwitches(tinyxml2::XMLDocument& databaseDoc);
    static void genVariables(tinyxml2::XMLDocument& databaseDoc);
    static void genItems(tinyxml2::XMLDocument& databaseDoc);
    static void genCharacters(tinyxml2::XMLDocument& databaseDoc);
};