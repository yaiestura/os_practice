#include <sys/types.h>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <algorithm>

std::vector <std::string> ls(char *dirname) {
    struct dirent *d;
    DIR *dp;
    std::vector <std::string> files;
       
    dp = opendir(dirname);
    if((dp == NULL)) {
        printf("%s\n","Error! A directory can not be opened.");
        exit(0);
    }
    
    while(d = readdir(dp))
    {
        if(d->d_ino != 0 && d->d_type != DT_DIR) {
            std::string str = std::string(d->d_name);
            files.push_back(str);
        }        
    }

    closedir(dp);
    std::sort(files.begin(), files.end());
    for (auto i = files.begin(); i != files.end(); i++)
    std::cout << *i <<std::endl;
    return files;
    }

int main() {
    char *dirname = "/home/yaiestura";
    std::vector <std::string> dir;
    dir = ls(dirname);
    return 0;
}