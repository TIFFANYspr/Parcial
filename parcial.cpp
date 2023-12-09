//Stefany Potosi , Angel Santiago Estupiñan Gomez
#include <iostream>
#include <vector>
using namespace std;

// Estructura para los datos de un vuelo
struct Vuelo {
    int id;
    string ciudadOrigen;
    string ciudadDestino;
    string fecha;
    string hora;
    int capacidad;

    // Constructor para inicializar los atributos del vuelo
    Vuelo(int idVuelo, string origen, string destino, string fechaVuelo, string horaVuelo, int capacidadVuelo) {
        id = idVuelo;
        ciudadOrigen = origen;
        ciudadDestino = destino;
        fecha = fechaVuelo;
        hora = horaVuelo;
        capacidad = capacidadVuelo;
    }
};

// Estructura para los nodos del árbol de vuelos
struct NodoVuelo {
    Vuelo info;
    NodoVuelo* izq;
    NodoVuelo* der;

    // Constructor para inicializar los atributos del nodo
    NodoVuelo(Vuelo vuelo) {
        info = vuelo;
        izq = der = NULL;
    }
};

//  para gestionar los vuelos con un árbol binario de búsqueda
struct NodoVuelo {
    Vuelo info;
    NodoVuelo* izq;
    NodoVuelo* der;

    NodoVuelo(Vuelo vuelo) : info(vuelo), izq(NULL), der(NULL) {}
};

NodoVuelo* registrarVuelo(NodoVuelo* raiz, Vuelo nuevoVuelo) {
    NodoVuelo* nuevoNodo = new NodoVuelo(nuevoVuelo);
    if (raiz == nullptr) {
        return nuevoNodo;
    } else {
        raiz = insertarNodo(raiz, nuevoNodo);
        return raiz;
    }
}

NodoVuelo* insertarNodo(NodoVuelo* padre, NodoVuelo* nuevoNodo) {
    if (padre == NULL) {
        return nuevoNodo;
    } else {
        // Comparación para determinar si el nuevo nodo debe ir a la izquierda o derecha
        if (nuevoNodo->info.fecha < padre->info.fecha || 
            (nuevoNodo->info.fecha == padre->info.fecha && nuevoNodo->info.hora < padre->info.hora)) {
            padre->izq = insertarNodo(padre->izq, nuevoNodo);
        } else {
            padre->der = insertarNodo(padre->der, nuevoNodo);
        }
        return padre;
    }
}

    void cancelarVuelo(int idVuelo) {
        raiz = eliminarNodo(raiz, idVuelo);
    }

NodoVuelo* eliminarNodo(NodoVuelo* nodoActual, int idVuelo) {
    if (nodoActual == NULL) {
        return nodoActual;
    }

    // Si el ID del vuelo es menor que el ID del nodo actual, ir a la izquierda
    if (idVuelo < nodoActual->info.id) {
        nodoActual->izq = eliminarNodo(nodoActual->izq, idVuelo);
    }
    // Si el ID del vuelo es mayor que el ID del nodo actual, ir a la derecha
    else if (idVuelo > nodoActual->info.id) {
        nodoActual->der = eliminarNodo(nodoActual->der, idVuelo);
    }
    // Si se encuentra el nodo con el ID del vuelo, proceder a eliminarlo
    else {
        // Nodo sin hijo izquierdo o derecho
        if (nodoActual->izq == NULL) {
            NodoVuelo* temp = nodoActual->der;
            delete nodoActual;
            return temp;
        } else if (nodoActual->der == NULL) {
            NodoVuelo* temp = nodoActual->izq;
            delete nodoActual;
            return temp;
        }

        // Nodo con dos hijos, encontrar sucesor (menor valor en el subárbol derecho)
        NodoVuelo* temp = nodoActual->der;
        while (temp->izq != NULL) {
            temp = temp->izq;
        }

        // Copiar el sucesor encontrado al nodo actual
        nodoActual->info = temp->info;

        // Eliminar el sucesor
        nodoActual->der = eliminarNodo(nodoActual->der, temp->info.id);
    }
    return nodoActual;
}

    void recorrerVuelosPrioridad() {
        recorrerArbol(raiz);
    }

    void recorrerArbol(NodoVuelo* nodo) {
        if (nodo != NULL) {
            recorrerArbol(nodo->der);
            cout << "Vuelo ID: " << nodo->info.id << " - Prioridad: " << nodo->info.fecha << " " << nodo->info.hora << endl;
            recorrerArbol(nodo->izq);
        }
    }
};

// Estructura para los datos de un pasajero
struct Pasajero {
    int id;
    string nombre;
    bool esSobrevendido;

