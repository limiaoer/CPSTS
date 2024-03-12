#include "translate.h"
#include <regex>
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




bool RegexMatch(string source_string, regex regex_string)
{
    if (regex_match(source_string, regex_string))
        return true;
    else
        return false;
}



string ModelTransformation(string expression)
{
    regex reg1("^.*=in.*$");
    regex reg2("^.*out.*$");
    regex reg3("^.*accelerate.*$");
    regex reg4("^.*brake.*$");
    regex reg5("^.*road2.*$");
    regex reg7("^.*login.*$");
    regex reg11("^.*read.*$");
    regex reg12("^.*guardroom.*enter.*$");
    regex reg13("^.*exit.*$");
    regex reg14("^.*mainarea.*$");
    string result;
    if (regex_match(expression, reg1) == true)
    {
        result = "driver[e5,e6,tom,-,-,-,-,-,-,-,-].$0|car[c1].$1|$2->car[c1].(driver[e5,e6,tom,-,-,-,-,-,-,-,-].$0|$1)|$2; ";
        return result;
    }
    else if (regex_match(expression, reg2) == true)
    {
        result = "C1.(driver[d,d,d].$0|$1)|$2->driver[x,y,z].$0|C1.$1|$2;";
        return result;
    }
    else if (regex_match(expression, reg3) == true)
    {
        result = "car[c1].(driver[e5,e6,tom,s,-,-,-,-,-,-,-].$0|$1)|$2->car[c1].(driver[e5,e6,tom,s,-,a,-,-,-,-,-].$0|$1)|$2; ";
        return result;
    }
    else if (regex_match(expression, reg4) == true)
    {
        result = "car[c1].(driver[e5,e6,tom,s,-,-,-,-,-,-,-].$0|$1)|$2->car[c1].(driver[e5,e6,tom,s,-,-,b,-,-,-,-].$0|$1)|$2;";
        return result;
    }
    else if (regex_match(expression, reg5) == true)
    {
        // result = "car enter road2+road2.$0|road1.(driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1|$2)|$3→road2.($0|(driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1))|road1.($2)|$3;*driver enter road2+road2.$0|road1.(driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1|$2)|$3→road2.($0|(driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1))|road1.($2)|$3;";
        result = "road2.$0|road1.(driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1|$2)|$3->road2.($0|(driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1))|road1.($2)|$3;";
        return result;
    }
    else if (regex_match(expression, reg7) == true)
    {
        // result = "driver login+parklot[work].mainarea.($0|guardroom.(server.IPMS.$1|$2))|driver[e5,e6,tom,s,-,-,-,-,-,-,-].$3→parklot[work].mainarea.($0|guardroom.(server.IPMS.$1|$2))|driver[e5,e6,tom,s,-,-,-,-,-,l,-].$3;*guard login+parklot[work].mainarea.(guardroom.($0|guard[jack,-,-])|$1)|$2→parklot[work].mainarea.(guardroom.($0|guard[jack,login,-])|$1)|$2;";
        result = "parklot[work].mainarea.(guardroom.($0|guard[jack,-,-])|$1)|$2->parklot[work].mainarea.(guardroom.($0|guard[jack,login,-])|$1)|$2;";
        return result;
    }
    else if (regex_match(expression, reg11) == true)
    {
        result = "parklot[work].mainarea.((guardroom.(guard[jack,login,-]|driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1|$2)|$3))|$4->parklot[work].mainarea.((guardroom.(guard[jack,login,-]|driver[e5,e6,tom,-,-,-,-,-,-,login,re].$1|$2)|$3))|$4;";
        return result;
    }
    else if (regex_match(expression, reg12) == true)
    {
        result = "guard enter guardroom+parklot[work].mainarea.(guard[jack,-,-]|guardroom.$0|$1)|$2->parklot[work].mainarea.(guardroom.($0|guard[jack,-,-])|$1)|$2;*driver enter guardroom+parklot[work].mainarea.((driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1|guardroom.(guard[jack,l,-]|$2)|$3))|$4->parklot[work].mainarea.((guardroom.(guard[jack,login,-]|driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1|$2)|$3))|$4;";
        return result;
    }
    else if (regex_match(expression, reg13) == true)
    {
        result = "parklot[work].mainarea.(guardroom.($0|guard[jack,login,-])|$1)|$2->parklot[work].mainarea.(guard[jack,-,-]|guardroom.$0|$1)|$2;";
        return result;
    }
    else if (regex_match(expression, reg14) == true)
    {
        result = "road2.($0|driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1)|parklot[work].mainarea.$2|$3->road2.$0|parklot[work].mainarea.(driver[e5,e6,tom,-,-,-,-,-,-,-,-].$1|$2)|$3;";
        return result;
    }
    else
    {
        result = "";
        return result;
    }
}

