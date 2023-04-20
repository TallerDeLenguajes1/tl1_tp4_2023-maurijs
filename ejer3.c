/*Cree un nuevo branch llamado lista-enlazada donde tendrá que reemplazar la
implementación que realizó con listas enlazadas, para ello en vez de tener 2 arreglos de
tareas ahora tendrá 2 listas enlazadas (una para las tareas pendientes y otra para las tareas
realizadas) y cada vez que se marque como realizada tendrá que mover la tarea de la lista de
tareas pendientes a la lista de tareas realizada
Tareas
Cada empleado tiene un listado de tareas a realizar.
Las estructuras de datos necesarias son las siguientes: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Tarea{
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
}typedef TAREA;

struct Nodo{
TAREA Tarea;
struct Nodo *Siguiente;
};

typedef struct Nodo *ListaTareas;

void liberarMemoria(ListaTareas TareasPendientes, ListaTareas TareasRealizadas);
ListaTareas crearLista();
ListaTareas crearNodoTarea(ListaTareas TareasPendientes, int id, char descripcion[], int duracion);
void verificarTareas(ListaTareas TareasPendientes, ListaTareas TareasRealizadas, int cant_tareas);
void EliminarNodo(ListaTareas *ListaT, int id);

int main() 
{
    int cant_tareas, duracion;
    char descripcion[30];
    ListaTareas TareasPendientes;
    ListaTareas TareasRealizadas;

    TareasPendientes = crearLista();
    TareasRealizadas = crearLista();

    printf("Ingrese la cantidad de tareas\n");
    scanf("%d", &cant_tareas);
    for (int i = 0; i <cant_tareas; i++)
    {
        printf("\nTAREA %d:", i + 1);
        gets(descripcion);
        printf("\nIngresar descripcion:");
        scanf("%d", &duracion);
        printf("\nIngresar duracion:");
        TareasPendientes = insertarNodoTarea(TareasPendientes, i, descripcion, duracion);
    }

    verificarTareas(TareasPendientes, TareasRealizadas,cant_tareas);
}

//DECLARACION DE FUNCIONES

ListaTareas crearLista()
{
    return NULL;
}
ListaTareas crearNodoTarea(ListaTareas TareasPendientes, int id, char descripcion[], int duracion)
{   
    ListaTareas nuevaTarea;
    nuevaTarea = (ListaTareas)malloc(sizeof(struct Nodo));

    nuevaTarea->Tarea.TareaID = id; 
    strcpy(nuevaTarea->Tarea.Descripcion, descripcion);
    nuevaTarea->Tarea.Duracion = duracion;
    nuevaTarea->Siguiente = TareasPendientes;
    TareasPendientes = nuevaTarea;
    return TareasPendientes;
}

void verificarTareas(ListaTareas TareasPendientes, ListaTareas TareasRealizadas, int cant_tareas) 
{
    for (int i = 0; i < cant_tareas; i++)
    {
        int respuesta;
        print("Realizo la tarea %d?\n", i + 1);
        printf("1-Si\n2-No\n");
        scanf("%d", &respuesta);
        if (respuesta == 1){
            TareasRealizadas = insertarNodoTarea(TareasPendientes, i+1, TareasRealizadas->Tarea.Descripcion, TareasRealizadas->Tarea.Duracion);
            EliminarNodo(TareasPendientes, i);
        }
    }
}

void liberarMemoria(ListaTareas TareasPendientes, ListaTareas TareasRealizadas) 
{
    ListaTareas aux = TareasPendientes;
    while (aux)
    {
        free(aux);
        TareasPendientes = TareasPendientes->Siguiente;
        aux = TareasPendientes;
    }

    ListaTareas aux = TareasRealizadas;
    
    while (aux)
    {
        free(aux);
        TareasRealizadas = TareasRealizadas->Siguiente;
        aux = TareasRealizadas;
    }
}

void EliminarNodo(ListaTareas * ListaT, int id)
{
ListaTareas Aux = ListaT;
ListaTareas AuxAnterior = ListaT;
while (Aux && Aux->Tarea.TareaID != id)
{
    AuxAnterior = Aux;
    Aux = Aux->Siguiente;
}
if(Aux) 
{
    AuxAnterior->Siguiente = Aux->Siguiente;
    free(Aux);
}
}
