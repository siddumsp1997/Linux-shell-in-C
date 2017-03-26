// OS LAB  
// Assignment 2, Problem 2 : run.c file
// Siddharrth Priyadharsan M
// 14CS10046

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// main function
int main(int argc,char *argv[]){


  char *argv1[5];
  int status = 0;  

  int id =fork();

    if(id==0){ // child process 
    argv1[0] = (char *)malloc(6*sizeof(char));  // xterm
    argv1[1] = (char *)malloc(6*sizeof(char));  // -hold
    argv1[2] = (char *)malloc(3*sizeof(char));  // -e
    argv1[3] = (char *)malloc(8*sizeof(char));  // ./shell
    //argv1[4] = (char *)malloc(strlen(argv[1])*sizeof(char)); 
    
  // passing " xterm -hold -e ./sort1 input_file_name " as array of strings
    strcpy(argv1[0],"xterm");
    strcpy(argv1[1],"-hold");
    strcpy(argv1[2],"-e");
    strcpy(argv1[3],"./shell");
  //  strcpy(argv1[4],argv[1]);
    argv1[4] = NULL;

    int f=execvp(argv1[0],argv1); // execv() system call

   // program control will be here if there is any error
    if(f<0){
      perror("execv failed:\n");
      exit(-1);
    }

    }//end of child process
    
   else { // parent process
    
   waitpid(id,&status,0); // wait for the child process to complete
   printf("Parent process terminated.\n");
   exit(0);
   
 }
 
 return 0;
}
 // end of main program


