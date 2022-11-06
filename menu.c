#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h> 
#include <stdbool.h>
#include"competition.h"
#include"simulation.h"
#include"menu.h"

void print_menu(){
    printf("\n\n****************************************\n");
    printf("0. Quit\n");
    printf("1. Add new applicant to the list\n");
    printf("2. Modify applicant in the list\n");
    printf("3. Delete applicant from the list\n");
    printf("4. Create list of applicants by area \n");
    printf("5. Create complete list of applicants \n");
    printf("6. Start the competition \n");
    printf("****************************************\n");
}

void menu(){
    bool validation = true; 
    while(validation){
        print_menu();
        int n;
        scanf("%d", &n);
        switch (n)
        {
        case 0:
            printf("\n Bye! ૮꒰ ˶• ༝ •˶꒱ა \n");
            validation = false;
            break;
        case 1:
            addApplicant();
            break;
        case 2:
            modifyApplicant();
            break;
        case 3:
            deleteApplicant();
            break;
        case 4:
            createListByArea();
            break;
        case 5:
            createCompleteList();
            break;
        case 6:
            bunny_race();
            break;
        default: 
            printf("You didn't enter a number from the menu!");
            break;
        }
    }
}