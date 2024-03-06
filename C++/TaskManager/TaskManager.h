#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include <memory>
#include <functional>
#include <list>
#include <condition_variable>
#include <thread>
namespace ServiceUtil
{
    class TaskManager;

    struct TaskState;

    class Task
    {
        friend class TaskManager;

        public:
            void start();

        protected:
            Task(const std::shared_ptr<TaskState>& state);

        private:
            std::shared_ptr<TaskState> m_state;

            TaskManager*               m_taskManager;
    };

    class TaskManager
    {
        friend class Task;

        protected:
            TaskManager();
        
        public:

            static TaskManager& getInstance();

            ~TaskManager();
            
            Task createTask(const std::function<void()>&);

            void stop();

        private:
            
            void workingRoutine();

        private:

            std::list<std::shared_ptr<TaskState>> m_taskHandle;

            std::mutex                            m_taskHandleMutex;

            std::condition_variable               m_notifyCV;

            std::thread*                          m_routineThread = nullptr;

            bool                                  m_routineRunningFlag = false;

            bool                                  m_hasTask = false;


            

    };
};
#endif //TASK_MANAGER_H