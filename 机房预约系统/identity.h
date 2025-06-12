#pragma once
#include<iostream>
using namespace std;
#include<fstream>
//身份抽象类
class Identity{
    public:
    //各自操作菜单 纯虚函数
    virtual void openmenu() =0;
    string m_name;//用户名
    string m_pwd;//password
};