#ifndef LEAF_H
#define LEAF_H
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


class Leaf : public Process{

    private:
        SharedMemoryDriver* sharedMemoryDriver = new SharedMemoryDriver();
        Command* sharedCommand;
        int grandParentId;
        pthread_t thread; 

        //Semaforo
        sem_t *semaphore;
 
    private:
        Command* read(string name);
        void execute();
        static void* thread_run(void* data);

    public:
        Leaf(int id) : Process(id){};
        void createLeaf(sem_t* semaphore);
        void setGrandParentId(int grandParentId);
        int getGrandParentId();
        
};

#endif // LEAF_H