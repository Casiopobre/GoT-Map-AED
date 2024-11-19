#ifndef GOTMAP_H
#define GOTMAP_H
#include "grafo.h"

// FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

// Opción a del menú, introducir un vertice en el grafo
void introducir_vertice(grafo *G);

// Opción b del menú, eliminar un vértice del grafo
void eliminar_vertice(grafo *G);

// Opción c del menú, crear una relación entre dos vértices
void nuevo_arco(grafo *G);

// Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G);

// Opción i del menú, imprimir el grafo
void imprimir_grafo(grafo G);

// Funcion que lee los archivos e inicializa el grafo
void leerArchivos(char *nombreArchivo1, char *nombreArchivo2, grafo *G);

// Funcion que guarda los datos en dos archivos (primero el de vertices y luego el de aristas)
void guardarArchivos(int argc, char **argv, grafo G);

// Opción e del menú, imprimir la ruta más corta en el grafo
void imprimir_ruta_mas_corta(grafo G);

// Opción f del menú, imprimir la ruta más rápida en el grafo
void imprimir_ruta_mas_rapida(grafo G);

// Opción g del menú, imprimir la mínima infraestructura necesaria para mantener las conexiones en el grafo
void minima_infraestructura(grafo G);

#endif  /* GOTMAP_H */
