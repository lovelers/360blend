#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QImage>
#include <QDesktopWidget>
#include "layoutpersist.h"


static sin_to_2order_curve_coff_t gFrontCoff    = {-1.232291, 1.232291, -0.014249, 1.3};
static sin_to_2order_curve_coff_t gBackCoff     = {-1.232291,  1.232291, -0.014249, 1.3};
static sin_to_2order_curve_coff_t gLeftCoff     = {-0.8215275,   0.8215275,  -0.0094991, 1.2};
static sin_to_2order_curve_coff_t gRightCoff    = {-0.8215275,   0.8215275,  -0.0094991, 1.2};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int width   = QApplication::desktop()->screenGeometry(this).width();
    int height  = QApplication::desktop()->screenGeometry(this).height();
    LayoutPersist::getInstance()->setScreenSize(width, height);

    mFrontImagePath.clear();
    mBackImagePath.clear();
    mLeftImagePath.clear();
    mRightImagePath.clear();
    mpPolyfitDialog = new Polyfit();

    ui->setupUi(this);
    QWidget::showMaximized();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ProcessBtn_clicked()
{
    // front image.
    QImage imageF(mFrontImagePath);
    if (imageF.isNull())
    {
        qDebug() <<" bad front image input" <<endl;
        return;
    }
    QImage imageFPolyfit = DoImagePloyFit(imageF, &gFrontCoff);
    imageFPolyfit.save("FrongPolyfit.jpg");
    ui->labelFront->setPixmap(QPixmap::fromImage(imageFPolyfit));
    QImage imageB(mBackImagePath);
    if (imageB.isNull())
    {
        qDebug() <<" bad back image input" << endl;
        return;
    }

    QImage imageBPolyfit = DoImagePloyFit(imageF, &gBackCoff);
    imageBPolyfit.save("BackPolyfit.jpg");
    ui->labelBack->setPixmap(QPixmap::fromImage(imageBPolyfit));

    QImage imageL(mLeftImagePath);
    if (imageL.isNull())
    {
        qDebug() << "bad left image input " << endl;
        return;
    }
    QImage imageLPolyfit = DoImagePloyFit(imageL, &gLeftCoff);
    imageLPolyfit.save("LeftPolyfit.jpg");
    ui->labelLeft->setPixmap(QPixmap::fromImage(imageLPolyfit));

    QImage imageR(mRightImagePath);
    if (imageR.isNull())
    {
        qDebug() <<"bad right image input " <<endl;
        return;
    }
    QImage imageRPolyfit = DoImagePloyFit(imageR, &gRightCoff);
    imageRPolyfit.save("RightPolyfit.jpg");
    ui->labelRight->setPixmap(QPixmap::fromImage(imageRPolyfit));

    // front image need do the projection.
}


void MainWindow::on_FrontBtn_clicked()
{
    mFrontImagePath = QFileDialog::getOpenFileName(this, tr("open log"), tr(""), tr("image file (*)"));
    if (mFrontImagePath.isEmpty()) {
       qDebug() << "file is empty()" << endl;
       return;
    }
    ui->FrontEdit->setText(mFrontImagePath);
}

void MainWindow::on_BackBtn_clicked()
{
    mBackImagePath = QFileDialog::getOpenFileName(this, tr("open log"), tr(""), tr("image file (*)"));
    if (mBackImagePath.isEmpty()) {
       qDebug() << "file is empty()" << endl;
       return;
    }
    ui->BackEdit->setText(mBackImagePath);
}

void MainWindow::on_LeftBtn_clicked()
{
    mLeftImagePath = QFileDialog::getOpenFileName(this, tr("open log"), tr(""), tr("image file (*)"));
    if (mLeftImagePath.isEmpty()) {
       qDebug() << "file is empty()" << endl;
       return;
    }
    ui->LeftEdit->setText(mLeftImagePath);
}

void MainWindow::on_RightBtn_clicked()
{
    mRightImagePath = QFileDialog::getOpenFileName(this, tr("open log"), tr(""), tr("image file (*)"));
    if (mLeftImagePath.isEmpty()) {
       qDebug() << "file is empty()" << endl;
       return;
    }
    ui->RightEdit->setText(mRightImagePath);
}

void MainWindow::on_actionPolyFit_triggered()
{
    if (nullptr != mpPolyfitDialog)
    {
        mpPolyfitDialog->myShow();
    }

}

QImage MainWindow::DoImagePloyFit(QImage image, sin_to_2order_curve_coff_t * coff)
{
    int width   = image.width();
    int height  = image.height();
    int height1 = static_cast<int>(coff->hratio * height);
    qDebug("a = %llf b = %llf c = %llf hratio = %llf",
           coff->a, coff->b, coff->c, coff->hratio);
    qDebug("original image size: %d x %d", width, height);
    qDebug("new image size: %d x %d", width, height1);
    QImage newImage(width, height1, QImage::Format_RGB888);
    for (int w = 0; w < width; ++w)
    {
        double x    = w / static_cast<double>(width);
        double y    = coff->a * x * x + coff->b * x + coff->c;

        int hbase   = static_cast<int>((coff->hratio - y - 1) * height);
        if (w > 500 && w < 600) qDebug("x = %lf, y = %lf, hBase = %d", x, y, hbase);
        if (hbase < 0) hbase = 0;

        for (int h = 0 ; h < height; ++h)
        {
            newImage.setPixel(w, h+hbase, image.pixel(w, h));
        }
    }
    return newImage;
}
