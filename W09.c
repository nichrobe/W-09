#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* substring(char*, int, int);

enum State {
  NON_COMMENT,
  START_COMMENT,
  END_COMMENT
};

int main(int argc, char **argv) {
  static const char filename[] = "W09.c";

  char line[128];
  char comment[128];
  char userInput[50];
  char actualFile[50];
  // Sets the initial state.
  enum State state = NON_COMMENT;

  if (argc == 1) {
    printf("Please provide the file you wish to inspect: ");
    scanf("%s", userInput);
  }

  if ((argc == 1) && (strlen(userInput) == 0)) {
    printf("A file has not been entered. Please try the application again");
  } else {
    // Find out the way the user entered the file.
    if (argc == 1) {
      strcpy(actualFile, userInput);
    } else {
      strcpy(actualFile, argv[1]);
    }
  }

  FILE *file = fopen(actualFile, "r");
  if (file != NULL) {
    // Read a line.
    while (fgets(line, sizeof line, file) != NULL) {
      int start_index = 0;
      int stop_index = 0;
      char *startC = "/*";
      char *endC = "*/";

      // Output if completed.
      if (state == END_COMMENT) {
        printf("%s", comment);
        state = NON_COMMENT;
        strcpy(comment, "");
      }

      char *pch = strstr(line, startC);
      if (pch) {
        state = START_COMMENT;
        char *result = strstr(line, "/*");
        start_index = result - line;
      }

      pch = strstr(line, endC);
      if (pch && (state == START_COMMENT)) {
        char * nresult = strstr(line, "*/");
        stop_index = nresult - line;
        state = END_COMMENT;
      } else {
        stop_index = strlen(line);
      }

      if (state != NON_COMMENT) {
        strcpy(comment, substring(line, start_index, stop_index));
      }
    }
    fclose(file);
  } else {
    perror(actualFile);
  }
  return 0;
}


char *substring(char *string, int position, int length)
{
   char *pointer;
   int c;

   pointer = malloc(length+1);

   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(EXIT_FAILURE);
   }

   for (c = 0 ; c < position -1 ; c++)
      string++;

   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *string;
      string++;
   }

   *(pointer+c) = '\0';

   return pointer;
}
