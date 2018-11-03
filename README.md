Implementing C++ Program proccessing UNIX file system during OS Course Syllabus.

## Stat Structure

In order to fetch some data about type of file, you should use system calls stat(), or fstat(). 
Such system calls are declared in these header files:

```
#include <sys/types.h>
#include <sys/stat.h>
```
Both system calls put information about file(in first case, the specified name, and in second, with a file descriptor fd) into a structure variable, on which stbuf is pointed. The calling function must take care of reserving space for the returned information; if successful, returns 0, otherwise -1 and an error code in errno.

```
int stat(const char *name, struct stat *stbuf);
int fstat(int fd, struct stat *stbuf); 
```
The stat structure is described in the ```sys/stat.h``` header file.

```
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

```
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

Function: DIR * opendir (const char *dirname)

The opendir function opens and returns a directory stream for reading the directory whose file name is dirname. The stream has type DIR *.
If unsuccessful, opendir returns a null pointer. 

## Closing a Directory

int closedir (DIR *dirptr);   /* dirptr - дескриптор каталога */

## Changing a Directory

To change the directory chdir() system call is used, function described in unistd.h header:
```
#include <unistd.h>
int chdir (char *pathname);
```
##



