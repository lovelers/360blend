#include "polyfit.h"
#include "polyfitlabel.h"
#include "ui_polyfit.h"
#include <QDebug>
#include <QPushButton>
#include "layoutpersist.h"
Polyfit::Polyfit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Polyfit)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Polyfit"));
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->buttonBox->addButton(tr("Open"),static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Open));
    ui->buttonBox->addButton(tr("Save"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Save));
    ui->buttonBox->addButton(tr("Process"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Process));
    ui->buttonBox->addButton(tr("Reset"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Reset));
    ui->buttonBox->addButton(tr("Exit"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Exit));

    mpTableModelFront = new PolyfitTableModel();
    Q_ASSERT(nullptr != mpTableModelFront);
    ui->tableViewFront->setModel(mpTableModelFront);

    mpTableModelBack = new PolyfitTableModel();
    Q_ASSERT(nullptr != mpTableModelBack);
    ui->tableViewBack->setModel(mpTableModelBack);

    mpTableModelLeft = new PolyfitTableModel();
    Q_ASSERT(nullptr != mpTableModelLeft);
    ui->tableViewLeft->setModel(mpTableModelLeft);

    mpTableModelRight = new PolyfitTableModel();
    Q_ASSERT(nullptr != mpTableModelRight);
    ui->tableViewRight->setModel(mpTableModelRight);
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
            onPolyfitProces();
            break;
        case Polyfit_Exit:
            this->close();
            break;
        default:
            break;
    }
    qDebug() << "role = " << role << endl;
}

void Polyfit::myShow()
{

    this->hide();
    const int polyfitWidth      = LayoutPersist::getInstance()->getPolyfitLayoutWidth();
    const int polyfitHeight     = LayoutPersist::getInstance()->getPolyfitLayoutHeight();
    qDebug("polyfit %d:%d", polyfitWidth, polyfitHeight);

    this->resize(polyfitWidth, polyfitHeight);

    const int polyfitTableRow   = PolyfitTableModel::getMaxPolyFitRow();
    const int polyfitTableCol   = PolyfitTableModel::getMaxPolyFitCol();

    int tableViewWidth          = static_cast<int>(polyfitWidth * 0.95);
    int tableViewHeight         = static_cast<int>(polyfitHeight * 0.4);

    int columnWidth             = tableViewWidth / (polyfitTableCol+1);
    int rowHeight               = tableViewHeight / (polyfitTableRow+1);

    ui->tableViewFront->setGeometry((polyfitWidth - tableViewWidth)/2 , polyfitHeight - tableViewHeight * 1.2f, tableViewWidth, tableViewHeight);
    for (int i = 0; i < polyfitTableRow; i++)
    {
        ui->tableViewFront->setRowHeight(i, rowHeight);
    }
    for (int i = 0; i < polyfitTableCol; i++)
    {
        ui->tableViewFront->setColumnWidth(i, columnWidth);
    }

    this->updateGeometry();
    this->show();
}

void Polyfit::onPolyfitProcess()
{
    if (nullptr != mpTableModelFront)
    {
        float *data = nullptr;
        int size    = 0;
        mpTableModelFront->getPolyFitData(&data, &size);

        if (nullptr == data || size < 0)
        {
            qDebug("invalid data: %p, size: %d", data, size);
        }
        ui->labelFront->updateData(data, size);

    }
}
