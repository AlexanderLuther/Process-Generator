#include "FilesDriver.h"
#define PATH "resources/file.txt"

FilesDriver::FilesDriver(){
}

/**
 * Metodo encargado de verificar la existencia de un archivo.
 * El path del archivo a buscar se encuentra definido en el macro PATH
 * return   true Si se encuentra el archivo.
 *          false Si no se encuentra el archivo.
*/
bool FilesDriver::fileExist(){
    file.open(PATH, ios::in);
    if(file.fail()){
        return false;
    } 
    return true;
}

/**
 * Metodo encargado de obtener los datos contenidos dentro de un archivo.
 * return String con los datos obtenidos. 
*/
void FilesDriver::readFile(vector<string>* data){
    string currentLine;
    while(!file.eof()){
        getline(file,currentLine);
        if(!currentLine.empty())
            data->push_back(currentLine);
    }
    file.close();
}

FilesDriver::~FilesDriver(){
}