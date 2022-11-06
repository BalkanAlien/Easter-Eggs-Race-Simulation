#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <unistd.h>
#include"competition.h"
#include"menu.h"


void addApplicant() {
    char bunnyName[20];
    char livingArea[20];
    char numberOfTimes[20];

    int s;
    printf("\nPlease enter the applicant's data \n");
    printf("Name: ");
    scanf("%s", bunnyName);
    printf("\nLiving area: ");
    printf("\nBaratfa - 1");
    printf("\nLovas - 2");
    printf("\nSzula - 3");
    printf("\nKigyos-patak - 4");
    printf("\nMalom telek - 5");
    printf("\nPaskom - 6");
    printf("\nKaposztas kert - 7 \n");
    scanf("%d", &s);
    while(s>7 || s <1){
        scanf("%d", &s);
    }
    switch(s){
        case 1:
            strncpy(livingArea, "Baratfa", 20);
            break;
        case 2:
            strncpy(livingArea, "Lovas", 20);
            break;
        case 3:
            strncpy(livingArea, "Szula", 20);
            break;
        case 4:
            strncpy(livingArea, "Kigyos-patak", 20);
            break;
        case 5:
            strncpy(livingArea, "Malom telek", 20);
            break;
        case 6:
            strncpy(livingArea, "Paskom", 20);
            break;
        case 7:
            strncpy(livingArea, "Kaposztas kert", 20);
            break;
    }
    printf("Number of times it enters the competition: ");
    scanf("%s", numberOfTimes);
    FILE *f = fopen("test.txt", "a");
    fprintf(f, "%s %s %s %s", bunnyName, livingArea, numberOfTimes, "\n"); //inserts formatted string into output stream
    fclose(f);
}


void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void modifyApplicant() {
    //in order to modify, first we delete then we add
    FILE *f1, *f2;
    char c[100];
    int delLine, temp = 0,NumOfLines = 0;
    f1 = fopen("test.txt", "r");
    //fgets() reads line by line so it is easier to count lines 
    while(fgets(c,100,f1) != NULL) 
    {
        printf("%s", c);NumOfLines++;
    }

    printf("Which line do you want to modify?[1 - %d]\n",NumOfLines);
    scanf("%d", &delLine);
    while(delLine > NumOfLines)
    {
        printf("Invalid line number, Please keep the number in range [1-%d]\nTry again: ",NumOfLines);
        scanf("%d", &delLine);
    }

    //Now after we are sure that the user gave a valid line number, 
    //we will creat a new line and insert it to the new file we are coppying to in the same line number user chose.

 

    ///Lets create the line we want to insert.
            char bunnyName[20];
            char livingArea[20];
            char numberOfTimes[20];

            int s;
            flush_stdin();
            printf("\nPlease enter the applicant's data \n");
            printf("Name: ");
            scanf("%[^\n]s", bunnyName);//this way the name can include white spaces
            printf("\nLiving area: ");
            printf("\nBaratfa - 1");
            printf("\nLovas - 2");
            printf("\nSzula - 3");
            printf("\nKigyos-patak - 4");
            printf("\nMalom-telek - 5");
            printf("\nPaskom - 6");
            printf("\nKaposztas-kert - 7 \n");
            flush_stdin();////Or  fflush(stdin)
            scanf("%d", &s);
            while(s>7 || s <1){
                perror("Please try to input correct range\n");
                scanf("%d", &s);
            }
            const char areas[7][20] = {"Baratfa","Lovas","Szula", "Kigyos-patak", "Malom telek", "Paskom","Kaposztas kert"};
            strcpy(livingArea,areas[s-1]);
            printf("Number of times it enters the competition: ");
            scanf("%s", numberOfTimes);


char modifedline[70];
sprintf(modifedline,"%s %s %s\n",bunnyName,livingArea,numberOfTimes); //format the string output
printf("%s",modifedline);
   //open new file in write mode
    f2 = fopen("temp.txt","w");

    if(f2 == NULL)
    {
        printf("Couldnt open new file\n");
        exit(1);
    }

rewind(f1);
while(fgets(c,100,f1) != NULL) 
    {
        temp++;
        if(temp == delLine)
        {
            fprintf(f2,"%s",modifedline);
            continue;
        }
        fprintf(f2,"%s",c);
    }    
    
    fclose(f1);
    fclose(f2);

    remove("test.txt");
    //rename temp file to original file name
    rename("temp.txt", "test.txt");

    f1 = fopen("test.txt", "r");
    printf("Here is our file:\n");
    while(fgets(c,100,f1) != NULL){
        printf("%s", c);
    }
    fclose(f1);
}


void deleteApplicant(){
    FILE *f1, *f2;
    char c;
    int delLine, temp = 1;

    f1 = fopen("test.txt", "r");
    c = getc(f1);
    while(c != EOF){
        printf("%c", c = getc(f1));
    }
    rewind(f1);
    printf("Which line do you want to delete?\n");
    scanf("%d", &delLine);

    //open new file in write mode
    f2 = fopen("replica.c", "w");
    c = getc(f1);
    while(c != EOF){
        c = getc(f1);
        //copy all lines in f2 except the line we want to delete
        if(temp != delLine){
            putc(c, f2);
        }
        if(c == '\n'){
            temp++;
        }
    }
    fclose(f1);
    fclose(f2);
    remove("test.txt");
    //rename temp file to original file name
    rename("replica.c", "test.txt");
    f1 = fopen("test.txt", "r");
//    while(c != EOF){
//        printf("%c", c);
//        c = getc(f1);
//    }
    fclose(f1);
}

void createListByArea(){
    printf("Hi! Enter the number corresponding to the area you want to choose!");
    printf("\nBaratfa - 1");
    printf("\nLovas - 2");
    printf("\nSzula - 3");
    printf("\nKigyos-patak - 4");
    printf("\nMalom telek - 5");
    printf("\nPaskom - 6");
    printf("\nKaposztas kert - 7 \n");
    int s;
    scanf("%d", &s);
    char livingArea[20];
    while(s>7 || s <1){
        scanf("%d", &s);
    }
    switch(s){
        case 1:
            strncpy(livingArea, "Baratfa", 20);
            break;
        case 2:
            strncpy(livingArea, "Lovas", 20);
            break;
        case 3:
            strncpy(livingArea, "Szula", 20);
            break;
        case 4:
            strncpy(livingArea, "Kigyos-patak", 20);
            break;
        case 5:
            strncpy(livingArea, "Malom-telek", 20);
            break;
        case 6:
            strncpy(livingArea, "Paskom", 20);
            break;
        case 7:
            strncpy(livingArea, "Kaposztas-kert", 20);
            break;
    }

    FILE *f1; 
    char line[200];
    f1 = fopen("test.txt", "r");
    printf("Applicants living in the area %s:\n", livingArea);
    while(fgets(line, 200, f1) != NULL || !feof(f1)){//read a line
        if(strstr(line,livingArea)) //if line contains the area
            fputs(line, stdout); //print the line
    }
    fclose(f1);
}

void createCompleteList(){
    FILE *f1;
    char c;
    f1 = fopen("test.txt", "r");
    while(1){
        c = fgetc(f1);
        if(feof(f1)){
            break;
        }
        printf("%c", c);
    }
    fclose(f1);
}