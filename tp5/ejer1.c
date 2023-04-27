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

ListaTareas crearLista();
ListaTareas crearNodoTarea(ListaTareas LTareas, int id, char*descripcion, int duracion);
void liberarMemoria(ListaTareas LTareas);
void verificarTareas(ListaTareas *TareasPendientes, ListaTareas *TareasRealizadas, int cant_tareas);
void EliminarNodo(ListaTareas *ListaT, int id);
int busquedaTarea(ListaTareas ListaT, int id);
void mostrarDatos(ListaTareas ListaT);
int opcionesMover(int lista);
int menu();
int opcionesTarea();


int main() 
{
    int opcion, duracion, resultado;
    int cant = 0;
    char *buffer = NULL;
    char descripcion[30];
    ListaTareas TareasPendientes;
    ListaTareas TareasRealizadas;
    ListaTareas TareasEnProceso;

    TareasPendientes = crearLista();
    TareasRealizadas = crearLista();
    TareasEnProceso = crearLista();
    int id;
    int opcion = menu();
    int lista;
    while (opcion)
    {
        switch (opcion)
        {
        case 1:
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
            break;
        
        case 2:
            printf("Listado de Tareas:\n");
            printf("\n=========Mostrando datos de Tareas Pendientes=========\n");
            mostrarDatos(TareasPendientes);
            printf("\n=========Mostrando datos de Tareas Realizadas=========\n");
            mostrarDatos(TareasRealizadas);
            printf("\n=========Mostrando datos de Tareas en Proceso=========\n");
            mostrarDatos(TareasEnProceso);

            printf("\nIngrese la lista a la cual pertenece la tarea:\n");
            printf("1-Tareas pendientes\n2-Tareas realizadas\n3-Tareas en proceso");
            scanf("%d", &opcion);

            printf("\nIngrese el id de la tarea a seleccionar: ");
            scanf("%d", &id);
            switch (opcion)
            {
            case 1:
                resultado = busquedaTarea(TareasPendientes, id); //Para saber si existe una tarea con ese id
                break;
            case 2:
                resultado = busquedaTarea(TareasRealizadas, id);
                break;
            case 3:
                resultado = busquedaTarea(TareasEnProceso, id);
                break;
            }
            if (resultado)
            {
                lista = opcionesMover(opcion);    
            } else {
                printf("No se pudo encontrar la tarea con ese id\n");
            }
            
            
            switch (opcion) // Lista donde pertenece la tarea
            {
            case 1:             // Seleccione tareas pendientes
                if (lista == 1) //Movere la tarea a tareas realizadas
                {
                    cambiarTareas(TareasPendientes, TareasRealizadas, id);
                } else if (lista == 2) //Movere la tarea a tareas en proceso
                {
                    cambiarTareas(TareasPendientes, TareasEnProceso, id);
                } 
                break;  
            case 2:             // Seleccione tareas realizadas
                if (lista == 1) //Movere la tarea a tareas pendientes
                {
                    cambiarTareas(TareasRealizadas, TareasPendientes, id);
                } else if (lista == 2) //Movere la tarea a tareas en proceso
                {
                    cambiarTareas(TareasRealizadas, TareasEnProceso, id);
                } 
                break;

            case 3:             // Seleccione tareas en proceso
                if (lista == 1) //Movere la tarea a tareas pendientes
                {
                    cambiarTareas(TareasEnProceso, TareasPendientes, id);
                } else if (lista == 2) //Movere la tarea a tareas realizadas
                {
                    cambiarTareas(TareasEnProceso, TareasRealizadas, id);
                } 
                break;
            }
            break;
        }
        opcion = menu();
    }

    liberarMemoria(TareasPendientes);
    liberarMemoria(TareasRealizadas);
    return;
}

//----------------DECLARACION DE FUNCIONES------------------------


//================INTERFAZ DE USUARIO==============================
int menu() 
{
    int opcion;
    printf("\n===========MENU============\n");
    printf("0-Salir del programa\n1-Ingresar nueva Tarea\n2-Modificar una tarea\n");
    scanf("%d", &opcion);
    return opcion;
}
int opcionTareas() 
{
    printf("Opciones:\n1-Eliminar Tarea\n2-Mover a otra lista\n3-Volver\n");
    int opcion;
    scanf("%d", &opcion);
    return opcion;
}

int opcionesMover(int opcion)
{
    int lista;
    printf("\n A que lista desea mover la tarea?\n");
    if (opcion == 1)
    {
        printf("1-Tareas Pendientes\n2-Tareas en Proceso");
    } else if (opcion == 2)
    {
        printf("1-Tareas Realizadas\n2-Tareas en Proceso");
    } else
    {
        printf("1-Tareas Pendientes\n2-Tareas Realizadas");
    }
    scanf("%d", &lista);
    return lista;
}

//============================================================================

//==================FUNCIONES DE LISTA========================================
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
//====================================================================

//==================FUNCION PARA LISTA DE TAREAS=======================
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

int busquedaTarea(ListaTareas ListaT, int id) 
{
    ListaTareas aux = ListaT;
    while (aux)
    {
        if (aux->Tarea.TareaID == id )
        {
            printf("\nTarea Encontrada");
            printf("\nID: %d", id);
            printf("\nDescripcion: %s", aux->Tarea.Descripcion);
            printf("\nDuracion: %d", aux->Tarea.Duracion);
            return 1;
        }
        aux = aux->Siguiente;
    }
    printf("\nNo se encontro la tarea en esta lista\n");
    return 0;
}

void mostrarDatos(ListaTareas ListaT)
{
    ListaTareas aux = ListaT;
    int TiempoTotal = 0;
    int cant_tareas = 0;
    while (aux != NULL)
    {
        sleep(1);
        printf("ID: %d\n", aux->Tarea.TareaID);
        printf("Descripcion: %s\n", aux->Tarea.Descripcion);
        printf("Duracion: %d\n", aux->Tarea.Duracion);
        aux = aux->Siguiente;
        cant_tareas++;
        TiempoTotal = TiempoTotal + aux->Tarea.Duracion;
    }
    printf("--------------------------------------------\n");
    printf("Cantidad de tareas: %d\n", cant_tareas);
    printf("Duracion total: %d\n", TiempoTotal);
    printf("--------------------------------------------\n");
}
//=================================================================

//=================FUNCION DE MEMORIA=================================

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