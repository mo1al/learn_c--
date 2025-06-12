#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include<vector>
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"
class Manager:public Identity{
    public:
    Manager();
    //有参构造
    Manager(string name,string pwd);
    //展示菜单
    void openmenu();
    //添加账号
    void addPerson();
    //初始化容器
    void initVector();
    //学生容器
    vector<Student>sv;
    //老师容器
    vector<Teacher>tv;
    vector<computerRoom>cv;
    //去重函数封装
    bool checkRepeat(int id,int type);//type???????
    
    //查看账号
    void showPerson();
    //显示机房信息
    void showComouter();
    //清空预约记录
    void clearRecord();
};