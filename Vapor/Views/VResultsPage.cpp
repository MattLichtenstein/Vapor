#include "VResultsPage.h"

#include <QMetaMethod>
#include <QDateTime>

#include "Components/VResultItem.h"
#include "Utilities/VColors.h"

VResultsPage::VResultsPage(QWidget *parent) : QWidget(parent)
{
    setupContent();
}

//Sets up layout for the Scan Results page
void VResultsPage::setupContent()
{
    m_zeroStateLabel = new VLabel("No results");
    m_zeroStateLabel->setTextColor(VColors::LightGrey);

    m_pageLayout = new QVBoxLayout();
    m_pageLayout->setAlignment(Qt::AlignCenter);
    m_pageLayout->addWidget(m_zeroStateLabel);

    QWidget* widget = new QWidget();
    widget->setLayout(m_pageLayout);
    widget->setStyleSheet("background-color: transparent");

    m_scrollArea = new VScrollArea();
    m_scrollArea->setWidget(widget);
    m_scrollArea->setWidgetResizable(true);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_scrollArea);

    setLayout(layout);
}

//Update results page when scan is complete (finished or cancelled)
void VResultsPage::onScanComplete(QString filesScanned, QString threatsDetected)
{
    //Triggered when first scan of the session completes
    if(m_isZeroState)
    {
        m_isZeroState = false;
        m_zeroStateLabel->hide();
        m_pageLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding));
    }

    //Gets scan data read in from XML file from singleton
    m_scanData = m_xmlReader->getScanData();

    QString scanTimestamp = QDateTime::currentDateTime().toString("MM/dd/yyyy - h:mm:ss ap");

    //Checks which signal called onScanComplete (to know whether the scan was cancelled or actually finished)
    QMetaMethod metaMethod = sender()->metaObject()->method(senderSignalIndex());
    if(metaMethod.name() == "sigScanCancelled")
    {
        scanTimestamp += " (incomplete)";
    }

    //Building result item to display on this page
    VResultItem* item = new VResultItem();
    item->setTimestamp(scanTimestamp);
    item->setScanType(m_scanData.getScanType());
    item->setFilesScanned(filesScanned.toInt());
    item->setThreatsDetected(threatsDetected.toInt());
    if(threatsDetected.toInt() > 0)
    {
        //Only send over the number of threats detected (i.e. scan may contain 10 threats, but scan was cancelled
        //after only 1 was found. Only send that 1 threat that was detected
        item->setThreats(m_scanData.getThreats().mid(0, threatsDetected.toInt()));
    }

    //Accounts for hiden zero-state widget
    m_pageLayout->insertWidget(1, item);

}

//Slot triggered when "View Results" button is clicked on the Scan in Progress page
void VResultsPage::onViewResultsClicked()
{
    m_scrollArea->verticalScrollBar()->setValue(0);
}
