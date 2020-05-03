#ifndef VSCANINPROGRESSPAGE_H
#define VSCANINPROGRESSPAGE_H

#include <QWidget>
#include <QTimer>

#include <Components/VProgressBar.h>
#include <Components/VLabel.h>
#include <Components/VButton.h>
#include <Utilities/XMLReader.h>

class VScanInProgressPage : public QWidget
{
    Q_OBJECT
public:
    explicit VScanInProgressPage(QWidget* parent = nullptr);

private:    
    void setupContent();
    void scanFinished();

     VProgressBar* m_scanProgressBar = nullptr;
     VLabel* m_filesScannedLabel = nullptr;
     VLabel* m_threatsDetectedLabel = nullptr;
     VButton* m_viewResultsButton = nullptr;
     VButton* m_pauseScanButton = nullptr;
     VButton* m_cancelScanButton = nullptr;

     bool m_isPaused = false;

     QTimer* m_timer = nullptr;

     XMLReader* m_xmlReader = XMLReader::getInstance();
     VScanData m_scanData;

signals:
     void sigScanFinished(QString filesScanned, QString threatsDetected);
     void sigScanPaused();
     void sigScanResumed();
     void sigScanCancelled(QString filesScanned, QString threatsDetected);
     void sigViewResultsClicked();

public slots:
     void onScanStarted(QString scanType);

private slots:
    void update();
    void onPauseScanClicked();
    void onCancelScanClicked();
    void onViewResultsClicked();

};

#endif // VSCANINPROGRESSPAGE_H
