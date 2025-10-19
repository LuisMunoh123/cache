#ifndef LRU_CACHE_H
#define LRU_CACHE_H

// Estructura para un nodo de la lista doblemente enlazada 
typedef struct Nodo {
    char dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

// Estructura del Cache
typedef struct {
    int capacidad;
    int tamano;
    Nodo* cabeza;  // Elemento más reciente
    Nodo* cola;    // Elemento menos reciente
} CacheLRU;

// Funciones principales
CacheLRU* crear_cache(int capacidad);
void agregar_dato(CacheLRU* cache, char dato);
void usar_dato(CacheLRU* cache, char dato);
int buscar_dato(CacheLRU* cache, char dato);
void mostrar_cache(CacheLRU* cache);
void liberar_cache(CacheLRU* cache);

// Funciones auxiliares 
Nodo* crear_nodo(char dato);
void mover_al_frente(CacheLRU* cache, Nodo* nodo);
void eliminar_nodo(CacheLRU* cache, Nodo* nodo);
void agregar_al_frente(CacheLRU* cache, Nodo* nodo);

#endif
