#include <stdio.h>
#include <string.h>

int
main() {
  printf("read one line\n");

  char buffer[31] = {0,};
  char oneLine[31] = {0,};

  FILE *fp = fopen("abc.txt", "r");
  
  char next[31] = {0,};
  int next_len = 0;
  int success = 1;
  while(success) {
    memset(buffer, 0, sizeof(buffer));
    success = fread(buffer, sizeof(buffer)-1, 1, fp);
    //printf("buffer:%s\n", buffer);

    int read_len = 0;
    char *start_pos = buffer;
    char * end_pos = NULL;
    char * write_pos = oneLine;
    while((end_pos = strchr(start_pos, '\n')) != NULL) {
      memset(oneLine, 0, sizeof(oneLine));
      write_pos = oneLine;
      if(next_len > 0) {
        strncpy(oneLine, next, next_len);
        write_pos = &oneLine[next_len];
        next_len = 0;
      }

      int len = end_pos - start_pos;
      //printf("len : %d\t", len);
      strncpy(write_pos, start_pos, len);
      read_len += len+1;
      start_pos = &(start_pos[len+1]);
      printf("oneLine:%s\n", oneLine);
    }
    next_len = 30 - read_len;
    if(next_len > 0) {
      memset(next, 0, sizeof(next));
      strncpy(next, start_pos, next_len);
      //printf("next len:%d, str=%s\n", next_len, next);
    }
    
  }
  fclose(fp);
  return 0;
}
