#ifndef VMAINWINDOW_H
#define VMAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include <Components/VNavigator.h>

class VMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    VMainWindow(QWidget *parent = nullptr);
    ~VMainWindow() {}

protected:
    void resizeEvent(QResizeEvent *e);

private:
    void setupWindow();
    void setupWindowContent();

    VNavigator* m_navigator = nullptr;
    QVBoxLayout* m_windowLayout = nullptr;

    QWidget* m_currentlyDisplayedPage = nullptr;


private slots:
    void onPageChanged(QWidget* page);
};
#endif // VMAINWINDOW_H
