#include "VThreatItem.h"

#include <QHBoxLayout>

#include <Utilities/VColors.h>
#include <Utilities/VSizes.h>

VThreatItem::VThreatItem(QWidget *parent) : QWidget(parent)
{
    setupContent();
}

void VThreatItem::setFileName(QString fileName)
{
    m_fileNameLabel->setText(fileName);
}

void VThreatItem::setFilePath(QString filePath)
{
    m_filePathLabel->setText(filePath);
}

void VThreatItem::setMalwaretype(QString malwareType)
{
    m_malwareTypeLabel->setText(malwareType);
}

//Sets up the layout for a threat item
void VThreatItem::setupContent()
{
    VLabel* fileNameStringLabel = new VLabel("File name");
    fileNameStringLabel->setTextSize(LabelTextSize::Small);
    fileNameStringLabel->setTextColor(VColors::LightGrey);
    fileNameStringLabel->setFixedWidth(VSizes::FixedLabelWidth.toInt());

    VLabel* filePathStringLabel = new VLabel("File path");
    filePathStringLabel->setTextSize(LabelTextSize::Small);
    filePathStringLabel->setTextColor(VColors::LightGrey);
    filePathStringLabel->setFixedWidth(VSizes::FixedLabelWidth.toInt());

    VLabel* malwareTypeStringLabel = new VLabel("Malware type");
    malwareTypeStringLabel->setTextSize(LabelTextSize::Small);
    malwareTypeStringLabel->setTextColor(VColors::LightGrey);
    malwareTypeStringLabel->setFixedWidth(VSizes::FixedLabelWidth.toInt());

    m_fileNameLabel = new VLabel("-");
    m_fileNameLabel->setTextSize(LabelTextSize::Small);

    m_filePathLabel = new VLabel("-");
    m_filePathLabel->setTextSize(LabelTextSize::Small);

    m_malwareTypeLabel = new VLabel("-");
    m_malwareTypeLabel->setTextSize(LabelTextSize::Small);

    QHBoxLayout* fileNameLayout = new QHBoxLayout();
    fileNameLayout->addWidget(fileNameStringLabel);
    fileNameLayout->addWidget(m_fileNameLabel);
    fileNameLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));

    QHBoxLayout* filePathLayout = new QHBoxLayout();
    filePathLayout->addWidget(filePathStringLabel);
    filePathLayout->addWidget(m_filePathLabel);
    fileNameLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));

    QHBoxLayout* malwareTypeLayout = new QHBoxLayout();
    malwareTypeLayout->addWidget(malwareTypeStringLabel);
    malwareTypeLayout->addWidget(m_malwareTypeLabel);
    fileNameLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));

    QVBoxLayout* pageLayout = new QVBoxLayout();
    pageLayout->addLayout(fileNameLayout);
    pageLayout->addLayout(filePathLayout);
    pageLayout->addLayout(malwareTypeLayout);

    setLayout(pageLayout);
}
