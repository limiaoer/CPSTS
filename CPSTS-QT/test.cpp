#include "test.h"
#include<qdebug.h>
#include "QFile"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include<fstream>
#include<cstdlib>
#include <bits/stdc++.h>
#include<qdebug.h>
using namespace std;

Test::Test()
{

}

string Test::befsplit(string array){
    int a = array.find(".");
    string b = array.substr(0,a);
    return b;
}


int Test::examBgm(string file, string name,string respath)//file is filepath,name is xxx.bgm
{
        string fname=befsplit(name);
        FILE *fp2;
        char buf2[1024] =   { 0 };
        ofstream wFile;
        respath=testResSufPath+fname+"-result.txt";
        qDebug()<< QString::fromStdString(respath);
        wFile.open(respath, ios::out);
        string c2="./bigmc "+BigraphSufPath+fname+".bgm";
//        string c2="/home/dy826/bigmc/bigmcBase/src/bigmc "+BigraphSufPath+fname+".bgm";
            cout<<"string"<<c2<<endl;
        char* comd2=const_cast<char*>(c2.c_str());
            cout<<"char*"<<comd2<<endl;
        if ((fp2 = popen(comd2, "r")) == NULL)
            {
                qDebug() <<"Fail to test";
                return 0;
            }
        else if (wFile.is_open()){
            qDebug() << "writeFile Open sucess!" ;
            while (fgets(buf2, 1024, fp2) != NULL)
                {
                    //cout<<buf2<<endl;
                    qDebug()<<QString::fromStdString(buf2);
                    wFile<<buf2<<endl;
                }
        }
        else {
            qDebug() << "Testing Results Writing File Open failure!" ;
            return 0;
        }
        pclose(fp2);
        wFile.close();
        qDebug() <<"Test Success! ";
        qDebug() <<" Testing results writing file write sucess! " ;
        return 1;
}

