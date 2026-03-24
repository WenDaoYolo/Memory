#include "MemoryPool.h"
/********************************TEST1********************************/

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

        void* operator new[](const size_t size);
        void* operator new(const size_t size);
        void operator delete[](void* block);
        void operator delete(void* block);
};

/**************为了方便使用类对象建议重写new和delete操作符**************/
FixedSizePool student_pool(sizeof(student));

void* student::operator new[](const size_t size)
{
    return (student*)(student_pool.allocate_block());
}

void* student::operator new(const size_t size)
{
    return (student*)(student_pool.allocate_block());
}

void student::operator delete[](void* block)
{
    student_pool.deallocate_block(block);
}

void student::operator delete(void* block)
{
    student_pool.deallocate_block(block);
}

class student_list
{
    public:
        student* head;
};

/********************************************************************/
void Create(student_list& list)
{
    student* tmp=nullptr;
    for(int i=0;i<20;i++)
    {
       tmp=new student(rand()%100+i,"未知","未知");
       tmp->next=list.head;
       list.head=tmp;
    }
}

void Print(student_list& list)
{
    student* find=list.head;
    std::cout
    <<std::setw(10)<<std::left<<"ID"
    <<std::setw(10)<<std::left<<"姓名"
    <<std::setw(10)<<std::left<<"性别"
    <<std::endl;

    while(find!=nullptr)
    {
        std::cout
        <<std::setw(10)<<std::left<<find->id
        <<std::setw(10)<<std::left<<find->name
        <<std::setw(10)<<std::left<<find->sex
        <<std::endl;
        
        find=find->next;
    }
}

void Destroy(student_list& list)
{
    student* tmp;
    while(list.head!=nullptr)
    {
        tmp=list.head;
        list.head=tmp->next;
        delete tmp;
    }
}

void test1()
{   
    student_list list;
    list.head=nullptr;

    Create(list);
    Print(list);
    student_pool.PoolInformaton();
    Destroy(list);
}

int main()
{
    test1();

    return 0;
}