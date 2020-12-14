#ifndef TABLE_MODULE_H
#define TABLE_MODULE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "custom_io_module.h"

#define MAX_TABLE_NAME_LENGTH 1024

typedef struct Table
{
   char uniqueName[MAX_TABLE_NAME_LENGTH];
   size_t rows;
   size_t cols;
   double entry[];
} Table;
typedef Table *TableAddress;

TableAddress createTable(const char *tableName, const size_t tableCols);
TableAddress insertIntoTable(TableAddress oldTable, const size_t entriesCount, const double entries[]);
void *deleteTable(TableAddress tableAddr);
int displayTable(TableAddress tableAddr, FILE *stream);
TableAddress dropFromTable(TableAddress oldTable, const size_t rowToDrop);
int displayStatOfTable(TableAddress tableAddr, FILE *stream);
int sortTable(TableAddress tableAddr, const size_t colToSort);
TableAddress copyTableEntriesToAnotherTable(TableAddress destTable, TableAddress srcTable);
TableAddress loadTableFromFile(const char *fileName);
int saveTableIntoFile(TableAddress tableAddr, const char *fileName);

#endif