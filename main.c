#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h> 
#include <unistd.h>     
#include "menu.h"
#include"competition.h"

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        perror("Error!\n");
        exit(1);
    }

    menu();
        

    return 0;
}