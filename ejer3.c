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

void liberarMemoria(ListaTareas LTareas);
ListaTareas crearLista();
ListaTareas crearNodoTarea(ListaTareas LTareas, int id, char*descripcion, int duracion);
void verificarTareas(ListaTareas *TareasPendientes, ListaTareas *TareasRealizadas, int cant_tareas);
void EliminarNodo(ListaTareas *ListaT, int id);
void mostrarTareas(ListaTareas ListaT);

int main() 
{
    int opcion, duracion;
    int cant = 0;
    char *buffer = NULL;
    char descripcion[30];
    ListaTareas TareasPendientes;
    ListaTareas TareasRealizadas;

    TareasPendientes = crearLista();
    TareasRealizadas = crearLista();
    do
    {
        cant++;
        buffer = (char *)malloc(sizeof(char) * 30);
        printf("\nTAREA %d:", cant);
        printf("\nIngresar descripcion:");
        scanf("%29s", buffer);
        fflush(stdin);
        printf("Ingresar duracion:");
        scanf("%d", &duracion);
        TareasPendientes = crearNodoTarea(TareasPendientes, cant, buffer, duracion); 
        free(buffer);
        printf("Desea ingresar una nueva tarea?\n1-Si\n2-No\n");
        scanf("%d", &opcion);
    } while (opcion == 1);

    sleep(1);
    printf("\n=================Muestro las tareas ingresadas=====================\n");
    mostrarTareas(TareasPendientes);
    verificarTareas(&TareasPendientes, &TareasRealizadas, cant); //

    printf("\n=============TAREAS PENDIENTES==============\n");
    mostrarTareas(TareasPendientes);
    printf("\n=============TAREAS REALIZADAS==============\n");
    mostrarTareas(TareasRealizadas);

    liberarMemoria(TareasPendientes);
    liberarMemoria(TareasRealizadas);
}

//DECLARACION DE FUNCIONES

ListaTareas crearLista()
{
    return NULL;
}
ListaTareas crearNodoTarea(ListaTareas LTareas, int id, char*descripcion, int duracion)
{   
    ListaTareas nuevaTarea;
    nuevaTarea = (ListaTareas)malloc(sizeof(struct Nodo));

    nuevaTarea->Tarea.TareaID = id;
    nuevaTarea->Tarea.Descripcion = (char *)malloc(sizeof(char)*(strlen(descripcion) + 1));
    strcpy(nuevaTarea->Tarea.Descripcion, descripcion);
    nuevaTarea->Tarea.Duracion = duracion;
    nuevaTarea->Siguiente = LTareas;
    LTareas = nuevaTarea;
    return LTareas;
}

void EliminarNodo(ListaTareas*ListaT, int id) {
    // Verificar si la lista está vacía
    if (ListaT == NULL) {
        return;
    }
    
    // Encontrar el nodo con el dato a eliminar
    ListaTareas aux = *ListaT;
    ListaTareas auxAnterior = NULL;
    while (aux != NULL && aux->Tarea.TareaID != id) {
        auxAnterior = aux;
        aux = aux->Siguiente;
    }
    
    // Si no se encontró el nodo con el dato, salir
    if (aux == NULL) {
        return;
    }
    
    // Si el nodo a eliminar es el primer nodo de la lista
    if (auxAnterior == NULL) {
        *ListaT = aux->Siguiente;
    }
    // Si el nodo a eliminar es cualquier otro nodo de la lista
    else {
        auxAnterior->Siguiente = aux->Siguiente;
    }
    // Liberar la memoria ocupada por el nodo a eliminar
    free(aux->Tarea.Descripcion);
    free(aux);
}

//Como es funcion void debo pasar doble puntero asi se modifiquen las cabeceras de las listas
void verificarTareas(ListaTareas *TareasPendientes, ListaTareas *TareasRealizadas, int cant_tareas) 
{          //equivalente a struct Nodo **
    int i = 0;
    while (i < cant_tareas && TareasPendientes != NULL)
    {
        int respuesta;

        printf("Realizo la tarea %d?\n", cant_tareas);
        printf("1-Si\n2-No\n");
        scanf("%d", &respuesta);
        if (respuesta == 1){          
            *TareasRealizadas = crearNodoTarea(*TareasRealizadas, cant_tareas, (*TareasPendientes)->Tarea.Descripcion, (*TareasPendientes)->Tarea.Duracion);                                                     // i + 1 es el id
            EliminarNodo(TareasPendientes, cant_tareas); // cant_tareas es el id
            //Tambien es funcion void por lo que paso el puntero, estaria mal &TareasPendientes xq seria equivalente a Struct Nodo***
        } 
        cant_tareas--;
    }
}

void liberarMemoria(ListaTareas LTareas) 
{
    ListaTareas aux = LTareas;
    while (aux)
    {
        free(aux->Tarea.Descripcion);
        free(aux);

        LTareas = LTareas->Siguiente;
        aux = LTareas;
    }
}


void mostrarTareas(ListaTareas ListaT)
{
    ListaTareas aux = ListaT;
    while (aux != NULL)
    {
        sleep(1);
        printf("ID: %d\n", aux->Tarea.TareaID);
        printf("Descripcion: %s\n", aux->Tarea.Descripcion);
        printf("Duracion: %d\n\n", aux->Tarea.Duracion);
        aux = aux->Siguiente;
    }
}