    // Constructor para inicializar los atributos del pasajero
    Pasajero(int idPasajero, string nombrePasajero, bool sobrevendido) {
        id = idPasajero;
        nombre = nombrePasajero;
        esSobrevendido = sobrevendido;
    }
};

struct Pasajero {
    int id;
    char nombre[50];
    char numeroDocumento[20];
    char contacto[50];
    char nacionalidad[30];
    char fechaNacimiento[11]; // En formato dd/mm/aaaa
    char preferenciasAlimenticias[50];
    char informacionMedica[100];
    char programaViajero[50];
    char asientoPreferido[10];
    char idiomaPreferido[20];
    // Otros atributos del pasajero
};


struct Vuelo {
    int id;
    char ciudadOrigen[50];
    char ciudadDestino[50];
    char fecha[11]; // En formato dd/mm/aaaa
    char hora[6];   // En formato hh:mm
    int capacidad;
    // Otros atributos del vuelo
};

// Función para inicializar la gestión de pasajeros
void* inicializarGestionPasajeros(int cantidadVuelos) {
    Pasajero** pasajerosPorVuelo = (Pasajero*)malloc(sizeof(Pasajero) * cantidadVuelos);
    int* cantidadPasajeros = (int*)malloc(sizeof(int) * cantidadVuelos);
    // Verificación de la asignación de memoria
    if (!pasajerosPorVuelo || !cantidadPasajeros) {
        // Manejar el error de asignación de memoria
        return NULL;
    }
    // Inicialización del arreglo de cantidad de pasajeros por vuelo a 0
    for (int i = 0; i < cantidadVuelos; ++i) {
        cantidadPasajeros[i] = 0;
    }
    // Devolver un puntero que almacena ambos arreglos
    void** gestionPasajeros = (void*)malloc(sizeof(void) * 2);
    gestionPasajeros[0] = pasajerosPorVuelo;
    gestionPasajeros[1] = cantidadPasajeros;
    return gestionPasajeros;
}

// Función para vincular un pasajero a un vuelo
void vincularPasajeroAVuelo(void* gestionPasajeros, int idVuelo, Pasajero pasajero) {
    Pasajero** pasajerosPorVuelo = (Pasajero*)(((void*)gestionPasajeros)[0]);
    int* cantidadPasajeros = (int*)(((void**)gestionPasajeros)[1]);
    // Verificar si hay espacio para más pasajeros en el vuelo
    if (cantidadPasajeros[idVuelo] >= MAX_PASAJEROS_POR_VUELO) {
        printf("El vuelo está completo, no hay espacio para más pasajeros.\n");
    } else {
        // Vincular al pasajero con el vuelo correspondiente
        pasajerosPorVuelo[idVuelo][cantidadPasajeros[idVuelo]] = pasajero;
        cantidadPasajeros[idVuelo]++;
        printf("Pasajero vinculado al vuelo exitosamente.\n");
    }
}

