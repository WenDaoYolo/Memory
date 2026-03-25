#include<iostream>
using namespace std;

struct ttt{         //无默认对齐数
    int a;          //0~3
    char b;         //4
    double c;       //5~7对齐填充，8~15
    short d;        //16~17，18~23对齐填充
};                  //总大小24

#pragma pack(2)
struct sss{         //默认对齐数2
    int a;          //0~3
    char b;         //4
    double c;       //5对齐填充，6~13
    short d;        //14~15
};                  //总大小16
#pragma pack()

int main()
{
    cout<<sizeof(ttt)<<endl;
    cout<<sizeof(sss)<<endl;
    return 0;
}