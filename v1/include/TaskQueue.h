#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using std::queue;
using std::mutex;
using std::unique_lock;
using std::condition_variable;
using std::function;

using ElemType = function<void()>;

class TaskQueue
{
public:
    TaskQueue(size_t capa);
    ~TaskQueue();

    //添加任务与获取任务
    void push(ElemType &&task);
    ElemType pop();

    //判空与判满
    bool empty() const;
    bool full() const;

    //将所有等待在_notEmpty条件变量上的线程全部唤醒
    void wakeup();

private:
    size_t _capacity;//任务队列的大小
    queue<ElemType> _que;//存放数据的数据结构
    mutex _mutex;//互斥锁
    condition_variable _notEmpty;//非空条件变量
    condition_variable _notFull;//非满条件变量
    bool _flag;
};

#endif
