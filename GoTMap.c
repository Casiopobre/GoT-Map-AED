#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"
#include "colors.h"
#define BUF_MAX 256
#define MAX 16
#define VEL_CABALLO_TIERRA 5.5
#define VEL_CABALLO_MAR 11.25
#define VEL_DRAGON 80.0

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vertice en el grafo

void introducir_vertice(grafo *G) {
    tipovertice v1;
    printf(BOLD_WHITE "Introduce el nombre de la nueva ciudad: " RESET);
    scanf(" %[^\n\r]", v1.nombreCiudad);
    printf(BOLD_WHITE "Introduce la region de la nueva ciudad: " RESET);
    scanf(" %[^\n\r]", v1.nombreRegion);
    if (existe_vertice(*G, v1))
        printf(RED "Esa ciudad ya esta añadida\n" RESET);
    else
        insertar_vertice(G, v1);
}

//Opción b del menú, eliminar un vértice del grafo
void eliminar_vertice(grafo *G) {
    tipovertice v1;
    printf(BOLD_WHITE "Introduce en nombre de la ciudad a eliminar: " RESET);
    scanf(" %[^\n\r]", v1.nombreCiudad);
    if (existe_vertice(*G, v1))
        borrar_vertice(G, v1);
    else
        printf(RED "Esa ciudad ya esta añadida\n" RESET);
}

//Opción c del menú, crear una relación entre dos vértices
void nuevo_arco(grafo *G) {
    tipovertice v1, v2;
    //Insertamos una nueva relación pidiendo los datos al usuario controlando que existan los vértices
    printf(BOLD_YELLOW "Nueva relacion ciudad1-->ciudad2\n" RESET);

    //Vértice origen del arco
    printf(BOLD_WHITE "Introduce el nombre de la ciudad origen: \n" RESET);
    scanf(" %[^\n\r]", v1.nombreCiudad);
    if (!existe_vertice(*G, v1)) {
        printf(RED "La ciudad %s no existe en el grafo\n" RESET, v1.nombreCiudad);
        return;
    }

    //Vértice destino del arco
    printf(BOLD_WHITE "Introduce la ciudad destino: " RESET);
    scanf(" %[^\n\r]", v2.nombreCiudad);
    if (!existe_vertice(*G, v2)) {
        printf(RED "La ciudad %s no existe en el grafo\n" RESET, v2.nombreCiudad);
        return;
    }

    // Distancia y tiempo de conexion
    int dist;
    printf(BOLD_WHITE "Introduce la distancia en km desde la ciudad 1 hasta la ciudad 2: \n" RESET);
    scanf("%d", &dist);
    char tipo;
    do {
        printf(BOLD_WHITE "Introduce el tipo de conexion ('t' para tierra o 'm' para mar): \n" RESET);
        scanf(" %c", &tipo);
    } while ((tipo != 't') && (tipo != 'm'));
    
    //Creación dos arcos
    if (!distancia(*G, posicion(*G, v1), posicion(*G, v2)))
        crear_arco(G, posicion(*G, v1), posicion(*G, v2), dist, tipo);
    
}

//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G) {
    tipovertice v1, v2;
    //Eliminamos una relación pidiendo los datos al usuario controlando que existan los vértices
    printf(BOLD_YELLOW "Eliminar la conexion enntre la ciudad1 y la ciudad2\n" RESET);

    //Vértice origen del arco
    printf(BOLD_WHITE "Introduce el nombre de la ciudad origen: " RESET);
    scanf(" %[^\n\r]", v1.nombreCiudad);
    if (!existe_vertice(*G, v1)) {
        printf(RED "La ciudad %s no existe en el grafo\n" RESET, v1.nombreCiudad);
        return;
    }

    //Vértice destino del arco
    printf(BOLD_WHITE "Introduce la ciudad destino: " RESET);
    scanf(" %[^\n\r]", v2.nombreCiudad);
    if (!existe_vertice(*G, v2)) {
        printf(RED "La ciudad %s no existe en el grafo\n" RESET, v2.nombreCiudad);
        return;
    }
    //Eliminación del arco
    if (distancia(*G, posicion(*G, v1), posicion(*G, v2)))
        borrar_arco(G, posicion(*G, v1), posicion(*G, v2));
}

