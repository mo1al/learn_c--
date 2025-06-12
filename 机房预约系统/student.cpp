#include"student.h"
Student::Student(){

};
//有参构造 学号 姓名 密码
Student::Student(int id,string name,string pwd){
    //初始化属性
    this->m_id = id;
    this->m_name = name;
    this->m_pwd = pwd;
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
    ifs.close();    
    
};
//菜单界面
void Student::openmenu(){
    cout << "欢迎学生代表：" << this->m_name<< "登录！" << endl;
    cout << "\t\t -----------------------------|\n";
    cout << "\t\t|                             |\n";
    cout << "\t\t|      1.申请预约             |\n";
    cout << "\t\t|                             |\n";
    cout << "\t\t|      2.查看我的预约         |\n";
    cout << "\t\t|                             |\n";
    cout << "\t\t|      3.查看所有预约         |\n";
    cout << "\t\t|                             |\n";
    cout << "\t\t|      4.取消预约             |\n";
    cout << "\t\t|                             |\n";
    cout << "\t\t|      0.注销登录             |\n";
    cout << "\t\t|                             |\n"<<endl;
    cout << "请选择您的操作：" << endl;
};
//申请预约
void Student::applyOrder(){
    cout << "机房开放时间为周一至周五！" << endl;
    cout << "请输入申请预约的时间：" << endl;
    cout << "1、周一" << endl;
    cout << "2、周二" << endl;
    cout << "3、周三" << endl;
    cout << "4、周四" << endl;
    cout << "5、周五" << endl;
    int date=0;//日期
    int interval = 0;//时间段
    int room =0 ;//机房号
    while(true){
        cin>>date;
        if(date>=1&&date<=5){
            break;
        }
        cout<<"输入有误,请重新输入"<<endl;
    }
    cout<<"请输入申请预约的时间段"<<endl;
    cout<<"1.上午"<<endl;
    cout<<"2.下午"<<endl;
    while(true){
        cin>>interval;
        //正确时间段
        if(interval>=1&&interval<=2){
            break;
        }
        cout<<"输入错误,请重新输入"<<endl;
    }
    cout<<"请输入预约的机房号"<<endl;
    //cv 初始化了 放了cr类 读取了文件 0 1放了该有的元素
    for(int i=0;i<cv.size();i++){
        cout<<cv[i].m_comid<<"号机房容量为:"<<cv[i].m_maxnum<<endl;
    }
    while(true){
        cin>>room;
        if(room>=1&&room<=3){
            break;
        }
        cout<<"输入错误,请重新输入"<<endl;
    }
    cout<<"申请预约成功!"<<endl;
    //写入文件当中
    ofstream ofs(ORDER_FILE,ios::app);
    ofs<<"date:"<<date<<" ";
    ofs<<"interval:"<<interval<<" ";
    ofs<<"stuId:"<<this->m_id<<" ";
    ofs<<"stuName:"<<this->m_name<<" ";
    ofs<<"roomId:"<<room<<" ";
    ofs<<"status:"<<1<<endl;//默认审核中
    ofs.close();
    system("pause");
    system("cls");

};
//查看自身预约
void Student::showMyorder(){
    Orderfile of;//创建一个类
    if(of.m_size==0){//无人预约
        cout<<"无预约记录"<<endl;
        system("pause");
        system("cls");
        return ;
    }
    for(int i=0;i<of.m_size;i++){
//.c_str():将C++的std::string 转换为 C 风格字符串（const char*） atoi():将字符串转换为整数
        if(atoi(of.M[i]["stuId"].c_str())==this->m_id){//key与value都是string类型
            cout<<"预约日期: 周"<<of.M[i]["date"]<<" ";
            cout<<"时段："<<(of.M[i]["interval"]=="1"?"上午":"下午")<<" ";//三目运算符
            cout<<"机房："<<of.M[i]["roomId"]<<" ";
            string status = "状态";//0 取消预约的状态 1 审核中 2 已预约 -1预约失败 namespeed
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
    }
    system("pause");
    system("cls");

}
//查看所有预约
void Student::showAllOrder(){
    Orderfile of;//创建一个类
    if(of.m_size==0){//无人预约
        cout<<"无预约记录"<<endl;
        system("pause");
        system("cls");
        return ;
    }
    for(int i=0;i<of.m_size;i++){
        cout<<i+1<<"、";
        cout<<"预约日期: 周"<<of.M[i]["date"]<<" ";
        cout<<"时段:"<<(of.M[i]["interval"]=="1"?"上午":"下午")<<" ";//三目运算符
        cout<<"学号:"<<of.M[i]["stuId"]<<" ";
        cout<<"姓名:"<<of.M[i]["stuName"]<<" ";
        cout<<"机房:"<<of.M[i]["roomId"]<<" ";
        string status = "状态";//0 取消预约的状态 1 审核中 2 已预约 -1预约失败 namespeed
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
//取消预约 取消预约成功或审核中的预约
void Student::cancelOrder(){
    Orderfile of;//创建一个类
    if(of.m_size==0){//无人还清空啥
        cout<<"无预约记录"<<endl;
        system("pause");
        system("cls");
        return ;
    }
    cout<<"审核中或预约成功的记录可以取消,请输入取消的记录"<<endl;//有条件的
    vector<int>v;//存放在最大容器中的下标编号
    int index=1;//代表编号
    //遍历全部人 怎么遍历全部人的？
    for(int i=0;i<of.m_size;i++){
        if(atoi(of.M[i]["stuId"].c_str())==this->m_id){//筛选是不是自身的id 
                if(of.M[i]["status"]=="1"||of.M[i]["status"]=="2"){//筛选status 1|2
                    v.push_back(i);//本人吗
                    cout<<index++<<"、";
                    cout<<"预约日期: 周"<<of.M[i]["date"]<<" ";
                    cout<<"时段："<<(of.M[i]["interval"]=="1"?"上午":"下午")<<" ";
                    cout<<"机房："<<of.M[i]["roomId"]<<" ";
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
            }
 
    }
    cout<<"请输入取消的记录,0代表返回"<<endl;
    int select = 0;
    while(true){
        //单人多条记录
        cin>>select;
        if(select>=0&&select<=v.size()){
            if(select==0){
                break;
            }
            else{
                of.M[v[select-1]]["status"]="0";
                of.updateFile();//更新文件
                cout<<"已取消预约记录"<<endl;
                break;
            }
        }
        cout<<"输入有误,请重新输入"<<endl;
    }
    system("pause");
    system("cls");
};
