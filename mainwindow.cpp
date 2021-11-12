#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileSelected("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectNewFile_clicked()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,
                                            "Wskaż plik",
                                            "",
                                            "Plik tekstowy (*.txt)");
    fileSelected(fileName);
}

void MainWindow::fileSelected(QString in_fileName)
{
    static QString fileName = "";
    if(!in_fileName.isEmpty())
        fileName = in_fileName;
    bool noEmpty = !fileName.isEmpty();

    if(noEmpty)
    {
        ui->pathDisp->setText(fileName);
        m_MyFile.setFileName(fileName);
        ui->statusbar->showMessage("Plik ustawiony");
    }
    else
    {
        ui->pathDisp->setText("Brak pliku");
        ui->statusbar->showMessage("Brak pliku");
    }
    ui->readBut->setEnabled(noEmpty);
    ui->writeBut->setEnabled(noEmpty);
    ui->revBut->setEnabled(noEmpty);
    ui->clearBut->setEnabled(noEmpty);
    ui->addValueBut->setEnabled(noEmpty);
    ui->getValueBut->setEnabled(noEmpty);
}


void MainWindow::on_writeBut_clicked()
{
    m_MyFile.close();
    if(m_MyFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream outStream(&m_MyFile);
        QString contents = ui->textDisp->toPlainText();
        outStream << contents;
        ui->statusbar->showMessage("Zapisano tekst");
        m_MyFile.close();
    }
    else ui->statusbar->showMessage("Bład otwarcia pliku!");
}

void MainWindow::on_readBut_clicked()
{
    m_MyFile.close();
    if(m_MyFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         QTextStream inStream(&m_MyFile);
         QString contents = inStream.readAll();
         ui->textDisp->setPlainText(contents);
         ui->statusbar->showMessage("Odczytano tekst");
         m_MyFile.close();
    }
    else ui->statusbar->showMessage("Bład otwarcia pliku!");
}

void MainWindow::on_addValueBut_clicked()
{
    m_MyFile.close();
    if(m_MyFile.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream outStream(&m_MyFile);
        double value = ui->setVal->value();
        outStream << value << ' ';
        ui->statusbar->showMessage("Dopisano: " + QString::number(value));
        m_MyFile.close();
    }
    else ui->statusbar->showMessage("Bład otwarcia pliku!");
}


void MainWindow::on_getValueBut_clicked()
{
    static QTextStream inStream;

    if(!m_MyFile.isOpen())
    {
        if(m_MyFile.open(QIODevice::ReadOnly | QIODevice::Text))
            inStream.setDevice(&m_MyFile);
        else
        {
            ui->statusbar->showMessage("Bład otwarcia pliku!");
            return;
        }
    }

    double value;
    inStream >> value;

    if(!inStream.atEnd())
    {
        ui->statusbar->showMessage("Odczytano: " + QString::number(value));
        ui->readBox->setText(QString::number(value));
    }
    else
    {
        ui->statusbar->showMessage("Koniec Pliku!");
        ui->getValueBut->setEnabled(false);
    }
}


void MainWindow::on_clearBut_clicked()
{
    m_MyFile.close();
    if(m_MyFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream outStream(&m_MyFile);
        outStream << "";
        ui->statusbar->showMessage("Wyczyszczono!");
        m_MyFile.close();
    }
    else ui->statusbar->showMessage("Bład otwarcia pliku!");
}


void MainWindow::on_revBut_clicked()
{
    m_MyFile.close();
    ui->getValueBut->setEnabled(true);
}