//Opción i del menú, imprimir el grafo
//Función que imprime el grafo utilizando num_vertices para saber cuántos vértices tiene y array_vertices para recuperar el vector de vértices y recorrerlo
void imprimir_grafo(grafo G) {
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    int n = num_vertices(G);
    VECTOR = array_vertices(G);

    printf(BRIGHT_GREEN "El grafo actual es:\n\n" RESET);
    for (int i = 0; i < n; i++) {
        //Imprimo el vértice
        printf(BLUE "Vertice(%d):\n\tCiudad:%s\n\tRegion:%s\n" RESET, i, VECTOR[i].nombreCiudad, VECTOR[i].nombreRegion);
        //Chequeo sus arcos
        for (int j = 0; j < n; j++)
            if (distancia(G, i, j)){
                printf(BRIGHT_BLUE "\t%s --> %s\n", VECTOR[i].nombreCiudad, VECTOR[j].nombreCiudad);
                printf("\tDistancia: %d km\n", distancia(G, i, j));
                printf("\tTipo de conexión: %c\n\n" RESET, tipoconexion(G, i, j));
            }
    }
}

//Funcion que lee los archivos e inicializa el grafo
void leerArchivos(char *nombreArchivo1, char *nombreArchivo2, grafo *G){
    // Abrimos los archivos iniciales
    FILE *archivoVertices = fopen(nombreArchivo1, "r");
    if (archivoVertices == NULL){
        perror(RED "Error al abrir el archivo1: \n" RESET);
        return;
    }
    FILE *archivoAristas = fopen(nombreArchivo2, "r");
    if (archivoAristas == NULL){
        perror(RED "Error al abrir el archivo2: \n" RESET);
        return;
    }

    // Leemos los datos de los dos archivos y los introducimos en el grafo
    tipovertice v, v1, v2;
    int dist;
    char tipo;
    char buffer[BUF_MAX];
    fseek(archivoVertices, 0, SEEK_SET);
    fgets(buffer, sizeof(buffer), archivoVertices); // Ignoramos la cabecera
    while(fgets(buffer, sizeof(buffer), archivoVertices) != NULL){
        sscanf(buffer, "%[^,],%[^\n]", v.nombreCiudad, v.nombreRegion);
        if (!existe_vertice(*G, v))
            insertar_vertice(G, v);
    }

    fseek(archivoAristas, 0, SEEK_SET);
    fgets(buffer, sizeof(buffer), archivoAristas);
    while(fgets(buffer, sizeof(buffer), archivoAristas) != NULL){
        sscanf(buffer, "%[^,],%[^,],%d,%c", v1.nombreCiudad, v2.nombreCiudad, &dist, &tipo);
        if (!distancia(*G, posicion(*G, v1), posicion(*G, v2)))
            crear_arco(G, posicion(*G, v1), posicion(*G, v2), dist, tipo);
    }

    // Cerramos los archivos
    fclose(archivoVertices);
    fclose(archivoAristas);
}

// Funcion para guardar los datos en dos archivos, uno para las ciudades y otro para los caminos
void guardarArchivos(int argc, char **argv, grafo G){
    FILE *archivoVertices, *archivoAristas;
    char archivoUsuarioV[MAX], archivoUsuarioA[MAX];
    // Si el programa se inicializo con archivos, guarda los datos en esos archivos, si no, se crean 2 archivos nuevos
    if(argc >= 3){
        printf(BRIGHT_GREEN "Actualizando los archivos iniciales . . .\n\n" RESET);
        archivoVertices = fopen(argv[1], "w");
        archivoAristas = fopen(argv[2],"w");
    } else{
        printf(BOLD_WHITE "Indrozudca el nombre con el que quiere guardar el archivo de las ciudades (vertices): ");
        scanf(" %[^\n\r]", archivoUsuarioV);
        archivoVertices = fopen(archivoUsuarioV, "w");
        printf(BOLD_WHITE "Indrozudca el nombre con el que quiere guardar el archivo de las conexiones (aristas): ");
        scanf(" %[^\n\r]", archivoUsuarioA);
        archivoAristas = fopen(archivoUsuarioA, "w");
    }
    
    // Guardamos los datos
    fprintf(archivoVertices,"Ciudad,Region\n"); // Imprimimos la cabecera
    fprintf(archivoAristas, "Origen,Destino,Distancia,Tipo\n"); // Imprimimos la cabecera
    tipovertice *vectorVertices = array_vertices(G);
    int n = num_vertices(G);
    for(int i = 0; i < n; i++){
        fprintf(archivoVertices, "%s,%s\n", vectorVertices[i].nombreCiudad, vectorVertices[i].nombreRegion);
        for(int j = i; j < n; j++){
            if(distancia(G, i, j) > 0)
                fprintf(archivoAristas, "%s,%s,%d,%c\n", vectorVertices[i].nombreCiudad, vectorVertices[j].nombreCiudad, distancia(G, i, j), tipoconexion(G, i, j));
        }
    }
    fclose(archivoVertices);
    fclose(archivoAristas);
}

