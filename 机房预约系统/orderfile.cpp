#include"orderfile.h"
//构造函数
Orderfile::Orderfile(){
    ifstream ifs(ORDER_FILE,ios::in);
    string date;//日期
    string interval;//时间段
    string stuId;//学生编号
    string stuName;//学生姓名
    string roomId;//机房编号
    string status;//预约状态
    this->m_size = 0;//记录条数
    while(ifs>>date&&ifs>>interval&&ifs>>stuId&&ifs>>stuName&&ifs>>roomId&&ifs>>status){
        // cout<<date<<endl;
        // cout<<interval<<endl;
        // cout<<stuId<<endl;
        // cout<<stuName<<endl;
        // cout<<roomId<<endl;
        // cout<<status<<endl;
        string key;
        string value;
        map<string,string>m;
        //截取数据
        int pos = date.find(":");
        if(pos!=-1){
            key = date.substr(0,pos);
            value = date.substr(pos+1,date.size()-pos-1);
            m.insert(make_pair(key,value));
        }
        pos = interval.find(":");
        if(pos!=-1){
            key = interval.substr(0,pos);
            value = interval.substr(pos+1,interval.size()-pos-1);
            m.insert(make_pair(key,value));
        }
        pos = stuId.find(":");
        if(pos!=-1){
            key = stuId.substr(0,pos);
            value = stuId.substr(pos+1,stuId.size()-pos-1);
            m.insert(make_pair(key,value));
        }
        pos =stuName.find(":");
        if(pos!=-1){
            key = stuName.substr(0,pos);
            value = stuName.substr(pos+1,stuName.size()-pos-1);
            m.insert(make_pair(key,value));
        }
        pos = roomId.find(":");
        if(pos!=-1){
            key = roomId.substr(0,pos);
            value = roomId.substr(pos+1,roomId.size()-pos-1);
            m.insert(make_pair(key,value));
        }
        pos = status.find(":");
        if(pos!=-1){
            key = status.substr(0,pos);
            value = status.substr(pos+1,status.size()-pos-1);
            m.insert(make_pair(key,value));
        } 
        //将小容器放到大容器里面
        this->M.insert(make_pair(this->m_size,m));
        this->m_size++;
    }
    ifs.close();
}
//更新预约记录
void Orderfile::updateFile(){
    if(this->m_size==0){
        return ;//预约记录为0直接退出
    }
    ofstream ofs(ORDER_FILE,ios::out|ios::trunc);//重新创建文件
    for(int i=0;i<this->m_size;i++){
        ofs<<"date:"<<this->M[i]["date"]<<" ";//写入日期
        ofs<<"interval:"<<this->M[i]["interval"]<<" ";//["stuId"] 从该元素中获取键为 "stuId" 的值
        ofs<<"stuId:"<<this->M[i]["stuId"]<<" ";
        ofs<<"stuName:"<<this->M[i]["stuName"]<<" ";
        ofs<<"roomId:"<<this->M[i]["roomId"]<<" ";
        ofs<<"status:"<<this->M[i]["status"]<<endl;
    }
    ofs.close();
}