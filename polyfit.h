#ifndef POLYFIT_H
#define POLYFIT_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class Polyfit;
}

class Polyfit : public QDialog
{
    Q_OBJECT

public:
    explicit Polyfit(QWidget *parent = nullptr);
    ~Polyfit();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Polyfit *ui;
};

#endif // POLYFIT_H
