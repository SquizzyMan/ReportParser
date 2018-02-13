#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QTextEdit>
#include <QWebElementCollection>
#include <QWebElement>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//=============== Define variables ====================

QString inputFileName;
QFile inputFile(inputFileName);
QFile outputFile("out.txt");
QFile outputFileHtml("outhtml.txt");

//=====================================================
//=============== Open file dialog ====================
//=====================================================

void MainWindow::on_openButton_clicked()
{
    inputFileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Open File"),
                    "C://",
                    "HTML File (*.html) ;; Text File (*.txt)"

                    );
    ui->lineEdit->setText(inputFileName);

    QFile inputFile(inputFileName);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,
                                    "Ошибка файла",
                                    "Не удалось открыть файл",
                                    QMessageBox::Ok);
    }

    QTextStream inputText (&inputFile);
    ui->textBrowser->setText(inputText.readAll());


    outputFileHtml.open(QIODevice::WriteOnly);
    //QTextStream outText (&outputFileHtml);
    outputFileHtml.write(ui->textBrowser->toPlainText().toUtf8());
}

//=====================================================
//================== Generator ========================
//=====================================================

void MainWindow::on_genegateButton_clicked()
{



}

//=====================================================
//=============== Save file ===========================
//=====================================================

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
            tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

            if (fileName != "")
            {
                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    // error message
                }
                else
                {
                    file.write(ui->textEdit->toPlainText().toUtf8());
                    file.close();
                }
            }
}

//=====================================================
//==================== Exit program ===================
//=====================================================

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}
