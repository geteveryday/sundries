#include <iostream>
#include <vector>
#include <iostream>

#include <queue>
#include <unordered_set>
using namespace std;
//首先，写一个页面管理类，分析类的属性和方法有哪些
class Page_manager
{
private:
    int missing_page=0;//记录整个管理周期的缺页的次数
    int**memory;//用于操作内存块，二维数组行为区块序号，列为区块中页面停留时间
    int memory_size;//内存块数量
    vector<int>page_access_sequence;//因为顺序是在0时结束，而不是直接获取个数，所以使用vector更加合适
    int time=0;
public:

    //设置内存块数量
    void set_memory();
    //设计页面访问时序：
    void set_page_visit();
    //FIFO算法函数
    void FIFO_run();
};

int main()
{
    class Page_manager one;
    one.set_memory();
    one.set_page_visit();
    one.FIFO_run();
    return 0;
}


//设置内存块数量
 void Page_manager::set_memory()
{
    cout<<"请输入内存块数量：\n"<<endl;
    cin>>this->memory_size;

   this->memory=new int*[memory_size];
    if (this->memory == NULL)
    {
            cout << "内存分配失败！" << endl;
            exit(1);
    }
    for(int i=0;i<memory_size;i++)
    {
        memory[i]=new int[2];
        if(this->memory[i]==NULL)
        {
            cout<<"内存分配失败！"<<endl;
            exit(2);
        }
    }
    for(int i=0;i<this->memory_size;i++)
    {
        for(int j=0;j<2;++j)
        {
            this->memory[i][j]=0;
        }
    }
}
//设计页面访问时序：
void Page_manager::set_page_visit()
{

    int input=0;
    cout<<"请输入访问时序，插入0截止！"<<endl;
    do
    {
        cin>>input;
        this->page_access_sequence.push_back(input);
    }while(input!=0);

}
//FIFO算法函数
void Page_manager::FIFO_run() {
    // 创建队列以模拟内存中的页面
    queue<int> pages_in_memory;

    // 创建无序集合以记录内存中的页面
    unordered_set<int> in_memory;

    // 遍历页面访问序列
    for (int i = 0; i < this->page_access_sequence.size(); ++i)
    {
        int page = this->page_access_sequence[i]; // 当前访问的页面

        // 如果页面已经在内存中，继续下一次循环
        if (in_memory.find(page) != in_memory.end()) {
            this->time+=1;
            continue;
        }
        // 页面缺失，增加缺页次数
        this->missing_page++;
        this->time+=1;
        // 如果内存已满，执行页面置换
        if (pages_in_memory.size() >= this->memory_size) {
            int victim = pages_in_memory.front(); // 最早进入内存的页面
            pages_in_memory.pop(); // 从内存队列中移除最早进入的页面
            in_memory.erase(victim); // 从内存记录中移除最早进入的页面
        }

        // 将新页面加入内存队列和记录中
        pages_in_memory.push(page);
        in_memory.insert(page);

        // 打印当前内存状态
        cout << "当前内存状态：" << endl;
        int count = 1;

        // 打印内存中的页面
        queue<int> temp_queue = pages_in_memory;
        while (!temp_queue.empty()) {
            cout << "内存块 " << count << ": 页面 " << temp_queue.front() << endl;
            temp_queue.pop();
            count++;
        }

        // 打印缺页次数
        cout<<"时间："<<this->time<<endl;
        cout << "缺页次数：" << this->missing_page << endl;
    }
    double missing=(double)this->missing_page/(double)time;
    cout<<"缺页率"<<missing<<endl;
}


/*页面置换算法->
 *      LRU：最近最久未使用
 *      FIFO：先进先出
 *      OPT：最佳置换
 * 页面置换原理：当进程运行时，如果需要访问某个页面时，需要在内存里面访问，而不是在磁盘或者其他存储设备上访问，
 * 但是内存空间是有限的，所以当我们调用某个不在内存的页面时，就需要置换之前某个页面，删除页面就会引起缺页，而且
 * 删除哪一个也需要考虑，于是就有了这些算法去管理页面置换算法。
 *比如有三个物理内存块，就可以同时存储3个不同的页面，如果页面超过了3个，就要考虑进行置换
 */

/*下面是来自GPT的扩展说明：
 *
 *
页面置换算法是计算机操作系统中用于管理虚拟内存的一种算法。它们用于确定哪些页面应保留在内存中，
哪些页面应该被置换（换出到磁盘或其他存储设备），以便有效地利用有限的物理内存空间。

当系统需要访问一个页面，但该页面不在内存中时，就会发生缺页中断。页面置换算法决定了要将哪
些页面从内存中移出，以便为新页面腾出空间。

常见的页面置换算法包括：

先进先出（FIFO）：最早进入内存的页面被置换出去。
最近最少使用（LRU）：最近最少被使用的页面被置换出去。
最少使用（LFU）：最少被使用次数的页面被置换出去。
时钟算法（Clock）：根据页面是否被访问过来进行替换。
最佳置换算法（OPT）：根据未来最长时间内不被访问的页面进行置换，理想情况下。
每种算法都有其优点和缺点，适用于不同类型的工作负载和系统环境。选择合适的页面置换算法可以
在有限的内存资源下最大限度地提高系统性能。

*
*
*
什么是缺页，为什么缺页缺页的坏处是什么
ChatGPT
在虚拟内存管理中，当程序需要访问某个页面但该页面当前不在物理内存中时，就会发生缺页中断。这意味着所需的
页面必须从磁盘或其他辅助存储设备加载到内存中，以便程序可以继续执行。这个过程涉及较长的IO操作，会导致程
序暂停执行，直到缺页中断处理完成，需要的页面加载到内存中。

缺页的坏处主要体现在性能上：

延迟和响应时间增加：当发生缺页时，CPU必须等待所需页面加载到内存，这会导致程序暂停执行，增加了整体执
行时间，降低了系统响应速度。

系统开销增加：频繁的缺页意味着需要不断地从磁盘加载页面到内存中，这会增加IO操作和系统开销，降低系统整体性能。

可能引起磁盘IO瓶颈：如果缺页次数过多，系统频繁地从磁盘读取数据，可能导致磁盘IO成为系统的瓶颈，限制了整体性能。

为了减少缺页带来的影响，操作系统采用了虚拟内存技术和页面置换算法，以尽量减少缺页次数，提高系统的性能和响应速度
。优化页面置换算法和合理管理内存是减少缺页带来负面影响的重要方式。

User
缺页的好处呢
ChatGPT
缺页在一定程度上也具有一些好处，尤其是在虚拟内存系统中：

更大的可用内存空间： 虚拟内存系统使得可以使用比物理内存更大的地址空间。当程序运行时，不是所有的代码和数
据都需要同时存在于内存中。缺页机制允许系统根据需要动态地将数据从磁盘加载到内存中，从而扩展了可用的内存空间。

更高的程序并发性： 虚拟内存系统允许多个程序共享有限的物理内存。因为不是所有程序的所有部分都需要同时存在于
内存中，虚拟内存可以根据需要为不同的程序分配内存，从而增加了程序并发执行的可能性。

更好的内存管理： 缺页机制使得内存管理更加灵活。系统可以根据程序需求和访问模式，动态地将数据从磁盘加载
到内存中，同时根据页面置换算法决定哪些页面需要置换出去，从而更好地管理内存资源。

虽然缺页会导致性能上的一些损失，但虚拟内存系统的设计使得它成为一种权衡，在可用性和性能之间取得平衡。缺页
的机制允许系统更高效地管理内存资源，提供更大的地址空间，以适应现代计算机系统对内存需求的不断增长。
*/
