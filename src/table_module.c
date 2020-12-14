#include "table_module.h"

TableAddress createTable(const char *tableName, const size_t tableCols)
{
   if (tableCols > 0)
   {
      TableAddress newTable = malloc(sizeof(Table));

      if (newTable)
      {
         snprintf(newTable->uniqueName, MAX_TABLE_NAME_LENGTH, "%s", tableName);
         newTable->cols = tableCols;
         newTable->rows = 0;
      }
      return newTable;
   }
   else
   {
      return NULL;
   }
}

void *deleteTable(TableAddress tableAddr)
{
   if (!tableAddr)
   {
      free(tableAddr);
   }
   return NULL;
}

TableAddress insertIntoTable(TableAddress oldTable, const size_t entriesCount, const double entries[])
{
   TableAddress newTable = realloc(oldTable, sizeof(Table) + ((oldTable->rows + 1) * (oldTable->cols) * sizeof(double)));

   if (newTable)
   {
      for (size_t i = 0; i < newTable->cols; i++)
      {
         if (i < entriesCount)
         {
            newTable->entry[(newTable->rows * newTable->cols) + i] = entries[i];
         }
         else
         {
            newTable->entry[(newTable->rows * newTable->cols) + i] = 0;
         }
      }
      newTable->rows++;
   }
   return newTable;
}

int displayTable(TableAddress tableAddr, FILE *stream)
{
   if (tableAddr->rows != 0)
   {
      for (size_t i = 0; i < tableAddr->rows; i++)
      {
         fprintf(stream, "[%zu] [", i);
         for (size_t j = 0; j < tableAddr->cols; j++)
         {
            fprintf(stream, "%.2lf ", tableAddr->entry[(i * tableAddr->cols) + j]);
         }
         fprintf(stream, "%s", "\b]\n");
      }

      fflush(stream);
      return 1;
   }
   else
   {
      return 0;
   }
}

TableAddress dropFromTable(TableAddress oldTable, const size_t rowToDrop)
{
   if (rowToDrop < oldTable->rows)
   {
      oldTable->rows--;
      if (rowToDrop != oldTable->rows)
      {
         memcpy(&oldTable->entry[oldTable->cols * rowToDrop], &oldTable->entry[oldTable->cols * oldTable->rows], oldTable->cols * sizeof(double));
      }
      TableAddress newTable = realloc(oldTable, sizeof(Table) + (oldTable->rows * oldTable->cols * sizeof(double)));

      return newTable;
   }
   else
   {
      return NULL;
   }
}

int displayStatOfTable(TableAddress tableAddr, FILE *stream)
{
   if (tableAddr->rows != 0)
   {
      double currentCell;
      double sum[tableAddr->cols];
      double sum2[tableAddr->cols];
      double max[tableAddr->cols];
      double min[tableAddr->cols];
      double avg[tableAddr->cols];
      double var[tableAddr->cols];
      double std[tableAddr->cols];

      for (size_t i = 0; i < tableAddr->cols; i++)
      {
         currentCell = tableAddr->entry[i];
         max[i] = currentCell;
         min[i] = currentCell;
         sum[i] = currentCell;
         sum2[i] = currentCell * currentCell;

         for (size_t j = 1; j < tableAddr->rows; j++)
         {
            currentCell = tableAddr->entry[(j * tableAddr->cols) + i];
            if (max[i] < currentCell)
            {
               max[i] = currentCell;
            }
            if (min[i] > currentCell)
            {
               min[i] = currentCell;
            }
            sum[i] += currentCell;
            sum2[i] += currentCell * currentCell;
         }
         avg[i] = (double)sum[i] / tableAddr->rows;
         var[i] = ((double)sum2[i] / tableAddr->rows) - (avg[i] * avg[i]);
         std[i] = sqrt(var[i]);
      }

      fprintf(stream, "[%s] [", "min");
      for (size_t i = 0; i < tableAddr->cols; i++)
      {
         fprintf(stream, "%.2lf ", min[i]);
      }
      fprintf(stream, "%s", "\b]\n");

      fprintf(stream, "[%s] [", "max");
      for (size_t i = 0; i < tableAddr->cols; i++)
      {
         fprintf(stream, "%.2lf ", max[i]);
      }
      fprintf(stream, "%s", "\b]\n");

      fprintf(stream, "[%s] [", "sum");
      for (size_t i = 0; i < tableAddr->cols; i++)
      {
         fprintf(stream, "%.2lf ", sum[i]);
      }
      fprintf(stream, "%s", "\b]\n");

      fprintf(stream, "[%s] [", "avg");
      for (size_t i = 0; i < tableAddr->cols; i++)
      {
         fprintf(stream, "%.2lf ", avg[i]);
      }
      fprintf(stream, "%s", "\b]\n");

      fprintf(stream, "[%s] [", "var");
      for (size_t i = 0; i < tableAddr->cols; i++)
      {
         fprintf(stream, "%.2lf ", var[i]);
      }
      fprintf(stream, "%s", "\b]\n");

      fprintf(stream, "[%s] [", "std");
      for (size_t i = 0; i < tableAddr->cols; i++)
      {
         fprintf(stream, "%.2lf ", std[i]);
      }
      fprintf(stream, "%s", "\b]\n");

      fflush(stream);
      return 1;
   }
   else
   {
      return 0;
   }
}

