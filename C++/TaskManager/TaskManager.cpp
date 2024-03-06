#include "TaskManager.h"
namespace ServiceUtil
{
    struct TaskState
    {
        std::thread* workingThread = nullptr;

        std::function<void()> func;

        std::mutex mutex;

        TaskState(const std::function<void()>& _func)
            :func{_func}
        {

        }

        ~TaskState()
        {
            delete workingThread;
        }
        
        TaskState(const TaskState&) = delete;

        TaskState& operator=(const TaskState&) = delete;

    };

    Task::Task(const std::shared_ptr<TaskState>& state)
        :m_state{state}
        ,m_taskManager{&TaskManager::getInstance()}
    {
        
    }



    void Task::start()
    {
        if (m_state)
        {
            
            m_state->workingThread = new std::thread([this]()
            {
                m_state->func();
                {
                    std::unique_lock<std::mutex> lock(m_taskManager->m_taskHandleMutex);
                    
                    m_taskManager->m_taskHandle.emplace_back(m_state);

                    m_taskManager->m_hasTask = true;

                    m_taskManager->m_notifyCV.notify_all();
                }
            });
        }
    }


    TaskManager& TaskManager::getInstance()
    {
        static TaskManager instance;
        return instance;
    }

    TaskManager::~TaskManager()
    {
        // stop();
    }
    
    void TaskManager::stop()
    {
        m_routineRunningFlag = false;
        {
            std::unique_lock<std::mutex> lock(m_taskHandleMutex);

            m_taskHandle.clear();

            m_hasTask = true;

            m_notifyCV.notify_all();

        }
    }

    Task TaskManager::createTask(const std::function<void()>& function)
    {
        if (function == nullptr)
        {
            return Task(nullptr);
        }

        std::shared_ptr<TaskState> state = std::make_shared<TaskState>(function);

        return Task(state);
    }

    TaskManager::TaskManager()
    {
        m_routineRunningFlag = true;

        m_routineThread = new std::thread(&TaskManager::workingRoutine, this);
    }

    void TaskManager::workingRoutine()
    {
        while(m_routineRunningFlag)
        {
            if (m_taskHandle.empty())
            {
                std::unique_lock<std::mutex> lock(m_taskHandleMutex);
                m_notifyCV.wait(lock,[this](){return m_hasTask;});
            };
            if(!m_routineRunningFlag)
            {
                break;
            } 

            while(!m_taskHandle.empty())
            {
                std::shared_ptr<TaskState> task = m_taskHandle.front();

                m_taskHandle.pop_front();

                if (task->workingThread)
                {
                    task->workingThread->join();
                }

            }

            m_hasTask = false;
        };
            
    }


};
