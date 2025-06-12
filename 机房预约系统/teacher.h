#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include<string>
#include"orderfile.h"//把所有学生信息拿到
#include<vector>
class Teacher:public Identity{
    public:
    Teacher();
    //有参构造
    Teacher(int emp,string name,string pwd);
    //显示菜单
    void openmenu();
    //显示预约记录
    void showOrder();
    //审核预约
    void validOrder();
    int m_empid;//职工号
};