#include "../include/TaskQueue.h"

TaskQueue::TaskQueue(size_t capa)
: _capacity(capa)
, _que()
, _mutex()
, _notEmpty()
, _notFull()
, _flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

//添加任务与获取任务
void TaskQueue::push(ElemType &&task)
{
    unique_lock<mutex> ul(_mutex);

    while(full())
    {
        //上半部:解锁、睡眠
        //下半部:被唤醒、上锁、返回
        _notFull.wait(ul);
    }
    //如果不是满的,就可以生产数据，就可以唤醒消费者线程
    _que.push(std::move(task));
    _notEmpty.notify_one();
}

ElemType TaskQueue::pop()
{
    unique_lock<mutex> ul(_mutex);

    while(empty() && _flag)
    {
        //如果是空的，就睡眠
        _notEmpty.wait(ul);
    }

    if(_flag)
    {
        //如果不空，获取数据，唤醒生产者
        ElemType tmp  = _que.front();
        _que.pop();
        _notFull.notify_one();

        return tmp;
    }
    else
    {
        return nullptr;
    }
}

//判空与判满
bool TaskQueue::empty() const
{
    return 0 == _que.size();
}

bool TaskQueue::full() const
{
    return _capacity == _que.size();
}

//将所有等待在_notEmpty条件变量上的线程全部唤醒
void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notify_all();
}
