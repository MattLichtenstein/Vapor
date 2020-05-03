#include "VLabel.h"

#include <Utilities/VSizes.h>
#include <Utilities/VColors.h>

VLabel::VLabel(QString text, LabelTextSize size, QWidget* parent) : QLabel(parent)
{
    setText(text);
    setTextSize(size);
    setTextColor(VColors::AlmostWhite);
}

void VLabel::setTextSize(LabelTextSize size)
{
    switch(size)
    {
        case LabelTextSize::Small:
            m_fontSize = VSizes::SmallFont;
            break;
        case LabelTextSize::Medium:
            m_fontSize = VSizes::MediumFont;
            break;
        case LabelTextSize::Large:
            m_fontSize = VSizes::LargeFont;
            break;
        default:
            break;
    }

    applyStyleSheet();
}

void VLabel::setTextColor(QString color)
{
    m_fontColor = color;
    applyStyleSheet();
}

void VLabel::applyStyleSheet()
{
    setStyleSheet("QLabel { "
                  "font-size: " + m_fontSize + "px;"
                  "color: " + m_fontColor + ";"
                  "}"
                  );
}
