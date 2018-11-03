Implementing C++ Program proccessing UNIX file system during OS Course Syllabus.

## Stat Structure

In order to fetch some data about type of file, you should use system calls stat(), or fstat(). 
Such system calls are declared in these header files:

```cpp
#include <sys/types.h>
#include <sys/stat.h>
```
Both system calls put information about file(in first case, the specified name, and in second, with a file descriptor fd) into a structure variable, on which stbuf is pointed. The calling function must take care of reserving space for the returned information; if successful, returns 0, otherwise -1 and an error code in errno.

```cpp
int stat(const char *name, struct stat *stbuf);
int fstat(int fd, struct stat *stbuf); 
```
The stat structure is described in the ```sys/stat.h``` header file.

```cpp
struct stat
{
 dev_t st_dev;    /* device file */
 ino_t st_ino;    /* file serial inode */
 ushort st_mode;  /* file mode */
 short st_nlink;  /* number of links */
 ushort st_uid;   /* user ID */
 ushort st_gid;   /* group ID */
 dev_t st_rdev;   /* device ident */
 off_t st_size;   /* size of file */
 time_t st_atime; /* last access time */
 time_t st_mtime; /* last modify time */
 time_t st_ctime; /* last status change */
};
```

## Dirent Structure

Most of the system calls working with directories operate with the ```dirent``` structure which is declared in the ```<dirent.h> ``` header file.

```cpp
struct dirent
{
 ino_t d_ino;         /* inode */
 char d_name[DIRSIZ]; /* filename */
}
```

## Create and Delete a Directory

Creating and deleting a directory could be proccessed with the mkdir() and rmdir() system calls. Note: When creating a directory using the mkdir() system call, it places two links ("." and "..").

```cpp
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int mkdir (char *pathname, mode_t mode);
int rmdir (char *pathname);
```

## Opening a Directory Stream

Upon successful opening of the directory, the system call returns a pointer to a variable of type DIR, which is a directory handle declared in the dirent.h header file and used when reading and writing to the directory.
```cpp
DIR * opendir (const char *dirname)
```

The opendir function opens and returns a directory stream for reading the directory whose file name is dirname. The stream has type DIR *.
If unsuccessful, opendir returns a null pointer. 

## Closing a Directory

```cpp
int closedir (DIR *dirptr);   /* dirptr - catalog descriptor */
```

## Changing a Directory

To change the directory chdir() system call is used, function described in unistd.h header:
```cpp
#include <unistd.h>
int chdir (char *pathname);
```
## Fast Implementation using STL

First of all, let's include some necessary libraries:
```cpp
#include <string>
#include <vector>
#include <algorithm>
```
Next, we'll create **d** pointer to the dirent structure, and **DIR** pointer also.
To store our filenames we need some data structure, array for instance. But to make it with ease we'll create a string Vector named files:

```cpp
struct dirent *d;
DIR *dp;
std::vector <std::string> files;
```

Some simple code here processing all the files in current directory(if current file's inode not null and it's not a directory we push filename to our Vector instance):
```cpp
while(d = readdir(dp))
    {
        if(d->d_ino != 0 && d->d_type != DT_DIR) {
            std::string str = std::string(d->d_name);
            files.push_back(str);
        }        
    }
closedir(dp);
```
Using <alghoritm> library and C++ iterators you can easily sort Vector of Strings, and print it out to the terminal:

```cpp
std::sort(files.begin(), files.end());
    for (auto i = files.begin(); i != files.end(); i++)
std::cout << *i <<std::endl;
```

Obviously you can also pull another data about your file using stat structure :shipit: :

- [x] We already have a filename
- [ ] Also we can fetch filesize
- [ ] And its time of last access
- [ ] And etc. :+1:



