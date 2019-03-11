#include "polyfit.h"
#include "polyfitlabel.h"
#include "ui_polyfit.h"
#include <QDebug>
#include <QPushButton>
#include "blendcommon.h"
#include "layoutpersist.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
Polyfit::Polyfit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Polyfit)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Polyfit"));
    this->setWindowFlags(Qt::Popup);

    ui->buttonBox->addButton(tr("Open"),static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Open));
    ui->buttonBox->addButton(tr("Save"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Save));
    ui->buttonBox->addButton(tr("Process"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Process));
    ui->buttonBox->addButton(tr("Reset"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Reset));
    ui->buttonBox->addButton(tr("Exit"), static_cast<QDialogButtonBox::ButtonRole>(Polyfit_Exit));

    mpTableModelFront = new PolyfitTableModel();
    Q_ASSERT(nullptr != mpTableModelFront);
    ui->tableViewFront->setModel(mpTableModelFront);
    ui->tableViewFront->horizontalHeader()->setVisible(false);

    mpTableModelBack = new PolyfitTableModel();
    Q_ASSERT(nullptr != mpTableModelBack);
    ui->tableViewBack->setModel(mpTableModelBack);
    ui->tableViewBack->horizontalHeader()->setVisible(false);

    mpTableModelLeft = new PolyfitTableModel();
    Q_ASSERT(nullptr != mpTableModelLeft);
    ui->tableViewLeft->setModel(mpTableModelLeft);
    ui->tableViewLeft->horizontalHeader()->setVisible(false);

    mpTableModelRight = new PolyfitTableModel();
    Q_ASSERT(nullptr != mpTableModelRight);
    ui->tableViewRight->setModel(mpTableModelRight);
    ui->tableViewRight->horizontalHeader()->setVisible(false);

    // -----
    const int polyfitWidth      = LayoutPersist::getInstance()->getPolyfitLayoutWidth();
    const int polyfitHeight     = LayoutPersist::getInstance()->getPolyfitLayoutHeight();
    qDebug("polyfit %d:%d", polyfitWidth, polyfitHeight);

    this->resize(polyfitWidth, polyfitHeight);
    this->updateGeometry();

    QRect tabRect   = ui->tabWidget->geometry();
    QRect labelRect = ui->labelFront->geometry();
    labelRect.setHeight(tabRect.height() / 2);

    ui->labelFront->setGeometry(labelRect);
    ui->labelBack->setGeometry(labelRect);
    ui->labelLeft->setGeometry(labelRect);
    ui->labelRight->setGeometry(labelRect);
#if 0
    ui->labelFront->resize(labelRect.width(), labelRect.height());
    ui->labelBack->resize(labelRect.width(), labelRect.height());
    ui->labelLeft->resize(labelRect.width(), labelRect.height());
    ui->labelRight->resize(labelRect.width(), labelRect.height());
#endif
    ui->labelFront->updateGeometry();
    ui->labelBack->updateGeometry();
    ui->labelLeft->updateGeometry();
    ui->labelRight->updateGeometry();

    QRect tableRect;
    tableRect.setTop(labelRect.top() + labelRect.height());
    tableRect.setLeft(labelRect.left());
    tableRect.setWidth(labelRect.width());
    tableRect.setHeight(labelRect.height());

    ui->tableViewFront->setGeometry(tableRect);
    ui->tableViewBack->setGeometry(tableRect);
    ui->tableViewLeft->setGeometry(tableRect);
    ui->tableViewRight->setGeometry(tableRect);
#if 0
    ui->tableViewFront->resize(tableRect.width(), tableRect.height());
    ui->tableViewBack->resize(tableRect.width(), tableRect.height());
    ui->tableViewLeft->resize(tableRect.width(), tableRect.height());
    ui->tableViewRight->resize(tableRect.width(), tableRect.height());
