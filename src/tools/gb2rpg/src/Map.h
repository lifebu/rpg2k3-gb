#include <vector>
#include <string>

class GBFile;
namespace tinyxml2 {
    class XMLDocument;
    class XMLNode;
};

class Map {
public:
    Map(GBFile& gbFile);
    ~Map();


    // TODO: 
    // could make this non-copyable but moveable, makes semantic sense.
    //  - could save gbFile to recreate event on copy 
    //  - shallow copy on event => BUT this requires other to be non-const. 

    // tinyxml2::XMLDocument is non copyable => therefore map cannot be! (also semantic)
    Map(const Map& other) {
        throw;
    };
    Map& operator=(const Map& other) = delete;

    Map(Map&& other) {
        throw;
    };
    Map& operator=(Map&& other) = delete;

    /*
    * Export to .xml file for the map at the full filepath.
    */
    void exportXML(std::string filePath);

    static std::vector<Map> genMapFiles(std::vector<GBFile>& gbFiles);

private:
    void generateDMGROM();
    void generateMapROM(GBFile& gbFile);
    void generateMapRAM();

    // Setup and Helper Functions.
    // TODO: Some of these helper functions should go into to a more general code-base. e.g. Generation of Command Parameters can be made more general.
    void setEventIDNameCoord(tinyxml2::XMLDocument* event, int id, std::string& name, int x, int y);

    void changeCommandParameters(tinyxml2::XMLNode* command, std::string parameter);
    void setupMapRomHeader(tinyxml2::XMLDocument* mapRomHeader);
    void setupMapRomLabel(tinyxml2::XMLDocument* mapRomLabel, int labelID, int firstVar, int secondVar);

    tinyxml2::XMLDocument* mapDoc;
    // MAP RAM Events start with this ID.
    int mapRAMID;
};