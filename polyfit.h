#ifndef POLYFIT_H
#define POLYFIT_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QAbstractButton>
#include "polyfitalgo.h"
#include "polyfittablemodel.h"
namespace Ui {
class Polyfit;
}

class Polyfit : public QDialog
{
    Q_OBJECT

    enum PlotfitRole
    {
        Polyfit_Open    = QDialogButtonBox::ActionRole,
        Polyfit_Save    = QDialogButtonBox::AcceptRole,
        Polyfit_Reset   = QDialogButtonBox::ResetRole,
        Polyfit_Exit    = QDialogButtonBox::YesRole,
        Polyfit_Process = QDialogButtonBox::ApplyRole,
        Polyfit_Invalid = QDialogButtonBox::InvalidRole,
    };
public:
    explicit Polyfit(QWidget *parent = nullptr);
    ~Polyfit();

    void myShow();
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Polyfit         *ui;
    polyfitdata_t       mProcessData[BLEND_END];
    polyfitdata_t       mSaveData[BLEND_END];

    PolyfitTableModel   *mpTableModelFront;
    PolyfitTableModel   *mpTableModelBack;
    PolyfitTableModel   *mpTableModelLeft;
    PolyfitTableModel   *mpTableModelRight;

    void                onPolyfitProcess();
};

#endif // POLYFIT_H
