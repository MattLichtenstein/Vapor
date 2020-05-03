#ifndef VRESULTITEM_H
#define VRESULTITEM_H

#include <QWidget>
#include <QVBoxLayout>

#include <Components/VLabel.h>
#include <Components/VThreatItem.h>
#include <Models/VScanData.h>

class VResultItem : public QWidget
{
    Q_OBJECT
public:
    explicit VResultItem(QWidget *parent = nullptr);
    void setTimestamp(QString timestamp);
    void setScanType(QString scanType);
    void setFilesScanned(int filesScanned);
    void setThreatsDetected(int threatsDetected);
    void setThreats(QList<VThreat> threatsList);


private:
    void setupContent();

    VLabel* m_timestampLabel = nullptr;
    VLabel* m_threatsDetectedHeaderLabel = nullptr;
    VLabel* m_filesScannedLabel = nullptr;
    VLabel* m_threatsDetectedLabel = nullptr;
    VLabel* m_scanTypeLabel = nullptr;

    QVBoxLayout* m_allThreatsLayout = nullptr;
};

#endif // VRESULTITEM_H
