#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////////////// TIPOS DE DATOS

// Estructura privada
struct tipografo {
    int N; //número de vértices del grafo
    tipovertice VERTICES[MAXVERTICES]; //vector de vértices
    tipoarco MA[MAXVERTICES][MAXVERTICES]; //matriz de adyacencia
};


//////////////////////////////////////////////////////////////// FUNCIONES

//HAY QUE MODIFICAR ESTA FUNCIÓN SI SE CAMBIA EL TIPO DE DATO tipovertice
/* 
 * Esta función devuelve 0 si los dos nodos son iguales
 * y 1 en otro caso.
 */
int _comparar_vertices(tipovertice V1, tipovertice V2){
	return strcmp(V1.nombreCiudad, V2.nombreCiudad) == 0 ? 0 : 1;
}

//Creación del grafo con 0 nodos
void crear_grafo(grafo *G) {
    *G = (struct tipografo*) malloc(sizeof (struct tipografo)); // Reservalle memoria ao grafo
    (*G)->N = 0; // Iguala o numero de vertices a 0
}

//Devuelve la posición del vértice Vert en el vector VERTICES del grafo G
//Si devuelve -1 es porque no encontró el vértice
int posicion(grafo G, tipovertice V) {
    int contador = 0;
    //comparo V con todos los vertices almacenados en VERTICES 
    while (contador < G->N) {
		if (_comparar_vertices(G->VERTICES[contador], V) == 0){ // Si atopei o vertice
            return contador; 
        }
        contador++;
    }
    return -1;
}

//Devuelve 1 si el grafo G existe y 0 en caso contrario
int existe_grafo(grafo G) {
    return (G != NULL);
}

//Devuelve 1 si el vértice Vert existe en el grafo G
int existe_vertice(grafo G, tipovertice V) {
    return (posicion(G, V) >= 0);
}

//Inserta un vértice en el grafo, devuelve -1 si no ha podido insertarlo por estar el grafo lleno
int insertar_vertice(grafo *G, tipovertice V) {
    if ((*G)->N == MAXVERTICES)
    	return -1; // O grafo esta cheo
    
    (*G)->N++; // Incrementamos o num de vertices
    (*G)->VERTICES[((*G)->N) - 1] = V; // Insertamos o vertice no vector de vertices
    for (int i = 0; i < (*G)->N; i++) {
        (*G)->MA[i][((*G)->N) - 1].distancia = 0; // Todas as columnas do ultimo vertice anadido = 0 (pq nn esta conectado a ningun outro vertice)
        (*G)->MA[((*G)->N) - 1][i].distancia = 0; // Todas as filas do ultimo vertice anadido = 0
    }
	return (*G)->N-1; // Devolve a posicion do vertice anadido
}

//Borra un vertice del grafo
void borrar_vertice(grafo *G, tipovertice V) {
    int pos, N = (*G)->N; // N = num de vertices do grafo
    pos = posicion(*G, V); // pos = posicion do verrtice no grafo
    if(pos == -1){
        perror("O vertice non esta no grafo\n");
    	return; 
    }
    // i = fila; j = columna
    for (int i = pos; i < N - 1; i++){
        (*G)->VERTICES[i] = (*G)->VERTICES[i + 1];
	}
    for (int j = pos; j < N - 1; j++){
        for (int i = 0; i < N; i++){
            (*G)->MA[i][j] = (*G)->MA[i][j + 1];
        }
	}
    for (int i = pos; i < N - 1; i++){
        for (int j = 0; j < N; j++){
            (*G)->MA[i][j] = (*G)->MA[i + 1][j];
        }
	}
    (*G)->N--;    
}

//Crea el arco de relación entre VERTICES(pos1) y VERTICES(pos2)
void crear_arco(grafo *G, int pos1, int pos2, int distancia, char tipo) {
    tipoarco arco;
    arco.distancia = distancia;
    arco.tipo = tipo;
    (*G)->MA[pos1][pos2] = arco;
}

//Borra el arco de relación entre VERTICES(pos1) y VERTICES(pos2)
void borrar_arco(grafo *G, int pos1, int pos2) {
    (*G)->MA[pos1][pos2].distancia = 0;
}

//Devuelve la distancia entre dos vertices (0 si no son adyacetes)
int distancia(grafo G, int pos1, int pos2) {
    return (G->MA[pos1][pos2].distancia);
}

// Devuelve el tipo de conexion entre dos vertices
char tipoconexion(grafo G, int pos1, int pos2){
    return (G->MA[pos1][pos2].tipo); 
}

//Destruye el grafo
void borrar_grafo(grafo *G) {
    free(*G);
    *G = NULL;
}

//Devuelve el número de vértices del grafo G
int num_vertices(grafo G) {
    return G->N;
}

//Devuelve el vector de vértices VERTICES del grafo G
tipovertice* array_vertices(grafo G) {
    return G->VERTICES;
}

