#include "mainwindow.h"
#include <string>
#include "ui_mainwindow.h"
#include "QDebug"
#include "qfiledialog.h"
#include "QFile"
#include "qmessagebox.h"
#include "test.h"
#include "translate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tabWidget);//设置组件居中平铺
}

MainWindow::~MainWindow()
{
    delete ui;


}



void MainWindow::on_actionNewProcess_triggered()
{
//    ui->tabWidget->addTab(this,"NewProcessEvt");
//    ui->tabWidget->setMovable(true);
//    ui->tabWidget->setTabPosition(QTabWidget::North);
//    connect(ui->tabWidget,&QTabWidget::tabCloseRequested,[=](int index){
//        ui->tabWidget->removeTab(index);
//        qDebug() << index;
//    });
    /*if(ui->tabWidget->count()!=0){
        for(int i=0 ; i<ui->tabWidget->count() ;i++)
        {
            ui->tabWidget->removeTab(i);
        }
    }*/
    int temp_tabCount= ui->tabWidget->count()-1;
    qDebug()<<" tab count: " << temp_tabCount;

    for(int i=temp_tabCount;i>=0  ;i-- )
    {
        qDebug()<<" remove tab: "<< i;
       ui->tabWidget->removeTab(i);


    }
    ui->tabWidget->addTab(new QTextEdit(),"NewProcessEvt");
}

void MainWindow::on_actionImportProcess_triggered()
{
    int temp_tabCount= ui->tabWidget->count()-1;
    qDebug()<<" tab count: " << temp_tabCount;

    for(int i=temp_tabCount;i>=0 ;i-- )
    {
        qDebug()<<" remove tab: "<< i;
       ui->tabWidget->removeTab(i);


    }
    QString fileName = QFileDialog::getOpenFileName(this,"OpenFile",ProcessSufPath);
    QFile file(fileName);
    currentProcessFile = fileName;
    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","Can not Open the File : "+file.errorString());
        return;
    }
    qDebug()<<currentProcessFile;
    QFileInfo fileinfo(file.fileName());
    QString fs(fileinfo.suffix());
    if(fs!="txt"){
        QMessageBox::critical(this,"error","not processevent file");
    }
    else{
        QString fn(fileinfo.fileName());
        //setWindowTitle(fileName);
        QTextStream in(&file);
        QString text = in.readAll();
        //ui->textEdit->setText(text);
        QTextEdit * textedit=new QTextEdit();
        textedit->setText(text);
        ui->tabWidget->addTab(textedit,fn);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count());
        file.close();
    }

}

void MainWindow::on_actionImportBigraph_triggered()
{
    int temp_tabCount= ui->tabWidget->count()-1;
    qDebug()<<" tab count: " << temp_tabCount;

    for(int i=temp_tabCount;i>=0  ;i-- )
    {
        qDebug()<<" remove tab: "<< i;
       ui->tabWidget->removeTab(i);


    }
    QString fileName = QFileDialog::getOpenFileName(this,"OpenFile",BigraphSufPath);
    QFile file(fileName);
    currentBigraphsFile = fileName;
    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","Can not Open the File : "+file.errorString());
        return;
    }
    QFileInfo fileinfo(file.fileName());
    QString fs(fileinfo.suffix());
    if(fs!="bgm"){
        QMessageBox::critical(this,"error","not processevent file");
    }
    else{
        QString fn(fileinfo.fileName());
        QTextStream in(&file);
        QString text = in.readAll();
        //ui->textEdit->setText(text);
        QTextEdit * textedit=new QTextEdit();
        textedit->setText(text);
        textedit->setReadOnly(true);
        ui->tabWidget->addTab(textedit,fn);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count());
        file.close();
    }

}


void MainWindow::on_actionSaveProcess_triggered()
{
       QString fileName;
       if(currentProcessFile.isEmpty()){//新建文件是在临时编辑框里，需要用对话框找一个保存目录
           fileName =QFileDialog::getSaveFileName(this,"Save File",ProcessSufPath);
           currentProcessFile =fileName;
       }else{//导入文件有路径
           fileName =currentProcessFile;
       }
       //用QFile打开文件
       QFile file(fileName);
       if(!file.open(QIODevice::WriteOnly|QFile::Text)){
           QMessageBox::warning(this,"Warning","Can not Save the File:"+file.errorString());
           return;
       }
       currentProcessFile = fileName;
       setWindowTitle(fileName);
       //用流写入文件
       QTextStream out(&file);
       //QString text =ui->textEdit->toHtml();//toPlanText() ,
       //out<<text;
       QTextEdit * textedit=(QTextEdit *)ui->tabWidget->currentWidget();
       if(textedit){
           out<<textedit->toPlainText();
       }
       QFileInfo fileinfo(file.fileName());
       QString fn(fileinfo.fileName());
       ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),fn);
       file.close();

}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
     ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
     ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionVersion_triggered()
{
    QMessageBox::information(this,"SystemInformation","Cyber Physical System Model Checker (CPSMC) \n version:1.0");

}


void MainWindow::on_actionTranslate_triggered()
{
    int temp_tabCount= ui->tabWidget->count()-1;
    qDebug()<<" tab count: " << temp_tabCount;

    for(int i=temp_tabCount;i>=1  ;i-- )
    {
        qDebug()<<" remove tab: "<< i;
       ui->tabWidget->removeTab(i);

    }

    QString File=currentProcessFile;
    QFileInfo fileinfo(currentProcessFile);
    QString name(fileinfo.fileName());
    string bgm;
    vector<string> beforeRules;
    vector<string> afterRules;
    Translate trans ;//= new Translate();
    int ret=trans.generateRules(File.toStdString(),name.toStdString(),beforeRules,afterRules,bgm);
    qDebug()<<ret;
    if(ret==0){
        QMessageBox::critical(this,"error1","ConversionErro");
    }
    else{
        QString bgmpath=BigraphSufPath+fileinfo.baseName()+".bgm";
        qDebug()<<bgmpath;
        currentBigraphsFile=bgmpath;
        //QString file=currentFile;
        QFile file(currentBigraphsFile);
        if(!file.open(QIODevice::ReadOnly|QFile::Text)){
            qDebug()<<"Can not Open the translated File";
            QMessageBox::warning(this,"Warning2","Can not Open the File : "+file.errorString());
            return;
        }
        QFileInfo fileinfo(file.fileName());
        QString fs(fileinfo.suffix());
        if(fs!="bgm"){
            QMessageBox::critical(this,"error3","not processevent file");
        }
        else{
            QString fn(fileinfo.fileName());
            QTextStream in(&file);
            QString text = in.readAll();
            //ui->textEdit->setText(text);
            QTextEdit * textedit=new QTextEdit();
            textedit->setText(text);
            textedit->setReadOnly(true);
            ui->tabWidget->addTab(textedit,fn);
            ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
            file.close();
        }
    }
}

void MainWindow::on_actionExam_triggered()
{
    int temp_tabCount= ui->tabWidget->count()-1;
    qDebug()<<" tab count: " << temp_tabCount;

    for(int i=temp_tabCount;i>=2  ;i-- )
    {
        qDebug()<<" remove tab: "<< i;
       ui->tabWidget->removeTab(i);


    }
    QString File=currentBigraphsFile;
    QFileInfo fileinfo(currentBigraphsFile);
    QString name(fileinfo.fileName());
    qDebug()<<name;
    string res;
    Test test;//=new Test();
    int r=test.examBgm(File.toStdString(),name.toStdString(),res);
    qDebug()<<r;
    if(r==0){
        QMessageBox::critical(this,"Error","ExaminationError");
    }
    else{
        QString respath=testResSufPath+fileinfo.baseName()+"-result.txt";
        qDebug()<<respath;
        currentResFile=respath;
        QFile file(currentResFile);
        if(!file.open(QIODevice::ReadOnly|QFile::Text)){
            QMessageBox::warning(this,"Warning","Can not Open the File : "+file.errorString());
            return;
        }
        QFileInfo fileinfo(file.fileName());
        QString fs(fileinfo.suffix());
            QString fn(fileinfo.fileName());
            QTextStream in(&file);
            QString text = in.readAll();
            //ui->textEdit->setText(text);
            QTextEdit * textedit=new QTextEdit();
            textedit->setText(text);
            textedit->setReadOnly(true);
            ui->tabWidget->addTab(textedit,fn);
            ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
            file.close();
    }
}

void MainWindow::on_actionTransAndExam_triggered()
{
    on_actionTranslate_triggered();
    on_actionExam_triggered();
}
