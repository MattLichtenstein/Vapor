#ifndef VDROPDOWN_H
#define VDROPDOWN_H

#include<QComboBox>

#include <Utilities/VColors.h>
#include <Utilities/VSizes.h>

class VDropdown : public QComboBox
{
    Q_OBJECT
public:
    VDropdown(QWidget* parent = nullptr);

private:
    void setupContent();
    void applyStyleSheet();
};

#endif // VDROPDOWN_H
