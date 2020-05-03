#ifndef VNAVIGATOR_H
#define VNAVIGATOR_H

#include <QWidget>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QMap>

#include "Utilities/VSizes.h"
#include <Utilities/VColors.h>

//Forward declaration
class VNavButton;

class VNavigator : public QWidget
{
    Q_OBJECT
public:
    explicit VNavigator(QWidget *parent = nullptr);
    void addNavItem(QWidget* page, QString name);
    void addTempNavItem(QWidget* page, QString name);
    void showTempNavItem();

private:
    void setupContent();
    void applyStyleSheet();

    QList<VNavButton*> m_navBtnList;
    QMap<VNavButton*, QWidget*> m_pageMap;
    QHBoxLayout* m_layout = new QHBoxLayout();

signals:
    void sigPageChanged(QWidget* page);

public slots:
    void onScanStarted();
    void onScanFinished();
    void onScanPaused();
    void onScanResumed();
    void onScanCancelled();
    void onViewResultsClicked();

private slots:
    void navBtnClicked();


};



enum class RadioButtonTheme{
    Unchecked,
    Checked
};

class VNavButton : public QRadioButton
{
    Q_OBJECT
public:
    explicit VNavButton(QString text = "", QWidget* parent = nullptr);
    void setTheme(RadioButtonTheme theme);


private:
    void applyStyleSheet();

    bool m_isChecked = false;

    QString m_textColor;
    bool m_underline = false;

};

#endif // VNAVIGATOR_H
