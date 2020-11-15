#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(){
  char input[BUFFER_SIZE];
  char output[BUFFER_SIZE] , huruf;
  int fd[2];
  int c = 0;
  pid_t pid;
  if (pipe(fd) == -1) {
    fprintf(stderr,"Pipe failed");
    return 1;
  }
  pid = fork();
  if (pid < 0) {
  fprintf(stderr, "Fork Failed");
    return 1;
  }
  if (pid > 0) { 
  close(fd[READ_END]);
  scanf("%[^\n]s", input);  
  write(fd[WRITE_END],  input, strlen(input)+1);
  close(fd[WRITE_END]);
  }
  else { 
    close(fd[WRITE_END]);
    read(fd[READ_END], output, BUFFER_SIZE);
    while (output[c] != '\0') {
      huruf = output[c];
      if (huruf >= 'A' && huruf <= 'Z')
        output[c] = output[c] + 32;
      else if (huruf >= 'a' && huruf <= 'z')
        output[c] = output[c] - 32;  
      c++;  
    }
    printf("%s",output);
    close(fd[READ_END]);
  }
  wait(NULL);
  return 0;
}