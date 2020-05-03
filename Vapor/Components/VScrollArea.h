#ifndef VSCROLLAREA_H
#define VSCROLLAREA_H

#include <QScrollArea>
#include <QScrollBar>

class VScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    VScrollArea(QWidget* parent = nullptr);

private:
    void applyStyleSheet();
};

#endif // VSCROLLAREA_H