int sortTable(TableAddress tableAddr, const size_t colToSort)
{
   if (tableAddr->rows != 0)
   {
      double *currentCellPtr;
      double *nextCellPtr;
      double tempRow[tableAddr->cols];

      for (size_t pass = 1; pass < tableAddr->rows; pass++)
      {
         for (size_t i = 0; i < tableAddr->rows - 1; i++)
         {
            currentCellPtr = &tableAddr->entry[(i * tableAddr->cols) + colToSort];
            nextCellPtr = currentCellPtr + tableAddr->cols;

            if (*currentCellPtr < *nextCellPtr)
            {
               currentCellPtr -= colToSort;
               nextCellPtr -= colToSort;

               memcpy(tempRow, currentCellPtr, tableAddr->cols * sizeof(double));
               memcpy(currentCellPtr, nextCellPtr, tableAddr->cols * sizeof(double));
               memcpy(nextCellPtr, tempRow, tableAddr->cols * sizeof(double));
            }
         }
      }
      return 1;
   }
   else
   {
      return 0;
   }
}

TableAddress copyTableEntriesToAnotherTable(TableAddress destTable, TableAddress srcTable)
{
   TableAddress newTable = realloc(destTable, sizeof(Table) + ((destTable->rows + srcTable->rows) * (destTable->cols) * sizeof(double)));

   if (newTable)
   {
      newTable->rows = srcTable->rows + destTable->rows;
      newTable->cols = destTable->cols;
      for (size_t i = destTable->rows; i < newTable->rows; i++)
      {
         for (size_t j = 0; j < newTable->cols; j++)
         {
            if (j < srcTable->cols)
            {
               newTable->entry[(i * newTable->cols) + j] = srcTable->entry[((i - destTable->rows) * srcTable->cols) + j];
            }
            else
            {
               newTable->entry[(i * newTable->cols) + j] = 0;
            }
         }
      }
   }
   return newTable;
}

TableAddress loadTableFromFile(const char *fileName)
{
   FILE *fp = fopen(fileName, "r");
   if (fp)
   {
      char tableName[MAX_TABLE_NAME_LENGTH] = "";
      size_t rows = 0;
      size_t cols = 0;

      rewind(fp);
      fgetsln(tableName, MAX_TABLE_NAME_LENGTH, fp);
      fscanf(fp, "%zd %zd\n", &rows, &cols);

      TableAddress newTable = malloc(sizeof(Table) + (rows * cols * sizeof(double)));
      if (newTable)
      {
         snprintf(newTable->uniqueName, MAX_TABLE_NAME_LENGTH, "%s", tableName);
         newTable->rows = rows;
         newTable->cols = cols;
         for (size_t i = 0; i < rows * cols; i++)
         {
            fscanf(fp, "%lf", &newTable->entry[i]);
         }
         return newTable;
      }
      fclose(fp);
   }
   return NULL;
}

int saveTableIntoFile(TableAddress tableAddr, const char *fileName)
{
   FILE *fp = fopen(fileName, "w");
   if (fp)
   {
      rewind(fp);
      fprintf(fp, "%s\n%zd %zd\n", tableAddr->uniqueName, tableAddr->rows, tableAddr->cols);
      for (size_t i = 0; i < tableAddr->rows * tableAddr->cols; i++)
      {
         fprintf(fp, "%.2lf ", tableAddr->entry[i]);
      }

      fflush(fp);
      fclose(fp);
      return 1;
   }
   return 0;
}