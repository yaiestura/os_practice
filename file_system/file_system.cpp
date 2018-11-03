#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>


struct Data {
       unsigned char d_type;
       char* name;  
       __ino_t d_ino;
   };

struct List {
   Data data;
   struct List *next;
};


struct List* push(struct List* head, struct Data data)
{
    struct List* tmp = (struct List*)malloc(sizeof(struct List));
    if(tmp == NULL)
    {
        exit(0);
    }
    tmp->data = data;
    tmp->next = head;
    head = tmp;
    return head;
}

void init(struct List* head)
{
    head = NULL;
}

bool isEmpty(struct node* head)
{
    return head == NULL ? 1 : 0;
}

void print(struct List* head) {
    struct List *current;
    current = head;
    if(current!= NULL)
    {
        while (current!= NULL) {
            char *fileType;

            switch(current->data.d_type) {
            case DT_UNKNOWN:
                fileType = "Unknown file";
            break;
            case DT_REG:
                fileType = "A regular file";
            break;
            case DT_DIR:
                fileType = "A directory";
            break;
            case DT_FIFO:
                fileType = "FIFO";
            break;
            case DT_SOCK:
                fileType = "A local-domain socket";
            break;
            case DT_CHR:
                fileType = "A character device";
            break;
            case DT_BLK:
                fileType = "A block device";
            break;
            case DT_LNK:
                fileType = "A symbolic link";
            break;
            }
            printf("%s ",fileType);
            printf("%d ",current->data.d_ino);
            printf("%s\n",current->data.name);
            current = current->next;
        }
        printf("\n");
    } else {
        printf("No files are found\n");
    } 
}

void sort(struct List* head) {
    struct List *current, *follow;
    struct Data swap;
    current = head;
    while(current != NULL) {
        follow = current->next;
        while(follow != NULL) {
            if(int(tolower(current->data.name[0])) > int(tolower(follow->data.name[0]))) {
                swap = current->data;
                current->data = follow->data;
                follow->data = swap;
            }            
            follow = follow->next;
        }
        current = current->next;
    }
}

void ls(const char *directory) {
    struct List* head; 
    struct dirent *d;
    DIR *dp;
    
    init(head);

    dp = opendir(directory);
    if((dp == NULL)) {
        printf("%s\n","Error! A directory can not be opened.");
        exit(0);
    }

    while(d = readdir(dp))
    {
        if(d->d_ino != 0 && d->d_type != DT_DIR) {
            Data data;
            data.d_type = d->d_type;
            data.name = d->d_name;
            data.d_ino = d->d_ino;
            head = push(head,data);                       
        }        
    }

    closedir(dp);
    sort(head);
    print(head);
    }

int main(int argc, char **argv) {
     if (argc == 1)
        {
         ls(".");
        }
        if (argc > 2)
        {
         printf("Error! Too many arguments\n");
         return (EXIT_FAILURE);
        }
        else
        {
         char path[PATH_MAX] = {};
         strcpy(path, argv[1]);
         ls(argv[1]);
        }
         return EXIT_SUCCESS;
}
