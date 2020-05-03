#include "VScrollArea.h"

//Extends QScrollArea
VScrollArea::VScrollArea(QWidget* parent) : QScrollArea(parent)
{
    applyStyleSheet();
}

void VScrollArea::applyStyleSheet()
{
    setStyleSheet("QScrollArea {"
                      "background: transparent;"
                  "}"
              );
}
