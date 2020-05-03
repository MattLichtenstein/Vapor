#include "VButton.h"

VButton::VButton(QString text, ButtonTheme theme, QWidget* parent)
    : QPushButton(parent)
{
    m_text = text;
    setText(text);
    setTheme(theme);
    setMinimumWidth(VSizes::ButtonMinimumWidth.toInt());

}

void VButton::setHoverText(QString text)
{
    m_hoverText = text;
}

void VButton::setTheme(ButtonTheme theme)
{

    switch(theme)
    {
        case ButtonTheme::AccentText:
            m_textColor = VColors::Accent;
            m_backgroundColor = VColors::AlmostBlack;
            m_borderWidth = VSizes::ButtonBorderWidth;
            break;
        case ButtonTheme::AccentBackground:
            m_textColor = VColors::AlmostBlack;
            m_backgroundColor = VColors::Accent;
            m_borderWidth = VSizes::ButtonBorderWidthNone;
            break;
        default:
            break;
    }

    applyStyleSheet();

}

//Enter event used to know when we are hovering over a button
void VButton::enterEvent(QEvent* e)
{
    Q_UNUSED(e);
    if(m_hoverText != "")
    {
        setText(m_hoverText);
    }
}

//Leave event to know when we are no longer hovering over a button
void VButton::leaveEvent(QEvent* e)
{
    Q_UNUSED(e);
    if(m_hoverText != "")
    {
        setText(m_text);
    }
}

void VButton::applyStyleSheet()
{
    setStyleSheet("QPushButton {"
                      "background-color: " + m_backgroundColor + ";"
                      "color: " + m_textColor + " ;"
                      "font-size: " + VSizes::SmallFont + "px;"
                      "border-style: solid;"
                      "border-width: " + m_borderWidth + ";"
                      "border-radius: " + VSizes::ButtonBorderRadius + "px;"
                      "padding: " + VSizes::ButtonHeightPadding + "px " + VSizes::ButtonWidthPadding + "px;"
                  "}"
                  "QPushButton:hover {"
                      "background-color: " + VColors::LightGrey + ";"
                  "}"
                  "QPushButton:pressed {"
                      "background-color: " + VColors::Grey + ";"
                  "}"
                  "QPushButton:disabled {"
                       "background-color: " + VColors::Grey + ";"
                       "color: " + VColors::LightGrey + ";"
                  "}"
                  );

}
