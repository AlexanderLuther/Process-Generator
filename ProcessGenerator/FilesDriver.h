#ifndef FILESDRIVER_H
#define FILESDRIVER_H
#define READ_PATH "resources/input.txt"
#define WRITE_PATH "resources/output.txt"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

class FilesDriver{
        
    public:
        FilesDriver();
        bool fileExist();
        void readFile(vector<string>* data, string path);
        void writeFile(string data, string path);
        ~FilesDriver();
};

#endif // FILESDRIVER_H
