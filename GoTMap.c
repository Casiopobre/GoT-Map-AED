#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "colors.h"
#define BUF_MAX 256
#define MAX 16

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vertice en el grafo

void introducir_vertice(grafo *G) {
    tipovertice v1;
    printf(CYAN "Introduce el nombre de la nueva ciudad: " RESET);
    scanf(" %[^\n\r]", v1.nombreCiudad);
    printf(CYAN "Introduce la region de la nueva ciudad: " RESET);
    scanf(" %[^\n\r]", v1.nombreRegion);
    if (existe_vertice(*G, v1))
        printf(RED "Esa ciudad ya esta añadida\n" RESET);
    else
        insertar_vertice(G, v1);
}

//Opción b del menú, eliminar un vértice del grafo
void eliminar_vertice(grafo *G) {
    tipovertice v1;
    printf(CYAN "Introduce en nombre de la ciudad a eliminar: " RESET);
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
    printf(CYAN "Introduce el nombre de la ciudad origen: \n" RESET);
    scanf(" %[^\n\r]", v1.nombreCiudad);
    if (!existe_vertice(*G, v1)) {
        printf(RED "La ciudad %s no existe en el grafo\n" RESET, v1.nombreCiudad);
        return;
    }

    //Vértice destino del arco
    printf(CYAN "Introduce la ciudad destino: " RESET);
    scanf(" %[^\n\r]", v2.nombreCiudad);
    if (!existe_vertice(*G, v2)) {
        printf(RED "La ciudad %s no existe en el grafo\n" RESET, v2.nombreCiudad);
        return;
    }

    // Distancia y tiempo de conexion
    int dist;
    printf(CYAN "Introduce la distancia en km desde la ciudad 1 hasta la ciudad 2: \n" RESET);
    scanf("%d", &dist);
    char tipo;
    do {
        printf(CYAN "Introduce el tipo de conexion ('t' para tierra o 'm' para mar): \n" RESET);
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
    printf(CYAN "Introduce el nombre de la ciudad origen: " RESET);
    scanf(" %[^\n\r]", v1.nombreCiudad);
    if (!existe_vertice(*G, v1)) {
        printf(RED "La ciudad %s no existe en el grafo\n" RESET, v1.nombreCiudad);
        return;
    }

    //Vértice destino del arco
    printf(CYAN "Introduce la ciudad destino: " RESET);
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
        printf(CYAN "Indrozudca el nombre con el que quiere guardar el archivo de las ciudades (vertices): ");
        scanf(" %[^\n\r]", archivoUsuarioV);
        archivoVertices = fopen(archivoUsuarioV, "w");
        printf(CYAN "Indrozudca el nombre con el que quiere guardar el archivo de las conexiones (aristas): ");
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
