#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_Upload_triggered();
    void on_UploadRun_triggered();
    void onUpdateTitle(double frequency);
    
signals:
    void openFile(std::string path);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
