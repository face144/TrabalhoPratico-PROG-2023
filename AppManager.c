#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AppManager.h"

int Init(FAppManager* App)
{
    if (App == NULL)
    {
        return 0;
    }

    srand(time(0));
    App->MetroManager = FMetroManagerCreate();

    // Load from save files
    if (TDynamicArrayDeserialize(&App->MetroManager.StationList, DEFAULT_STATION_SAVE_PATH) == 0)
    {
        printf("Erro ao carregar informacao das estacoes\n");
    }


    if (TLinkedListDeserialize(&App->MetroManager.RouteList, DEFAULT_ROUTE_SAVE_PATH) == 0)
    {
        printf("Erro ao carregar informacao das rotas\n");
    }

    return 1;
}

void Menu(FAppManager* App)
{
    printf("--- Menu ---\n");

    printf("1 - Visualizar Estacoes\n");
    printf("2 - Adicionar Estacoes\n");
    printf("3 - Remover Estacao\n");

    printf("4 - Visualizar Rotas\n");
    printf("5 - Adicionar Rotas\n");
    printf("6 - Editar Rota\n");
    printf("7 - Remover Rota\n");
    printf("8 - Importar Rota\n");

    printf("9 - Sair\n");


    int OptionNum = 0;
    while (1)
    {
        printf("\nInput: \n");
        char Option[16];
        scanf("%s", Option);
        OptionNum = atoi(Option);

        if (OptionNum >= 1 && OptionNum <= 9)
            break;

        printf("Opcao invalida\n");
    }

    switch (OptionNum) {

        case 1:
            PrintStations(&App->MetroManager);
            break;

        case 2:
            AddStationMenu(App);
            break;

        case 3:
            RemoveStationMenu(App);
            break;

        case 4:
            PrintRoutes(&App->MetroManager);
            break;

        case 5:
            AddRouteMenu(App);
            break;

        case 6:
            break;

        case 7:
            break;

        case 8:
            break;

        case 9:
            SaveData(App);
            exit(0);

        default:
            break;

    }

    printf("\n");
}

void Loop(FAppManager* App)
{
    while(1)
    {
        Menu(App);
    }
}

int AddStationMenu(FAppManager* App)
{
    printf("--- Adicionar nova estacao ---\n\n");
    printf("Nome: ");
    char Nome[32];
    fflush(stdin);
    gets(Nome);

    FStation* Temp = AddStation(&App->MetroManager, Nome);
    if (Temp != NULL)
    {
        printf("AVISO: Estacao adicionada com o codigo %s.\n", Temp->StationCode);
        return 1;
    }

    printf("AVISO: Nao foi possivel adicionar estacao. Por favor verifique se o nome esta repetido.\n");
    return 0;
}

int RemoveStationMenu(FAppManager *App)
{
    printf("--- Remover estacao ---\n\n");
    printf("Codigo: ");
    char Code[32];
    fflush(stdin);
    gets(Code);

    if (DeleteStation(&App->MetroManager, Code) == 1)
    {
        printf("AVISO: Estacao com o codigo %s removida\n", Code);
        return 1;
    }

    printf("AVISO: Nao foi possivel econtrar uma estacao com o codigo %s."
           " Por favor verifique se o codigo esta correto.\n", Code);
    return 0;
}

int AddRouteMenu(FAppManager *App)
{
    printf("--- Adicionar rota ---\n\n");
    printf("Nome: ");
    char Name[32];
    fflush(stdin);
    gets(Name);

    FRoute New = FRouteCreate();
    strcpy(New.RouteName, Name);
    if (AddRoute(&App->MetroManager, &New) == 0)
    {
        printf("AVISO: Erro ao adicionar rota\n");
        return 0;
    }

    printf("AVISO: Rota com o nome %s foi adicionada\n", New.RouteName);
    return 1;
}

int EditRouteMenu(FAppManager *App)
{

}

int SaveData(FAppManager *App)
{
    // Estacoes
    if (TDynamicArraySerialize(&App->MetroManager.StationList, DEFAULT_STATION_SAVE_PATH) == 0)
    {
        printf("AVISO: Erro ao salvar estacoes\n");
        system("pause");
        return 0;
    }

    // Todo: Save das Routes
    if (TLinkedListSerialize(&App->MetroManager.RouteList, DEFAULT_ROUTE_SAVE_PATH) == 0)
    {
        printf("AVISO: Erro ao salvar rotas\n");
        system("pause");
        return 0;
    }

    return 1;
}
