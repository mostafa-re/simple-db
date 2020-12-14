#ifndef TABLE_MANAGER_MODULE_H
#define TABLE_MANAGER_MODULE_H

#include "table_module.h"

typedef struct Container
{
   size_t countOfTables;
   TableAddress tables[];
} Container;
typedef Container *ContainerAddress;

ContainerAddress createContainer();
TableAddress *searchTableInContainer(const ContainerAddress containerAddr, const char *tableName);
void addTableToContainer(ContainerAddress *containerAddressPtr, const char *tableName, const size_t tableCols);
void displayTableByName(const ContainerAddress containerAddr, const char *tableName);
void displayStatOfTableByName(const ContainerAddress containerAddr, const char *tableName);
void dropFromTableByName(ContainerAddress containerAddr, const char *tableName, const size_t rowToDrop);
void removeTableFromContainer(ContainerAddress *containerAddressPtr, const char *tableName);
void displayAllTablesInContainer(ContainerAddress containerAddr);
void mergeTwoTable(ContainerAddress *containerAddressPtr, const char *tableName1, const char *tableName2);
void sortTableTableByName(const ContainerAddress containerAddr, const char *tableName, const size_t tableCols);
void importToTableByName(ContainerAddress containerAddr, const char *tableName, const char *fileName);
void exportFromTableByName(ContainerAddress containerAddr, const char *tableName, const char *fileName);
void insertDataIntoTableByName(const ContainerAddress containerAddr, const char *tableName, char *dataString);
void terminateContainer(ContainerAddress *containerAddressPtr);

#endif