#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Tarea 
{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef TAREA;

typedef TAREA* ListaTareas; //puntero a TAREA

void asignarMemoria(ListaTareas* doblePTareas, int cant);
void liberarMemoria(ListaTareas *doblePTareas, int cant);
void cargarTarea(ListaTareas Tarea, int id);
void mostrarTarea(ListaTareas Tareas);
void verificarTareas(ListaTareas *TareasP, ListaTareas *TareasR, int cant);
TAREA buscarTareaID(ListaTareas *doblePTarea, int id, int cant);
TAREA buscarTareaPalabra(ListaTareas *doblePTarea, int cant, char palabra[]);
int menu();

int main() 
{
    ListaTareas* TareasPendientes = NULL;
    ListaTareas* TareasRealizadas = NULL;
    int cant_tarea, id;
    printf("\nIngresar la cantidad de tareas a realizar\n");
    scanf("%d", &cant_tarea);
    fflush(stdin);

    TareasPendientes = (ListaTareas*)malloc(sizeof(ListaTareas) * cant_tarea);
    TareasRealizadas = (ListaTareas*)malloc(sizeof(ListaTareas) * cant_tarea);
    asignarMemoria(TareasPendientes, cant_tarea);
    asignarMemoria(TareasRealizadas, cant_tarea);

    for (int i = 0; i < cant_tarea; i++) {

        printf("\nCargar tarea %d:\n", i + 1);

        cargarTarea(TareasPendientes[i],i); // Paso el id
    }
    for (int i = 0; i < cant_tarea; i++) {
        printf("\nTarea %d:\n", i + 1);
        mostrarTarea(TareasPendientes[i]);
    }
    
    verificarTareas(TareasPendientes, TareasRealizadas, cant_tarea);

    printf("\n==================Tareas pendientes=======================\n");
    for (int i = 0; i < cant_tarea; i++)
    {
        printf("\nTarea P %d:", i + 1);
        if (TareasPendientes[i] !=NULL)
        {
            mostrarTarea(TareasPendientes[i]);
        } else {
            printf("\nTarea no realizada\n");
        }
        
        
        mostrarTarea(TareasPendientes[i]);
        sleep(1);
    }
    sleep(1);

    printf("\n==================Tareas Realizadas========================\n");
    for (int i = 0; i < cant_tarea; i++)
    {
        printf("\nTarea R %d:", i + 1);
        if (TareasRealizadas[i] != NULL)
        {
        mostrarTarea(TareasRealizadas[i]);
        } else {
          printf("\nTarea no realizada\n");
        }
        
        
        sleep(1);
    }
    sleep(1);

    int opcion = menu();

    TAREA tareaBuscada;
    switch (opcion)
    {
    case 1:
        printf("\n=============BUSQUEDA POR ID=========================\n");
    
        printf("\nIngrese el ID de la tarea a buscar\n");
        
        scanf("%d", &id);
        printf("\nBuscamos en tareas pendientes:\n");
        
        tareaBuscada = buscarTareaID(TareasPendientes, id, cant_tarea);
        if (tareaBuscada.TareaID == -1 )
        {
            printf("\nNo se encuentra en tareas pendientes, buscamos en tareas realizadas\n");
            printf("\nBuscamos en tareas realizadas:\n");
        
            tareaBuscada = buscarTareaID(TareasRealizadas, id, cant_tarea);
            if (tareaBuscada.TareaID != -1)
            {
                printf("\nSe encontro en tareas realizadas\n");
                mostrarTarea(&tareaBuscada);
            } else {
                printf("\nNo existe ninguna tarea con ese ID\n");
            }   
        } else {
            printf("\nSe encontro en tareas pendientes\n");
            mostrarTarea(&tareaBuscada);
        }
    break;
    
    case 2:
        printf("\n=============BUSQUEDA POR PALABRA=========================\n");
        //BUSQUEDA DE TAREAS POR PALABRA
        printf("\nIngrese la palabra de la tarea a buscar\n");
        char palabra[15];
        scanf("%s", palabra);

        printf("\nBuscamos en tareas pendientes:\n");
        tareaBuscada = buscarTareaPalabra(TareasPendientes, cant_tarea, palabra);
        if (tareaBuscada.TareaID == -1 )
        {
            printf("\nNo se encuentra en tareas pendientes, buscamos en tareas realizadas\n");
            printf("\nBuscamos en tareas realizadas:\n");

            tareaBuscada = buscarTareaPalabra(TareasRealizadas, cant_tarea, palabra);
            if (tareaBuscada.TareaID != -1)
            {
                printf("\nSe encontro en tareas realizadas\n");
                mostrarTarea(&tareaBuscada);
            } else {
                printf("\nNo existe ninguna tarea con esa palabra\n");
            }   
        } else {
            printf("\nSe encontro en tareas pendientes\n");
            mostrarTarea(&tareaBuscada);
        }
    break;
    }

    //LIBERAMOS MEMORIA
    liberarMemoria(TareasPendientes, cant_tarea);
    liberarMemoria(TareasRealizadas, cant_tarea);
    return 0;
}

//DECLARACION DE FUNCIONES 

//FUNCIONES DE MEMORIA
int menu()
{
    int opcion;
    printf("\n============MENU==========\n");
    printf("0-Salir del programa\n1- Busqueda por ID\n2-Busqueda por palabra clave\n");
    scanf("%d", &opcion);  
}

void asignarMemoria(ListaTareas* doblePTareas, int cant)
{
    for (int i = 0; i < cant; i++)
    {
        doblePTareas[i] = (ListaTareas)malloc(sizeof(TAREA));
    }
}

void liberarMemoria(ListaTareas *doblePTareas, int cant)
{
    for (int i = 0; i < cant; i++)
    {
        free(doblePTareas[i]);
    }    
}
//======================================================
void cargarTarea(ListaTareas Tarea, int id)
{
    Tarea->TareaID = id;
    fflush(stdin);
    char *buffer = (char *)malloc(sizeof(char) * 100);
    printf("Ingrese la descripcion de la tarea:\n");
    gets(buffer);
    Tarea->Descripcion = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(Tarea->Descripcion, buffer);
    free(buffer);
    printf("\nIngrese la duracion de la tarea (entre 10 y 100):\n");
    scanf("%d", &(Tarea->Duracion));
    fflush(stdin);
}
    
void mostrarTarea(ListaTareas Tareas) 
{
    if (Tareas != NULL)
    {
    printf("\nDescripcion de la tarea: %s\n", Tareas->Descripcion);
    printf("Duracion de la tarea: %d\n", Tareas->Duracion);
    printf("ID: %d\n\n",Tareas->TareaID);
    }
}

void verificarTareas(ListaTareas* TareasP, ListaTareas* TareasR, int cant) 
{
    
    for (int i = 0; i < cant; i++)
    {
        int respuesta;
        printf("Realizo la tarea %d?\n1) Si\n2) No\n", i + 1);
        scanf("%d", &respuesta);
        if (respuesta == 1)
        {
            TareasR[i] = TareasP[i];
            TareasP[i] = NULL;
        } else  {
            TareasR[i] = NULL;
        }
        
    }
    
}

//EJER 2)6
TAREA buscarTareaID(ListaTareas* doblePTarea,int id, int cant)
{
    printf("\nfuncion buscarTareaID\n");
    for (int i = 0; i < cant; i++)
    {
        if (doblePTarea[i] != NULL)
        {
            if (doblePTarea[i]->TareaID == id)
            {
                printf("\nSe encontro el id que coincide\n");
                return *doblePTarea[i];
            }
        }
        
    }
    TAREA tareaNoEncontrada;
    tareaNoEncontrada.TareaID = -1; //o cualquier otro valor que indique que la tarea no fue encontrada
    printf("\nNo se encontro la tarea de id = %d\n", id);
    return tareaNoEncontrada;
}

//EJER 2)7
TAREA buscarTareaPalabra(ListaTareas* doblePTarea, int cant, char palabra[]) 
{
    char *puntPalabra = NULL;
    for (int i = 0; i < cant; i++)
    {
        if (doblePTarea[i] != NULL)
        {
            puntPalabra = strstr(doblePTarea[i]->Descripcion, palabra);
            if (puntPalabra) {
                puts(puntPalabra);
                return *doblePTarea[i];
            }
        }
        
    }
    TAREA tareaNoEncontrada;
    tareaNoEncontrada.TareaID = -1;
    return tareaNoEncontrada;
}