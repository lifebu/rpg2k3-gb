#include <vector>

class GBFile;

class Database {
public:
    Database(std::vector<GBFile>& gbFiles);

    static void genDatabase(std::vector<GBFile>& gbFiles);
private:

};