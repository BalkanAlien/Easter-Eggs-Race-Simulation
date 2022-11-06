#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <time.h>
#include "competition.h"


const char areas[7][20] = {"Baratfa","Lovas","Szula", "Kigyos-patak", "Malom telek", "Paskom","Kaposztas kert"};

void bunny_race() {
    pid_t supervisor1, supervisor2; //child processes

    int pipefd1[2];
    int pipefd2[2];
    int pipefd3[2];
    int pipefd4[2];
    int pipefd5[2];
    int pipefd6[2];

    if(pipe(pipefd1) == -1){
        perror("Pipe1 is broken! Call the handy man!\n");
        exit(EXIT_FAILURE);
    }
    if(pipe(pipefd2) == -1){
        perror("Pipe2 is broken! Call the handy man!\n");
        exit(EXIT_FAILURE);
    }
    if(pipe(pipefd3) == -1){
        perror("Pipe3 is broken! Call the handy man!\n");
        exit(EXIT_FAILURE);
    }
    if(pipe(pipefd4) == -1){
        perror("Pipe4 is broken! Call the handy man!\n");
        exit(EXIT_FAILURE);
    }
    if(pipe(pipefd5) == -1){
        perror("Pipe5 is broken! Call the handy man!\n");
        exit(EXIT_FAILURE);
    }
    if(pipe(pipefd6) == -1){
        perror("Pipe6 is broken! Call the handy man!\n");
        exit(EXIT_FAILURE);
    }

    supervisor1 = fork();
    if(supervisor1 < 0){
        perror("Fork error!\n");
        exit(EXIT_FAILURE);
    }

    if(supervisor1 == 0){
        /// child 1
        // sleep(10);
        close (pipefd5[1]); //close unused write end
        int numOfBunnies = 0 ;
        read(pipefd5[0],&numOfBunnies, sizeof(int)); //reading the number of bunnies in the 5th pipe
        //printf("numOfBunnies received:%d\n",numOfBunnies);
        close (pipefd5[0]); // reading is finished, close the pipe
        close(pipefd1[1]); //  close unused write end
        close(pipefd2[0]); // close unused read end

        for(int i = 0 ; i  < numOfBunnies;i++){        
            int l = 0 ; 
            char data[200];
            read(pipefd1[0],&l, sizeof(int)); 
            read(pipefd1[0],data,l); 
            printf("supervisor 1 received:%s\n", data); // 1st child receives data
            srand(getpid() + i);
            int rand_int = rand() % 100 ;

            write(pipefd2[1],&rand_int , sizeof(int)); //we're writing the random number 
            write(pipefd2[1],&l , sizeof(int));
            write(pipefd2[1], data, l);
            printf("supervisor 1 sends:%s,collected eggs:%d\n", data,rand_int); 
        }
        
        close(pipefd1[0]); // reading is finished, close the pipe
        close(pipefd2[1]); // writing is finished, close the pipe
        
        exit(EXIT_SUCCESS);
    }
    else {
        supervisor2 = fork();
        if(supervisor2 < 0 ){
            printf("Forking ERROR!\n");
            exit(EXIT_FAILURE);
        }
        if(supervisor2 == 0) {
        /// supervisor2
        // sleep(3);
        close (pipefd6[1]); // close unused write end
        int numOfBunnies = 0 ;
        close(pipefd3[1]); // close unused write end
        close(pipefd4[0]); // close unused read end
        read(pipefd6[0],&numOfBunnies, sizeof(int)); //reading the number of bunnies that the 2nd supervisor will receive
        //printf("numOfBunnies in 2:%d\n" , numOfBunnies);
        close (pipefd6[0]); // finished reading, close pipe

        for(int i = 0 ; i  < numOfBunnies;i++){        
            int l = 0 ; 
            char data[200];
            read(pipefd3[0],&l, sizeof(int)); // specify the number of bytes we will read
            read(pipefd3[0],data,l); //supervisor2 receives each bunny
            printf("supervisor 2 received:%s\n", data); 
            srand(getpid() + i);
            int rand_int = rand() % 100 ;
    
            write(pipefd4[1],&rand_int , sizeof(int)); //then we write the random number to each bunny
            write(pipefd4[1],&l , sizeof(int));
            write(pipefd4[1], data, l);
            printf("supervisor 2 sends:%s, number of eggs:%d\n", data,rand_int );
        }
        
        close(pipefd3[0]); //close reading pipe
        close(pipefd4[1]); //close writing pipe
        exit(EXIT_SUCCESS);
        }
        else {        
            // Chief bunny - Parent

            FILE* f = fopen("test.txt","r");
            if(f == NULL) {
                perror("File can't open!");
                exit(1);
            }

            char line[200];
            printf("\n\nParent starts filtering the bunnies\n");
            
            close (pipefd1[0]); //close unused read end
            close (pipefd3[0]); //close unused read end

            int numOfBunniesInArea1 = 0 ;
            int numOfBunniesInArea2 = 0 ;

            while(fgets(line, 200, f) != NULL){
                line[strlen(line) - 1 ] = '\0';
                if(strstr(line,"Baratfa")!=NULL || strstr(line,"Lovas")!=NULL || strstr(line,"Szula")!=NULL || strstr(line,"Kigyos-patak")!=NULL) {
                    int l = strlen(line) + 1;
                    write(pipefd1[1] , &l, sizeof(int)); //writing appropriate bunnies to each group
                    write(pipefd1[1] , line,l);
                    numOfBunniesInArea1++;
                }
                else{
                    int l = strlen(line) + 1;
                    write(pipefd3[1] , &l, sizeof(int));
                    write(pipefd3[1] , line,l);
                    numOfBunniesInArea2++;
                }    
            }

            close(pipefd5[0]); //close unused read end
            close(pipefd6[0]); //close unused read end

            write(pipefd5[1] , &numOfBunniesInArea1, sizeof(int)); 
            write(pipefd6[1] , &numOfBunniesInArea2, sizeof(int)); 
            
            close(pipefd5[1]); //finish writing
            close(pipefd6[1]); // finish writing
            close (pipefd1[1]); //finish writing
            close (pipefd3[1]); // finish writing

            printf("\nParent finished sending the data of  the bunnies to supervisor A and B\n\n");
            int st1 ;
            int st2 ;
            waitpid(supervisor1,&st1,0);
            waitpid(supervisor2,&st2,0);

            close (pipefd2[1]); 
            close (pipefd4[1]);

            printf("\n\nParent received from supervisor 1: \n");
            int collectedEggsOfTheWinner = 0 ;
            char winner[200];
            int numOfCollectedEggs;
            int l = 0 ; 
            char DataOfBunny[200]; 

            for(int i = 0 ; i < numOfBunniesInArea1;i++){
                read(pipefd2[0],&numOfCollectedEggs,sizeof(int));
                read(pipefd2[0],&l,sizeof(int));
                read(pipefd2[0],DataOfBunny,l);
                printf("Parent received: [(Bunny: %s), Collected eggs: %i]\n",DataOfBunny,numOfCollectedEggs);
                if(collectedEggsOfTheWinner  <numOfCollectedEggs){
                    collectedEggsOfTheWinner = numOfCollectedEggs;
                    strcpy(winner,DataOfBunny);
                }
            }

            printf("\n\nParent received from supervisor 2: \n");
            
            for(int i = 0 ; i < numOfBunniesInArea2;i++){
                read(pipefd4[0],&numOfCollectedEggs,sizeof(int));
                read(pipefd4[0],&l,sizeof(int));
                read(pipefd4[0],DataOfBunny,l);
                printf("Parent received: [(Buny:%s),Collected eggs:%i]\n",DataOfBunny,numOfCollectedEggs);
                if(collectedEggsOfTheWinner  < numOfCollectedEggs){
                    collectedEggsOfTheWinner = numOfCollectedEggs;
                    strcpy(winner,DataOfBunny);
                }
            }
            close (pipefd2[0]);
            close (pipefd4[0]);
        
            printf("\n\n[Winer:%s, collected eggs:%d]\n", winner, collectedEggsOfTheWinner);
            printf("Parent finished!\n");
        }

    } 

}


