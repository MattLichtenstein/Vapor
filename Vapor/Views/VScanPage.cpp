#include "VScanPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>

VScanPage::VScanPage(QWidget *parent) : QWidget(parent)
{
    setupContent();
}

//Sets up layout of Scan Page
void VScanPage::setupContent()
{
    //Tricky way to set text color of certain words in a label
    VLabel* welcomeLabel = new VLabel("Welcome to <font color=" + VColors::Accent + ">" + "Vapor</font>, the <font color=" + VColors::Accent + ">" +
                                      "vaporware</font> that <font color=" + VColors::Accent + ">" +
                                      "vaporizes</font> viruses");

    welcomeLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    welcomeLabel->setAlignment(Qt::AlignHCenter);

    VLabel* instructionsLabel = new VLabel("Select a type of scan below and click begin to get vaporizing");
    instructionsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    instructionsLabel->setAlignment(Qt::AlignHCenter);
    instructionsLabel->setTextSize(LabelTextSize::Medium);

    QStringList scanTypes = {"Quick scan", "Full scan"};

    m_scanTypeDropdown = new VDropdown();
    m_scanTypeDropdown->addItems(scanTypes);
    connect(m_scanTypeDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(onScanTypeChanged()));

    //The order of these strings must match the order of the ScanTypeDescription enum in the header
    //and the order of the scan types in the dropdown
    QStringList scanTypeDescriptionStrings = {"Scans only the locations on your system that are most likely to contain malware",
                                        "Scans your entire system and vaporizes anything in it's path",
                                       };

    m_scanTypeToDescriptionMap[ScanTypeDescription::QuickScan]= scanTypeDescriptionStrings[0];
    m_scanTypeToDescriptionMap[ScanTypeDescription::FullScan]= scanTypeDescriptionStrings[1];

    m_scanTypeDescription = new VLabel(scanTypeDescriptionStrings[0], LabelTextSize::Small);
    m_scanTypeDescription->setAlignment(Qt::AlignCenter);

    m_scanButton = new VButton("Begin scan", ButtonTheme::AccentText);
    connect(m_scanButton, &VButton::clicked, this, &VScanPage::onScanBtnClicked);

    m_lastScanTime = new VLabel("Last scan: Never", LabelTextSize::Small);
    m_lastScanTime->setAlignment(Qt::AlignCenter);

    QHBoxLayout* scanTypeDropdownLayout = new QHBoxLayout();
    scanTypeDropdownLayout->setAlignment(Qt::AlignHCenter);
    scanTypeDropdownLayout->addWidget(m_scanTypeDropdown);

    QVBoxLayout* scanTypeAndDescriptionLayout = new QVBoxLayout();
    scanTypeAndDescriptionLayout->setAlignment(Qt::AlignHCenter);
    scanTypeAndDescriptionLayout->setSpacing(VSizes::HelperTextSpacing.toInt());
    scanTypeAndDescriptionLayout->addLayout(scanTypeDropdownLayout);
    scanTypeAndDescriptionLayout->addWidget(m_scanTypeDescription);

    QHBoxLayout* scanTypeLayout = new QHBoxLayout();
    scanTypeLayout->addLayout(scanTypeAndDescriptionLayout);

    QVBoxLayout* btnAndScanTimeLayout = new QVBoxLayout();
    btnAndScanTimeLayout->setAlignment(Qt::AlignHCenter);
    btnAndScanTimeLayout->setSpacing(VSizes::HelperTextSpacing.toInt());
    btnAndScanTimeLayout->addWidget(m_scanButton);
    btnAndScanTimeLayout->addWidget(m_lastScanTime);

    QHBoxLayout* scanButtonLayout = new QHBoxLayout();
    scanButtonLayout->addLayout(btnAndScanTimeLayout);

    QVBoxLayout* pageLayout = new QVBoxLayout();
    pageLayout->setAlignment(Qt::AlignHCenter);
    pageLayout->addWidget(welcomeLabel);
    pageLayout->addSpacerItem(new QSpacerItem(0, VSizes::ControlsSpacing.toInt()/2, QSizePolicy::Preferred, QSizePolicy::Fixed));
    pageLayout->addWidget(instructionsLabel);
    pageLayout->addSpacerItem(new QSpacerItem(0, VSizes::ControlsSpacing.toInt(), QSizePolicy::Preferred, QSizePolicy::Fixed));
    pageLayout->addLayout(scanTypeLayout);
    pageLayout->addSpacerItem(new QSpacerItem(0, VSizes::ControlsSpacing.toInt(), QSizePolicy::Preferred, QSizePolicy::Fixed));
    pageLayout->addLayout(scanButtonLayout);

    setLayout(pageLayout);
}

//Updates time of last scan underneath the begin scan button
void VScanPage::updateLastScanTime(bool didComplete)
{
    QString lastScanDateAndTimeString = "Last scan: " + QDateTime::currentDateTime().toString("MM/dd/yyyy - h:mm:ss ap");
    lastScanDateAndTimeString = didComplete ? lastScanDateAndTimeString : lastScanDateAndTimeString + " (incomplete)";
    m_lastScanTime->setText(lastScanDateAndTimeString);
}

//Re-enables contents on Scan Page when a scan is finished
void VScanPage::onScanFinished()
{
    updateLastScanTime(true);
    m_scanButton->setEnabled(true);
    m_scanTypeDropdown->setEnabled(true);
}

//Re-enables contents on Scan Page when a scan is cancelled
void VScanPage::onScanCancelled()
{
    updateLastScanTime(false);
    m_scanButton->setEnabled(true);
    m_scanTypeDropdown->setEnabled(true);
}

//Disables the users ability to start another scan while one is in progress
//Emits signals to inform Scan in Progress page to begin scanning
void VScanPage::onScanBtnClicked()
{
    m_scanButton->setEnabled(false);
    m_scanTypeDropdown->setEnabled(false);
    emit sigScanStarted(m_scanTypeDropdown->currentText());

}

//Triggered by selecting a new dropdown option from the Scan Type Dropdown.
//Updates the helper text underneath the Scan Type Dropdown to give users a description of the type of scan selected
void VScanPage::onScanTypeChanged()
{
    m_scanTypeDescription->setText(m_scanTypeToDescriptionMap[(ScanTypeDescription)m_scanTypeDropdown->currentIndex()]);
}
