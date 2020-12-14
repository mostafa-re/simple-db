#include "custom_io_module.h"

int fgetsln(char *string, size_t size, FILE *stream)
{
   if (fgets(string, size, stream))
   {
      char *tmp = string;
      while (*tmp)
      {
         if (iscntrl(*tmp))
            *tmp = '\0';
         tmp++;
      }
      return 1;
   }
   else
   {
      return 0;
   }
}

char *prompt(const char *promptString)
{
   if (*promptString)
   {
      fprintf(OUTPUT_STREAM, "%s ", promptString);
   }
   fprintf(OUTPUT_STREAM, "%s ", PROMPT_NOTIFIER);

   fflush(OUTPUT_STREAM);

   static char inputBuffer[3 * MAX_INPUT_BUFFER_LENGTH + 1] = "";
   if (fgetsln(inputBuffer, MAX_INPUT_BUFFER_LENGTH + 1, INPUT_STREAM))
   {
      return inputBuffer;
   }
   return "";
}

void printErr(const char *errorString)
{
   fprintf(ERROR_STREAM, "%s %s\n", ERROR_NOTIFIER, errorString);
   fflush(ERROR_STREAM);
}

void clearScreen()
{
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
   system("cls");
#else /* presume POSIX */
   system("clear");
#endif
}

void toLowerString(char *str)
{
   while (*str)
   {
      *str = tolower(*str);
      str++;
   }
}