#include "VResultItem.h"

#include <QHBoxLayout>

#include <Utilities/VColors.h>
#include <Utilities/VSizes.h>

VResultItem::VResultItem(QWidget *parent) : QWidget(parent)
{
    setupContent();
}

void VResultItem::setTimestamp(QString timestamp)
{
    m_timestampLabel->setText(timestamp);
}

void VResultItem::setScanType(QString scanType)
{
    m_scanTypeLabel->setText(scanType);
}

void VResultItem::setFilesScanned(int filesScanned)
{
    m_filesScannedLabel->setText(QString::number(filesScanned));
}

void VResultItem::setThreatsDetected(int threatsDetected)
{
    if(threatsDetected > 0)
    {
        //threat vs threats (plural)
        if(threatsDetected == 1)
        {
            m_threatsDetectedHeaderLabel->setText(QString::number(threatsDetected) + " threat detected");
        }
        else
        {
            m_threatsDetectedHeaderLabel->setText(QString::number(threatsDetected) + " threats detected");
        }
        m_threatsDetectedHeaderLabel->setTextColor(VColors::LightRed);
        m_threatsDetectedLabel->setTextColor(VColors::LightRed);
    }
    else
    {
        m_threatsDetectedHeaderLabel->setText("No threats detected");
        m_threatsDetectedHeaderLabel->setTextColor(VColors::Accent);
        m_threatsDetectedLabel->setTextColor(VColors::Accent);
    }
    m_threatsDetectedLabel->setText(QString::number(threatsDetected));

}

//Sets up threat items
void VResultItem::setThreats(QList<VThreat> threatsList)
{
    //Iterates through all threats and adds them to the layout
    for(int i = 0; i < threatsList.count(); i++)
    {
        VThreatItem* threatItem = new VThreatItem;

        threatItem->setFileName(threatsList[i].getFileName());
        threatItem->setFilePath(threatsList[i].getFilePath());
        threatItem->setMalwaretype(threatsList[i].getMalwareType());

        QHBoxLayout* threatLayout = new QHBoxLayout();
        threatLayout->setContentsMargins(VSizes::FixedLabelMargin.toInt(), 0, 0, 0);
        threatLayout->addWidget(threatItem);

        m_allThreatsLayout->addLayout(threatLayout);

        if(i < threatsList.count() - 1)
        {
            //creates a horizontal separator
            QFrame* hSep = new QFrame();
            hSep->setFrameShape(QFrame::HLine);
            hSep->setEnabled(false);
            hSep->setFixedWidth(VSizes::SmallSeparatorWidth.toInt());

            QVBoxLayout* separatorLayout = new QVBoxLayout();
            separatorLayout->setAlignment(Qt::AlignHCenter);
            separatorLayout->addWidget(hSep);

            m_allThreatsLayout->addLayout(separatorLayout);
        }
    }
}

//Sets up result item content layout
void VResultItem::setupContent()
{
    VLabel* scanTypeStringLabel = new VLabel("Scan type");
    scanTypeStringLabel->setTextSize(LabelTextSize::Small);
    scanTypeStringLabel->setTextColor(VColors::LightGrey);

    VLabel* filesScannedStringLabel = new VLabel("Files scanned");
    filesScannedStringLabel->setTextSize(LabelTextSize::Small);
    filesScannedStringLabel->setTextColor(VColors::LightGrey);

    VLabel* threatsDetectedStringLabel = new VLabel("Threats detected");
    threatsDetectedStringLabel->setTextSize(LabelTextSize::Small);
    threatsDetectedStringLabel->setTextColor(VColors::LightGrey);

    m_timestampLabel = new VLabel("-", LabelTextSize::Medium);

    m_threatsDetectedHeaderLabel = new VLabel("-", LabelTextSize::Medium);

    m_scanTypeLabel = new VLabel("-");
    m_scanTypeLabel->setTextSize(LabelTextSize::Small);

    m_filesScannedLabel = new VLabel("-");
    m_filesScannedLabel->setTextSize(LabelTextSize::Small);

    m_threatsDetectedLabel = new VLabel("-");
    m_threatsDetectedLabel->setTextSize(LabelTextSize::Small);

    QFrame* horizontalSeparator = new QFrame();
    horizontalSeparator->setFrameShape(QFrame::HLine);
    horizontalSeparator->setEnabled(false);

    QHBoxLayout* headerLabelsLayout = new QHBoxLayout();
    headerLabelsLayout->addWidget(m_timestampLabel);
    headerLabelsLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
    headerLabelsLayout->addWidget(m_threatsDetectedHeaderLabel);

    QVBoxLayout* headerLayout = new QVBoxLayout();
    headerLayout->addLayout(headerLabelsLayout);
    headerLayout->addWidget(horizontalSeparator);

    QHBoxLayout* scanTypeLayout = new QHBoxLayout();
    scanTypeLayout->addWidget(scanTypeStringLabel);
    scanTypeLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
    scanTypeLayout->addWidget(m_scanTypeLabel);

    QHBoxLayout* filesScannedLayout = new QHBoxLayout();
    filesScannedLayout->addWidget(filesScannedStringLabel);
    filesScannedLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
    filesScannedLayout->addWidget(m_filesScannedLabel);

    QHBoxLayout* threatsDetectedLayout = new QHBoxLayout();
    threatsDetectedLayout->addWidget(threatsDetectedStringLabel);
    threatsDetectedLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
    threatsDetectedLayout->addWidget(m_threatsDetectedLabel);

    m_allThreatsLayout = new QVBoxLayout();

    QVBoxLayout* pageLayout = new QVBoxLayout();
    pageLayout->addLayout(headerLayout);
    pageLayout->addLayout(scanTypeLayout);
    pageLayout->addLayout(filesScannedLayout);
    pageLayout->addLayout(threatsDetectedLayout);
    pageLayout->addLayout(m_allThreatsLayout);

    setLayout(pageLayout);
}
