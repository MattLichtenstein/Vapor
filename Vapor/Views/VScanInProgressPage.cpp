#include "VScanInProgressPage.h"

#include <QVBoxLayout>

const int TIMEOUT = 1;
const QString FILESSCANDEFAULTSTRING = "0";
const QString THREATSDETECTEDSTRING = "0";
const QString PAUSESCANSTRING = "Pause scan";
const QString RESUMESCANSTRING = "Resume scan";

VScanInProgressPage::VScanInProgressPage(QWidget *parent) : QWidget(parent)
{
    setupContent();
}

//sets up layout for Scan in Progress page
void VScanInProgressPage::setupContent()
{
    //initializing timer to be used to update scan progress
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &VScanInProgressPage::update);

    m_scanProgressBar = new VProgressBar();

    VLabel* filesScannedDescriptionLabel = new VLabel("Files scanned", LabelTextSize::Small);
    filesScannedDescriptionLabel->setTextColor(VColors::LightGrey);

    VLabel* threatsDetectedDescriptionLabel = new VLabel("Threats detected", LabelTextSize::Small);
    threatsDetectedDescriptionLabel->setTextColor(VColors::LightGrey);

    m_filesScannedLabel = new VLabel(FILESSCANDEFAULTSTRING);
    m_filesScannedLabel->setAlignment(Qt::AlignCenter);

    m_threatsDetectedLabel = new VLabel(THREATSDETECTEDSTRING);
    m_threatsDetectedLabel->setAlignment(Qt::AlignCenter);
    m_threatsDetectedLabel->setTextColor(VColors::Accent);

    m_pauseScanButton = new VButton(PAUSESCANSTRING);
    connect(m_pauseScanButton, &VButton::clicked, this, &VScanInProgressPage::onPauseScanClicked);

    m_cancelScanButton = new VButton("Cancel scan");
    connect(m_cancelScanButton, &VButton::clicked, this, &VScanInProgressPage::onCancelScanClicked);

    m_viewResultsButton = new VButton("View results", ButtonTheme::AccentBackground);
    connect(m_viewResultsButton, &VButton::clicked, this, &VScanInProgressPage::onViewResultsClicked);
    m_viewResultsButton->hide();

    QVBoxLayout* filesScannedLayout = new QVBoxLayout();
    filesScannedLayout->setAlignment(Qt::AlignCenter);
    filesScannedLayout->addWidget(m_filesScannedLabel);
    filesScannedLayout->addWidget(filesScannedDescriptionLabel);

    QVBoxLayout* threatsDetectedLayout = new QVBoxLayout();
    threatsDetectedLayout->setAlignment(Qt::AlignCenter);
    threatsDetectedLayout->addWidget(m_threatsDetectedLabel);
    threatsDetectedLayout->addWidget(threatsDetectedDescriptionLabel);

    QFrame* verticalSeparator = new QFrame();
    verticalSeparator->setFrameShape(QFrame::VLine);
    verticalSeparator->setEnabled(false);

    QHBoxLayout* statsLayout = new QHBoxLayout();
    statsLayout->addLayout(filesScannedLayout);
    statsLayout->addWidget(verticalSeparator);
    statsLayout->addLayout(threatsDetectedLayout);

    QHBoxLayout* buttonControlsLayout = new QHBoxLayout();
    buttonControlsLayout->setSpacing(VSizes::ControlsSpacing.toInt());
    buttonControlsLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Maximum));
    buttonControlsLayout->addWidget(m_pauseScanButton);
    buttonControlsLayout->addWidget(m_cancelScanButton);
    buttonControlsLayout->addWidget(m_viewResultsButton);
    buttonControlsLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Maximum));

    QVBoxLayout* pageLayout = new QVBoxLayout();
    pageLayout->addWidget(m_scanProgressBar);
    pageLayout->addLayout(statsLayout);
    pageLayout->addSpacerItem(new QSpacerItem(0, VSizes::SIPControlsSpacing.toInt(), QSizePolicy::Maximum, QSizePolicy::Fixed));
    pageLayout->addLayout(buttonControlsLayout);

    setLayout(pageLayout);
}

