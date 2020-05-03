#ifndef VWINDOWTITLEBAR_H
#define VWINDOWTITLEBAR_H

#include <QWidget>
#include <QHBoxLayout>

class VWindowTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit VWindowTitleBar(QWidget *parent = nullptr);
    void addWidget(QWidget* widget);

private:
    void setupContent();

    QHBoxLayout* m_layout = nullptr;

};

#endif // VWINDOWTITLEBAR_H
