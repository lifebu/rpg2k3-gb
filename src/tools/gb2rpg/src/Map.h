#include <vector>
#include <string>

class GBFile;
namespace tinyxml2 {
    class XMLDocument;
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

    Map(Map&& other) = delete;
    Map& operator=(Map&& other) = delete;

    /*
    * Export to .xml file for the map at the full filepath.
    */
    void exportXML(std::string filePath);

    static std::vector<Map> genMapFiles(std::vector<GBFile>& gbFiles);

private:
    void generateMapROM(GBFile& gbFile);
    void generateMapRAM();

    
    tinyxml2::XMLDocument* events;
    int nextEventID;

    inline static int mapTemplateRefCount = 0;
    inline static tinyxml2::XMLDocument* mapTemplate = nullptr;
    inline static int dmgTemplateRefCount = 0;
    inline static tinyxml2::XMLDocument* dmgTemplate = nullptr;
};