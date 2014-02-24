/* http://www.brodowsky.com/main.c */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int mylock(const char *filename, int start, int end) {
  int fd = open(filename, O_RDWR | O_APPEND);
  /* mit lseek an start */
  /* mit lockf end-start bytes locken */
  /* file offen lassen!! */
  
  int test;
  int bereich = end - start;
  
  test = lseek(fd,(off_t) start,SEEK_SET);
  if(test > 0)
  {
  	  printf("Verschoben an Position %d\n",start);
  }
  
  if(test < 0)
  {
  	  int errornummer = errno;
  	  const char *error_string = strerror(errornummer);
  	  printf("errno=%d\nmessage=%s\n",errornummer,error_string);
  }
  
  test = lockf(fd, F_TLOCK, bereich);
  
  if(test == 0)
  {
  	  printf("Jetzt geschlossen!\n");
  }
  else
  {
  	  printf("Konnte nicht gesperrt werden!\n");
  }
  
  sleep(30);
  test = lockf(fd, F_ULOCK, bereich);
  
  if(test == 0)
  {
  	  printf("Jetzt offen!\n");
  }
  return fd;
}


int main(int argc, char *argv[]) {
  const char *FILENAME="temp_lock";
  if (argc == 1) {
    char text[1337];
    int i;
    for (i = 0; i < 1337; i++) {
      text[i] = (char) ((i % 90) + 32);
    }
    FILE *file = fopen(FILENAME, "w");
    fwrite(text, 1, 1337, file);
    fclose(file);
    exit(0);
  }
  if (argc < 3) {
    printf("wrong number of arguments\n");
    exit(1);
  }
  
  long x, y, len;
  sscanf(argv[1], "%ld", &x);
  printf("x=%ld\n", x);
  sscanf(argv[2], "%ld", &y);
  printf("y=%ld\n", y);
  len = y - x;
  
  int fd = mylock(FILENAME, x, y);
  sleep(10);
  close(fd);
  exit(0);
}