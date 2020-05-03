#include "VMainWindow.h"

#include <QApplication>

#include <Utilities/VIcons.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(VIcons::DesktopIcon));
    VMainWindow w;
    w.show();
    return a.exec();
}
