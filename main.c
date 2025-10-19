#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cache.h"

int main() {
    CacheLRU* cache = NULL;
    char comando[100];
    
    printf("=== LRU Cache System ===\n");
    printf("Comandos disponibles:\n");
    printf("  lru create <tamaño>\n");
    printf("  lru add <LETRA>\n");
    printf("  lru search <LETRA>\n");
    printf("  lru get <LETRA>\n");
    printf("  lru all\n");
    printf("  lru exit\n\n");
    
    while (1) {
        printf(">");
        if (fgets(comando, 100, stdin) == NULL) {
            break;
        }
        
        // Eliminar salto de línea
        comando[strcspn(comando, "\n")] = 0;
        
        if (strstr(comando, "lru create")) {
            int tamano;
            if (sscanf(comando, "lru create %d", &tamano) == 1) {
                if (cache != NULL) {
                    printf("Error: Cache ya existe. Use 'lru exit' primero.\n");
                } else {
                    cache = crear_cache(tamano);
                    if (cache != NULL) {
                        printf("Cache creado con tamaño %d\n", tamano);
                    }
                }
            } else {
                printf("Error: Formato incorrecto. Use: lru create <tamaño>\n");
            }
        }
        else if (strstr(comando, "lru add")) {
            char dato;
            if (cache == NULL) {
                printf("Error: Cache no inicializado. Use 'lru create' primero.\n");
            } else if (sscanf(comando, "lru add %c", &dato) == 1) {
                if (isupper(dato)) {
                    agregar_dato(cache, dato);
                } else {
                    printf("Error: Solo se aceptan letras mayusculas\n");
                }
            } else {
                printf("Error: Formato incorrecto. Use: lru add <LETRA>\n");
            }
        }
        else if (strstr(comando, "lru search")) {
            char dato;
            if (cache == NULL) {
                printf("Error: Cache no inicializado.\n");
            } else if (sscanf(comando, "lru search %c", &dato) == 1) {
                int pos = buscar_dato(cache, dato);
                printf("Posicion: %d\n", pos);
            } else {
                printf("Error: Formato incorrecto. Use: lru search <LETRA>\n");
            }
        }
        else if (strstr(comando, "lru get")) {
            char dato;
            if (cache == NULL) {
                printf("Error: Cache no inicializado.\n");
            } else if (sscanf(comando, "lru get %c", &dato) == 1) {
                usar_dato(cache, dato);
            } else {
                printf("Error: Formato incorrecto. Use: lru get <LETRA>\n");
            }
        }
        else if (strstr(comando, "lru all")) {
            if (cache == NULL) {
                printf("Error: Cache no inicializado.\n");
            } else {
                mostrar_cache(cache);
            }
        }
        else if (strstr(comando, "lru exit")) {
            if (cache != NULL) {
                printf("Limpiando cache y saliendo...\n");
                liberar_cache(cache);
            }
            break;
        }
        else if (strlen(comando) > 0) {
            printf("Comando desconocido. \n");
        }
    }
    
    return 0;
}
