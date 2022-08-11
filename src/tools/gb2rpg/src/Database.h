#pragma once

#include <vector>

namespace lcf {
    class Database;
};

namespace gb2rpg {
    class Database {
    public:
        Database() = delete;

        static void genDatabase();

    private:
        static void genSwitches(lcf::Database& database);
        static void genVariables(lcf::Database& databaseDoc);
        static void genItems(lcf::Database& databaseDoc);
        static void genCharacters(lcf::Database& databaseDoc);
        static void genCommonEvents(lcf::Database& databaseDoc);
    };
};