#include "table_manager_module.h"

ContainerAddress createContainer()
{
   ContainerAddress newContainer = malloc(sizeof(Container));
   if (newContainer)
   {
      newContainer->countOfTables = 0;
   }
   return newContainer;
}

void addTableToContainer(ContainerAddress *containerAddressPtr, const char *tableName, const size_t tableCols)
{
   if (tableCols > 0)
   {
      if (strlen(tableName) <= MAX_TABLE_NAME_LENGTH)
      {
         if (!searchTableInContainer(*containerAddressPtr, tableName))
         {
            TableAddress table = createTable(tableName, tableCols);
            if (table)
            {
               ContainerAddress newContainer = realloc(*containerAddressPtr, sizeof(Container) + (((*containerAddressPtr)->countOfTables + 1) * sizeof(TableAddress)));
               if (newContainer)
               {
                  (*containerAddressPtr)->tables[(*containerAddressPtr)->countOfTables] = table;
                  (*containerAddressPtr)->countOfTables++;

                  *containerAddressPtr = newContainer;
               }
               else
               {
                  printErr("Failed to add new table, because we cannot allocate memory :(");
                  deleteTable(table);
               }
            }
            else
            {
               printErr("Failed to create new table, because we cannot allocate memory :(");
            }
         }
         else
         {
            printErr("Sorry, this table name has been chosen before :(");
         }
      }
      else
      {
         printErr("Failed to create new table, because of long name that has been chosen :|");
      }
   }
   else
   {
      printErr("Failed to create new table, because of invalid columns size :|");
   }
}

TableAddress *searchTableInContainer(const ContainerAddress containerAddr, const char *tableName)
{
   for (size_t i = 0; i < containerAddr->countOfTables; i++)
   {
      if (!strcmp(containerAddr->tables[i]->uniqueName, tableName))
      {
         return &containerAddr->tables[i];
      }
   }
   return NULL;
}

void displayTableByName(const ContainerAddress containerAddr, const char *tableName)
{
   TableAddress *table = searchTableInContainer(containerAddr, tableName);

   if (table)
   {
      if ((*table)->rows != 0)
      {
         fprintf(OUTPUT_STREAM, "%s DISPLAY table '%s' with %zd ROWS and %zd COLS below:\n", INFO_NOTIFIER, (*table)->uniqueName, (*table)->rows, (*table)->cols);
         displayTable((*table), OUTPUT_STREAM);
         fputc('\n', OUTPUT_STREAM);
      }
      else
      {
         printErr("Sorry, this table is empty :|");
      }
   }
   else
   {
      printErr("Sorry, this table doesn't exist :(");
   }
}

void displayStatOfTableByName(const ContainerAddress containerAddr, const char *tableName)
{
   TableAddress *table = searchTableInContainer(containerAddr, tableName);

   if (table)
   {
      if ((*table)->rows != 0)
      {
         fprintf(OUTPUT_STREAM, "%s STATISTICS table '%s' with %zd ROWS and %zd COLS below:\n", INFO_NOTIFIER, (*table)->uniqueName, (*table)->rows, (*table)->cols);
         displayStatOfTable((*table), OUTPUT_STREAM);
         fputc('\n', OUTPUT_STREAM);
      }
      else
      {
         printErr("Sorry, this table is empty :|");
      }
   }
   else
   {
      printErr("Sorry, this table doesn't exist :(");
   }
}

void dropFromTableByName(ContainerAddress containerAddr, const char *tableName, const size_t rowToDrop)
{
   TableAddress *table = searchTableInContainer(containerAddr, tableName);

   if (table)
   {
      if ((*table)->rows != 0)
      {
         if (rowToDrop < (*table)->rows)
         {
            TableAddress newTable = dropFromTable((*table), rowToDrop);
            if (newTable)
            {
               *table = newTable;
            }
            else
            {
               printErr("Failed to drop selected row from table, because we cannot allocate memory :(!");
            }
         }
         else
         {
            printErr("Sorry, the entered row isn't in range :|");
         }
      }
      else
      {
         printErr("Sorry, this table is empty :|");
      }
   }
   else
   {
      printErr("Sorry, this table doesn't exist :(");
   }
}

void removeTableFromContainer(ContainerAddress *containerAddressPtr, const char *tableName)
{
   TableAddress *table = searchTableInContainer(*containerAddressPtr, tableName);

   if (table)
   {
      deleteTable(*table);
      (*containerAddressPtr)->countOfTables--;

      if (*table != (*containerAddressPtr)->tables[(*containerAddressPtr)->countOfTables])
      {
         *table = (*containerAddressPtr)->tables[(*containerAddressPtr)->countOfTables];
      }
      (*containerAddressPtr)->tables[(*containerAddressPtr)->countOfTables] = NULL;
      *containerAddressPtr = realloc(*containerAddressPtr, sizeof(Container) + ((*containerAddressPtr)->countOfTables * sizeof(TableAddress)));
   }
   else
   {
      printErr("Sorry, this table doesn't exist :|");
   }
}

