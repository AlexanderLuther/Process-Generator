#include "FilesDriver.h"

FilesDriver::FilesDriver(){
}

/**
 * Metodo encargado de verificar la existencia de un archivo.
 * El path del archivo a buscar se encuentra definido en el macro PATH
 * return   true Si se encuentra el archivo.
 *          false Si no se encuentra el archivo.
*/
bool FilesDriver::fileExist(){
    ifstream file;
    file.open(READ_PATH, ios::in);
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
    ifstream file;  
    file.open(READ_PATH, ios::in);
    string currentLine;
    while(!file.eof()){
        getline(file,currentLine);
        if(!currentLine.empty())
            data->push_back(currentLine);
    }
    file.close();
}

/**
 * Metodo encargado de escribir datos dentro de un archivo de texto.
 */ 
void FilesDriver::writeFile(string PID){
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    //cmd.append(" 2>&1");

    stream = popen(("pstree " + PID).c_str(), "r");
    if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
    }

    ofstream file(WRITE_PATH);
    file << data;
    file.close();
}


FilesDriver::~FilesDriver(){
}