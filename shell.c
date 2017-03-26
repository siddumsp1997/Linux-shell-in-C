// Assignment -2 
// Part -2 : shell.c
// Siddharrth Priyadharsan M
// 14CS10046


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

int isex(char *arg){

 if(arg==NULL) return 0;

 struct stat buff;

 if(stat(arg,&buff)<0) // file doesnt exist
   return 0; 

 else
   return 1;
}


//function to search for a character in a string
int search( char *str, char t){

  int len = strlen(str); 
  int i;

  for(i=0;i<len;i++){

   if(str[i]==t) return 1;

 }

 return 0;

}
//end of search function


// function to count of no of occurences of a char in the string
int count(char *str,char t){

 int cnt =0;
 int i;

 for(i=0;i<strlen(str);i++){

   if(str[i]==t) cnt++;

 }

 return cnt;

} //end of count function



void executeme(char **argv, int argc){

  int status;

  if(argc > 1)
  {
    if(strcmp(argv[1], "|") == 0)
    {
     int pipes, i, j;
     pipes = 0;
     i=0;

        // counting no of pipes in the command
     while(i<argc){
      if(strcmp(argv[i],"|") == 0)
        {pipes++;}
      i++;
    }


    int fd[pipes][2];

    i = 0;
        // creating pipes required
    while(i<pipes){
      pipe(fd[i]);
      i++;
    }

    int pid1 = fork();
	if(!pid1) // child process
	{
		int pidr = fork();
		if(!pidr) //child process
		{
			dup2(fd[0][1], 1);
			int y4 =execvp(argv[0], argv);
      if(y4<0){ perror("Error in command arg1"); exit(-1); }
    }
		else // parent process
		{
			waitpid(pidr, &status, 0);
			dup2(fd[0][0], 0);
			if(pipes > 1)
				dup2(fd[1][1], 1);
     int y3=execvp(argv[2], argv);
     if(y3<0){ perror("Error in command arg3"); exit(-1);}
     
   }
 }
 else
   {waitpid(pid1, &status, 0); }

 j = 1; i =1;

 while(i<pipes){
  pid1 = fork();
		if(!pid1) // child process
		{
			dup2(fd[i][0], 0);
			if(i != pipes - 1)
			{
        dup2(fd[i+1][1],1);
      }
      j++;

      int y4 =execvp(argv[2 * j], argv);
      if(y4<0){ perror("Error in command argument"); exit(-1);}
      
    }
    else
      {waitpid(pid1, &status, 0);}

    i++;
	} //end of while loop
}
}
else
{
  int background = 1;
  if(strcmp(argv[argc - 1],"&") == 0)
  {
   background = 0;
   argv[argc-1] = '\0';
 }
 
 int pid = fork();
 int isExec;
 
		if(pid == 0) //child process
		{
			isExec = execvp(argv[0], argv);
      if(isExec<0){ perror("Error"); exit(-1);}
    }
	       else if(pid>0){ // parent process

          if(background)
            waitpid(pid,&status,0);
        }
        else{
		 exit(1); // fork failed
		}
	}


 return;
}
//end of executeme function


// redirection function
void  redirect_fn(char *arg1,char **arg,int in,int out) {

  
  if(in){
    int fd0 = open(arg[1], O_RDONLY);
    
    if(fd0<0) { perror("Error"); exit(-1); }

    else{
      dup2(fd0, STDIN_FILENO);
      close(fd0);
    }
  }
  
  if(out){
        int fd1 = open(arg[3],O_WRONLY|O_CREAT|O_TRUNC,0640);  // opening file2 ( creates a new file under that name, if it doesn't exist )

        if(fd1<0){ perror("Error"); exit(-1); }
        
        else{
          dup2(fd1, STDOUT_FILENO);
          close(fd1);
        }

      }


      int flag = execvp(arg1,arg);
      
      if(flag<0) { perror("Error"); exit(-1); }
      else exit(0);     

    }


// another version of redirect function
    void redirect_fn1(char *arg1,char **arg,int in,int out){

      if (in)
      {
        int fd0 = open(arg[1], O_RDONLY);
        
        if(fd0<0) { perror("Error"); exit(-1); }

        else{
          dup2(fd0, STDIN_FILENO);
          close(fd0);
        }
      }

      if (out)
      {
        //int fd1 = creat("output.txt" ,0644) ;

        
        int fd1 = open(arg[1],O_WRONLY|O_CREAT|O_TRUNC,0640);  // opening file2 ( creates a new file under that name, if it doesn't exist )

        if(fd1<0){ perror("Error"); exit(-1); }
        
        else{
          dup2(fd1, STDOUT_FILENO);
          close(fd1);
        }
      }

      int flag = execvp(arg1,arg);
      
      if(flag<0) { perror("Error"); exit(-1); }
      else exit(0);
    }
   //end of function





