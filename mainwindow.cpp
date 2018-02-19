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
    ui->genegateButton->setEnabled(true);
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
    QFile outputFile3("generate.txt");
    QFile outputFile4("generate.txt");
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
                if (inputText2 != "\r\n")
                {
                    QString outputText = inputText2.remove("\r\n") + " \t";
                    generate2 << outputText;
                }
                else
                {
                    break;
                }
            }
            else
            {
                inputText2 = "bot\r\n";
                generate2 << inputText2;
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

    outputFile3.open(QIODevice::ReadOnly);
    // Create title
    QString Str = "Filename: \n\nPosition of PCB: \nLeft under edge: X=0 / Y=0 \n\nname\tX-axis\tY-axis\tangle\tvalue\tpackage\tside\n\n";
    QString Str2 = "REF1T\t0.00\t0.00\t0.00\t1mm\tCircle\ttop\nREF2T\t0.00\t0.00\t0.00\t1mm\tCircle\ttop\nREF1B\t0.00\t0.00\t0.00\t1mm\tCircle\tbot\nREF2B\t0.00\t0.00\t0.00\t1mm\tCircle\tbot\n\n";
    ui->textEdit_2->clear();
    ui->textEdit_2->append(Str);
    ui->textEdit_2->append(Str2);

    qint32 topCount=0, botCount=0, lineCount=0;
    QString outputText1;
    while(!outputFile3.atEnd())
    {
        QString inputText3 = outputFile3.readLine();
        QStringList listSort = inputText3.split(QRegExp("\\s\\t"),QString::SkipEmptyParts);
        QString pos = listSort.at(8);
                        if (pos == "top\r\n")
                        {
                            pos = "top";
                            topCount++;
                        }
                        else
                        {
                            pos = "bot";
                            botCount++;
                        }
        outputText1 = (listSort.at(0) + "\t" + listSort.at(5) + "\t" + listSort.at(6) + "\t" + listSort.at(7) + "\t" + listSort.at(2) + "\t" + listSort.at(1) + "\t" + pos);
        ui->textEdit_2->append(outputText1);
        lineCount++;
    }
    ui->allCount->setNum(lineCount);
    ui->allCountTop->setNum(topCount);
    ui->allCountBot->setNum(botCount);
    outputFile3.close();

//============= Generate in table =====================

    ui->tableWidget->setRowCount(0);
    outputFile4.open(QIODevice::ReadOnly);
    for (int row = 0; !outputFile4.atEnd(); row++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            QString inputText4 = outputFile4.readLine();
            QStringList listSort = inputText4.split(QRegExp("\\s\\t"),QString::SkipEmptyParts);
            QString pos = listSort.at(8);
                            if (pos == "top\r\n")
                            {
                                pos = "top";
                                topCount++;
                            }
                            else
                            {
                                pos = "bot";
                                botCount++;
                            }
            QTableWidgetItem *newItem1 = new QTableWidgetItem();
            QTableWidgetItem *newItem2 = new QTableWidgetItem();
            QTableWidgetItem *newItem3 = new QTableWidgetItem();
            QTableWidgetItem *newItem4 = new QTableWidgetItem();
            QTableWidgetItem *newItem5 = new QTableWidgetItem();
            QTableWidgetItem *newItem6 = new QTableWidgetItem();
            QTableWidgetItem *newItem7 = new QTableWidgetItem();

            newItem1 -> setText(listSort.at(0));
            newItem2 -> setText(listSort.at(5));
            newItem3 -> setText(listSort.at(6));
            newItem4 -> setText(listSort.at(7));
            newItem5 -> setText(listSort.at(2));
            newItem6 -> setText(listSort.at(1));
            newItem7 -> setText(pos);

            ui->tableWidget->setItem(row, 0, newItem1);
            ui->tableWidget->setItem(row, 1, newItem2);
            ui->tableWidget->setItem(row, 2, newItem3);
            ui->tableWidget->setItem(row, 3, newItem4);
            ui->tableWidget->setItem(row, 4, newItem5);
            ui->tableWidget->setItem(row, 5, newItem6);
            ui->tableWidget->setItem(row, 6, newItem7);
    }
    outputFile4.close();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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
                    file.write(ui->textEdit_2->toPlainText().toUtf8());
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
