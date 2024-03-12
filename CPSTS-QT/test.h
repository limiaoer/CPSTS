#ifndef TEST_H
#define TEST_H
#include<iostream>
using namespace std;

class Test
{
public:
    Test();
    int examBgm(string file,string name,string respath);
    string befsplit(string array);

private:
    //string BigraphSufPath="/home/dy826/bigmc/bigmcBase/doc/bigraph/";
    //string testResSufPath="/home/dy826/bigmc/bigmcBase/doc/testingRes/";
    string ProcessSufPath="processEvent/";
    string BigraphSufPath="bigraph/";
    string testResSufPath="testingRes/";
};

#endif // TEST_H