// main function
    int main(){


  char* command = (char*)malloc(500*sizeof(char)) ;  // string for the input command line  
  char* curr_path =(char*)malloc(500*sizeof(char)) ; //string for the current path

  // command line constituents
  char* arg1 =  (char*)malloc(100*sizeof(char));
  char* arg2 =  (char*)malloc(100*sizeof(char));
  char* arg3 =  (char*)malloc(100*sizeof(char));
  char* rem =   (char*)malloc(100*sizeof(char));
  char* temp =  (char*)malloc(500*sizeof(char)) ;

  DIR *directory ;
  struct dirent *cur_dir ; 



  printf("----------------------------------SHELL--------------------------------------\n");

  while(1){
   
 getcwd(curr_path, 500);      //getting current path

 printf("%s>",curr_path);

 gets(command);  // getting command

 strcpy(temp,command);

 //breaking the command into contituent keywords using delimiters
 arg1 = strtok_r(command," ", &rem);
 
 arg2 = strtok_r(NULL," ", &rem); 

 arg3 = rem;

 
 //printf("1. %s \n 2. %s \n 3. %s \n", arg1,arg2,arg3);

 // Implementation of the commands


 if(arg1==NULL)
  continue;


// "pwd" command used to print the current directory
if(strcmp(arg1,"pwd")==0){

 printf("%s\n",curr_path);
 
}
// end of pwd


// "cd" command used to change the directory
else if(strcmp(arg1,"cd")==0){


 if(arg2==NULL) // single word command
   chdir("/home/sid");

 
 else{ // 2 word command

   int flag = chdir(arg2);
   
 if(flag==-1) // error 
 perror("Error");  // priting the error 
}

}
 //end of cd



// "mkdir" command to create a new directory 
else if(strcmp(arg1,"mkdir")==0){

 if(arg2==NULL)
   printf("mkdir: missing operand\n");

 else{

  int flag = mkdir(arg2,S_IRWXU);

  if(flag==-1)
    perror("Error");
}

} //end of mkdir


// "rmdir" command to remove an existing directory
else if(strcmp(arg1,"rmdir")==0){
 
 if(arg2==NULL)
   printf("rmdir: missing operand\n");

 else{

   int flag = rmdir(arg2);

   if(flag==-1)
     perror("Error");
 }

} //end of rmdir



//"ls" command to show the files and directories in the current directory
else if(strcmp(arg1,"ls")==0){

 directory = opendir(curr_path); //open the directory in the current path

 if(arg2)
 { // is it is a 2 word command "ls -l"

if(strcmp(arg2,"-l")==0)
{
 
  if(directory)
  {
   cur_dir = readdir(directory);

   while(cur_dir!=NULL)
   {
    struct stat cur_stat ;
    int flag = stat(cur_dir->d_name, &cur_stat);

    if(flag>=0){
            if(S_ISDIR(cur_stat.st_mode)) printf("d");  // if it is a directory
            else printf("-");                           // if it is a file
            
            if(S_IRUSR & cur_stat.st_mode) printf("r"); // read permission, owner
            else printf("-");

            if(S_IWUSR & cur_stat.st_mode) printf("w"); // write permission, owner
            else printf("-");

            if(S_IXUSR & cur_stat.st_mode) printf("x"); // execute/search permission, owner
            else printf("-");      

            if(S_IRGRP & cur_stat.st_mode) printf("r"); //read permission, group
            else printf("-");

            if(S_IWGRP & cur_stat.st_mode) printf("w"); //write permission, group
            else printf("-");
            
            if(S_IXGRP & cur_stat.st_mode) printf("x"); //execute/search permission, owner
            else printf("-");   
            
            if(S_IROTH & cur_stat.st_mode) printf("r"); //read permission, others
            else printf("-");
            
            if(S_IWOTH & cur_stat.st_mode) printf("w"); //write permission, others
            else printf("-");
            
            if(S_IXOTH & cur_stat.st_mode) printf("x"); //execute/search permission, others
            else printf("-");

            

        char *ltime = ctime(&cur_stat.st_atime); // local time of last access to the file/directory

        int no_of_hardlink = (int)cur_stat.st_nlink ;  // no of hardlinkks for the file/directory
        int total_size = (int)cur_stat.st_size ;  // total size of the file/directory
        
        printf("%d  %d  %s  %s\n",no_of_hardlink,total_size, ltime, cur_dir->d_name);

         } //end of if(flag>=0)

         cur_dir = readdir(directory);


        } //end of inner while loop

        closedir(directory); //closing the directory
        
      }//end of if(directory)

      else
      perror("Empty Directory"); // printing error
    
  }

  else
  printf("Error : command not found\n"); // printing error for incorrect argument 


 } //end of if(arg2)


 else{ // if it is just "ls"
  
   
   if(directory){ // if directory is valid and not-null

     cur_dir = readdir(directory);

     while(cur_dir!=NULL){
       printf("%s\n", cur_dir->d_name);
       cur_dir =readdir(directory);
     }
     
   closedir(directory) ; //closing the directory

   } //end of inner if

   
   else
   perror("Empty Directory "); //printing error
 

} 
  //end of else


}
//end of ls


// command "clear" doesn't exist (given in problem statement)
else if(strcmp(arg1,"clear")==0){

  printf("Error : command not found\n");

}
//



// command "cp file1 file2" to copy contents of file1 to file2
else if(strcmp(arg1,"cp")==0){

//printf(" 1= %s\n 2=%s \n 3=%s\n",arg1,arg2,arg3);

 if(arg2==NULL)
   printf("cp: missing file operand\n");

 else if(arg3==NULL||(strcmp(arg3,"")==0))
   printf("cp: missing destination file operand after %s\n",arg2);

 else{
  
   
   int fd1,fd2;

 fd2 = open(arg3,O_WRONLY|O_CREAT|O_TRUNC,0640);  // opening file2 ( creates a new file under that name, if it doesn't exist )
 
 fd1 = open(arg2, O_RDONLY);  // opening file1 ( flag = -1 if any error occurs )

 char *buffer =(char*)malloc(400*sizeof(char)); //creating buffer 

 if(fd1<0)
   perror("Error"); 

 else if(fd2<0)
   perror("Error");

 else{ // no error

   int readbyte ;

   while(1){
     
    readbyte = read(fd1,buffer,400);

    write(fd2,buffer,readbyte);

    if(readbyte<400)
      break;

   } //end ofwhile

   close(fd1);
   close(fd2);

 } //end of outer else

 } //end of else


}
//end of cp command


// "exit" command to exit the terminal
else if(strcmp(arg1,"exit")==0){
 
 printf("\n Process terminated\n");
 break;

}


//else
else{
 
 int g1 = search(temp,'<');
 int g2 = search(temp,'>');

 int cnt = count(temp,'|');

  // single executable file command
 if(arg2==NULL){

   int status = 0;
   int background;

   int len = strlen(arg1);

   if(arg1[len-1]=='&') { background = 1; arg1[len-1] = 0; }
   else background =0 ;
   
   if(!(isex(arg1))){

    printf("Error : File doesnt exist\n");
    continue;
  }
  


  int id =fork();

  if(id==0){
   char **t = (char**)malloc(1*sizeof(char*));
   t[0] = NULL;

   int flag= execvp(arg1,t);

   if(flag<0){ perror("Error"); exit(-1); }
   else exit(0);
 }

   else{  //parent process
     if(background==0)
       waitpid(id,&status,0); 
   }

 }
    // end of if(arg2==NULL)

 
 else if(arg2!=NULL&&search(arg2,'&')){

  int background=0;
  int status = 0;


  if(strlen(arg2)==1)
  {

    if(arg3==NULL||(strcmp(arg3,"")==0))
      background =1;

    else 
    {
     printf("Error : '%s' command not found\n",arg3);
     continue;
   }

 }

 else{
   printf("Error : '%s' command not found\n",arg2);
   continue;
 }

 if(!(isex(arg1))){

   printf("Error : File doesnt exist\n");
   continue;
 }



 int id =fork();

 if(id==0){
   char **t = (char**)malloc(1*sizeof(char*));
   
   t[0] = NULL;
   

   int flag= execvp(arg1,t);

   if(flag<0){ perror("Error"); exit(-1); }
   else exit(0);
 }

   else{  //parent process
     if(background==0)
       waitpid(id,&status,0);

   }

 }
  // end of arg2 ! = NULL
 


   else if(g1==1&&g2==1){   // both < and > are present

     char *arg4 = (char*)malloc(100*sizeof(char));
     char *arg5 = (char*)malloc(100*sizeof(char));
     char *arg6 = (char*)malloc(100*sizeof(char));

     char *final = (char*)malloc(10*sizeof(char));

     arg4 = strtok_r(NULL," ",&rem);

     if(rem!=NULL)
       arg5 = strtok_r(NULL," ",&rem);
     
     if(rem!=NULL)
       arg6 = strtok_r(NULL," ",&rem);
     
     if(rem!=NULL)
       final = strtok_r(NULL," ",&rem);

     
     if((arg2!=NULL&&strcmp(arg2,"<")!=0)||(arg5!=NULL&&(strcmp(arg5,">")!=0))){

      printf("Error: command not found\n");
      continue;
      
    } 
    
    
    
    
    char **arg = (char**)malloc(5*sizeof(char*));

    arg[0] = (char*)malloc(50*sizeof(char));
    arg[1] = (char*)malloc(50*sizeof(char));
    arg[2] = (char*)malloc(50*sizeof(char));
    arg[3] = (char*)malloc(50*sizeof(char));
    
    int background,status;
    status =0;

    int hj = strlen(arg6);


    if(arg6[hj -1] == '&'){
     arg6[hj-1] =0;
     background = 1;
   }
   
   else if(final!=NULL&&search(final,'&')){
     
     if(strlen(final)==1)
       background = 1;
     
     else{
       printf("Error : '%s' command not found\n",final);
       continue;
     }
     
 }//end of if else

 else 
   background = 0;


 strcpy(arg[0],arg2);
 strcpy(arg[1],arg4);
 strcpy(arg[2],arg5);
 strcpy(arg[3],arg6);
 arg[4]=NULL;

 if(!(isex(arg1))){

  printf("Error : file not found\n");
  continue;
}



int pid = fork();

if(pid<0) perror("Error");

 else if(pid==0) { redirect_fn(arg1,arg,1,1); } // child

 else{ //parent 
  
    // Be parental 
  if(background==0){
    waitpid(pid,&status,0);
  }

   } //end of else
   
 }
  //end of g1==1 and g2==1




 else if(strcmp(arg2,">")==0||strcmp(arg2,"<")==0){

   int in,out,status,background;
   in = out = status = 0;



   char *final = (char*)malloc(15*sizeof(char));


   final = strtok_r(NULL," ",&rem);
   final = strtok_r(NULL," ",&rem);

   if(arg3==NULL||strcmp(arg3,"")==0){ printf("Error : missing operand\n"); continue; }
   
   int len = strlen(arg3);

   if(arg3[len-1]=='&') { background = 1; arg3[len-1]=0; }
   
   else if(final!=NULL&&search(final,'&')){
     
     if(strlen(final)==1) 
       background =1;
     
     else{
       printf("Error : '%s' command not found \n",final);
       continue;
     }

   }//end of if else
   
   else 
     background = 0;


   if(strcmp(arg2,">")==0) out = 1;
   else in = 1;

   if(!(isex(arg1))){
     
     printf("Error : file not found\n");
     continue;
   }


   char **arg = (char**)malloc(3*sizeof(char*));

   arg[0] = (char*)malloc(50*sizeof(char));
   arg[1] = (char*)malloc(50*sizeof(char));

   strcpy(arg[0],arg2);
   strcpy(arg[1],arg3);
   arg[2]=NULL;

   int pid = fork();
   
   if(pid<0) perror("Error");

   else if (pid == 0)
   {
    redirect_fn1(arg1,arg,in,out);
  }
  else
  {
    // Be parental 
    if(background==0){
      
      waitpid(pid,&status,0);
    }

  }
  
 } //end of arg2=='>'



 else if(cnt>0){
   
   char *tmp = (char*)malloc(500*sizeof(char));

   strcpy(tmp,temp);
   
   int argc =0 ; 
   int i,status,pid;

   char **argv = (char**)malloc(10*sizeof(char*));

   
   for(i=0;i<10;i++) 
     argv[i] = (char*) malloc(50*sizeof(char));

   char *rem1 = (char*)malloc(100*sizeof(char));

   while((rem1=strtok_r(tmp," ",&tmp))){
     strcpy(argv[argc],rem1); 
     argc++;
   }

 // checking for ampersand
   int background;

   int len = strlen(argv[argc-1]);
   char last = argv[argc-1][len-1];

   if(strcmp(argv[argc-1],"&")==0){
    argc--;
    background =1;
  }
  
  else if(last=='&'){
    argv[argc-1][len-1]=0;
    background =1;
  }
  
  else
    background = 0;


  int exit1 = 0;

  for(i=1;i<argc;i=i+2){
   
   if(strcmp(argv[i],"|")!=0){
    exit1 =1;
    break;
  }


 } //end of for loop

 if(exit1==1){
   
   printf("Error : Command not found\n");
   continue;
 } 

 if(argc%2==0){
   printf("Error: Invalid command\n");
   continue;
 }
 

 int exit2 =0;
 for(i=0;i<argc;i=i+2){
   
   if(!(isex(argv[i]))){
     exit2 =1;
     break;
   }

 }


 if(exit2==1){
   printf("Error : Command not found\n");
   continue;
 }

 int idf = fork();

 if(!idf){
  executeme(argv,argc);
  exit(0);
}

else{

  if(!background)
    waitpid(idf,&status,0);

}

}
 // end of if(cnt>0)



else{

 printf("Error: Command not found\n");
 continue;

}


}
//end of the final else

} 
// end of infinite while loop

} 

//end of main function

