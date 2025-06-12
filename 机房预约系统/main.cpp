#include<iostream>
using namespace std;
#include"identity.h"
#include<fstream>
#include"student.h"
#include"globalFile.h"
#include<string>
#include"manager.h"
#include"teacher.h"
//进入学生界面
void teacherMenu(Identity*&teacher){
    while(true){
        Teacher*tea = (Teacher*)teacher;
        tea ->openmenu();
        int select = 0;
        cin>>select;
        if(select==1){
            //查看所有预约
            tea->showOrder();
        }
        else if(select==2){
            //审核成功
            tea->validOrder();
        }
        else{
            delete teacher;
            cout<<"注销成功"<<endl;
            system("pause");
            system("cls");
            return ; 
        }
    }
}
//进入学生菜单界面
void studentMenu(Identity*&student){
    while(true){
        Student * stu = (Student*)student;
        student->openmenu();
        int select =0;
        cin>>select;
        if(select==1){
            stu->applyOrder();
        }
        else if(select==2){
            stu->showMyorder();
        }
        else if(select==3){
            stu->showAllOrder();
        }
        else if(select==4){
            stu->cancelOrder();
        }
        else{
            delete student ;
            cout<<"注销成功"<<endl;
            system("pause");
            system("cls");
            return ;
        }
    }
}
//进入管理员子菜单界面
void managerMenu(Identity*&manager){
    while(true){
        //管理员菜单
        Manager*man = (Manager*)manager;//有点难想啊
        manager->openmenu();//?????????
        int select =0;
        cin>>select; 
        if(select ==1){//添加账号
            // cout<<"添加账号"<<endl;
            man->addPerson();
        }
        else if(select==2){
            // cout<<"查看账号"<<endl;
            man->showPerson();
        }
        else if(select==3){//查看机房
            // cout<<"查看机房"<<endl;
            man->showComouter();
            }
        else if(select==4){//清空预约
            // cout<<"清空预约"<<endl;
            man->clearRecord();
        }    
        else{
            delete manager;
            cout<<"注销成功"<<endl;
            system("pause");
            system("cls");
            return ;
        }

    }
}
//登录功能 操作文件名称 操作身份类型
void LoginIn(string fileName,int type){
    //父类指针 用于指向子类对象
     Identity* person = nullptr;
    //读文件
    ifstream ifs(fileName,ios::in);
    //判断文件是否存在
    if(!ifs.is_open()){
        cout<<"文件不存在"<<endl;
        ifs.close();
        return;
    }
    //准备接受文件信息
    int id=0;
    string name;
    string pwd;
    //判断身份
    if(type==1){//学生
        cout<<"请输入你的学号"<<endl;
        cin>>id;
    } 
    else if(type==2){//老师
        cout<<"请输入你的职工号"<<endl;
        cin>>id;
    }
    cout<<"请输入你的用户名"<<endl;
    cin>>name;
    
    cout<<"请输入你的密码"<<endl;
    cin>>pwd;
    //开始验证
    if(type==1){//学生身份验证
        int fid;
        string fname;
        string fpwd;
        while(ifs>>fid&&ifs>>fname&&ifs>>fpwd){
            if(fid==id&&fname==name&&fpwd==pwd){
                cout<<"学生登陆成功"<<endl;
                system("pause");
                system("cls");
                person = new Student(id,name,pwd);
                //进入学生身份的子菜单
                studentMenu(person);
                return;
            }
        }
    }
    else if(type==2){
        int fid;
        string fname;
        string fpwd;
        while(ifs>>fid&&ifs>>fname&&ifs>>fpwd){
            cout<<"老师登录成功"<<endl;
            system("pause");
            system("cls");
            person =new Teacher(id,name,pwd);
            //进入老师端
            teacherMenu(person);
            return ;
        }
    }
    else if(type==3){//管理员身份验证
        string fname;
        string fpwd;
        while(ifs>>fname&&ifs>>fpwd){
            cout<<"管理员登录成功"<<endl;
            system("pause");
            system("cls");
            person = new Manager(name,pwd);//new出来会自动初始化
            managerMenu(person);
            return;
        }
    }
    //其它的情况
    cout<<"输入错误,请重新输入"<<endl;
    system("pause");
    system("cls");
    return ;

}
int main() {
    int select=0;
    while(true){
        cout << "========================================欢迎来到传智播客机房预约系统========================================"
        <<endl; 
        cout<<endl<< "请输入您的身份" << endl;
        cout << "\t\t-----------------------------\n";
        cout << "\t\t|                              |\n";
        cout << "\t\t|         1.学生代表            |\n";
        cout << "\t\t|                              |\n";
        cout << "\t\t|          2.老师              |\n";
        cout << "\t\t|                              |\n";
        cout << "\t\t|         3.管理员              |\n";
        cout << "\t\t|                              |\n";
        cout << "\t\t|         0.退出               |\n";
        cout << "\t\t|                              |\n";
        cout << "\t\t--------------------------------\n";
        cout << "输入您的选择:";
        cout<<"  "<<endl;
        cin>>select;
        switch(select){
            case 1://学生
                LoginIn(STUDENT_FILE,1);
                break;
            case 2://老师
                LoginIn(TEACHER_FILE,2);
                break;
            case 3://管理员
                LoginIn(ADMIN_FILE,3);
                break;
            case 0://退出系统
                cout<<"欢迎下次使用"<<endl;
                system("pause");
                return 0;

            default:
                cout<<"输入有误,请重新选择"<<endl;
                system("pause");
                system("cls");
                break;//return 0 是退出编译 break还可以重新进入循环
        }
    }
    system("pause");
    return 0;
}
