#include "polyfit.h"
#include "ui_polyfit.h"
#include <QDebug>
#include <QPushButton>
Polyfit::Polyfit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Polyfit)
{


    ui->setupUi(this);
    this->setWindowTitle(tr("Polyfit"));
    ui->buttonBox->addButton(tr("Open"),static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Open));
    ui->buttonBox->addButton(tr("Save"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Save));
    ui->buttonBox->addButton(tr("Process"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Process));
    ui->buttonBox->addButton(tr("Reset"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Reset));
    ui->buttonBox->addButton(tr("Exit"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Exit));
}

Polyfit::~Polyfit()
{
    delete ui;
}


void Polyfit::on_buttonBox_clicked(QAbstractButton *button)
{
    PlotfitRole role = static_cast<PlotfitRole>(ui->buttonBox->buttonRole(button));
    switch (role)
    {
        case Polyfit_Open:
            break;
        case Polyfit_Save:
            break;
        case Polyfit_Reset:
            break;
        case Polyfit_Process:
            break;
        case Polyfit_Exit:
            this->close();
            break;
        default:
            break;
    }
    qDebug() << "role = " << role << endl;
}
