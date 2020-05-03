#ifndef VSCANDATA_H
#define VSCANDATA_H

#include <QString>
#include <QList>

//Threat data model
class VThreat
{
public:
    VThreat() {}
    void setFileName(QString fileName) { m_fileName = fileName; }
    void setFilePath(QString filePath) { m_filePath = filePath; }
    void setMalwareType(QString malwareType) { m_malwareType = malwareType; }

    QString getFileName() { return m_fileName; }
    QString getFilePath() { return m_filePath; }
    QString getMalwareType() { return m_malwareType; }

private:
    QString m_fileName;
    QString m_filePath;
    QString m_malwareType;

};

//Scan result data model
class VScanData
{
public:
    VScanData() {}
    void setScanType(QString scanType) { m_scanType = scanType; }
    void setFilesScanned(int filesScanned) { m_filesScanned = filesScanned; }
    void setThreatsDetected(int threatsDetected) { m_threatsDetected = threatsDetected; }
    void addThreat(VThreat threat) { m_threats.append(threat); }

    QString getScanType() { return m_scanType; }
    int getFilesScanned() { return m_filesScanned; }
    int getThreatsDetected() { return m_threatsDetected; }
    QList<VThreat> getThreats() { return m_threats; }

private:
    QString m_scanType;
    int m_filesScanned;
    int m_threatsDetected;
    QList<VThreat> m_threats;
};

#endif // VSCANDATA_H