//Replace pause/cancel buttons with view results button when scan is finished
void VScanInProgressPage::scanFinished()
{
    m_pauseScanButton->hide();
    m_cancelScanButton->hide();
    m_viewResultsButton->show();
}

//Resets all values and states on scan start
void VScanInProgressPage::onScanStarted(QString scanType)
{
    //Get scan data from xml file once we know which once to parse based on the scanType string passed in to this function
    m_xmlReader->parseScanDataFile(scanType);
    m_scanData = m_xmlReader->getScanData();

    m_scanProgressBar->setMaximum(m_scanData.getFilesScanned());
    m_scanProgressBar->setValue(0);

    m_pauseScanButton->setTheme(ButtonTheme::AccentText);
    m_pauseScanButton->setText(PAUSESCANSTRING);
    m_isPaused = false;

    m_pauseScanButton->show();
    m_cancelScanButton->show();
    m_viewResultsButton->hide();

    m_filesScannedLabel->setText(FILESSCANDEFAULTSTRING);
    m_threatsDetectedLabel->setText(THREATSDETECTEDSTRING);
    m_threatsDetectedLabel->setTextColor(VColors::Accent);
    m_timer->start(TIMEOUT);
}

//Updates progress bar and labels (on 1msec timer)
void VScanInProgressPage::update()
{
    int numFilesScanned = m_filesScannedLabel->text().toInt();
    numFilesScanned++;
    QString newNumFilesScanned = QString::number(numFilesScanned);
    m_filesScannedLabel->setText(newNumFilesScanned);

    m_scanProgressBar->setValue(numFilesScanned);

    //Evenly increment numThreatsDetected throughout the scan
    //numFilesScanned / numThreatsDetected (i.e. 900 files | 3 threats | 900/3 = 1 threat every 300 files scanned
    if(m_scanData.getThreatsDetected() > 0)
    {
        int threatFrequency = m_scanData.getFilesScanned() / m_scanData.getThreatsDetected();
        //Make sure we don't display more or less threats than stated in xml file (due to rounding)
        if(numFilesScanned % threatFrequency == 0 && m_threatsDetectedLabel->text().toInt() < m_scanData.getThreatsDetected())
        {
            int numThreatsDetected = m_threatsDetectedLabel->text().toInt();
            numThreatsDetected++;
            QString newNumThreatsDetected = QString::number(numThreatsDetected);
            m_threatsDetectedLabel->setText(newNumThreatsDetected);
            m_threatsDetectedLabel->setTextColor(VColors::LightRed);
        }
    }

    //Scan is finished once it has gone through all files
    if(numFilesScanned == m_scanData.getFilesScanned())
    {
        m_timer->stop();
        scanFinished();
        emit sigScanFinished(m_filesScannedLabel->text(), m_threatsDetectedLabel->text());
    }
}

//Pauses/resumes scan in progress (timer)
void VScanInProgressPage::onPauseScanClicked()
{
    if(!m_isPaused)
    {
        m_timer->stop();
        m_pauseScanButton->setTheme(ButtonTheme::AccentBackground);
        m_pauseScanButton->setText(RESUMESCANSTRING);
        emit sigScanPaused();
    }
    else
    {
        m_timer->start(TIMEOUT);
        m_pauseScanButton->setTheme(ButtonTheme::AccentText);
        m_pauseScanButton->setText(PAUSESCANSTRING);
        emit sigScanResumed();
    }

    m_isPaused = !m_isPaused;
}

//Stops scans and posts results to the results page for what the scan has done thus far
void VScanInProgressPage::onCancelScanClicked()
{
    m_timer->stop();
    scanFinished();
    emit sigScanCancelled(m_filesScannedLabel->text(), m_threatsDetectedLabel->text());
}

//Takes to you results page from scan in progress page
void VScanInProgressPage::onViewResultsClicked()
{
    emit sigViewResultsClicked();
}
