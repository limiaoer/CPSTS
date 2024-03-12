#ifndef TRANSLATE_H
#define TRANSLATE_H
#include<iostream>
using namespace std;
#include <regex>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include<fstream>
#include<cstdlib>
#include <bits/stdc++.h>



class Translate
{
public:
    Translate();
    //~translate();
    int generateRules(string file,string name,vector<string> &beforeRules, vector<string> &afterRules,string bgmpath);
private:
    //string BigraphSufPath="/home/dy826/bigmc/bigmcBase/doc/bigraph/";
    //string testResSufPath="/home/dy826/bigmc/bigmcBase/doc/testingRes/";
    //string ruleTextPath="/home/dy826/bigmc/bigmcBase/doc/processEvent/rules.txt/";
    string ProcessSufPath="processEvent/";
    string BigraphSufPath="bigraph/";
    string testResSufPath="testingRes/";
    string ruleTextPath="processEvent/rules.txt";
    int rulesConversion(vector<string> &beforeRules, vector<string> &afterRules);
};

#endif // TRANSLATE_H
