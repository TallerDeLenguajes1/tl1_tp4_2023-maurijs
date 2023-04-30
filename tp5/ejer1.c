
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
void cambiarTareas(ListaTareas *ListaOrigen, ListaTareas *ListaDestino, int id);
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
    int id, decision, listaOrigen, listaDestino;
    //Crear Tareas
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
    printf("Desea ingresar una nueva tarea?\n1-Si\n0-No\n");
    scanf("%d", &opcion);
    } while (opcion);

    do
    {
        printf("Listado de Tareas:\n");
        printf("\n=========Mostrando datos de Tareas Pendientes=========\n");
        mostrarDatos(TareasPendientes);
        sleep(1);
        printf("\n=========Mostrando datos de Tareas Realizadas=========\n");
        mostrarDatos(TareasRealizadas);
        sleep(1);
        printf("\n=========Mostrando datos de Tareas en Proceso=========\n");
        mostrarDatos(TareasEnProceso);
        sleep(1);

        printf("\nIngrese la lista a la cual pertenece la tarea:\n");
        printf("1-Tareas pendientes\n2-Tareas realizadas\n3-Tareas en proceso\n");
        scanf("%d", &listaOrigen);
        printf("\nIngrese el id de la tarea a seleccionar: ");

        scanf("%d", &id);
        switch (listaOrigen) //Para saber si existe una tarea con ese id
        {
        case 1:
            resultado = busquedaTarea(TareasPendientes, id); 
            break;
        case 2:
            resultado = busquedaTarea(TareasRealizadas, id);
            break;
        case 3:
            resultado = busquedaTarea(TareasEnProceso, id);
            break;
        }
        
        //verifico si existe la tarea
        decision = 0;
        if (resultado)
        {
            printf("\nSeleccione que hacer con la tarea:\n1-mover la tarea\n2-Eliminar la tarea\n3-No hacer nada\n");
            scanf("%d",&decision);
            
            if (decision == 2)  {
                //elimino la tarea de la lista 
                if (listaOrigen == 1) { // si la tarea se encuentra en Tareas pendientes
                    EliminarNodo(&TareasPendientes, id);
                } else if (listaOrigen == 2) {
                    EliminarNodo(&TareasRealizadas, id);
                } else {
                    EliminarNodo(&TareasEnProceso, id);
                }   
            } 
        }

        if (decision == 1)
        {
            listaDestino = opcionesMover(listaOrigen);   //Elijo a que lista mover esa tarea  
            // Segun la lista donde esta la tarea que seleccione, me apareceran las opciones de listas
            switch (listaOrigen) 
            {
            case 1:             // Seleccione tareas pendientes
                if (listaDestino == 1) //Movere la tarea a tareas realizadas
                {
                    cambiarTareas(&TareasPendientes, &TareasRealizadas, id); // (Origen, destino, id)
                } else {
                    cambiarTareas(&TareasPendientes, &TareasEnProceso, id);
                } 
                break;  
            case 2:             // Seleccione tareas realizadas
                if (listaDestino == 1) //Movere la tarea a tareas pendientes
                {
                    cambiarTareas(&TareasRealizadas, &TareasPendientes, id);
                } else {               //Movere la tarea a tareas en proceso
                    cambiarTareas(&TareasRealizadas, &TareasEnProceso, id);
                } 
                break;

            case 3:             // Seleccione tareas en proceso
                if (listaDestino == 1) //Movere la tarea a tareas pendientes
                {
                    cambiarTareas(&TareasEnProceso, &TareasPendientes, id);
                } else { //Movere la tarea a tareas realizadas
                    cambiarTareas(&TareasEnProceso, &TareasRealizadas, id);
                } 
                break;
            }
        } 
        printf("\nDesea seleccionar otra tarea?\n1-Si\n0-No\n");
        scanf("%d", &opcion);
    } while (opcion);

    printf("\n=========Mostrando datos de Tareas Pendientes=========\n");
    mostrarDatos(TareasPendientes);
    sleep(1);
    printf("\n=========Mostrando datos de Tareas Realizadas=========\n");
    mostrarDatos(TareasRealizadas);
    sleep(1);
    printf("\n=========Mostrando datos de Tareas en Proceso=========\n");
    mostrarDatos(TareasEnProceso);
    sleep(1);

    liberarMemoria(TareasPendientes);
    liberarMemoria(TareasRealizadas);
    return 0;
}
      
    


//----------------DECLARACION DE FUNCIONES------------------------


//================INTERFAZ DE USUARIO==============================

int opcionTareas() 
{
    printf("Opciones:\n1-Eliminar Tarea\n2-Mover a otra lista\n3-Volver\n");
    int opcion;
    scanf("%d", &opcion);
    return opcion;
}

int opcionesMover(int listaOrigen)
{
    int listaDestino;
    printf("\n A que lista desea mover la tarea?\n");
    if (listaOrigen == 1)
    {
        printf("1-Tareas Realizadas\n2-Tareas en Proceso\n");
    } else if (listaOrigen == 2)
    {
        printf("1-Tareas pendientes\n2-Tareas en Proceso\n");
    } else
    {
        printf("1-Tareas Pendientes\n2-Tareas Realizadas\n");
    }
    scanf("%d", &listaDestino);
    return listaDestino;
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

void cambiarTareas(ListaTareas *ListaOrigen, ListaTareas *ListaDestino, int id) {
    printf("\n====Funcion cambiar tareas===\n");
    ListaTareas aux = *ListaOrigen;
    while (aux != NULL) {
        if (aux->Tarea.TareaID == id) {
            *ListaDestino = crearNodoTarea(*ListaDestino, id, aux->Tarea.Descripcion, aux->Tarea.Duracion);
            EliminarNodo(ListaOrigen, id);
            printf("\nSe cambio de lista la tarea\n");
            return;
        }
        aux = aux->Siguiente;
    }
    printf("\nNo se pudo cambiar la tarea a la otra lista\n");
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
    printf("\nNo se encontro la tarea con ese id\n");
    return 0;
}

void mostrarDatos(ListaTareas ListaT)
{
    if (ListaT)
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
            TiempoTotal = TiempoTotal + aux->Tarea.Duracion;
            aux = aux->Siguiente;
            cant_tareas++;
        }
        printf("--------------------------------------------\n");
        printf("Cantidad de tareas: %d\n", cant_tareas);
        printf("Duracion total: %d\n", TiempoTotal);
        printf("--------------------------------------------\n");
    } 
    else
    {
        printf("\nLista vacia\n");
    }
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