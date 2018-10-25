#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <algorithm>

/*
struct data
{
 std::string str; 
 dev_t st_dev;    
 ino_t st_ino;    
 ushort st_mode;  
 short st_nlink;  
 ushort st_uid;   
 ushort st_gid;   
 dev_t st_rdev;   
 off_t st_size;   
 time_t st_atime; 
 time_t st_mtime; 
 time_t st_ctime; 
}
*/

std::vector <std::string> ls(char *dirname) {
    struct dirent *d;
    struct stat *st;
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

/*int main(int argc, char **argv) {
    dirname = "/home/yaiestura";
    if (argc < 1) {
        printf("Error! No arguments given\n");
        return (EXIT_FAILURE);
    }
    if (argc == 1) {
    } else {
        printf("More than two arguments given\n");
        return (EXIT_FAILURE);
    }
    return 0;
}*/

int main() {
    char *dirname = "/home/yaiestura/University";
    std::vector <std::string> dir;
    dir = ls(dirname);
    return 0;
}