#include "VWindowTitleBar.h"

#include <QLabel>

#include <Utilities/VIcons.h>
#include <Utilities/VSizes.h>

VWindowTitleBar::VWindowTitleBar(QWidget *parent) : QWidget(parent)
{
    setupContent();
}

//Adds widgets to the far right of the title bar
void VWindowTitleBar::addWidget(QWidget* widget)
{
    m_layout->addWidget(widget);
}

//Sets up the content on the window title bar
void VWindowTitleBar::setupContent()
{
    QLabel* logoLabel = new QLabel();
    QPixmap logo(VIcons::LogoPath);
    logoLabel->setPixmap(logo);

    m_layout = new QHBoxLayout();
    m_layout->addWidget(logoLabel);
    m_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));

    setFixedHeight(VSizes::TitleBarHeight.toInt());
    setLayout(m_layout);
}
