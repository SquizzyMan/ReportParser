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
QFile outputFile2("out2.txt");

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
    ui->textEdit->setText(inputText.readAll());

    outputFileHtml.open(QIODevice::ReadWrite | QIODevice::Truncate);
    QTextStream outText (&outputFileHtml);
    QString str = ui->textEdit->toPlainText().toUtf8();
    QStringList row = str.split("\n");
    for (int i=0;i<row.size();i++)
    {
        outText << row[i]+"\r\n";
    }

    inputFile.close();
    outputFileHtml.close();

}

//=====================================================
//================== Generator ========================
//=====================================================

void MainWindow::on_genegateButton_clicked()
{

    QFile outputFile("out.txt");
    QFile outputFile1("out.txt");
    QFile outputFileHtml("outhtml.txt");
    QFile outputFile2("generate.txt");
    outputFileHtml.open(QIODevice::ReadOnly | QIODevice::Truncate);
    outputFile.open(QIODevice::ReadWrite | QIODevice::Truncate);
    outputFile2.open(QIODevice::ReadWrite | QIODevice::Truncate);
    QTextStream generate(&outputFile);
    QTextStream generate2(&outputFile2);
    int j=0;

    for (int i = 0; i < outputFileHtml.size(); i++)
    {
        QString inputText = outputFileHtml.readLine();
        if (j==16)
        {
            generate << inputText;
        }
        else
        {
            j++;
        }
    }

    outputFile.close();
    outputFile1.open(QIODevice::ReadOnly | QIODevice::Truncate);

    while(!outputFile1.atEnd())
    {
        QString inputText2 = outputFile1.readLine();
        if (inputText2 != "YES\r\n")
        {
            if (inputText2 != "NO\r\n")
            {
                if (inputText2 != "\r\n" || inputText2 != " \r\n")
                {
                    QString outputText = inputText2.remove("\r\n") + "\t";
                    generate2 << outputText;
                }
                else
                {
                    return;
                }
            }
            else
            {
                inputText2 = "bot\r\n";
                generate2 << inputText2;
                /*if (inputText2 == "YES\r\n")
                {
                    inputText2 = "top\r\n";
                    generate2 << inputText2;
                }
                else
                {
                    inputText2 = "bot\r\n";
                    generate2 << inputText2;
                }*/
            }
        }
        else
        {
            inputText2 = "top\r\n";
            generate2 << inputText2;
        }

    }
    outputFile1.close();
    outputFile2.close();
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