void spiltStr(string str, const string &split, vector<string> &strlist)
{
    strlist.clear();
    if (str == "")
        return;
    string strs = str + split;
    size_t pos = strs.find(split);
    int steps = split.size();

    while (pos != strs.npos)
    {
        // substr 复制字符串，起始位置，复制字符数目
        string temp = strs.substr(0, pos);
        strlist.push_back(temp);
        strs = strs.substr(pos + steps, strs.size());
        pos = strs.find(split);
    }
}

vector<string> beforeRules;
vector<string> afterRules;
int Translate::rulesConversion(vector<string> &beforeRules, vector<string> &afterRules)
{
    ifstream readFile;
    readFile.open(ruleTextPath, ios::in);
    if (readFile.is_open())
    {
        cout << "rules.txt Open sucess!" << endl;
        char buff[1000] = {0};
        while (readFile.getline(buff, sizeof(buff)))
        {
            // cout << buff << endl;
            beforeRules.push_back(buff);
            afterRules.push_back(ModelTransformation(buff));
        }
    }
    else
    {
        cout << "rules.txt Open failure!" << endl;
        return 0;
    }
    readFile.close();
    return 1;
}

char* strToChar(string str){
    char *c=const_cast<char*>(str.c_str());
    return c;
}

/*
split filename as '.'
return string before '.'
*/
string befsplit(string array){
    int a = array.find(".");
    string b = array.substr(0,a);
    return b;
}

/*
split filename as '.'
return string after '.', containing '.'
*/
string aftsplit(string array){
    int a = array.find(".");
    string b = array.substr(a,array.length());
    return b;
}

