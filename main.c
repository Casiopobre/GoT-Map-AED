#include <stdio.h>
#include <stdlib.h>
#include "GoTMap.h"
#include "colors.h"

/*
 * Programa que muestra el uso del TAD grafo de números enteros
 */

int main(int argc, char** argv) {
    //Grafo de números enteros
    grafo G; //grafo
    char opcion;

    //Creo el grafo
    crear_grafo(&G);

    //Proceso los archivos
    if(argc > 1){
        printf(BRIGHT_BOLD_GREEN "\nProcesando archivos . . .\n" RESET);
        leerArchivos(argv[1], argv[2], &G);
    } else 
        printf(BRIGHT_BOLD_GREEN "\nTrabajando SIN archivos . . .\n" RESET);

    do {
        printf(BOLD_MAGENTA);
        printf("\n--------------------------------------------------------");
        printf("\n~*~*~*~*~*~*~*~ Seleccione una opción ~*~*~*~*~*~*~*~\n");
        printf("\na) Insertar una nueva ciudad (vertice)\n");
        printf("\nb) Eliminar ciudad (vertice)\n");
        printf("\nc) Crear nueva conexion (arco)\n");
        printf("\nd) Eliminar una conexion (arco)\n");
        printf("\ni) Imprimir mapa (grafo)\n");
        printf("\ne) Imprimir camino más corto\n");
        printf("\nf) Imprimir camino más rápido\n");
        printf("\ng) Imprimir mínima infraestructura\n");
        printf("\ns) Salir\n");
        printf("--------------------------------------------------------\n");
        printf(RESET);
        printf("\nOpcion: ");
        scanf(" %c", &opcion); 

        switch (opcion) {
            case 'a':case'A':
                introducir_vertice(&G);
                break;
            case 'b':case 'B':
                eliminar_vertice(&G);
                break;
            case 'c': case 'C':
                nuevo_arco(&G);
                break;
            case 'd': case 'D':
                eliminar_arco(&G);
                break;
            case 'i': case 'I':
                imprimir_grafo(G);
                break;
            case 'e': case 'E':
                imprimir_ruta_mas_corta(G);
                break;
            case 'f': case 'F':
                imprimir_ruta_mas_rapida(G);
                break;
            case 'g': case 'G':
                minima_infraestructura(G);
                break;
            case 's': case 'S':
                opcion = 's';
                guardarArchivos(argc, argv, G);
                break;
            default:
                printf("Opción equivocada\n");
        }
    } while (opcion != 's');

    //Al salir, liberamos la memoria del TAD, lo destruimos
    borrar_grafo(&G);

    return (EXIT_SUCCESS);
}

