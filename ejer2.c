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


int main() 
{
    ListaTareas* TareasPendientes = NULL;
    ListaTareas* TareasRealizadas = NULL;
    int cant_tarea;
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

    printf("\nMostramos las Tareas pendientes:\n");
    for (int i = 0; i < cant_tarea; i++)
    {
        printf("Tarea P %d:\n", i + 1);
        mostrarTarea(TareasPendientes[i]);
        sleep(1);
    }
    sleep(1);

    printf("\nMostramos las Tareas Realizadas\n");
    for (int i = 0; i < cant_tarea; i++)
    {
        printf("Tarea R %d:\n", i + 1);
        mostrarTarea(TareasRealizadas[i]);
        sleep(1);
    }
    sleep(1);

    liberarMemoria(TareasPendientes, cant_tarea);
    liberarMemoria(TareasRealizadas, cant_tarea);
    return 0;
}

//DECLARACION DE FUNCIONES 

//funciones de memoria

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
//================================================

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
    printf("\nDuracion de la tarea: %d\n", Tareas->Duracion);
    printf("\nID: %d\n",Tareas->TareaID);
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