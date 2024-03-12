#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<string.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNewProcess_triggered();

    void on_actionImportProcess_triggered();

    void on_actionSaveProcess_triggered();

    void on_actionImportBigraph_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionVersion_triggered();

    void on_actionTranslate_triggered();

    void on_actionExam_triggered();

    void on_actionTransAndExam_triggered();

private:
    Ui::MainWindow *ui;
    //QString currentFile;
    QString currentProcessFile;
    QString currentBigraphsFile;
    QString currentResFile;
    //QString ProcessSufPath="/home/dy826/bigmc/bigmcBase/doc/processEvent/";
   // QString BigraphSufPath="/home/dy826/bigmc/bigmcBase/doc/bigraph/";
    //QString testResSufPath="/home/dy826/bigmc/bigmcBase/doc/testingRes/";
    QString ProcessSufPath="processEvent/";
    QString BigraphSufPath="bigraph/";
    QString testResSufPath="testingRes/";
};

#endif // MAINWINDOW_H
