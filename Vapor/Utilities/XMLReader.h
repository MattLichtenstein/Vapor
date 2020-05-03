#ifndef XMLREADER_H
#define XMLREADER_H

#include <Models/VScanData.h>

//Singleton
class XMLReader
{

public:
    static XMLReader* getInstance();
    void parseScanDataFile(QString scanType);
    VScanData getScanData() { return m_scanData; }

private:
    static XMLReader* m_instance;
    XMLReader() {};
    VScanData m_scanData;

};

#endif // XMLREADER_H
