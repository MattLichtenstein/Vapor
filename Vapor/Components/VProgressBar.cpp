#include "VProgressBar.h"

#include <Utilities/VColors.h>
#include <Utilities/VSizes.h>

//Extends QProgressBar
VProgressBar::VProgressBar(QWidget* parent) : QProgressBar(parent)
{
    setupContent();
}

//Sets up progress bar layout
void VProgressBar::setupContent()
{
    setFixedHeight(VSizes::ProgressBarHeight.toInt());
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    applyStyleSheet();
}

void VProgressBar::applyStyleSheet()
{
    setStyleSheet("QProgressBar::chunk {"
                      "background-color: " + VColors::Accent + ";"
                      "border-radius: " + VSizes::ButtonBorderRadius + ";"
                  "}"
                  "QProgressBar {"
                      "background-color: " + VColors::AlmostBlack + ";"
                      "border-width: " + VSizes::ButtonBorderWidth + ";"
                      "border-style: solid;"
                      "border-color: " + VColors::Accent + ";"
                      "border-radius: " + VSizes::ButtonBorderRadius + ";"
                      "text-align: center;"
                      "font-size: " + VSizes::MediumFont + "px;"
                      "padding: " + VSizes::ProgressBarPadding + "px " + VSizes::ProgressBarPadding + "px;"
                  "}"
                );
}
