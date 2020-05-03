#ifndef VPATHS_H
#define VPATHS_H

#include <QDir>
#include <QString>

//Paths that I refer to throughout the application
namespace VPaths {
    static const QString ApplicationPath = QDir::currentPath().split("Vapor/")[0];
    static const QString AssetPath = ApplicationPath + "Assets/";
    static const QString TestFilesPath = ApplicationPath + "Test Files/";

}

#endif // VPATHS_H