void _imprimir_matriz(int matriz[MAXVERTICES][MAXVERTICES], int numV) {
    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            if (matriz[i][j] == INT_MAX) {
                printf("INF ");
            } else {
                printf("%d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}


void _floyd_warshall(grafo G, int dist[MAXVERTICES][MAXVERTICES], int sig[MAXVERTICES][MAXVERTICES]) {
    int numV = num_vertices(G);
    
    // Inicializamos las matrices
    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (distancia(G, i, j) > 0) {
                dist[i][j] = distancia(G, i, j);
            } else {
                dist[i][j] = INT_MAX;
            }

            if (distancia(G, i, j) != 0 && i != j) {
                sig[i][j] = j;
            } else {
                sig[i][j] = 0;
            }
        }
    }

    //_imprimir_matriz(dist, numV);
    //printf("\n\n");
    //_imprimir_matriz(sig, numV);
    //printf("\n\n");

    // Aplicamos el algoritmo
    for (int k = 0; k < numV; k++) {
        for (int i = 0; i < numV; i++) {
            for (int j = 0; j < numV; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    sig[i][j] = sig[i][k];
                }
            }
        }
    }
}

void _imprimir_camino(grafo G, int sig[MAXVERTICES][MAXVERTICES], int origen, int destino) {
    tipovertice *arrayVertices = array_vertices(G);
    
    // Si no hay ruta, salimos
    if (sig[origen][destino] == -1) {
        printf("No existe ruta entre %s y %s\n", arrayVertices[origen].nombreCiudad, arrayVertices[destino].nombreCiudad);
        return;
    }

    // Imprime origen
    printf("%s", arrayVertices[origen].nombreCiudad);
    
    while (origen != destino) {
        int siguiente = sig[origen][destino];
        char tipoConexion = tipoconexion(G, origen, siguiente);
        if (tipoConexion == 't') {
            printf(" --> ");
        } else if (tipoConexion == 'm') {
            printf(" ~~> ");
        }
        origen = siguiente;
        printf("%s", arrayVertices[origen].nombreCiudad);
    }
}




void imprimir_ruta_mas_corta(grafo G) {
    tipovertice v1, v2;
    //Vértice origen
    printf(BOLD_WHITE "Introduce el nombre de la ciudad origen: " RESET);
    scanf(" %[^\n\r]", v1.nombreCiudad);
    if (!existe_vertice(G, v1)) {
        printf(RED "La ciudad %s no existe en el grafo\n" RESET, v1.nombreCiudad);
        return;
    }

    //Vértice destinoç
    printf(BOLD_WHITE "Introduce la ciudad destino: " RESET);
    scanf(" %[^\n\r]", v2.nombreCiudad);
    if (!existe_vertice(G, v2)) {
        printf(RED "La ciudad %s no existe en el grafo\n" RESET, v2.nombreCiudad);
        return;
    }

    int pos1 = posicion(G, v1);
    int pos2 = posicion(G, v2);

    int dist[MAXVERTICES][MAXVERTICES];
    int sig[MAXVERTICES][MAXVERTICES];

    _floyd_warshall(G, dist, sig);

    if (dist[pos1][pos2] == INT_MAX) {
        printf(RED "No hay ruta entre %s y %s\n" RESET, v1.nombreCiudad, v2.nombreCiudad);
    } else {
        printf(BRIGHT_GREEN "La distancia más corta entre %s y %s es: %d km\n" RESET, v1.nombreCiudad, v2.nombreCiudad, dist[pos1][pos2]);
        printf(BRIGHT_BLUE "Ruta: ");
        _imprimir_camino(G, sig, pos1, pos2);
        printf(RESET);
        printf("\n");
    }
}

