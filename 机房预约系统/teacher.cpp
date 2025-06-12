#include"teacher.h"
Teacher::Teacher(){
};
Teacher::Teacher(int emp,string name,string pwd){
    this->m_empid = emp;
    this->m_name= name;
    this->m_pwd=pwd;//试一下可不可以这个问题
};
void Teacher::openmenu(){
    cout << "欢迎教师：" << this->m_name << "登录！" << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.查看所有预约         |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.审核预约             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注销登录             |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作：" << endl;
};
void Teacher::showOrder(){
    Orderfile of;
    if(of.m_size==0){
        cout<<"文件为空"<<endl;
        system("pause");
        system("cls");
        return ;
    }
    for(int i=0;i<of.m_size;i++){
        cout<<i+1<<"、";
        cout<<"预约日期: 周"<<of.M[i]["date"]<<" ";
        cout<<"时段:"<<(of.M[i]["interval"]=="1"?"上午":"下午")<<" ";
        cout<<"学号:"<<of.M[i]["stuId"]<<" ";
        cout<<"姓名:"<<of.M[i]["stuName"]<<" ";
        cout<<"机房:"<<of.M[i]["roomId"]<<" ";
        string status = "状态";
        if(of.M[i]["status"]=="1"){
            status += "审核中";
        }
        else if(of.M[i]["status"]=="2"){
            status += "已预约";
        }
        else if(of.M[i]["status"]=="-1"){
            status += "预约失败";
        }
        else{
            status += "预约已取消";
        }
        cout<<status<<endl;
    }
    system("pause");
    system("cls");

};
//审核预约
void Teacher::validOrder(){
    Orderfile of;//创建一个类
    if(of.m_size==0){//无人还清空啥
        cout<<"无预约记录"<<endl;
        system("pause");
        system("cls");
        return ;
    }
    cout<<"待审核预约记录如下"<<endl;
    vector<int>v;//存放在最大容器中的下标编号
    int index=0;//代表编号
    //把i的信息打印出来
    for(int i=0;i<of.m_size;i++)
    {
        if(of.M[i]["status"]=="1"){//把特定的筛选出来 1为审核中
            v.push_back(i);
            cout<<++index<<"、";
            cout<<"预约日期: 周"<<of.M[i]["date"]<<" ";
            cout<<"时段："<<(of.M[i]["interval"]=="1"?"上午":"下午")<<" ";
            cout<<"机房："<<of.M[i]["roomId"]<<" ";
            string status = "状态";
            if(of.M[i]["status"]=="1"){
                status += "审核中";
            }
            cout<<status<<endl;
        }
    }
    cout<<"请输入审核中的预约记录,0代表返回"<<endl;
    int select =0;
    int ret=0;
    while(true){
        cin>>select;
        if(select>=0&&select<=v.size()){
            if(select==0){
                break;
            }
            else {
                cout<<"请输入审核结果"<<endl;
                cout<<"1.通过"<<endl;
                cout<<"2.不通过"<<endl;
                cin>>ret;
                if(ret==1){
                    of.M[v[select-1]]["status"] ="2";
                }
                else{
                    of.M[v[select-1]]["status"] = "-1";
                }
                of.updateFile();
                cout<<"审核完成"<<endl;
                break;
            }
        }
        cout<<"输入有误,请重新输入"<<endl;
    }
    system("pause");
    system("cls");
};