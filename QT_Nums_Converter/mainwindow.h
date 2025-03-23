#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QClipboard>
#include <QErrorMessage>
#include <QMessageBox>
#include "appcontext.h"
#include "logic.h"
#include "entrypoint.h"
#include <string.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMessageBox msgBox;

    AppContext context;

    void onCalculateClicked();
    void onClearClicked();
    void onSwapClicked();
    void updateFields(Params* params);
    void updateValue();
    void displayEmptyInputError();
    void onCopyClicked();
    void parseNumSystems();
    void parseNumber(Params* params);
    void displayIncorrectInputError();
    void displayOverflowError();
    void displayEmptyStartError();
    void displayEmptyEndError();
    void displayMaxValueError();
    void parseInputText(Params* params);
    void errorSwitchDisplay();
};
#endif // MAINWINDOW_H
