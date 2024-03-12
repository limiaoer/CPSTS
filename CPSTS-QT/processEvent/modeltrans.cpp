#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>  
#include<fstream>
#include<cstdlib>
#include <bits/stdc++.h>
using namespace std;

/*
读取进程代数文档，对其中每一条规则进行正则匹配，将对应模型输出到新的文档。
由于一条规则可能对应多个模型，所以初步打算转换到其中一个模型。
*/

// 正则匹配
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
int rulesConversion(vector<string> &beforeRules, vector<string> &afterRules)
{
	ifstream readFile;
	readFile.open("rules.txt", ios::in);
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
*/
string split(string array){
	int a = array.find(".");
	string b = array.substr(0,a);
	return b;
}

int editProcessEvent(){
	string name;
	cout<<"请输入进程文件名(test.txt):";
	cin>>name;
	string fname = split(name);
	ifstream readFile;
	string file="/home/dy826/bigmc/bigmcBase/doc/processEvent/"+fname+".txt";
			
	//Process Events Editing
	cout<<endl<<"( Process events editing starts )"<<endl;
	string c="gedit "+file;
	char* comd=const_cast<char*>(c.c_str());  
	FILE *fp1;  
	//fp1 = popen(comd, "r"); 
	if ((fp1 = popen(comd, "r")) == NULL)  
	{  
		perror("Fail to export\n");  
		exit(1);  
	} 
	pclose(fp1);
	cout<<"( Process events editing is over )"<<endl;
}

int generateRules(vector<string> &beforeRules, vector<string> &afterRules)
{
	if (rulesConversion(beforeRules, afterRules) == 1)
	{
		string name;
		cout<<"请输入进程文件名(test.txt):";
		cin>>name;
		string fname = split(name);
		ifstream readFile;
		string file="/home/dy826/bigmc/bigmcBase/doc/processEvent/"+fname+".txt";
		
		//Process Events Editing
		/*cout<<endl<<"===== Process events editing starts ====="<<endl;
		//cout<<"file"<<file<<endl;
		string c="gedit "+file;
		//cout<<"string"<<c<<endl;
	    char* comd=const_cast<char*>(c.c_str());
		//cout<<"char*"<<comd<<endl;  
		FILE *fp1;  
	    if ((fp1 = popen(comd, "r")) == NULL)  
		{  
		        perror("Fail to export\n");  
		        exit(1);  
		} 
		pclose(fp1);
		cout<<"===== Process events editing is over ====="<<endl;*/
		//Process Events Editing Over,Transform Starts
		cout<<endl<<"( Transforming starts )"<<endl;
		readFile.open(file, ios::in);
		ofstream writeFile;
		writeFile.open("/home/dy826/bigmc/bigmcBase/doc/bigraph/"+fname+".bgm", ios::out); 
                //writeFile.open("result.txt", ios::out);
                if (readFile.is_open())
		{
			cout << "Process events file -- "<<fname<<".txt Open sucess!" << endl;
  			if (writeFile.is_open())
			{
				cout << "Bigraph file -- "<<fname<<".bgm Open sucess!" << endl;
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
					// cout << "前" << str1 << endl;
					// cout << "后" << str2 << endl;
					vector<string> strlist;
					// cout << str1 << endl;
					// cout << "dang qian: " <<str1 << endl;
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
						cout << "Not Find!" << endl;
					}
				}
				writeFile << "%property CppResourceSecue !matches(parklot[work].mainarea.(guard[jack,login,-]|guardroom.(driver[e5,e6,tom,-,-,-,-,-,-,login,re].$1|$2)|$3)|$4);" << endl;
				writeFile << "%check" << endl;
			}
			else
			{
				cout << "writeFileOpen failure!" << endl;
				return 0;
			}
		} 
		else
		{
			cout << "readFileOpen failure!" << endl;
			return 0;
		}
		readFile.close();
		writeFile.close();
		cout<<"( Transforming is over )"<<endl;
		
		//test
		cout<<endl<<"( Testing starts )"<<endl;
		FILE *fp2;
		char buf2[1024] =   { 0 };
		ofstream wFile;
		wFile.open("/home/dy826/bigmc/bigmcBase/doc/testingRes/"+fname+"-result.txt", ios::out);
		string c2="bigmc /home/dy826/bigmc/bigmcBase/doc/bigraph/"+fname+".bgm";
//		cout<<"string"<<c2<<endl;
		char* comd2=const_cast<char*>(c2.c_str());
//		cout<<"char*"<<comd2<<endl;
		if ((fp2 = popen(comd2, "r")) == NULL)  
			{  
				perror("Fail to test\n");  
				exit(1);  
			} 
		else if (wFile.is_open()){
			cout << "writeFile Open sucess!" << endl;
			while (fgets(buf2, 1024, fp2) != NULL)  
				{  
					cout<<buf2<<endl;
					wFile<<buf2<<endl;   
				}
		} 
		else {
			cout << "Testing Results Writing File Open failure!" << endl;
			exit(1);
		}
		pclose(fp2);
		wFile.close();
		cout<<"( Test Success! )"<<endl; 
		cout << "( Testing results writing file write sucess! )" << endl;
		
	}
	else
	{
		cout << " Rule conversion failed! " << endl;
	}
	 
	    
	return 1;
}



int main()
{
	int req;
	cout<<"输入需求序号：";
	cin>>req;
	while(req!=0){
		switch(req){
			case 1:
				editProcessEvent();
				break;
			case 2:
				{
					vector<string> beforeRules;
				vector<string> afterRules;
				generateRules(beforeRules, afterRules);
				}
				break;
			default:
				cout<<"没有该需求！"<<endl;
				break;
		}
		cout<<"输入需求序号：";
		cin>>req;
	}
	return 0;
}
