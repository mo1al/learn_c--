#include"manager.h"
#include"student.h" 
#include"teacher.h"
#include"globalFile.h"
#include<vector>
#include<algorithm>
#include<string>
#include <type_traits>

Manager::Manager(){

};
//有参构造
Manager::Manager(string name,string pwd){
    this->m_name = name;
    this->m_pwd = pwd;
    //初始化容器
    this->initVector();
    //
    cv.clear();
    ifstream ifs(COMPUTER_FILE,ios::in);//文件打不开的情况
    computerRoom cr;
    if (!ifs.is_open()) {
        cout<< "无法打开文件: "<< endl;
        return ;
    }
    while(ifs>>cr.m_comid&&ifs>>cr.m_maxnum){
        cv.push_back(cr);
    }
    cout<<"当前机房数量为:"<<cv.size()<<endl;
    ifs.close();
};
//展示菜单
void Manager::openmenu(){
    cout << "欢迎管理员:" << this->m_name << "登录!" << endl;  // 显示欢迎信息（管理员名字存储在 m_Name）
    cout << "\t\t--------------------\n";
    cout << "\t\t|                  |\n";
    cout << "\t\t|  1.添加账号      |\n";  // 选项1：添加账号
    cout << "\t\t|                  |\n";
    cout << "\t\t|  2.查看账号      |\n";  // 选项2：查看账号
    cout << "\t\t|                  |\n";
    cout << "\t\t|  3.查看机房      |\n";  // 选项3：查看机房
    cout << "\t\t|                  |\n";
    cout << "\t\t|  4.清空预约      |\n";  // 选项4：清空预约
    cout << "\t\t|                  |\n";
    cout << "\t\t|  0.注销登录      |\n";  // 选项0：注销登录
    cout << "\t\t|                  |\n";
    cout << "\t\t--------------------\n";
    cout << "请选择您的操作: " << endl;  // 提示用户输入选择
};
//添加账号 把写的写进文件里 注意补充去重操作 cheatRepate&&initVector共同使用在此
//有个bug 就是打开系统 加两个相同id不会报错 不会及时更新 怎么解决呢?
void Manager::addPerson(){
    cout << "请输入添加账号的类型" << endl;
    cout << "1. 添加学生" << endl;
    cout << "2. 添加老师" << endl;
    string filename;//简易操作
    string tip;//提示符
    string errortip;
    int select;
    ofstream ofs;
    cin>>select;
    if(select==1){
        filename = STUDENT_FILE;//这样操作就会写入轻松多了
        tip = "请输入添加人的学号";
        errortip = "学号重复,请重新输入";
    }
    else if(select==2){
        filename = TEACHER_FILE;
        tip = "请输入添加人的职工号";
        errortip = "学号重复,请重新输入";
    }
    else{
        cout<<"输入错误"<<endl;
        system("pause");
        system("cls");
        addPerson();//      return;
    }
    ofs.open(filename,ios::out|ios::app);//写入形式追加进文件
    int id;
    string name;
    string pwd;
    cout<<tip<<endl;
    //加入循环判断
    while(true){
        cin>>id;
        bool ret = this->checkRepeat(id,select);
        if(ret==true){
            cout<<errortip<<endl;
        }
        else{
            break;
        }
    }
    cout<<"请输入姓名"<<endl;
    cin>>name;
    cout<<"请输入密码"<<endl;
    cin>>pwd;
    ofs<<id<<" "<<name<<" "<<pwd;
    system("pause");
    system("cls");
    ofs.close();
    //解决bug
    //initVector清空容器、读取文件数据
    this->initVector();
};
void Manager::initVector(){
    //读取学生文件
    ifstream ifs(STUDENT_FILE,ios::in);
    //判断文件
    if(!ifs.is_open()){
        cout<<"文件读取失败"<<endl;
        return ;
    }
    //清空容器 也可以放最上面
    sv.clear();
    tv.clear();
    //创建学生类
    Student s;
    //ifs拿到信息
    while(ifs>>s.m_id&&ifs>>s.m_name&&ifs>>s.m_pwd){
        sv.push_back(s);//存储student
    }
    cout<<"当前学生数量为:"<<sv.size()<<endl;//没弄明白????
    ifs.close();
    //完成学生初始化
    //同理拿到老师的信息
    ifs.open(TEACHER_FILE,ios::in);
    if(!ifs.is_open()){
        cout<<"文件读取失败"<<endl;
        return;
    }
    //容器读取信息
    Teacher t;
    while(ifs>>t.m_empid&&ifs>>t.m_name&&ifs>>t.m_pwd){
        tv.push_back(t);
    }
    cout<<"当前老师数量为:"<<tv.size()<<endl;//没弄明白????
    ifs.close();
}
bool Manager::checkRepeat(int id,int type){//select对应判断是老师还是学生
    if(type==1){
        //遍历数组
        for(vector<Student>::iterator it=sv.begin();it!=sv.end();it++){
            if(id==(*it).m_id){//(*it)???????? ::::= it->   其实就是一个类
                return true;//重复了
            }
        }
    }
    //检测老师
    else{   
        for(vector<Teacher>::iterator it=tv.begin();it!=tv.end();it++){
            if(id==it->m_empid){
                return true;
            }
        }
    }
    return false;
}
//怎么写成一个函数呢 ????写不出.....
void printStudent(Student & s)
{
    cout << "学号: " << s.m_id << " 姓名: " << s.m_name << " 密码: " << s.m_pwd << endl;
}

void printTeacher(Teacher & t)
{
    cout << "职工号: " << t.m_empid << " 姓名: " << t.m_name << " 密码: " << t.m_pwd << endl;
}

//查看账号 包括 id name password
void Manager::showPerson(){
    cout<<"请选择查看内容"<<endl;
    cout<<"1.查看所有学生"<<endl;
    cout<<"2.查看所有教师"<<endl;
    int select =0;
    cin>>select;
    if(select==1){
        cout<<"学生信息如下"<<endl;
        for_each(sv.begin(),sv.end(),printStudent);//遍历algorithm算法
    }
    else{
        cout<<"教师信息如下"<<endl;
        for_each(tv.begin(),tv.end(),printTeacher);
    }
    system("pause");
    system("cls");
};
void printComputer(computerRoom&c){
    cout<<"机房号:"<<c.m_comid<<"机房数量:"<<c.m_maxnum<<endl;
}
//查看机房信息
void Manager::showComouter(){
    //cv容器有东西了
    cout<<"机房信息如下"<<endl;
    for_each(cv.begin(),cv.end(),printComputer);
    system("pause");
    system("cls");
};
//清空预约记录
void Manager::clearRecord(){
    ofstream ofs(ORDER_FILE,  ios::trunc);//存在的话就要删干净
    ofs.close();
    cout<<"清空成功"<<endl;
    system("pause");
    system("cls");
};