#ifndef BRANCH_H
#define BRANCH_H
#include <unistd.h>
#include <sys/types.h>      
#include <sys/shm.h>    
#include <sys/wait.h>            
#include <semaphore.h>      
#include <fcntl.h> 
#include <pthread.h>
#include "Process.h"
#include "Command.h"
#include "SharedMemoryDriver.h"
#include "Leaf.h"

class Branch : public Process{

    private:
        SharedMemoryDriver* sharedMemoryDriver = new SharedMemoryDriver();
        Command* sharedCommand;
        int currentLeavesAmount = 0;
        int parentId;
        pthread_t thread; 

        //Semaforo
        sem_t *semaphore;
 
    private:
        Command* read(string name);
        void execute();
        static void* thread_run(void* data);

    public:
        Branch(int id) : Process(id){};
        void createBranch(sem_t* semaphore);
        void setParentId(int parentId);
        int getParentId();
        
};

#endif // BRANCH_H