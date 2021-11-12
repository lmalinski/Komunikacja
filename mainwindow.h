#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_selectNewFile_clicked();
    void on_writeBut_clicked();
    void on_readBut_clicked();
    void on_addValueBut_clicked();
    void on_getValueBut_clicked();
    void on_clearBut_clicked();
    void on_revBut_clicked();

private:
    void fileSelected(QString fileName);

    Ui::MainWindow *ui;
    QFile m_MyFile;
};
#endif // MAINWINDOW_H
