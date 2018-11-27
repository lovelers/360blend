#include "polyfit.h"
#include "ui_polyfit.h"
#include <QDebug>
Polyfit::Polyfit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Polyfit)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Polyfit"));
}

Polyfit::~Polyfit()
{
    delete ui;
}


void Polyfit::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::ButtonRole role = ui->buttonBox->buttonRole(button);
    switch (role)
    {
        case QDialogButtonBox::ApplyRole:

            break;
        case QDialogButtonBox::ResetRole:
            break;
        case QDialogButtonBox::YesRole:
            this->close();
            break;
        default:
            break;
    }
    qDebug() << "role = " << role << endl;
}
