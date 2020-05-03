#ifndef VICONS_H
#define VICONS_H

#include <QString>

#include <Utilities/VPaths.h>

//Icons that I refer to throughout the application
namespace VIcons {

    static const QString DesktopIcon = VPaths::AssetPath + "logodesktopicon.png";
    static const QString BackgroundPath = VPaths::AssetPath + "background.png";
    static const QString LogoPath = VPaths::AssetPath + "logo.png";
    static const QString DropDownArrow = VPaths::AssetPath + "dropdownarrow.png";
    static const QString DropDownArrowDisabled = VPaths::AssetPath + "dropdownarrow-disabled.png";
}

#endif // VICONS_H
