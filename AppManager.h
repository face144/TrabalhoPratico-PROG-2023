#ifndef TRABALHOPRATICO_APPMANAGER_H
#define TRABALHOPRATICO_APPMANAGER_H

#include "Metro/MetroManager.h"

#define DEFAULT_STATION_SAVE_PATH "Stations.bin"
#define DEFAULT_ROUTE_SAVE_PATH "Routes.bin"
#define FILENAME_MAXCHAR 32

typedef struct FAppManager
{
    FMetroManager MetroManager;

} FAppManager;

int Init(FAppManager* App);

_Noreturn void Loop(FAppManager* App);

void Menu(FAppManager* App);
int AddStationMenu(FAppManager* App);
int RemoveStationMenu(FAppManager* App);

int AddRouteMenu(FAppManager* App);
int EditRouteMenu(FAppManager* App);
int ImportRouteMenu(FAppManager* App);

int SaveData(FAppManager* App);

#endif //TRABALHOPRATICO_APPMANAGER_H
