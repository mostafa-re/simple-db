#include <string.h>
#include "custom_io_module.h"
#include "table_manager_module.h"

#define PROJECT_NAME "sdb"
#define VERSION "1.73"

int main()
{
  char *inputBufferPtr;
  int checkBuffer;

  char inputBufferString1[MAX_INPUT_BUFFER_LENGTH + 1] = "";
  char inputBufferString2[MAX_INPUT_BUFFER_LENGTH + 1] = "";
  size_t inputBufferSize_t = 0;

  ContainerAddress mainContainer = createContainer();
  if (!mainContainer)
  {
    printErr("Failed to launch the program, because we cannot allocate memory :(");
    pause();
    return 0;
  }

  fprintf(OUTPUT_STREAM, "### Hi welcome to %s version %s by MOSTAFA_RT! if you're newbie, just try 'help' :D\n", PROJECT_NAME, VERSION);

  while (mainContainer)
  {
    inputBufferPtr = prompt(PROJECT_NAME);
    checkBuffer = sscanf(inputBufferPtr, "%s", inputBufferString1);
    if (checkBuffer != 1)
    {
      continue;
    }
    toLowerString(inputBufferString1);

    if (!strcmp("create", inputBufferString1))
    {
      checkBuffer = sscanf(inputBufferPtr, "%*s %s %zd", inputBufferString1, &inputBufferSize_t);
      if (checkBuffer == 2)
      {
        addTableToContainer(&mainContainer, inputBufferString1, inputBufferSize_t);
      }
      else if (checkBuffer == 1)
      {
        printErr("Please enter columns of the table :/");
      }
      else
      {
        printErr("Please enter name of the table :/");
      }
    }
    else if (!strcmp("insert", inputBufferString1))
    {
      checkBuffer = sscanf(inputBufferPtr, "%*s %s %[^\n]", inputBufferString1, inputBufferString2);
      if (checkBuffer == 2)
      {
        insertDataIntoTableByName(mainContainer, inputBufferString1, inputBufferString2);
      }
      else if (checkBuffer == 1)
      {
        printErr("Please enter the data that should store in table :/");
      }
      else
      {
        printErr("Please enter name of the table :/");
      }
    }
    else if (!strcmp("drop", inputBufferString1))
    {
      checkBuffer = sscanf(inputBufferPtr, "%*s %s %zd", inputBufferString1, &inputBufferSize_t);
      if (checkBuffer == 2)
      {
        dropFromTableByName(mainContainer, inputBufferString1, inputBufferSize_t);
      }
      else if (checkBuffer == 1)
      {
        removeTableFromContainer(&mainContainer, inputBufferString1);
      }
      else
      {
        printErr("Please enter name of the table :/");
      }
    }
    else if (!strcmp("merge", inputBufferString1))
    {
      checkBuffer = sscanf(inputBufferPtr, "%*s %s %s", inputBufferString1, inputBufferString2);
      if (checkBuffer == 2)
      {
        mergeTwoTable(&mainContainer, inputBufferString1, inputBufferString2);
      }
      else if (checkBuffer == 1)
      {
        printErr("Please enter name of the second table :/");
      }
      else
      {
        printErr("Please enter name of the first table :/");
      }
    }
    else if (!strcmp("display", inputBufferString1))
    {
      checkBuffer = sscanf(inputBufferPtr, "%*s %s", inputBufferString1);
      if (checkBuffer == 1)
      {
        displayTableByName(mainContainer, inputBufferString1);
      }
      else
      {
        displayAllTablesInContainer(mainContainer);
      }
    }
    else if (!strcmp("sort", inputBufferString1))
    {
      checkBuffer = sscanf(inputBufferPtr, "%*s %s %zd", inputBufferString1, &inputBufferSize_t);
      if (checkBuffer == 2)
      {
        sortTableTableByName(mainContainer, inputBufferString1, inputBufferSize_t);
      }
      else if (checkBuffer == 1)
      {
        printErr("Please enter the column that you want to sort by :/");
      }
      else
      {
        printErr("Please enter name of the table :/");
      }
    }
    else if (!strcmp("stat", inputBufferString1))
    {
      checkBuffer = sscanf(inputBufferPtr, "%*s %s", inputBufferString1);
      if (checkBuffer == 1)
      {
        displayStatOfTableByName(mainContainer, inputBufferString1);
      }
      else
      {
        printErr("Please enter name of the table :/");
      }
    }
    else if (!strcmp("import", inputBufferString1))
    {
      checkBuffer = sscanf(inputBufferPtr, "%*s %s %s", inputBufferString1, inputBufferString2);
      if (checkBuffer == 2)
      {
        importToTableByName(mainContainer, inputBufferString1, inputBufferString2);
      }
      else if (checkBuffer == 1)
      {
        printErr("Please enter the file name that wanna be imported :/");
      }
      else
      {
        printErr("Please enter name of the table :/");
      }
    }
    else if (!strcmp("export", inputBufferString1))
    {
      checkBuffer = sscanf(inputBufferPtr, "%*s %s %s", inputBufferString1, inputBufferString2);
      if (checkBuffer == 2)
      {
        exportFromTableByName(mainContainer, inputBufferString1, inputBufferString2);
      }
      else if (checkBuffer == 1)
      {
        printErr("Please enter the file name that wanna be exported :/");
      }
      else
      {
        printErr("Please enter name of the table :/");
      }
    }
    else if (!strcmp("exit", inputBufferString1))
    {
      terminateContainer(&mainContainer);
    }
    else if (!strcmp("help", inputBufferString1))
    {
      fprintf(OUTPUT_STREAM, "command usage list:\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
              "help\t\t\t\t\tShows help",
              "create 'table name' 'columns size'\tCreates a new table in the memory",
              "insert 'table name' [data ...]\t\tInserts new row of data in table which covered in brackets",
              "display\t\t\t\t\tDisplays all tables that located in the memory",
              "display 'table name'\t\t\tDisplays selected table",
              "drop 'table name'\t\t\tRemoves selected table",
              "drop 'table name' 'selected row'\tTo drop a special row of selected table",
              "merge 'first table' 'second table'\tAppends entries of second table at the end of the first",
              "sort 'table name' 'selected column\tTo sort table by selected column",
              "stat 'table name'\t\t\tShows statistics of the table",
              "import 'table name' 'file name'\t\tImports data of a file and append them at the end of table",
              "export 'table name' 'file name'\t\tExports data of a special table to a file",
              "clear\t\t\t\t\tClears console screen",
              "exit\t\t\t\t\tTo exit");
    }
    else if (!strcmp("clear", inputBufferString1))
    {
      clearScreen();
    }
    else
    {
      printErr("This command doesn't available! Try 'help' :D");
    }
  }
  return 0;
}
