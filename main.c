#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    char dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    int capacidad;
    int tamano;
    Nodo* cabeza;
    Nodo* cola;
} CacheLRU;

CacheLRU* crear_cache(int capacidad) {
    CacheLRU* cache = (CacheLRU*)malloc(sizeof(CacheLRU));
    cache->capacidad = capacidad;
    cache->tamano = 0;
    cache->cabeza = NULL;
    cache->cola = NULL;
    return cache;
}

void agregar_dato(CacheLRU* cache, char dato) {
    printf("Dato %c agregado al cache\n", dato);
}

void usar_dato(CacheLRU* cache, char dato) {
    printf("Dato %c usado\n", dato);
}

void mostrar_cache(CacheLRU* cache) {
    printf("Contenido del cache: \n");
}

int main() {
    CacheLRU* cache = NULL;
    char comando[100];
    
    printf("LRU Cache System\n");
    
    while (1) {
        printf(">");
        fgets(comando, 100, stdin);
        
        if (strstr(comando, "lru create")) {
            int tamano;
            sscanf(comando, "lru create %d", &tamano);
            cache = crear_cache(tamano);
            printf("Cache creado con tamaño %d\n", tamano);
        }
        else if (strstr(comando, "lru add")) {
            char dato;
            sscanf(comando, "lru add %c", &dato);
            agregar_dato(cache, dato);
        }
        else if (strstr(comando, "lru get")) {
            char dato;
            sscanf(comando, "lru get %c", &dato);
            usar_dato(cache, dato);
        }
        else if (strstr(comando, "lru all")) {
            mostrar_cache(cache);
        }
        else if (strstr(comando, "lru exit")) {
            printf("Limpiando cache y saliendo...\n");
            break;
        }
    }
    
    return 0;
}