int Translate::generateRules(string file,string name,vector<string> &beforeRules, vector<string> &afterRules,string bgmpath)//file is filepath, name is xxx.txt
{
    cout<<"file:"<<file<<endl;
    cout<<"name:"<<name<<endl;
    if (rulesConversion(beforeRules, afterRules) == 1)
    {
        string fname = befsplit(name);
        cout<<"fname"<<fname<<endl;
        ifstream readFile;
        //string file="bigmcBase/doc/processEvent/"+fname+".txt";

        //Process Events Editing Over,Transform Starts
        qDebug()<<"( Transforming starts )";
        readFile.open(file, ios::in);
        ofstream writeFile;
        bgmpath=BigraphSufPath+fname+".bgm";
        //writeFile.open(BigraphSufPath+fname+".bgm", ios::out);
        writeFile.open(bgmpath, ios::out);
        if (readFile.is_open())
        {
            qDebug() << "Process events file -- .txt Open sucess!";
            if (writeFile.is_open())
            {
                qDebug() << "Bigraph file -- .bgm Open sucess!";
                char buff[1000] = {0};
                while (readFile.getline(buff, sizeof(buff)))
                {
                    // cout << buff << endl;
                    string str = string(buff);
                    string str1, str2;
                    if (str.find("=") != -1)
                    {
                        int denghao = str.find("=");
                        str1 = str.substr(0, denghao - 1);
                        str2 = str.substr(denghao + 1, str.size() - denghao - 1);
                    }
                    else
                    {
                        str1 = str;
                    }
                    vector<string> strlist;
                    if (str1 == "Rule")
                    {
                        spiltStr(str2, "||", strlist);
                        for (int i = 0; i < strlist.size(); i++)
                        {
                            //    cout<<"ASDF"<<endl;
                            vector<string> strlist1;
                            string temp_result = ModelTransformation(strlist[i]);
                            if (temp_result.find("*") != -1)
                            {
                                spiltStr(temp_result, "*", strlist1);
                                string str11, str22;
                                for (int j = 0; j < strlist1.size(); j++)
                                {
                                    int jiahao = strlist1[j].find("+");
                                    str11 = strlist1[j].substr(0, jiahao);
                                    str22 = strlist1[j].substr(jiahao + 1, strlist1[j].size() - jiahao - 1);
                                    writeFile << str22 << endl;
                                    writeFile << endl;

                                }
                            }
                            else
                            {
                                writeFile << temp_result << endl;
                                writeFile << endl;
                            }
                        }
                    }
                    else if (str1 == "Position")
                    {
                        str2 = str2.substr(1, str2.size() - 2);
                        // str2 = str2.substr(1, str2.size() - 3);
                        // cout << "str2.size(): " << str2.size() << endl;
                        vector<string> strlist1;
                        spiltStr(str2, ",", strlist1);
                        string str11, str22;
                        for (int j = 0; j < strlist1.size(); j++)
                        {
                            if (strlist1[j].find("(") != -1)
                            {
                                int kuohao = strlist1[j].find("(");
                                str11 = strlist1[j].substr(0, kuohao);
                                str22 = strlist1[j].substr(kuohao + 1, strlist1[j].size() - kuohao - 1);
                                writeFile << "%active " << str11 << " : " << str22 << ";" << endl;
                            }
                            else
                            {
                                writeFile << "%active " << strlist1[j] << ";" << endl;
                            }
                        }
                        writeFile << endl;
                    }
                    else if (str1 == "Man")
                    {
                        str2 = str2.substr(1, str2.size() - 2);
                        // str2 = str2.substr(1, str2.size() - 3);
                        vector<string> strlist1;
                        spiltStr(str2, ",", strlist1);
                        string str11, str22;
                        for (int j = 0; j < strlist1.size(); j++)
                        {
                            if (strlist1[j].find("(") != -1)
                            {
                                int kuohao = strlist1[j].find("(");
                                str11 = strlist1[j].substr(0, kuohao);
                                str22 = strlist1[j].substr(kuohao + 1, strlist1[j].size() - kuohao - 1);
                                writeFile << "%active " << str11 << " : " << str22 << ";" << endl;
                            }
                            else
                            {
                                writeFile << "%active " << strlist1[j] << ";" << endl;
                            }
                        }
                        writeFile << endl;
                    }
                    else if (str1 == "Car")
                    {
                        str2 = str2.substr(1, str2.size() - 2);
                        // str2 = str2.substr(1, str2.size() - 3);
                        vector<string> strlist1;
                        spiltStr(str2, ",", strlist1);
                        string str11, str22;
                        for (int j = 0; j < strlist1.size(); j++)
                        {
                            if (strlist1[j].find("(") != -1)
                            {
                                int kuohao = strlist1[j].find("(");
                                str11 = strlist1[j].substr(0, kuohao);
                                str22 = strlist1[j].substr(kuohao + 1, strlist1[j].size() - kuohao - 1);
                                writeFile << "%active " << str11 << " : " << str22 << ";" << endl;
                            }
                            else
                            {
                                writeFile << "%active " << strlist1[j] << ";" << endl;
                            }
                        }
                        writeFile << endl;
                    }
                    else if (str1 == "Sign")
                    {
                        str2 = str2.substr(1, str2.size() - 2);
                        // str2 = str2.substr(1, str2.size() - 3);
                        vector<string> strlist1;
                        spiltStr(str2, ",", strlist1);
                        string str11, str22;
                        for (int j = 0; j < strlist1.size(); j++)
                        {
                            if (strlist1[j].find("(") != -1)
                            {
                                int kuohao = strlist1[j].find("(");
                                str11 = strlist1[j].substr(0, kuohao);
                                str22 = strlist1[j].substr(kuohao + 1, strlist1[j].size() - kuohao - 1);
                                writeFile << "%passive " << str11 << " : " << str22 << ";" << endl;
                            }
                            else
                            {
                                writeFile << "%passive " << strlist1[j] << ";" << endl;
                            }
                        }
                        writeFile << endl;
                    }
                    else if (str1 == "Parklot")
                    {
                        str2 = str2.substr(1, str2.size() - 2);
                        // str2 = str2.substr(1, str2.size() - 3);
                        vector<string> strlist1;
                        spiltStr(str2, ",", strlist1);
                        string str11, str22;
                        for (int j = 0; j < strlist1.size(); j++)
                        {
                            if (strlist1[j].find("(") != -1)
                            {
                                int kuohao = strlist1[j].find("(");
                                str11 = strlist1[j].substr(0, kuohao);
                                str22 = strlist1[j].substr(kuohao + 1, strlist1[j].size() - kuohao - 1);
                                writeFile << "%active " << str11 << " : " << str22 << ";" << endl;
                            }
                            else
                            {
                                writeFile << "%active " << strlist1[j] << ";" << endl;
                            }
                        }
                        writeFile << endl;
                    }
                    else if (str1 == "Driver")
                    {
                        str2 = str2.substr(1, str2.size() - 2);
                        // str2 = str2.substr(1, str2.size() - 3);
                        vector<string> strlist1;
                        spiltStr(str2, ",", strlist1);
                        string str11, str22;
                        for (int j = 0; j < strlist1.size(); j++)
                        {
                            if (strlist1[j].find("(") != -1)
                            {
                                int kuohao = strlist1[j].find("(");
                                str11 = strlist1[j].substr(0, kuohao);
                                str22 = strlist1[j].substr(kuohao + 1, strlist1[j].size() - kuohao - 1);
                                writeFile << "%active " << str11 << " : " << str22 << ";" << endl;
                            }
                            else
                            {
                                writeFile << "%active " << strlist1[j] << ";" << endl;
                            }
                        }
                        writeFile << endl;
                    }
                    else if (str1 == "Eges")
                    {
                        str2 = str2.substr(1, str2.size() - 2);
                        // str2 = str2.substr(1, str2.size() - 3);
                        vector<string> strlist1;
                        spiltStr(str2, ",", strlist1);
                        vector<string>::iterator k;
                        k = find(strlist1.begin(), strlist1.end(), "sp");
                        // auto spPos = distance(strlist1.begin(), k);
                        string str11, str22;
                        int m = -1;
                        for (int j = 0; j < strlist1.size(); j++)
                        {
                            m++;
                            if (strlist1[j].find("(") != -1)
                            {
                            // 	if (m < spPos)
                            // 	{
                                    int kuohao = strlist1[j].find("(");
                                    str11 = strlist1[j].substr(0, kuohao);
                                    str22 = strlist1[j].substr(kuohao + 1, strlist1[j].size() - kuohao - 1);
                                    writeFile << "%name " << str11 << " : " << str22 << ";" << endl;
                            }
                            else
                            {

                                    writeFile << "%name " << strlist1[j] << ";" << endl;

                            }
                        }
                        writeFile << endl;
                    }
                    else if (str1 == "Outer")
                    {
                        str2 = str2.substr(1, str2.size() - 2);
                        // str2 = str2.substr(1, str2.size() - 3);
                        vector<string> strlist1;
                        spiltStr(str2, ",", strlist1);
                        string str11, str22;
                        for (int j = 0; j < strlist1.size(); j++)
                        {
                            if (strlist1[j].find("(") != -1)
                            {
                                int kuohao = strlist1[j].find("(");
                                str11 = strlist1[j].substr(0, kuohao);
                                str22 = strlist1[j].substr(kuohao + 1, strlist1[j].size() - kuohao - 1);
                                writeFile << "%outer " << str11 << " : " << str22 << ";" << endl;
                            }
                            else
                            {
                                writeFile << "%outer " << strlist1[j] << ";" << endl;
                            }
                        }
                        writeFile << endl;
                    }
                    else if (str1.find("PL") != -1)
                    {
                        writeFile << "mall[work]|shcool|construction|road2.(parksign[pk]|leftsign[lf])|road3|parklot[work].mainarea.(spot[-,-,-,-,-,-]|guard[jack,-,-]|guardroom.(server.IPMS.(DCM[e2]|DM[e1,e2]|EM[e1,login]|record[re])))|road1.(driver[e5,e6,tom,-,-,-,-,-,-,-,-].(GET[e3,e5]|G[e3,e4]|EXE[e4,e6])|car[c1].(SMM[e7,e8,e9,e10]|SSU[e10,ss]|SNU[e9,sn]|AU[e8,au]|BU[e7,bu]|DMM[e11,e12]|SW[e11,sw]|DMU[e12,dm])|crosswalk[-]);" << endl;
                        writeFile << endl;
                    }
                    else
                    {
                        qDebug() << "Not Find!" ;
                    }
                }
                writeFile << "%property CppResourceSecue !matches(parklot[work].mainarea.(guard[jack,login,-]|guardroom.(driver[e5,e6,tom,-,-,-,-,-,-,login,re].$1|$2)|$3)|$4);" << endl;
                writeFile << "%check" << endl;
            }
            else
            {
                qDebug() << "writeFileOpen failure!" ;
                return 0;
            }
        }
        else
        {
            qDebug() << "readFileOpen failure!" ;
            return 0;
        }
        readFile.close();
        writeFile.close();
       qDebug()<<"( Transforming is over )";

    }
    else
    {
        qDebug() << " Rule conversion failed! " ;
    }
    return 1;
}


Translate::Translate()
{

}
