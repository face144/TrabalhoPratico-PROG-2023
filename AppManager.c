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

    printf("1 - Visualizar Metro\n");

    printf("\n");

    printf("2 - Visualizar Estacoes\n");
    printf("3 - Adicionar Estacoes\n");
    printf("4 - Remover Estacao\n");

    printf("\n");

    printf("5 - Visualizar Rotas\n");
    printf("6 - Adicionar Rotas\n");
    printf("7 - Editar Rota\n");
    printf("8 - Importar Rota\n");

    printf("\n");

    printf("9 - Sair\n");


    int OptionNum = 0;
    while (1)
    {
        printf("\n-> ");
        char Option[16];
        scanf("%s", Option);
        OptionNum = atoi(Option);

        if (OptionNum >= 1 && OptionNum <= 9)
            break;

        printf("Opcao invalida\n");
    }

    switch (OptionNum) {

        case 1:
            PrintMetro(&App->MetroManager);
            break;

        case 2:
            PrintStations(&App->MetroManager);
            break;

        case 3:
            AddStationMenu(App);
            break;

        case 4:
            RemoveStationMenu(App);
            break;

        case 5:
            PrintRoutes(&App->MetroManager);
            break;

        case 6:
            AddRouteMenu(App);
            break;

        case 7:
            EditRouteMenu(App);
            break;

        case 8:
            ImportRouteMenu(App);
            break;

        case 9:
            SaveData(App);
            FMetroManagerDestroy(&App->MetroManager);
            exit(0);

        default:
            break;

    }

    system("pause");
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
    if (Temp == NULL)
    {
        printf("AVISO: Nao foi possivel adicionar estacao.\n");
        printf("Por favor verifique se o nome esta repetido ou se tem mais de 3 caracteres\n");
        return 0;
    }

    printf("AVISO: Estacao adicionada com o codigo %s.\n", Temp->StationCode);
    return 1;
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
        printf("Por favor verifique se a estacao tem o nome repetido ou se tem mais de 3 caracteres\n");
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

    if (AddRouteFromTextFile(&App->MetroManager, Filename) == 0)
    {
        printf("AVISO: Erro ao importar rota do ficheiro\n");
        printf("Por favor verifique se o nome do ficheiro esta correto\n");
        printf("Por favor verifique tambem se o nome da rota esta repetido e se as estacoes existem no sistema\n");
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
