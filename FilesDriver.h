#ifndef FILESDRIVER_H
#define FILESDRIVER_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

class FilesDriver{

    private:
        ifstream file;
        
    public:
        FilesDriver();
        bool fileExist();
        void readFile(vector<string>* data);
        ~FilesDriver();
};

#endif // FILESDRIVER_H