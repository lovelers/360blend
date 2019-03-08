#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "polyfit.h"

namespace Ui {
class MainWindow;
}
typedef struct sin_to_2order_curve_coff
{
    double a;
    double b;
    double c;
    double hratio;
} sin_to_2order_curve_coff_t;
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
    Polyfit*        mpPolyfitDialog;

    QImage          DoImagePloyFit(QImage image, sin_to_2order_curve_coff_t * coff);

private slots:
    void on_ProcessBtn_clicked();
    void on_RightBtn_clicked();
    void on_FrontBtn_clicked();
    void on_BackBtn_clicked();
    void on_LeftBtn_clicked();
    void on_actionPolyFit_triggered();
};

#endif // MAINWINDOW_H
