#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include<vector>
#include"computerRoom.h"
#include"globalFile.h"
#include"orderfile.h"
class Student:public Identity{
public:
    Student();
    //有参构造 学号 姓名 密码
    Student(int id,string name,string pwd);
    
    //菜单界面
    void openmenu();
    //申请预约
    void applyOrder();
    //查看自身预约
    void showMyorder();
    //查看所有预约
    void showAllOrder();
    //取消预约
    void cancelOrder();
    vector<computerRoom>cv;//机房容器
    int m_id;//学生学号

};