#ifndef VRESULTSPAGE_H
#define VRESULTSPAGE_H

#include <QWidget>
#include <QVBoxLayout>

#include <Components/VResultItem.h>
#include "Components/VScrollArea.h"
#include <Utilities/XMLReader.h>

class VResultsPage : public QWidget
{
    Q_OBJECT
public:
    explicit VResultsPage(QWidget *parent = nullptr);

private:
    void setupContent();

    VLabel* m_zeroStateLabel = nullptr;
    VScrollArea* m_scrollArea = nullptr;
    QVBoxLayout* m_pageLayout = nullptr;

    bool m_isZeroState = true;

    XMLReader* m_xmlReader = XMLReader::getInstance();
    VScanData m_scanData;

public slots:
    void onScanComplete(QString filesScanned, QString threatsDetected);
    void onViewResultsClicked();
};

#endif // VRESULTSPAGE_H
