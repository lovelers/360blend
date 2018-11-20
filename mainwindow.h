#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "polyfit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString         mFrontImagePath;
    QString         mBackImagePath;
    QString         mLeftImagePath;
    QString         mRightImagePath;
    Polyfit*        mPPolyfitDialog;

private slots:
    void on_ProcessBtn_clicked();
    void on_RightBtn_clicked();
    void on_FrontBtn_clicked();
    void on_BackBtn_clicked();
    void on_LeftBtn_clicked();
    void on_actionPolyFit_triggered();
};

#endif // MAINWINDOW_H