#endif
    const int polyfitTableRow   = PolyfitTableModel::getMaxPolyFitRow();
    const int polyfitTableCol   = PolyfitTableModel::getMaxPolyFitCol();

    int columnWidth             = tableRect.width() / (polyfitTableCol +1);
    int rowHeight               = tableRect.height() / (polyfitTableRow+1);
    qDebug("row: %d, col: %d", rowHeight, columnWidth);

    for (int i = 0; i < polyfitTableRow; i++)
    {
        ui->tableViewFront->setRowHeight(i, rowHeight);
        ui->tableViewBack->setRowHeight(i, rowHeight);
        ui->tableViewLeft->setRowHeight(i, rowHeight);
        ui->tableViewRight->setRowHeight(i, rowHeight);
    }
    for (int i = 0; i < polyfitTableCol; i++)
    {
        ui->tableViewFront->setColumnWidth(i, columnWidth);
        ui->tableViewBack->setColumnWidth(i, columnWidth);
        ui->tableViewLeft->setColumnWidth(i, columnWidth);
        ui->tableViewRight->setColumnWidth(i, columnWidth);
    }

    ui->tableViewFront->updateGeometry();
    ui->tableViewBack->updateGeometry();
    ui->tableViewLeft->updateGeometry();
    ui->tableViewRight->updateGeometry();
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
            onPolyfitOpen();
            break;
        case Polyfit_Save:
            onPolyfitSave();
            break;
        case Polyfit_Reset:
            onPolyfitReset();
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
    this->show();
}

void Polyfit::onPolyfitOpen()
{

}

void Polyfit::onPolyfitReset()
{

}
void Polyfit::onPolyfitSave()
{
    qDebug("Polyfit Save");
    //QFile file(POLYFIT_PATH);
    QFile file(QString(QLatin1String(POLYFIT_PATH)));
    if (file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        QString jval        = file.readAll();
        QJsonDocument jdoc  = QJsonDocument::fromJson(jval.toUtf8());
        QJsonObject jobj    = jdoc.object();
        jobj.insert("Data", QDateTime::currentDateTime().toString());
        float *data         = nullptr;
        int size            = 0;

        mpTableModelFront->getPolyFitData(&data, &size);
        if( nullptr == data || size < 0)
        {
            qDebug("get wrong polyfit data for front");
        }
        else {
            QString polyData;
            for (int i = 0; i < size - 1; i++)
            {
                polyData.append(QString("%1").arg(data[i]));
                polyData.append(",");
            }
            polyData.append(QString("%1").arg(data[size -1]));
            jobj.insert("Front", polyData);
        }
        mpTableModelBack->getPolyFitData(&data, &size);
        if( nullptr == data || size < 0)
        {
            qDebug("get wrong polyfit data for front");
        }
        else {
            QString polyData;
            for (int i = 0; i < size - 1; i++)
            {
                polyData.append(QString("%1").arg(data[i]));
                polyData.append(",");
            }
            polyData.append(QString("%1").arg(data[size -1]));
            jobj.insert("Back", polyData);
        }

        mpTableModelLeft->getPolyFitData(&data, &size);
        if( nullptr == data || size < 0)
        {
            qDebug("get wrong polyfit data for front");
        }
        else {
            QString polyData;
            for (int i = 0; i < size - 1; i++)
            {
                polyData.append(QString("%1").arg(data[i]));
                polyData.append(",");
            }
            polyData.append(QString("%1").arg(data[size -1]));
            jobj.insert("Left", polyData);
        }

        mpTableModelRight->getPolyFitData(&data, &size);
        if( nullptr == data || size < 0)
        {
            qDebug("get wrong polyfit data for front");
        }
        else {
            QString polyData;
            for (int i = 0; i < size - 1; i++)
            {
                polyData.append(QString("%1").arg(data[i]));
                polyData.append(",");
            }
            polyData.append(QString("%1").arg(data[size -1]));
            jobj.insert("Right", polyData);
        }

        jdoc    = QJsonDocument(jobj);
        file.write(jdoc.toJson());
        file.close();
    }
    else {
        qDebug("open file %s failed", POLYFIT_PATH);
    }

}
void Polyfit::onPolyfitProces()
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
    if (nullptr != mpTableModelBack)
    {
        float *data = nullptr;
        int size    = 0;
        mpTableModelBack->getPolyFitData(&data, &size);

        if (nullptr == data || size < 0)
        {
            qDebug("invalid data: %p, size: %d", data, size);
        }
        ui->labelBack->updateData(data, size);

    }
    if (nullptr != mpTableModelLeft)
    {
        float *data = nullptr;
        int size    = 0;
        mpTableModelLeft->getPolyFitData(&data, &size);

        if (nullptr == data || size < 0)
        {
            qDebug("invalid data: %p, size: %d", data, size);
        }
        ui->labelLeft->updateData(data, size);

    }
    if (nullptr != mpTableModelRight)
    {
        float *data = nullptr;
        int size    = 0;
        mpTableModelRight->getPolyFitData(&data, &size);

        if (nullptr == data || size < 0)
        {
            qDebug("invalid data: %p, size: %d", data, size);
        }
        ui->labelRight->updateData(data, size);
    }
}
