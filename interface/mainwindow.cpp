#include <QMessageBox>
#include <QThread>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    
    connect(this, &MainWindow::openFile, ui -> centralwidget, &CentralWidget::onOpenFile);
    connect(ui -> centralwidget, &CentralWidget::updateFrequency, this, &MainWindow::onUpdateTitle);
}

void MainWindow::onUpdateTitle(double frequency)
{
    auto freq  = QString::number(frequency, 'f', 3);
    auto title = tr("Орион-128 @ %1 MHz").arg(freq);
    
    this -> setWindowTitle(title);
}

void MainWindow::on_Upload_triggered()
{
    QFileDialog dialog(this);
    
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Files (*.com *.rko *.bru)"));
    dialog.setViewMode(QFileDialog::Detail);
    
    QStringList fileNames;
    
    if (dialog.exec())
    {
        auto file = dialog
            .selectedFiles()
            .first();
        
        emit openFile(file.toStdString());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_UploadRun_triggered()
{

}
