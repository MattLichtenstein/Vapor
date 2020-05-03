#ifndef VTHREATITEM_H
#define VTHREATITEM_H

#include <QWidget>

#include <Components/VLabel.h>

class VThreatItem : public QWidget
{
    Q_OBJECT
public:
    explicit VThreatItem(QWidget *parent = nullptr);
    void setFileName(QString fileName);
    void setFilePath(QString filePath);
    void setMalwaretype(QString malwareType);

private:
    void setupContent();

    VLabel* m_fileNameLabel = nullptr;
    VLabel* m_filePathLabel = nullptr;
    VLabel* m_malwareTypeLabel = nullptr;

};

#endif // VTHREATITEM_H
