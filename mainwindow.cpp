#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mFrontImagePath.clear();
    mBackImagePath.clear();
    mLeftImagePath.clear();
    mRightImagePath.clear();
    mPPolyfitDialog = new Polyfit();
    ui->setupUi(this);
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
    ui->labelFront->setPixmap(QPixmap::fromImage(imageF));
    QImage imageB(mBackImagePath);
    if (imageB.isNull())
    {
        qDebug() <<" bad back image input" << endl;
        return;
    }
    ui->labelBack->setPixmap(QPixmap::fromImage(imageB));

    QImage imageL(mLeftImagePath);
    if (imageL.isNull())
    {
        qDebug() << "bad left image input " << endl;
        return;
    }
    ui->labelLeft->setPixmap(QPixmap::fromImage(imageL));

    QImage imageR(mRightImagePath);
    if (imageR.isNull())
    {
        qDebug() <<"bad right image input " <<endl;
        return;
    }
    ui->labelRight->setPixmap(QPixmap::fromImage(imageR));

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
    if (nullptr != mPPolyfitDialog)
    {
        mPPolyfitDialog->show();
    }
}