void displayAllTablesInContainer(ContainerAddress containerAddr)
{
   if (containerAddr->countOfTables != 0)
   {
      for (size_t i = 0; i < containerAddr->countOfTables; i++)
      {
         fprintf(OUTPUT_STREAM, "%s #%zd table '%s' with %zd ROWS and %zd COLS\n", INFO_NOTIFIER, i + 1, containerAddr->tables[i]->uniqueName, containerAddr->tables[i]->rows, containerAddr->tables[i]->cols);
      }
      fputc('\n', OUTPUT_STREAM);
   }
   else
   {
      printErr("Ooh, there isn't any table here :|");
   }
}

void mergeTwoTable(ContainerAddress *containerAddressPtr, const char *tableName1, const char *tableName2)
{
   TableAddress *table1 = searchTableInContainer(*containerAddressPtr, tableName1);

   if (table1)
   {
      TableAddress *table2 = searchTableInContainer(*containerAddressPtr, tableName2);
      if (table2)
      {
         TableAddress newTable = copyTableEntriesToAnotherTable(*table1, *table2);
         if (newTable)
         {
            *table1 = newTable;
            removeTableFromContainer(containerAddressPtr, tableName2);
         }
         else
         {
            printErr("Failed to merge two tables, because we cannot allocate memory :(");
         }
      }
      else
      {
         printErr("Sorry, second table doesn't exist :|");
      }
   }
   else
   {
      printErr("Sorry, first table doesn't exist :|");
   }
}

void sortTableTableByName(const ContainerAddress containerAddr, const char *tableName, const size_t tableCols)
{
   TableAddress *table = searchTableInContainer(containerAddr, tableName);

   if (table)
   {
      if ((*table)->rows != 0)
      {
         sortTable(*table, tableCols);
      }
      else
      {
         printErr("Sorry, this table is empty :|");
      }
   }
   else
   {
      printErr("Sorry, this table doesn't exist :(");
   }
}

void importToTableByName(ContainerAddress containerAddr, const char *tableName, const char *fileName)
{
   TableAddress *table = searchTableInContainer(containerAddr, tableName);

   if (table)
   {
      TableAddress importedTable = loadTableFromFile(fileName);
      if (importedTable)
      {
         if (importedTable->cols == (*table)->cols)
         {
            TableAddress newTable = copyTableEntriesToAnotherTable(*table, importedTable);
            if (newTable)
            {
               *table = newTable;
            }
            else
            {
               printErr("Failed to add table to the container, because we cannot allocate memory :(");
            }
         }
         else
         {
            printErr("Ooh, imported table and the current table doesn't match in columns :/");
         }
         deleteTable(importedTable);
      }
      else
      {
         printErr("Failed to load the file, maybe this file doesn't exist :/");
      }
   }
   else
   {
      printErr("Sorry, this table doesn't exist :(");
   }
}

void exportFromTableByName(ContainerAddress containerAddr, const char *tableName, const char *fileName)
{
   TableAddress *table = searchTableInContainer(containerAddr, tableName);

   if (table)
   {
      if (saveTableIntoFile(*table, fileName))
      {
         fprintf(OUTPUT_STREAM, "%s table '%s' with %zd ROWS and %zd COLS successfully saved in %s \n", INFO_NOTIFIER, (*table)->uniqueName, (*table)->rows, (*table)->cols, fileName);
      }
      else
      {
         printErr("Failed to save the file, maybe it's READ-ONLY :(");
      }
   }
   else
   {
      printErr("Sorry, this table doesn't exist :(");
   }
}

void insertDataIntoTableByName(const ContainerAddress containerAddr, const char *tableName, char *dataString)
{
   TableAddress *table = searchTableInContainer(containerAddr, tableName);

   if (table)
   {
      double data[(*table)->cols];
      char *tmpPtr = dataString;
      while (*tmpPtr != '[')
      {
         if (!*tmpPtr)
         {
            printErr("Invalid data entering query :/");
            return;
         }
         *tmpPtr = ' ';
         tmpPtr++;
      }
      *tmpPtr = ' ';
      tmpPtr++;
      while (*tmpPtr != ']')
      {
         if (!*tmpPtr || *tmpPtr == '[')
         {
            printErr("Invalid data entering query :/");
            return;
         }
         tmpPtr++;
      }
      *tmpPtr = '\0';

      tmpPtr = dataString;
      size_t i = 0;
      char *token;
      while ((token = strtok_r(tmpPtr, " \t\v", &tmpPtr)))
      {
         if (sscanf(token, "%lf", &data[i]) == 1)
         {
            if (i < (*table)->cols)
            {

               i++;
            }
            else
            {
               printErr("Sorry, the data that have been entered doesn't match with table columns :/");
               return;
            }
         }
         else
         {
            printErr("Invalid data :|");
            return;
         }
      }

      if (i < (*table)->cols)
      {
         printErr("Sorry, the data that have been entered doesn't match with table columns :/");
         return;
      }

      TableAddress newTable = insertIntoTable(*table, (*table)->cols, data);
      if (newTable)
      {
         *table = newTable;
      }
      else
      {
         printErr("Failed to insert data into table, because we cannot allocate memory :(");
      }
   }
   else
   {
      printErr("Sorry, this table doesn't exist :(");
   }
}

void terminateContainer(ContainerAddress *containerAddressPtr)
{
   for (size_t i = 0; i < (*containerAddressPtr)->countOfTables; i++)
   {
      deleteTable((*containerAddressPtr)->tables[i]);
   }
   free(*containerAddressPtr);
   *containerAddressPtr = NULL;
}