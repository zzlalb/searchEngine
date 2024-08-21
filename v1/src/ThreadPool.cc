#include "../include/ThreadPool.h"
#include <iostream>

using std::cout;
using std::endl;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _threads()
, _queSize(queSize)
, _taskQue(_queSize)
, _isExit(false)
{

}

ThreadPool::~ThreadPool()
{

}

//线程池的启动与停止
void ThreadPool::start()
{
    //需要创建出线程(线程创建出来之后需要执行线程入口函数)
    for(size_t idx = 0; idx != _threadNum; ++idx)
    {
        _threads.push_back(thread(&ThreadPool::doTask, this));
    }
}

void ThreadPool::stop()
{
    //需要保证任务执行完毕之后，主线程才能继续向下执行
    //否则就卡在此处
    while(!_taskQue.empty())
    {
        //让主线程在此处睡眠1s
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    //线程池要退出来了，可以将标志位设置为true
    //然后回收工作线程
    _isExit = true;

    //需要将所有可能在_notEmpty条件变量上的线程唤醒
    /* _notEmpty.notify_all(); */
    _taskQue.wakeup();

    for(auto &th : _threads)
    {
        th.join();//回收子线程
    }
}

//添加任务与获取任务
void ThreadPool::addTask(Task &&task)
{
    if(task)
    {
        _taskQue.push(std::move(task));
    }
}

Task ThreadPool::getTask()
{
    return _taskQue.pop();
}

//线程池交给工作线程执行的任务
void ThreadPool::doTask()
{
    while(!_isExit)
    {
        Task taskcb = getTask();
        if(taskcb)
        {
            //执行任务
            //回调了注册的函数process
            taskcb();//函数对象
        }
        else
        {
            cout << "ptask == nullptr" << endl;
        }
    }
}