// Función para liberar la memoria de la gestión de pasajeros
void liberarGestionPasajeros(void* gestionPasajeros, int cantidadVuelos) {
    Pasajero** pasajerosPorVuelo = (Pasajero*)(((void*)gestionPasajeros)[0]);
    int* cantidadPasajeros = (int*)(((void**)gestionPasajeros)[1]);
    // Liberar la memoria de cada arreglo de pasajeros por vuelo
    for (int i = 0; i < cantidadVuelos; ++i) {
        free(pasajerosPorVuelo[i]);
    }
    free(pasajerosPorVuelo);
    free(cantidadPasajeros);
    // Liberar el puntero que almacena ambos arreglos
    free(gestionPasajeros);
}



    void categorizarPasajero(int idPasajero, bool sobrevendido) {
        Pasajero* encontrarPasajeroPorID(int idPasajero, std::vector<Pasajero>& pasajeros) {
    for (auto& pasajero : pasajeros) {
        if (pasajero.id == idPasajero) {
            return &pasajero;
        }
    }
    return NULL; // Retornar NULL si no se encuentra el pasajero
}

void categorizarPasajero(int idPasajero, bool sobrevendido, std::vector<Pasajero>& pasajeros) {
    Pasajero* pasajero = encontrarPasajeroPorID(idPasajero, pasajeros);

    if (pasajero != NULL) {
        pasajero->sobrevendido = sobrevendido;
        if (sobrevendido) {
            // Acciones si el pasajero está sobrevendido
            // Por ejemplo:
            std::cout << "El pasajero está marcado como sobrevendido." << std::endl;
        } else {
            // Acciones si el pasajero no está sobrevendido
            // Por ejemplo:
            std::cout << "El pasajero no está marcado como sobrevendido." << std::endl;
        }
    } else {
        // Manejar el caso donde no se encuentra el pasajero con el ID especificado
        std::cout << "No se encontró al pasajero con el ID especificado." << std::endl;
    }
}
    }

   void eliminarPasajero(int idPasajero, std::vector<Pasajero>& pasajeros) {
    for (auto it = pasajeros.begin(); it != pasajeros.end(); ++it) {
        if (it->id == idPasajero) {
            pasajeros.erase(it);
            std::cout << "Pasajero eliminado exitosamente." << std::endl;
            return;
        }
    }
    std::cout << "No se encontró al pasajero con el ID especificado." << std::endl;
}


    void mostrarVueloYPasajeros(int idVuelo, std::vector<Vuelo>& vuelos, std::vector<Pasajero>& pasajeros) {
    bool vueloEncontrado = false;
    for (const auto& vuelo : vuelos) {
        if (vuelo.id == idVuelo) {
            vueloEncontrado = true;
            std::cout << "Información del vuelo:" << std::endl;
            std::cout << "ID del vuelo: " << vuelo.id << std::endl;
            std::cout << "Ciudad de origen: " << vuelo.ciudadOrigen << std::endl;
            std::cout << "Ciudad de destino: " << vuelo.ciudadDestino << std::endl;
            std::cout << "Fecha: " << vuelo.fecha << std::endl;
            std::cout << "Hora: " << vuelo.hora << std::endl;
            std::cout << "Capacidad: " << vuelo.capacidad << std::endl;

            std::cout << "Pasajeros asociados:" << std::endl;
            bool pasajeroEncontrado = false;
            for (const auto& pasajero : pasajeros) {
                if (pasajero.idVueloAsociado == idVuelo) {
                    pasajeroEncontrado = true;
                    std::cout << "ID del pasajero: " << pasajero.id << std::endl;
                    std::cout << "Nombre del pasajero: " << pasajero.nombre << std::endl;
                    // Mostrar más información del pasajero si es necesario
                }
            }
            if (!pasajeroEncontrado) {
                std::cout << "No hay pasajeros asociados a este vuelo." << std::endl;
            }
            break;
        }
    }
    if (!vueloEncontrado) {
        std::cout << "No se encontró ningún vuelo con el ID especificado." << std::endl;
    }
}

};

// Función principal (main) para ejecutar el programa
// Función principal (main) para ejecutar el programa
int main() {
    GestionVuelos gestorVuelos;
    GestionPasajeros gestorPasajeros;

    int opcion;
    do {
        // Mostrar el menú de opciones
        cout << "1. Registro de Vuelos en el Árbol" << endl;
        cout << "2. Valoración de la Ubicación en el Árbol del Vuelo" << endl;
        cout << "3. Cancelación de Vuelos" << endl;
        cout << "4. Recorrido de Vuelos de Mayor a Menor Prioridad" << endl;
        cout << "5. Vinculación de Pasajeros a Cada Vuelo" << endl;
        cout << "6. Categorización del Tipo de Pasajero" << endl;
        cout << "7. Eliminación de Pasajero y Reasignación de Tipo" << endl;
        cout << "8. Mostrar un Vuelo y sus Pasajeros" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        // Según la opción seleccionada, realizar la acción correspondiente
        switch (opcion) {
    case 1:
        registrarVuelo(gestorVuelos); // Llamada a la función de registro de vuelos
        break;
    case 2:
        valorarUbicacionVuelo(gestorVuelos); // Llamada a la función para valorar ubicación en el árbol
        break;
    case 3:
        cancelarVuelo(gestorVuelos); // Llamada a la función de cancelación de vuelos
        break;
    case 4:
        recorrerVuelosPrioridad(gestorVuelos); // Llamada a la función de recorrido de vuelos
        break;
    case 5:
        vincularPasajeros(gestorPasajeros); // Llamada a la función de vinculación de pasajeros
        break;
    case 6:
        categorizarPasajero(gestorPasajeros); // Llamada a la función de categorización de pasajeros
        break;
    case 7:
        eliminarPasajero(gestorPasajeros); // Llamada a la función de eliminación de pasajeros
        break;
    case 8:
        mostrarVueloYPasajeros(gestorVuelos, gestorPasajeros); // Llamada a la función de mostrar vuelos y pasajeros
        break;
    case 0:
        cout << "Saliendo del programa..." << endl;
        break;
    default:
        cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
}

    } while (opcion != 0);

    return 0;
}