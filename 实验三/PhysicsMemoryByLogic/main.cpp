/*
 *  @仅供学习使用，转载请注明来源！
 *  @日期    2023-11-28
 *  @作者   谢领
 *  @联系方式 QQ:2953667569
 */
/*本代码为通过逻辑地址寻找物理地址的学习代码
 * 代码风格为C++风格
 * 页面大小为1KB
 * 逻辑地址分配如下表（依次为0到63页号分配的块号）
 * 0,42,29,15,45,31,44,43,
 * 41,28,1,30,12,24,6,32,
 * 14,27,13,46,7,33,10,22,
 * 40,2,51,11,39,23,49,50,
 * 26,16,25,4,47,17,3,48,
 * 52,36,58,35,57,34,21,63,
 * 5,37,18,8,62,56,20,54,
 * 60,19,38,9,61,55,59,53.
 * 基本公式：
 *          页号=逻辑地址/页面大小（取整舍余）
 *          物理地址=逻辑地址-页号*页面大小+块号*页面大小
 *          页内地址=逻辑地址-页号*页面大小
 *          块号地址=块号*页面大小
*/
#include <iostream>
#include <iomanip> // 包含用于输出十六进制的头文件
#include<sstream>

using namespace std;

// 创建一个物理地址类
class physics_adders
{
private:
    int logical_address; // 逻辑地址
    const int page_size = 1024; // 页面大小 1kb=1024bit
    int page_number; // 页号
    int offset; // 页内地址
    int block_number; // 块号
    int physics_adder; // 物理地址

public:
    void input_logical_address(); // 获取逻辑地址函数
    void work_out(); // 推算数据函数
    void output_physics_adders(); // 输出物理地址函数
    void show_every(); // 打印全部的函数
};

// 创建页号对照表数组
const int logic_to_physics[64] =
{ // 在程序运行过程中，此量不会更改，则使用const定义为只读变量,即常量
    0, 42, 29, 15, 45, 31, 44, 43,
    41, 28, 1, 30, 12, 24, 6, 32,
    14, 27, 13, 46, 7, 33, 10, 22,
    40, 2, 51, 11, 39, 23, 49, 50,
    26, 16, 25, 4, 47, 17, 3, 48,
    52, 36, 58, 35, 57, 34, 21, 63,
    5, 37, 18, 8, 62, 56, 20, 54,
    60, 19, 38, 9, 61, 55, 59, 53
};

int main()
{
    class physics_adders one;
    one.input_logical_address();
    one.work_out();
    one.output_physics_adders();

    return 0;
}

// 函数定义

// 获取逻辑地址函数
void physics_adders::input_logical_address()
{
    cout << "Please enter the logical address (in either decimal or hexadecimal): " << endl;
    string input;
    cin >> input;

    // 用 stringstream 处理不同进制的输入
    stringstream ss(input);

    // 检查输入是否以 "0x" 开头，确定输入格式
    if (input.substr(0, 2) == "0x") {
        ss >> hex >> this->logical_address; // 以十六进制读取输入
    } else {
        ss >> this->logical_address; // 以十进制读取输入
    }
}

// 推算数据函数
void physics_adders::work_out()
{
    this->page_number = this->logical_address / this->page_size; // 求页号
    this->offset = this->logical_address % this->page_size; // 求页内地址
    this->block_number = logic_to_physics[page_number]; // 求块号
    this->physics_adder = this->offset + this->block_number * this->page_size; // 求物理地址
}

// 输出物理地址函数
void physics_adders::output_physics_adders()
{
    cout << "Physics address is: " << this->physics_adder << endl; // 以十进制输出物理地址
}

// 打印全部的函数
void physics_adders::show_every()
{
    cout << "Logical Address: " << this->logical_address << endl;
    cout << "Page Size: " << this->page_size << endl;
    cout << "Page Number: " << this->page_number << endl;
    cout << "Offset: " << this->offset << endl;
    cout << "Block Number: " << this->block_number << endl;
    cout << "Physics Address: " << this->physics_adder << endl;
}

