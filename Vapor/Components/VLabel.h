#ifndef VLABEL_H
#define VLABEL_H

#include <QLabel>

enum class LabelTextSize{
    Small,
    Medium,
    Large
};

class VLabel : public QLabel
{
    Q_OBJECT
public:
    VLabel(QString text = "", LabelTextSize size = LabelTextSize::Large, QWidget* parent = nullptr);
    void setTextSize(LabelTextSize size);
    void setTextColor(QString color);

private:
    void applyStyleSheet();

    QString m_fontSize;
    QString m_fontColor;
};

#endif // VLABEL_H
