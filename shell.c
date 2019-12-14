#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
//this function is for the sigchld siginal to make
//the wait call and recieve the pid of the child process.
//the file function for the log file with the killed process ids
void sigHandler(int sig){

FILE *f = fopen("file1.log","ab");

if (f==NULL){
printf("file failed \n");
}
pid_t pid;
pid = wait(NULL);
if(pid>0){
fprintf(f,"this child has ended %d\n",pid);

//printf("pid %d ended \n",pid);
}
fclose(f);
}
int main()
{
FILE *f = fopen("file1.log","ab");

if (f==NULL){
printf("file failed \n");
}
signal(SIGCHLD,sigHandler);
 char userInput[300] ; // the array that holds the user whole input
 char *commands[300]; // the array that holds the tokenized commands or arguments

 while(1){
 char out []="exit";
int  i = 1;
printf("<< enter your command >>  ");
gets(userInput,300);
 char space[] = " ";
 char *ptr = strtok (userInput,space); // the starting of tokenization process
 commands[0] = ptr; // putting the command in first element in commands array
/*loop to take the rest of arguments */
 while (ptr!=NULL){
 commands[i] = ptr;

 ptr = strtok(NULL,space);
 commands[i] = ptr;
 i++;

 }

//********************************************************************
/*the check for exit command */
if (strcmp(commands[0],out)==0){
exit(1);
}
/* here i checked if the command have a argument or no to avoid segmantation fault */
if (commands[1]==NULL){
/* here the fork function */
pid_t chld;
pid_t pid = fork();
if (pid < 0) {
printf("error");
}
else if (pid > 0 ){
chld = wait(NULL);
fprintf(f,"this child has ended %d\n",chld); // log file writing

}
else {
int x = execvp(commands[0],commands);

if(x==-1){
printf("this command does not exist\n");
}
exit(0);


}



}
/* here the commands with arguments */
/* here i check with the itirator i used while tokenization to make sure that my array have arguments to avoid segmentation fault  */
if(i>2){
//********************************************************************
// the check for & to make the child process play in background
if (strcmp("&",commands[1])==0){
//strcpy(commands[1],"NULL"); // putting null instead of the &
 commands[1] = NULL;
pid_t pid = fork();
if (pid < 0) {
printf("error");
}
// no wait here so as to make sure the 2 processes run together
else if (pid > 0 ){
}
 else {
execvp(commands[0],commands);
exit(0);


}

}
//********************************************************************
/* cd check  */
else if (strcmp(commands[0],"cd")==0){
pid_t child ;
pid_t pid = fork();
if (pid < 0) {
printf("error");
}
else if (pid > 0 ){
child =  wait(NULL);
//fprintf(f,"this child has ended %d\n",child);
exit(0);
}
else {
int y = chdir(commands[1]);
if (y!=0){
printf("this directory doesnot exist\n");
}


}




}
/* this is for commands such as ls -l  that have an argument and is done with execvp */
else {

pid_t chld;
pid_t pid = fork();
if (pid < 0) {
printf("error");
}
else if (pid > 0 ){
chld = wait(NULL);
fprintf(f,"this child has ended %d\n",chld);

}
else {
int x = execvp(commands[0],commands);
if(x==-1){
printf("this command does not exist\n");
}
exit(0);


}
}
}

}
fclose(f);




    return 0;
}
