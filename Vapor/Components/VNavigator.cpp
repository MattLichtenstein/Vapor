#include "VNavigator.h"

VNavigator::VNavigator(QWidget *parent) : QWidget(parent)
{
    setupContent();
}

void VNavigator::addNavItem(QWidget* page, QString name)
{
    VNavButton* btn = new VNavButton(name);
    m_layout->insertWidget(m_layout->count() - 1, btn);
    m_navBtnList.append(btn);
    m_pageMap[btn] = page;
    btn->setTheme(RadioButtonTheme::Unchecked);
    connect(btn, &VNavButton::clicked, this, &VNavigator::navBtnClicked);

    //Set first button checked
    if(m_navBtnList.count() == 1)
    {
        btn->click();
    }

}

void VNavigator::addTempNavItem(QWidget *page, QString name)
{
    VNavButton* btn = new VNavButton(name);
    btn->hide();
    m_layout->insertWidget(m_layout->count(), btn);
    m_navBtnList.append(btn);
    m_pageMap[btn] = page;
    btn->setTheme(RadioButtonTheme::Unchecked);
    connect(btn, &VNavButton::clicked, this, &VNavigator::navBtnClicked);
}

//sets up navigation content
void VNavigator::setupContent()
{
    m_layout->setSpacing(VSizes::ControlsSpacing.toInt());
    m_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));

    setFixedHeight(100);
    setLayout(m_layout);
}

//styles the navigator buttons when they are checked/unchecked
void VNavigator::navBtnClicked()
{
    for(VNavButton* btn : m_navBtnList)
    {
        if(btn == QObject::sender())
        {
            btn->setTheme(RadioButtonTheme::Checked);
            emit sigPageChanged(m_pageMap[btn]);
        }
        else
        {
            btn->setTheme(RadioButtonTheme::Unchecked);
        }
    }
}

void VNavigator::onScanStarted()
{
    VNavButton* temp = m_navBtnList[m_navBtnList.count() - 1];
    temp->setText("Scan in Progress...");
    temp->show();
    temp->click();
    m_pageMap[temp]->show();
}

void VNavigator::onScanFinished()
{
    m_navBtnList[m_navBtnList.count() - 1]->setText("Scan Complete");
}

void VNavigator::onScanPaused()
{
    m_navBtnList[m_navBtnList.count() - 1]->setText("Scan Paused");
}

void VNavigator::onScanResumed()
{
    m_navBtnList[m_navBtnList.count() - 1]->setText("Scan in Progress...");
}

void VNavigator::onScanCancelled()
{
    m_navBtnList[m_navBtnList.count() - 1]->setText("Scan Cancelled");
}

void VNavigator::onViewResultsClicked()
{
    m_navBtnList[1]->click();

}


//VNavButton Class
//Extends QRadioButton to get the functionality that only one button can be checked at at ime
VNavButton::VNavButton(QString text, QWidget *parent) : QRadioButton(parent)
{
    setText(text);
    setTheme(RadioButtonTheme::Unchecked);
}

void VNavButton::setTheme(RadioButtonTheme theme)
{
    switch(theme)
    {
    case RadioButtonTheme::Unchecked:
        m_isChecked = false;
        m_textColor = VColors::AlmostWhite;
        m_underline = false;
        break;
    case RadioButtonTheme::Checked:
        m_isChecked = true;
        m_textColor = VColors::Accent;
        m_underline = true;
        break;
    default:
        break;
    }
    applyStyleSheet();
}

void VNavButton::applyStyleSheet()
{
    setStyleSheet("QRadioButton {"
                    "color: " + m_textColor + ";"
                    "font: bold;"
                    "text-decoration: " + (m_underline ? "underline" : "none") + ";"
                    "font-size: " + VSizes::LargeFont + "px;"
                  "}"
                  "QRadioButton:indicator {"
                    "width: 0px;"
                    "height: 0px;"
                  "}"
                  "QRadioButton:hover {"
                  "color: " + VColors::LightGrey + ";"
                  ""
                  "}"
                  "QRadioButton:pressed {"
                  "color: " + VColors::Grey + ";"
                  ""
                  "}"
                  );


}
