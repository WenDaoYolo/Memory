#include "MemoryPool.h"
#include<time.h>
#define TESTNUMS 50000000
double create1,destroy1;
double create2,destroy2;
/********************************TEST2********************************/

class student
{
    public:
        long long id;
        char name[10];
        char sex[7];
        student* next;

        student(const long long& id,const char name[10],const char sex[7])
        {
            this->id=id;
            strcpy(this->name,name);
            strcpy(this->sex,sex);
            this->next=nullptr;
        }
};

FixedSizePool student_pool(sizeof(student));

class student_list
{
    public:
        student* head;
};

void Create1(student_list& list)
{
    clock_t start=clock_t();
    student* tmp=nullptr;
    for(int i=0;i<TESTNUMS;i++)
    {
       tmp=new student(i,"未知","未知");
       tmp->next=list.head;
       list.head=tmp;
    }
    clock_t end=clock();
    create1=(double)end-start;
    
}

void Create2(student_list& list)
{
    clock_t start=clock();
    student* tmp=nullptr;
    for(int i=0;i<TESTNUMS;i++)
    {
       tmp=(student*)(student_pool.allocate_block());
       tmp->next=list.head;
       list.head=tmp;
    }
    clock_t end=clock();
    create2=(double)end-start;
}

void Destroy1(student_list& list)
{
    clock_t start=clock_t();
    student* tmp;
    while(list.head!=nullptr)
    {
        tmp=list.head;
        list.head=tmp->next;
        delete tmp;
    }
    clock_t end=clock();
    destroy1=(double)end-start;
}

void Destroy2(student_list& list)
{
    clock_t start=clock();
    student* tmp;
    while(list.head!=nullptr)
    {
        tmp=list.head;
        list.head=tmp->next;
        student_pool.deallocate_block(tmp);
    }
    student_pool.~FixedSizePool();

    clock_t end=clock();
    destroy2=(double)end-start;   
}

void test1()
{   
    student_list list1;
    student_list list2;
    list1.head=nullptr;
    list2.head=nullptr;

    Create1(list1);
    Create2(list2);

    Destroy1(list1);
    Destroy2(list2);
}

void PrintInformation()
{
    double total_1=create1+destroy1;
    double total_2=create2+destroy2;

    std::cout<<"[测试用例]"<<TESTNUMS<<std::endl;
    std::cout<<"普通方式"<<std::endl;
    std::cout<<"创建耗时:"<<create1<<"ms"<<std::endl;
    std::cout<<"销毁耗时:"<<destroy1<<"ms"<<std::endl;
    std::cout<<"总计耗时:"<<total_1<<"ms"<<std::endl;
    
    std::cout<<"内存池"<<std::endl;
    std::cout<<"创建耗时:"<<create2<<"ms"<<std::endl;
    std::cout<<"销毁耗时:"<<destroy2<<"ms"<<std::endl;
    std::cout<<"总计耗时:"<<total_2<<"ms"<<std::endl;

    std::cout<<"优化提升:%"
    <<std::setprecision(4)<<(total_1-total_2)/total_1*100<<std::endl;
}

int main()
{
    test1();
    PrintInformation();

    return 0;
}