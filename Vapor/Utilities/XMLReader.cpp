#include "XMLReader.h"

#include <QFile>
#include <QXmlStreamReader>

#include <Utilities/VPaths.h>

XMLReader* XMLReader::m_instance = nullptr;

//Parses XML and stores data in a model
//Assumes well-formed XML file (no error checking for the sake of time)
void XMLReader::parseScanDataFile(QString scanType)
{
    //scanType is either "Quick scan" or "Full scan"
    QString filePath = VPaths::TestFilesPath + scanType + ".xml";

    //open xml files
    QFile* xmlFile = new QFile(filePath);
    xmlFile->open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader* xmlReader = new QXmlStreamReader(xmlFile);

    while(!xmlReader->atEnd() && !xmlReader->hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }

        if(xmlReader->name() == "ResultItem")
        {
            VScanData result;
            //Iterate through everything in ResultItem
            while(xmlReader->readNextStartElement())
            {
                if(xmlReader->name() == "ScanType")
                {
                    result.setScanType(xmlReader->readElementText());
                }
                else if(xmlReader->name() == "FilesScanned")
                {
                    result.setFilesScanned(xmlReader->readElementText().toInt());
                }
                else if(xmlReader->name() == "ThreatsDetected")
                {
                    result.setThreatsDetected(xmlReader->readElementText().toInt());
                }
                else if(xmlReader->name() == "Threat")
                {
                    VThreat threat;
                    //Iterate through everything in Threat
                    while(xmlReader->readNextStartElement())
                    {
                        if(xmlReader->name() == "FileName")
                        {
                            threat.setFileName(xmlReader->readElementText());
                        }
                        else if(xmlReader->name() == "FilePath")
                        {
                            threat.setFilePath(xmlReader->readElementText());
                        }
                        else if(xmlReader->name() == "MalwareType")
                        {
                            threat.setMalwareType(xmlReader->readElementText());
                        }
                    }
                    result.addThreat(threat);
                }
            }
            m_scanData = result;
        }
    }
}

//XMLReader is a singleton class, that way data parsed from the XML can easily be accessed around the application
XMLReader* XMLReader::getInstance()
{
    if(!m_instance)
    {
        m_instance = new XMLReader();
    }

    return m_instance;
}
