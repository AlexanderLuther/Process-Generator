#include "Branch.h"

void Branch::setParentId(int parentId){
    this->parentId = parentId;
}

int Branch::getParentId(){
    return parentId;
}

/**
 * Metodo que crea un proceso Rama.
 */
void Branch::createBranch(sem_t* semaphore){
    this->semaphore = semaphore;
    switch(fork()){
        //Error
        case -1: 
            throw (string)"Error creando un nuevo proceso rama para la planta con id=" + to_string(this->getParentId()); 
        break;
        //Proceso Rama
        case 0: 
            execute(); 
        break;
        //Proceso Tallo
        default:
            pthread_create(&thread, NULL, thread_run, NULL);
        break;
    }
}

/**
 * Hilo para esperar a que el proceso hijo  termine y que este sea removido del planificador
 * para evitar que se convierta en un proceso zombie
 */
void* Branch::thread_run(void* data){ 
    wait(NULL); 
    pthread_exit(data);
}

/**
 * Metodo que llama a la lectura dentro de un espacio de memoria compartida
 */
Command* Branch::read(string name){
    try{
        Command* tempCommand;
        //Entrada Seccion Critica
        sem_wait(semaphore);
        tempCommand = sharedMemoryDriver->read(name);
        sem_post(semaphore);
        //Salida Seccion Critica
        return tempCommand;
    } catch(int error){
        exit(0);
    }
    return nullptr;
}

/**
 * Bucle de ejecucion de la rama
*/
void Branch::execute(){
    while(true){    
        sharedCommand = this->read(to_string(this->getParentId()));
        
        //Verificar si se termina el proceso Rama
        if(sharedCommand->getCommandType() == CREATE_TREE_BRANCH && sharedCommand->getBranchesAmount() == 0){
            exit(0);
        } else if(sharedCommand->getBranchesAmount() < this->getId()){
            exit(0);
        } 

        //Crear Hojas
        if(this->currentLeavesAmount < sharedCommand->getLeavesAmount()){
            for(int i=0; i<(sharedCommand->getLeavesAmount()-this->currentLeavesAmount); i++){
                Leaf* leaf = new Leaf(this->currentLeavesAmount+1);
                leaf->setGrandParentId(this->getParentId());
                leaf->createLeaf(this->semaphore);
                this->currentLeavesAmount++;
            }
        //Eliminar Hojas    
        } else if(this->currentLeavesAmount > sharedCommand->getLeavesAmount()){
            this->currentLeavesAmount = sharedCommand->getLeavesAmount();
        }
        sleep(1);
    }
}
