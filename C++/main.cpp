// Online C++ compiler to run C++ program online
#include <iostream>

class Listener
{
    public:
        virtual void listen() = 0;
};

class A: public Listener
{
    public:
        void listen() override
        {
            
        }
};

class A: public Listener
{
    public:
        void listen() override
        {
            
        }
};

class Observant
{
    public:
        void addListener(Listener* listener)
        {
            m_lisntener.push_back(listener);
        }
    private:
        std:;vector<Listener*> m_lisntener
    
};


int main() {
    Singleton* sing = Singleton::getInstance();
    Singleton* sing1 = Singleton::getInstance();
    sing->getMessage();
}