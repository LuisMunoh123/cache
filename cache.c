#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

// Crear un nuevo cache
CacheLRU* crear_cache(int capacidad) {
    if (capacidad < 5) {
        printf("Error: La capacidad minima es 5\n");
        return NULL;
    }
    
    CacheLRU* cache = (CacheLRU*)malloc(sizeof(CacheLRU));
    if (cache == NULL) {
        printf("Error: No se pudo asignar memoria\n");
        return NULL;
    }
    
    cache->capacidad = capacidad;
    cache->tamano = 0;
    cache->cabeza = NULL;
    cache->cola = NULL;
    
    return cache;
}

// Crear un nuevo nodo
Nodo* crear_nodo(char dato) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    if (nodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nodo\n");
        return NULL;
    }
    
    nodo->dato = dato;
    nodo->siguiente = NULL;
    nodo->anterior = NULL;
    
    return nodo;
}

// Agregar un nodo al frente de la lista 
void agregar_al_frente(CacheLRU* cache, Nodo* nodo) {
    if (cache->cabeza == NULL) {
        // Cache vacío
        cache->cabeza = nodo;
        cache->cola = nodo;
    } else {
        // Agregar al frente
        nodo->siguiente = cache->cabeza;
        cache->cabeza->anterior = nodo;
        cache->cabeza = nodo;
    }
    cache->tamano++;
}

// Eliminar un nodo de la lista 
void eliminar_nodo(CacheLRU* cache, Nodo* nodo) {
    if (nodo->anterior != NULL) {
        nodo->anterior->siguiente = nodo->siguiente;
    } else {
        cache->cabeza = nodo->siguiente;
    }
    
    if (nodo->siguiente != NULL) {
        nodo->siguiente->anterior = nodo->anterior;
    } else {
        cache->cola = nodo->anterior;
    }
    
    cache->tamano--;
}

// Mover un nodo al frente 
void mover_al_frente(CacheLRU* cache, Nodo* nodo) {
    if (cache->cabeza == nodo) {
        return; 
    }
    
    eliminar_nodo(cache, nodo);
    cache->tamano++; 
    
    nodo->anterior = NULL;
    nodo->siguiente = cache->cabeza;
    cache->cabeza->anterior = nodo;
    cache->cabeza = nodo;
}

// Buscar un dato en el cache 
int buscar_dato(CacheLRU* cache, char dato) {
    if (cache == NULL) {
        return -1;
    }
    
    Nodo* actual = cache->cabeza;
    int posicion = 0;
    
    while (actual != NULL) {
        if (actual->dato == dato) {
            return posicion;
        }
        actual = actual->siguiente;
        posicion++;
    }
    
    return -1;
}

// Agregar un dato al cache
void agregar_dato(CacheLRU* cache, char dato) {
    if (cache == NULL) {
        printf("Error: Cache no inicializado\n");
        return;
    }
    
    // Buscar si el dato ya existe
    Nodo* actual = cache->cabeza;
    while (actual != NULL) {
        if (actual->dato == dato) {
            printf("%c usado\n", dato);
            mover_al_frente(cache, actual);
            return;
        }
        actual = actual->siguiente;
    }
    
    // El dato no existe, crear nuevo nodo
    Nodo* nuevo = crear_nodo(dato);
    if (nuevo == NULL) {
        return;
    }
    
    // Si el cache está lleno, eliminar el último
    if (cache->tamano >= cache->capacidad) {
        Nodo* eliminar = cache->cola;
        printf("%c eliminado\n", eliminar->dato);
        eliminar_nodo(cache, eliminar);
        free(eliminar);
    }
    
    agregar_al_frente(cache, nuevo);
    printf("%c agregado al cache\n", dato);
}

// Usar un dato
void usar_dato(CacheLRU* cache, char dato) {
    if (cache == NULL) {
        printf("Error: Cache no inicializado\n");
        return;
    }
    
    Nodo* actual = cache->cabeza;
    while (actual != NULL) {
        if (actual->dato == dato) {
            mover_al_frente(cache, actual);
            printf("Elemento %c usado\n", dato);
            return;
        }
        actual = actual->siguiente;
    }
    
    printf("Error: %c no encontrado en el cache\n", dato);
}

// Mostrar el contenido del cache
void mostrar_cache(CacheLRU* cache) {
    if (cache == NULL || cache->tamano == 0) {
        printf("El cache esta vacio\n");
        return;
    }
    
    printf("Contenidos del cache: ");
    Nodo* actual = cache->cabeza;
    while (actual != NULL) {
        printf("%c", actual->dato);
        if (actual->siguiente != NULL) {
            printf(" - ");
        }
        actual = actual->siguiente;
    }
    printf("\n");
}

// Liberar memoria del cache
void liberar_cache(CacheLRU* cache) {
    if (cache == NULL) {
        return;
    }
    
    Nodo* actual = cache->cabeza;
    while (actual != NULL) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    
    free(cache);
}
