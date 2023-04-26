#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct Tarea {
    int TareaID;  // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;  // entre 10 – 100
} Tarea;

Tarea *BuscarTarea(Tarea **tareas, int cant, int id);
Tarea **crearArregloNull(Tarea **arreglo, int cant);
void cargarArreglo(Tarea **arreglo, int cant);
void mostrarTarea(Tarea *tarea);
void mostrarTareasPendientes(Tarea **tareasPendientes, int cant);
void mostrarTareasRealizadas(Tarea **tareasRealizadas, int cant);

int main() {
    int cantTareas, confirm = 0, bus = 0;
    printf("Ingresar cantidad de tareas: ");
    scanf("%d", &cantTareas);
    fflush(stdin);
    srand(time(NULL));

    Tarea **tareasPendientes = crearArregloNull(tareasPendientes, cantTareas);
    Tarea **tareasRealizadas = crearArregloNull(tareasRealizadas, cantTareas);
    cargarArreglo(tareasPendientes, cantTareas);

    // listar una a una las tareas y preguntar si se realizó o no la misma
    puts("___CONTROL DE TAREAS___\n");
    for (int i = 0; i < cantTareas; i++) {
        mostrarTarea(tareasPendientes[i]);
        printf("\nRealizo esta tarea? (si = 1, no = 0)\n");
        scanf("%d", &confirm);
        if (confirm) {
            tareasRealizadas[i] = (Tarea *)malloc(sizeof(Tarea));
            tareasRealizadas[i] = tareasPendientes[i];
            tareasPendientes[i] = NULL;
        }
    }

    mostrarTareasPendientes(tareasPendientes, cantTareas);
    mostrarTareasRealizadas(tareasRealizadas, cantTareas);
    fflush(stdin);

    return 0;
}

Tarea **crearArregloNull(Tarea **arreglo, int cant) {
    arreglo = (Tarea **)malloc(sizeof(Tarea *) * cant);
    for (int i = 0; i < cant; i++) {
        arreglo[i] = NULL;
    }
    return arreglo;
}

void cargarArreglo(Tarea **arreglo, int cant) {
    char *buff = (char *)malloc(sizeof(char) * 500);
    for (int i = 0; i < cant; i++) {
        arreglo[i] = (Tarea *)malloc(sizeof(Tarea));
        printf("\n___Tarea numero %d\n", i + 1);
        printf("Ingresar Descripcion: ");
        gets(buff);
        fflush(stdin);
        arreglo[i]->Descripcion = malloc(sizeof(char) * strlen(buff) + 1);
        strcpy(arreglo[i]->Descripcion, buff);
        printf("\n");
        printf("Ingresar Duracion: ");
        scanf("%d", &(arreglo[i]->Duracion));
        fflush(stdin);
        arreglo[i]->TareaID = i + 1;
    }
    free(buff);
}

void mostrarTarea(Tarea *tarea) {
    if (tarea == NULL) {
        printf("Tarea nula\n");
    } else {
        printf("ID: %d\n", tarea->TareaID);
        printf("Descripcion: %s\n", tarea->Descripcion);
        printf("Duracion: %d Horas\n", tarea->Duracion);
    }
}

void mostrarTareasPendientes(Tarea **tareasPendientes, int cant) {
    puts("___LISTADO DE TAREAS PENDIENTES___");
    for (int i = 0; i < cant; i++) {
        if (tareasPendientes[i] != NULL) {
            printf("\n-Tarea numero %d pendiente\n", i + 1);
            mostrarTarea(tareasPendientes[i]);
        }
    }
    puts("\n");
}
void mostrarTareasRealizadas(Tarea **tareasRealizadas, int cant) {
    puts("___LISTADO DE TAREAS REALIZADAS");
    for (int i = 0; i < cant; i++) {
        if (tareasRealizadas[i] != NULL) {
            printf("\n-Tarea numero %d realizada\n", i + 1);
            mostrarTarea(tareasRealizadas[i]);
        }
    }
    puts("\n");
}

Tarea *BuscarTarea(Tarea **tareas, int cant, int id) {
    for (int i = 0; i < cant; i++) {
        if (tareas[i] != NULL && tareas[i]->TareaID == id) {
            return tareas[i];
        }
    }
    return NULL;
}