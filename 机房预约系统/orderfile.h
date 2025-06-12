#pragma once
#include<iostream>
using namespace std;
#include<map>
#include"globalFile.h"
#include<fstream>
#include<string>
class Orderfile{
    public:
    //构造函数
    Orderfile();
    //更新文件
    void updateFile();
    //记录预约条数
    int m_size;
    //文件的第几个map 和记录的信息
    map<int,map<string,string>>M;

};