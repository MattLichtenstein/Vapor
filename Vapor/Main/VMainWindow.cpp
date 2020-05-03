#include "VMainWindow.h"

#include <QApplication>
#include <QScreen>

#include <Views/VScanPage.h>
#include <Views/VResultsPage.h>
#include <Views/VScanInProgressPage.h>
#include <Components/VWindowTitleBar.h>
#include <Utilities/VColors.h>
#include <Utilities/VIcons.h>

VMainWindow::VMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupWindow();
    setupWindowContent();
}

//Readjust background on resize event
void VMainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    QPixmap background(VIcons::BackgroundPath);
    background = background.scaled(size(), Qt::IgnoreAspectRatio);

    QPalette pal = palette();
    pal.setBrush(QPalette::Background, background);
    setPalette(pal);
}

//Setting min and max window size (such that max window size is the full screen)
void VMainWindow::setupWindow()
{
    setMinimumSize(1200,800);
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenRec = screen->geometry();
    int height = screenRec.height();
    int width = screenRec.width();
    setMaximumSize(QSize(width, height));
}

//Setting up the layout for the MainWindow content
void VMainWindow::setupWindowContent()
{
    m_navigator = new VNavigator();

    VWindowTitleBar* titleBar = new VWindowTitleBar();
    VScanPage* scanPage = new VScanPage();
    VResultsPage* resultsPage = new VResultsPage();
    VScanInProgressPage* sipPage = new VScanInProgressPage();

    m_windowLayout = new QVBoxLayout();
    m_windowLayout->setSpacing(VSizes::MainWindowSpacing.toInt());
    m_windowLayout->addWidget(titleBar);
    m_windowLayout->addWidget(m_navigator);
    m_windowLayout->addWidget(scanPage);
    m_windowLayout->addWidget(resultsPage);
    m_windowLayout->addWidget(sipPage);

    scanPage->hide();
    resultsPage->hide();
    sipPage->hide();

    m_windowLayout->setAlignment(Qt::AlignTop);
    connect(m_navigator, &VNavigator::sigPageChanged, this, &VMainWindow::onPageChanged);

    VButton* upgradeBtn = new VButton("Upgrade to premium", ButtonTheme::AccentBackground);
    upgradeBtn->setMouseTracking(true);
    upgradeBtn->setHoverText("Just kidding!");

    titleBar->addWidget(upgradeBtn);

    m_navigator->addNavItem(scanPage, "Scan");
    m_navigator->addNavItem(resultsPage, "Results");
    m_navigator->addTempNavItem(sipPage, "");

    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(m_windowLayout);

    setCentralWidget(centralWidget);

    //These connect statements act as the controller for the applicaation. This is how the different pages communicate with each other, since the MainWindow has access to all of the pages
    //For smaller applications, this is typically okay, but for larger applications, you may want to take the interface router for communication between files
    connect(sipPage, &VScanInProgressPage::sigScanFinished, scanPage, &VScanPage::onScanFinished);
    connect(sipPage, &VScanInProgressPage::sigScanCancelled, scanPage, &VScanPage::onScanCancelled);

    connect(scanPage, &VScanPage::sigScanStarted, sipPage, &VScanInProgressPage::onScanStarted);

    connect(sipPage, &VScanInProgressPage::sigScanFinished, resultsPage, &VResultsPage::onScanComplete);
    connect(sipPage, &VScanInProgressPage::sigScanCancelled, resultsPage, &VResultsPage::onScanComplete);
    connect(sipPage, &VScanInProgressPage::sigViewResultsClicked, resultsPage, &VResultsPage::onViewResultsClicked);

    connect(scanPage, &VScanPage::sigScanStarted, m_navigator, &VNavigator::onScanStarted);
    connect(sipPage, &VScanInProgressPage::sigScanFinished, m_navigator, &VNavigator::onScanFinished);
    connect(sipPage, &VScanInProgressPage::sigScanPaused, m_navigator, &VNavigator::onScanPaused);
    connect(sipPage, &VScanInProgressPage::sigScanResumed, m_navigator, &VNavigator::onScanResumed);
    connect(sipPage, &VScanInProgressPage::sigScanCancelled, m_navigator, &VNavigator::onScanCancelled);
    connect(sipPage, &VScanInProgressPage::sigViewResultsClicked, m_navigator, &VNavigator::onViewResultsClicked);

}

//Hide and show different pages based on tabs clicked in the navigator
void VMainWindow::onPageChanged(QWidget *page)
{
    if(!m_currentlyDisplayedPage)
    {
        page->show();
    }
    else
    {
        m_currentlyDisplayedPage->hide();
        page->show();
    }

    m_currentlyDisplayedPage = page;
}
