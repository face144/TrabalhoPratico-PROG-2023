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
    fflush(stdout);
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

    // Update Routes
    UpdateRoutes(&App->MetroManager);

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
    printf("7 - Importar Rota\n");

    printf("8 - Sair\n");


    int OptionNum = 0;
    while (1)
    {
        printf("\n-> ");
        char Option[16];
        scanf("%s", Option);
        OptionNum = atoi(Option);

        if (OptionNum >= 1 && OptionNum <= 8)
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
            EditRouteMenu(App);
            break;

        case 7:
            ImportRouteMenu(App);
            break;

        case 8:
            SaveData(App);
            exit(0);

        default:
            break;

    }

    printf("\n");
}

_Noreturn void Loop(FAppManager* App)
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
    printf("--- Editar Rota ---\n\n");
    printf("1 - Adicionar estacao\n");
    printf("2 - Remover estacao (Aviso: Nao remove estacao do sistema)\n");
    printf("3 - Apagar rota (Aviso: Nao remove estacoes do sistema)\n");
    printf("\n");

    int OptionNum = 0;
    while (1)
    {
        printf("\n-> ");
        char Option[16];
        scanf("%s", Option);
        OptionNum = atoi(Option);

        if (OptionNum >= 1 && OptionNum <= 3)
            break;

        printf("Opcao invalida\n");
    }

    switch (OptionNum)
    {
        case 1:
        {
            char Route[ROUTE_MAXCHAR];
            printf("Nome da rota: ");
            fflush(stdin);
            gets(Route);
            printf("\n");

            char StationCode[STATION_CODE_LENGTH];
            printf("Codigo da estacao: ");
            fflush(stdin);
            gets(StationCode);
            printf("\n");

            if (AddStationToRoute(&App->MetroManager, StationCode, Route) == 0)
            {
                printf("Erro ao adicionar estacao. Por favor verifique o nome e o codigo\n");
                return 0;
            }

            printf("Estacao com o codigo %s adicionada a rota %s\n", StationCode, Route);
            return 1;
        }
        case 2:
        {
            char Route[ROUTE_MAXCHAR];
            printf("Nome da rota: ");
            fflush(stdin);
            gets(Route);
            printf("\n");

            char StationCode[STATION_CODE_LENGTH];
            printf("Codigo da estacao: ");
            fflush(stdin);
            gets(StationCode);
            printf("\n");

            if (RemoveStationFromRoute(&App->MetroManager, StationCode, Route) == 0)
            {
                printf("Erro ao remover estacao. Por favor verifique o nome e o codigo.\n");
                return 0;
            }

            printf("Estacao com o codigo %s removida da rota %s.\n", StationCode, Route);
            return 1;
        }

        case 3:
        {
            char Route[ROUTE_MAXCHAR];
            printf("Nome da rota: ");
            fflush(stdin);
            gets(Route);
            printf("\n");

            if (DeleteRoute(&App->MetroManager, Route) == 0)
            {
                printf("Erro ao remover rota. Por favor verifique o nome.\n");
                return 0;
            }

            printf("Rota com o nome %s removida.\n", Route);
            return 1;

        }

        default:
            break;
    }

    return 1;
}

int ImportRouteMenu(FAppManager *App)
{
    char Filename[FILENAME_MAXCHAR];
    printf("Nome do ficheiro: ");
    fflush(stdin);
    gets(Filename);
    printf("\n");

    FRoute New = FRouteCreate();
    if (GetRouteFromTextFile(&New, Filename) == 0)
    {
        printf("Erro ao importar rota do ficheiro\n");
        return 0;
    }

    if (AddRoute(&App->MetroManager, &New))
    {
        printf("Erro ao adicionar rota\n");
        return 0;
    }


    printf("Rota adicionada\n");
    return 1;
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

    // Save das Routes
    if (TLinkedListSerialize(&App->MetroManager.RouteList, DEFAULT_ROUTE_SAVE_PATH) == 0)
    {
        printf("AVISO: Erro ao salvar rotas\n");
        system("pause");
        return 0;
    }

    return 1;
}
