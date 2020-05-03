#include "VDropdown.h"

#include <Utilities/VIcons.h>

VDropdown::VDropdown(QWidget* parent) : QComboBox(parent)
{
    setupContent();
}

//Sets up dropdown size and style
void VDropdown::setupContent()
{
    setMaximumWidth(VSizes::DropDownMaxWidth.toInt());
    applyStyleSheet();
}

void VDropdown::applyStyleSheet()
{
        setStyleSheet("QComboBox {"
                        "border-color:" + VColors::Accent + ";"
                        "border-width: " + VSizes::ButtonBorderWidth + "px;"
                        "border-style: solid;"
                        "border-radius: " + VSizes::ButtonBorderRadius + ";"
                        "padding: " + VSizes::ButtonHeightPadding + "px " + VSizes::ButtonWidthPadding + "px;"
                        "selection-color: " + VColors::LightGrey + ";"
                    "}"
                    "QComboBox:hover {"
                        "background-color: " + VColors::LightGrey + ";"
                    "}"
                    "QComboBox::drop-down {"
                        "border: 0px;"
                        "width: 30px;"
                    "}"
                    "QComboBox::down-arrow {"
                        "image: url(" + VIcons::DropDownArrow + ");"
                    "}"
                    "QComboBox:!editable {"
                        "color: " + VColors::Accent + ";"
                        "font-size:" + VSizes::SmallFont + "px;"
                    "}"
                    "QComboBox::item {"
                        "border-color: " + VColors::Accent + ";"
                        "border-width: 1px;"
                        "border-style: solid;"
                        "border-radius: " + VSizes::ButtonBorderRadius + ";"
                        "height: 50px;"
                    "}"
                    "QComboBox:disabled {"
                        "background-color: " + VColors::Grey + ";"
                        "color: " + VColors::LightGrey + ";"
                        "border-color: " + VColors::LightGrey + ";"
                    "}"
                    "QComboBox::down-arrow:disabled {"
                        "image: url(" + VIcons::DropDownArrowDisabled + ");"
                    "}"
              );
}
