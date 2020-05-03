#ifndef VSIZES_H
#define VSIZES_H

#include <QString>

//Sizes that I refer to throughout the application so I don't have to use "magic numbers"
namespace VSizes {

    static const QString ButtonBorderRadius = "6";
    static const QString ButtonBorderWidth = "2";
    static const QString ButtonBorderWidthNone = "0";
    static const QString ButtonMinimumWidth = "250";
    static const QString ButtonHeightPadding = "15";
    static const QString ButtonWidthPadding = "22";

    static const QString ProgressBarPadding = "3";
    static const QString ProgressBarHeight = "100";

    static const QString SmallFont = "16";
    static const QString MediumFont = "24";
    static const QString LargeFont = "32";

    static const QString FixedLabelWidth = "120";
    static const QString FixedLabelMargin = "100";

    static const QString DropDownMaxWidth = "200";

    static const QString SmallSeparatorWidth = "150";

    static const QString TitleBarHeight = "100";

    static const QString MainWindowSpacing = "20";

    static const QString ControlsSpacing = "60"; //Space between two control buttons (i.e. 2 buttons)

    static const QString HelperTextSpacing = "5"; //Space between a widget and it's helper text

    static const QString SIPControlsSpacing = "200";

}

#endif // VSIZES_H
