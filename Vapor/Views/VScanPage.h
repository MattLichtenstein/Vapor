#ifndef VSCANPAGE_H
#define VSCANPAGE_H

#include <QWidget>

#include <Components/VButton.h>
#include <Components/VDropdown.h>
#include <Components/VLabel.h>

enum class ScanTypeDescription{
    QuickScan = 0,
    FullScan
};

class VScanPage : public QWidget
{
    Q_OBJECT
public:
    explicit VScanPage(QWidget *parent = nullptr);

private:
    void setupContent();
    void updateLastScanTime(bool didComplete);

    VDropdown* m_scanTypeDropdown = nullptr;
    VButton* m_scanButton = nullptr;
    VLabel* m_lastScanTime = nullptr;
    VLabel* m_scanTypeDescription = nullptr;

    QMap<ScanTypeDescription, QString> m_scanTypeToDescriptionMap;

signals:
    void sigScanStarted(QString scanType);

public slots:
    void onScanFinished();
    void onScanCancelled();

private slots:
    void onScanBtnClicked();
    void onScanTypeChanged();

};

#endif // VSCANPAGE_H
