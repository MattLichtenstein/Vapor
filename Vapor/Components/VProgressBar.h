#ifndef VPROGRESSBAR_H
#define VPROGRESSBAR_H

#include <QProgressBar>

class VProgressBar : public QProgressBar
{
public:
    VProgressBar(QWidget* parent = nullptr);

private:
    void setupContent();
    void applyStyleSheet();

};

#endif // VPROGRESSBAR_H
