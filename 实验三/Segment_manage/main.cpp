/*!
 *  @仅供学习使用，转载请注明来源！
 *  @日期    2023-11-28
 *  @作者   谢领
 *  @联系方式 QQ:2953667569
 */

#include <iostream>
#define KB 1024

using namespace std;
//物理地址类
class physics_adders
{
private:

    int segment;//段号
    int offset; //段内地址
    int physics_adder; // 物理地址

public:
    void input_logical_address(); // 获取逻辑地址函数
    void work_out(); // 推算数据函数
    void output_physics_adders(); // 输出物理地址函数

};
//创建段表二维数组
const int logic_to_physics[5][3]=//分别是段号，起始地址，段长
{
{0,50,10},
{1,60,3},
{2,70,5},
{3,120,8},
{4,150,4}
};
int main()
{
    class physics_adders one;
    one.input_logical_address();
    one.work_out();
    one.output_physics_adders();
    return 0;
}
void physics_adders::input_logical_address()// 获取逻辑地址函数
{
    printf("enter duanhao and duannei address\n");
    cin>>this->segment;//段号
    cin>>this->offset;//段内地址


}
void physics_adders::work_out()// 推算数据函数
{
    if(this->segment<0||this->segment>4)
    {
        cout<<"溢出中断！"<<endl;
        exit(1);
    }
    else if(this->offset>KB*logic_to_physics[segment][2])
    {
        cout<<"溢出中断！"<<endl;
        exit(1);
    }
    else
    {
        this->physics_adder=logic_to_physics[segment][1]*KB+this->offset;
    }
}
void physics_adders::output_physics_adders()// 输出物理地址函数
{
        cout << "Physics address is: " << this->physics_adder << endl;
}


