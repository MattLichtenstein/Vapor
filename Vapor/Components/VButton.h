#ifndef VBUTTON_H
#define VBUTTON_H

#include <QPushButton>

#include "Utilities/VSizes.h"
#include "Utilities/VColors.h"

enum class ButtonTheme{
    AccentText,
    AccentBackground
};

class VButton : public QPushButton
{
    Q_OBJECT
public:
    VButton(QString text = "", ButtonTheme theme = ButtonTheme::AccentText, QWidget *parent = nullptr);
    void setHoverText(QString text);
    void setTheme(ButtonTheme theme);

protected:
    virtual void enterEvent(QEvent* e);
    virtual void leaveEvent(QEvent* e);

private:
    void applyStyleSheet();

    QString m_text = "";
    QString m_hoverText = "";
    QString m_borderWidth;
    QString m_textColor;
    QString m_backgroundColor;

};

#endif // VBUTTON_H
