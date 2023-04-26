#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX 100

typedef struct Tarea {
    int TareaID;  // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;  // entre 10 – 100
} Tarea;

Tarea *BuscarTareaId(Tarea **tareas, int cant, int id);
Tarea *BuscarTareaPalabra(Tarea **tareas, int cant, char *palabra);
Tarea **crearArregloNull(Tarea **arreglo, int cant);
void cargarArreglo(Tarea **arreglo, int cant);
void mostrarTarea(Tarea *tarea);
void mostrarTareasPendientes(Tarea **tareasPendientes, int cant);
void mostrarTareasRealizadas(Tarea **tareasRealizadas, int cant);
void buscarEnTareasPendientes(Tarea **tareasPendientes, int cant);
void buscarEnTareasRealizadas(Tarea **tareasrealizadas, int cant);
void borrarConsola(int tiempo);

int main() {
    int cantTareas, confirm = 0, bus = 0;
    printf("Ingresar cantidad de tareas: ");
    scanf("%d", &cantTareas);
    fflush(stdin);
    borrarConsola(0);
    srand(time(NULL));

    Tarea **tareasPendientes = crearArregloNull(tareasPendientes, cantTareas);
    Tarea **tareasRealizadas = crearArregloNull(tareasRealizadas, cantTareas);
    cargarArreglo(tareasPendientes, cantTareas);

    // listar una a una las tareas y preguntar si se realizó o no la misma
    puts("__CONTROL DE TAREAS__\n");
    for (int i = 0; i < cantTareas; i++) {
        mostrarTarea(tareasPendientes[i]);
        printf("\nRealizo esta tarea? (si = 1, no = 0)\n");
        scanf("%d", &confirm);
        if (confirm) {
            tareasRealizadas[i] = (Tarea *)malloc(sizeof(Tarea));
            tareasRealizadas[i] = tareasPendientes[i];
            tareasPendientes[i] = NULL;
        }
        borrarConsola(0);
    }

    mostrarTareasPendientes(tareasPendientes, cantTareas);
    mostrarTareasRealizadas(tareasRealizadas, cantTareas);
    fflush(stdin);
    printf("\nPresione enter para continuar...");
    getchar();
    borrarConsola(0);

    printf("__Buscador de tareas:\n");
    puts("1) buscar en tareas pendientes");
    puts("2) buscar en tareas realizadas");
    fflush(stdin);
    scanf("%d", &bus);
    borrarConsola(0);
    if (bus == 1) {
        buscarEnTareasPendientes(tareasPendientes, cantTareas);
    } else {
        buscarEnTareasRealizadas(tareasRealizadas, cantTareas);
    }

    return 0;
}

Tarea *BuscarTareaId(Tarea **tareas, int cant, int id) {
    for (int i = 0; i < cant; i++) {
        if (tareas[i] != NULL && tareas[i]->TareaID == id) {
            return tareas[i];
        }
    }
    return NULL;
}

Tarea *BuscarTareaPalabra(Tarea **tareas, int cant, char *palabra) {
    for (int i = 0; i < cant; i++) {
        if (tareas[i] != NULL && strstr(tareas[i]->Descripcion, palabra) != NULL) {
            return tareas[i];
        }
    }
    return NULL;
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
        // arreglo[i]->Descripcion = "descripcion";
        printf("\n");
        printf("Ingresar Duracion: ");
        // arreglo[i]->Duracion = rand() % 10001 + 1;
        scanf("%d", &(arreglo[i]->Duracion));
        fflush(stdin);
        arreglo[i]->TareaID = i + 1;
        borrarConsola(0);
    }
    free(buff);
    printf("\nPresione enter para continuar...");
    getchar();
    borrarConsola(0);
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
    puts("__LISTADO DE TAREAS PENDIENTES__");
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

void buscarEnTareasPendientes(Tarea **tareasPendientes, int cant) {
    int con = 1, bus = 0, id = 0;
    Tarea *buscada;
    char palabra[MAX];
    while (con) {
        puts("__buscador de tareas pendientes__\n");
        puts("1) buscar por id(1)\n2) buscar por palabra(2)\n");
        scanf("%d", &bus);
        borrarConsola(0);
        fflush(stdin);
        if (bus == 1) {
            printf("ingresar id buscado: ");
            scanf("%d", &id);
            buscada = BuscarTareaId(tareasPendientes, cant, id);
            if (buscada != NULL) {
                mostrarTarea(buscada);
            } else {
                puts("tarea no encontrada");
            }
        } else {
            printf("ingresar palabra buscada: ");
            gets(palabra);
            buscada = BuscarTareaPalabra(tareasPendientes, cant, palabra);
            if (buscada != NULL) {
                mostrarTarea(buscada);
            } else {
                puts("tarea no encontrada");
            }
        }

        puts("Presione enter para seguir buscando o 1 para terminar...");
        getchar();
        if (getchar() == '1') {
            con = 0;
        }
        borrarConsola(0);
    }

    getchar();
}

void buscarEnTareasRealizadas(Tarea **tareasrealizadas, int cant) {
    int con = 1, bus = 0, id = 0;
    Tarea *buscada;
    char palabra[MAX];
    while (con) {
        puts("___buscador de tareas realizadas\n");
        puts("1) buscar por id(1)\n2) buscar por palabra(2)\n");
        scanf("%d", &bus);
        borrarConsola(0);
        fflush(stdin);
        if (bus == 1) {
            printf("ingresar id buscado: ");
            scanf("%d", &id);
            buscada = BuscarTareaId(tareasrealizadas, cant, id);
            if (buscada != NULL) {
                mostrarTarea(buscada);
            } else {
                puts("tarea no encontrada");
            }
        } else {
            printf("ingresar palabra buscada: ");
            gets(palabra);
            buscada = BuscarTareaPalabra(tareasrealizadas, cant, palabra);
            if (buscada != NULL) {
                mostrarTarea(buscada);
            } else {
                puts("tarea no encontrada");
            }
        }

        puts("Presione enter para seguir buscando o 1 para terminar...");
        getchar();
        if (getchar() == '1') {
            con = 0;
        }
        borrarConsola(0);
    }

    getchar();
}

void borrarConsola(int tiempo) {
    sleep(tiempo);
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}