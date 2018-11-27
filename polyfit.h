#ifndef POLYFIT_H
#define POLYFIT_H

#include <QDialog>
#include <QAbstractButton>
#include "polyfitalgo.h"

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
    Ui::Polyfit     *ui;
    polyfitdata_t   mProcessData[BLEND_END];
    polyfitdata_t   mSaveData[BLEND_END];
};

#endif // POLYFIT_H
