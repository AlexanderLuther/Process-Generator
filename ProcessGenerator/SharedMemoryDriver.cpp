#include "SharedMemoryDriver.h"

SharedMemoryDriver::SharedMemoryDriver(){}

/**
 * Metodo encargado de crear un espacio de memoria compartida.
 * El nombre del espacio de memoria compartida se recibe como parametro.
 * Si existe algun  error durante  el proceso se  lanza  una  excepcion.
 * @brief SharedMemoryDriver::create
 * @param name
 */
void SharedMemoryDriver::create(string name){
    fileDescriptor = shm_open(name.c_str(), O_CREAT | O_RDWR,  00600);
    switch(fileDescriptor){
        case -1:
            close(fileDescriptor);
            throw 0;
        break;

        default:
            if(ftruncate(fileDescriptor, SHARE_MEMORY_OBJECT_SIZE) == -1){
                close(fileDescriptor);
                throw 1;
            }
            close(fileDescriptor);
        break;
    }
}

/**
 * Metodo que se encarga de escribir en un espacio de memoria compartida;
 * El nombre del espacio de memoria compartida se recibe como parametro.
 * El buffer de datos a escribir se recibe como parametro. Se escriben los
 * datos de una instancia de la clase Command.
 */
void SharedMemoryDriver::write(string name, Command* buffer){        
    fileDescriptor = shm_open(name.c_str(), O_RDWR, 0);
    switch (fileDescriptor){
        case -1:
            close(fileDescriptor);
            throw 0;
        break;
    
        default:
            command = static_cast<Command*>(mmap(NULL, sizeof(buffer), PROT_WRITE, MAP_SHARED, fileDescriptor, 0));
            if(command == MAP_FAILED){
                close(fileDescriptor);
                throw 1;
            }
            memcpy(command, buffer, SHARE_MEMORY_OBJECT_SIZE);
            close(fileDescriptor);
        break;
    }
}

/**
 * Metodo que se encarga de leer  un espacio de memoria compartida;
 * El nombre del espacio de memoria compartida se recibe como parametro.
 * Los datos leidos se almacenan en una instancia de la clase Command. 
 * Se retorna la instancia de la clase Command.
 */
Command* SharedMemoryDriver::read(string name){
    fileDescriptor = shm_open(name.c_str(), O_RDONLY, 0);
    switch(fileDescriptor){
        case -1:
            close(fileDescriptor);
            throw 0;
        break;

        default:
            if(fstat(fileDescriptor, &sharedMemoryObject) == -1){
                close(fileDescriptor);
                throw 1;
            } 
            command = static_cast<Command*>(mmap(NULL, sharedMemoryObject.st_size, PROT_READ, MAP_SHARED, fileDescriptor, 0));
            if(command == MAP_FAILED){
                close(fileDescriptor);
                throw 2;
            }
            close(fileDescriptor);
            return command;
        break;
    }
    return nullptr;
}

/**
 * Metodo que borra un espacio de memoria compartida.
 * El nombre del espacio de memoria compartida se recibe como parametro.
 * Todos los espacios de memoria compartida se encuentran en /dev/shm/
 */
void SharedMemoryDriver::remove(string name){
    system(("rm /dev/shm/" + name).c_str());
}
    
