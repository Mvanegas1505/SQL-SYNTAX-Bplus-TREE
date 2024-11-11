#include <iomanip>
#include "ArbolBPlus.h"
#include "Dato.h"

// Implementación del método insertar
// Muestra en la consola el comando simulado de inserción con columnas y valores dados
// Implementación del método insertar
// Muestra en la consola el comando simulado de inserción con columnas y valores dados
void ArbolBPlus::insertar(const std::string& tabla, std::vector<std::string> columnas, std::vector<std::string> valores) {
    std::cout << "Ejecutando: INSERT INTO " << tabla << " (";

    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }

    std::cout << ") VALUES (";
    for (size_t i = 0; i < valores.size(); ++i) {
        std::cout << valores[i];
        if (i < valores.size() - 1) std::cout << ", ";
    }
    std::cout << ")\n";

    // Verificar que el número de columnas y valores coincida
    if (columnas.size() != valores.size()) {
        std::cerr << "Error: El número de columnas y valores no coincide." << std::endl;
        return;
    }

    // Crear un nuevo Dato con los valores proporcionados
    Dato* dato = new Dato(valores[0], std::stoi(valores[1]));

    if (!root) {
        root = new BpNode(true);
        root->key.push_back(dato);
    } else {
        if (root->key.size() == (size_t)maxKeys) {
            BpNode* newRoot = new BpNode(false);
            newRoot->child_ptrs.push_back(root);
            BpNode* hijo = splitchild(newRoot, 0);
            newRoot->child_ptrs.push_back(hijo);
            root = newRoot;
        }
        insertNonFull(root, dato);
    }
}


// Implementación del método seleccionar
// Muestra en la consola el comando simulado de selección con columnas especificadas
void ArbolBPlus::seleccionar(const std::string& tabla, const std::vector<std::string>& columnas) {
    std::cout << "Ejecutando: SELECT ";
    // Itera y muestra cada columna seleccionada
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }
    std::cout << " FROM " << tabla << std::endl;

     if (!root) {
        std::cout << "Tabla vacía" << std::endl;
        return;
    }

    // Imprimir encabezados
    for (const auto& columna : columnas) {
        std::cout << std::setw(15) << std::left << columna;
    }
    std::cout << std::endl;
    std::cout << std::string(15 * columnas.size(), '-') << std::endl;

    // Encontrar el nodo más a la izquierda (primer nodo hoja)
    BpNode* actual = root;
    while (!actual->isLeaf) {
        actual = actual->child_ptrs[0];
    }

    // Procesar todos los nodos hoja encontrados
    while (actual != nullptr && actual->isLeaf) {
        for (size_t i = 0; i < actual->key.size(); i++) {
            // Mostrar datos según las columnas solicitadas
            for (const auto& columna : columnas) {
                if (columna == "id") {
                    std::cout << std::setw(15) << std::left << actual->key[i];
                }
                if (columna == "nombre" && actual->key.size() > i) {
                    std::cout << std::setw(15) << std::left << actual->key[i]->obtenerNombre();
                }
                // Añadir más columnas según sea necesario
            }
            std::cout << std::endl;
        }
        
        actual = actual->next;
        // Si tuviéramos un enlace al siguiente nodo hoja, lo usaríamos aquí
        break; // Por ahora terminamos después del primer nodo hoja
    }

}


// Implementación del método actualizar
// Muestra en la consola el comando simulado de actualización con asignaciones y condición
void ArbolBPlus::actualizar(const std::string& tabla, const std::map<std::string, std::string>& asignaciones, const std::string& condicion) {
    std::cout << "Ejecutando: UPDATE " << tabla << " SET ";
    size_t i = 0;
    // Itera y muestra cada asignación en el formato columna=valor
    for (const auto& asignacion : asignaciones) {
        std::cout << asignacion.first << " = " << asignacion.second;
        if (i < asignaciones.size() - 1) std::cout << ", ";
        ++i;
    }
    std::cout << " WHERE " << condicion << std::endl;

    
    auto it = asignaciones.begin();

    std::string keyUpper = it->first;
    std::transform(keyUpper.begin(), keyUpper.end(), keyUpper.begin(), ::toupper);
    if (it != asignaciones.end() && keyUpper == "ID"){
         Dato* aux = new Dato(condicion, std::stoi(it->second));
         BpNode* nodoObjetivo = buscarNodo(root, aux);
         if (nodoObjetivo != nullptr){
             
             nodoObjetivo->key[0]->establecerId(std::stoi(it->second));
               
             std::cout << "Actualizacion realizada en clave" << nodoObjetivo->key[0]->obtenerNombre() << ".\n";

         }else {
         std::cout << "No se encontro el registro.\n";
         }
         
    }

    /*int claveObjetivo = extraerClaveDesdeCondicion(condicion);

    BpNode* nodoObjetivo = buscarNodo(root, claveObjetivo);

    if(nodoObjetivo) {
        for(size_t j = 0; j < nodoObjetivo->key.size(); j++){
            if(nodoObjetivo->key[j]->obtenerId() == claveObjetivo){
                Dato* dato = nodoObjetivo->key[j];

                for(const auto& asignacion : asignaciones){
                    if(asignacion.first == "nombre"){
                        dato->establecerNombre(asignacion.second);
                    } else if(asignacion.first == "identificacion"){
                        dato->establecerId(std::stoi(asignacion.second));
                    }
                }
                std::cout << "Actualizacion realizada en clave" << claveObjetivo << ".\n";
                return;
            }
        }
    } else {
        std::cout << "Clave " << claveObjetivo << " no encontrada para actualizacion.\n";
    }

    */
}

// Implementación del método eliminar
// Muestra en la consola el comando simulado de eliminación con la condición dada
// Implementación del método eliminar
// Muestra en la consola el comando simulado de eliminación con la condición dada
void ArbolBPlus::eliminar(const std::string& tabla, const std::string& condicion) {
    std::cout << "Ejecutando: DELETE FROM " << tabla << " WHERE " << condicion << std::endl;

    if (!root) {
        std::cout << "El árbol está vacío. No hay nada que eliminar.\n";
        return;
    }

    Dato* claveEliminar;
    size_t pos = condicion.find('=');
    if (pos != std::string::npos) {
        std::string claveStr = condicion.substr(pos + 1);
        try {
            // Intenta convertir la clave a un número entero para eliminar por ID
            int claveId = std::stoi(claveStr);
            claveEliminar = new Dato("", claveId);  // Clave basada en ID
        } catch (const std::invalid_argument&) {
            // Si no es un número, tratamos la clave como un nombre para eliminar por nombre
            claveEliminar = new Dato(claveStr, 0); // Clave basada en nombre
        }
    } else {
        std::cout << "Condición inválida.\n";
        return;
    }

    eliminarClave(root, claveEliminar);
    delete claveEliminar;

    if (root->key.empty()) {
        root = root->isLeaf ? nullptr : root->child_ptrs[0];
    }
}

void ArbolBPlus::eliminarClave(BpNode* nodo, Dato* clave) {
    size_t i = 0;
    bool esBusquedaPorId = (clave->obtenerId() != 0); // Si el ID es no nulo, es una eliminación por ID

    // Búsqueda inicial: determinar la posición de la clave en el nodo
    while (i < nodo->key.size() && 
          (esBusquedaPorId ? nodo->key[i]->obtenerId() < clave->obtenerId() : nodo->key[i]->obtenerNombre() != clave->obtenerNombre())) {
        i++;
    }

    if (nodo->isLeaf) {
        // En nodo hoja: verificar si la clave se encuentra en el índice correcto y eliminarla
        bool encontrada = (i < nodo->key.size()) &&
                          (esBusquedaPorId ? nodo->key[i]->obtenerId() == clave->obtenerId()
                                           : nodo->key[i]->obtenerNombre() == clave->obtenerNombre());
        if (encontrada) {
            nodo->key.erase(nodo->key.begin() + i);
            std::cout << "Clave eliminada: " << (esBusquedaPorId ? "ID " + std::to_string(clave->obtenerId())
                                                                 : "Nombre " + clave->obtenerNombre()) << "\n";
            if (nodo->key.empty()) rebalancearDespuesDeEliminar(nodo);
        } else {
            std::cout << "Clave no encontrada en el árbol.\n";
        }
    } else {
        // En nodo interno: recursivamente eliminar en el hijo correspondiente
        if (i < nodo->child_ptrs.size()) {
            eliminarClave(nodo->child_ptrs[i], clave);
            if (nodo->child_ptrs[i]->key.empty()) rebalancearDespuesDeEliminar(nodo->child_ptrs[i]);
        }
    }
}

void ArbolBPlus::rebalancearDespuesDeEliminar(BpNode* nodo) {
    if (!nodo || nodo == root) return; // No hay necesidad de rebalancear si el nodo es nulo o es la raíz

    BpNode* padre = encontrarPadre(root, nodo);
    if (!padre) return; // Si no se encuentra el padre, no se puede rebalancear

    size_t idx = std::find(padre->child_ptrs.begin(), padre->child_ptrs.end(), nodo) - padre->child_ptrs.begin();

    if (idx > 0 && !padre->child_ptrs[idx - 1]->key.empty()) {
        redistribuirIzq(padre, idx - 1);
    } else if (idx < padre->child_ptrs.size() - 1 && !padre->child_ptrs[idx + 1]->key.empty()) {
        redistribuirDer(padre, idx);
    } else {
        fusionarNodos(padre, idx > 0 ? idx - 1 : idx);
    }
}

void ArbolBPlus::redistribuirIzq(BpNode* padre, size_t idx) {
    BpNode* izq = padre->child_ptrs[idx];
    BpNode* der = padre->child_ptrs[idx + 1];
    if (!izq || !der) return; // Verificar que los nodos izquierdo y derecho no sean nulos

    der->key.insert(der->key.begin(), padre->key[idx]);
    padre->key[idx] = izq->key.back();
    izq->key.pop_back();
}

void ArbolBPlus::redistribuirDer(BpNode* padre, size_t idx) {
    BpNode* izq = padre->child_ptrs[idx];
    BpNode* der = padre->child_ptrs[idx + 1];
    if (!izq || !der) return; // Verificar que los nodos izquierdo y derecho no sean nulos

    izq->key.push_back(padre->key[idx]);
    padre->key[idx] = der->key.front();
    der->key.erase(der->key.begin());
}

void ArbolBPlus::fusionarNodos(BpNode* padre, size_t idx) {
    BpNode* izq = padre->child_ptrs[idx];
    BpNode* der = padre->child_ptrs[idx + 1];
    if (!izq || !der) return; // Verificar que los nodos izquierdo y derecho no sean nulos

    izq->key.push_back(padre->key[idx]);
    izq->key.insert(izq->key.end(), der->key.begin(), der->key.end());
    izq->child_ptrs.insert(izq->child_ptrs.end(), der->child_ptrs.begin(), der->child_ptrs.end());

    padre->key.erase(padre->key.begin() + idx);
    padre->child_ptrs.erase(padre->child_ptrs.begin() + idx + 1);

    delete der;
}

BpNode* ArbolBPlus::encontrarPadre(BpNode* nodoActual, BpNode* nodoHijo) {
    if (!nodoActual || nodoActual->isLeaf || nodoActual == nodoHijo) return nullptr;
    for (auto* child : nodoActual->child_ptrs) {
        if (child == nodoHijo) return nodoActual;
        BpNode* resultado = encontrarPadre(child, nodoHijo);
        if (resultado) return resultado;
    }
    return nullptr;
}




void ArbolBPlus::insertNonFull(BpNode* nodo, Dato* llave) {
    if (nodo->isLeaf) {
        nodo->key.push_back(llave);
        std::sort(nodo->key.begin(), nodo->key.end());
    } else {
        size_t i = 0;
        while (i < nodo->key.size() && llave->obtenerId() > nodo->key[i]->obtenerId()) {
            i++;
        }
        if (nodo->child_ptrs[i]->key.size() == static_cast<size_t>(maxKeys)) {
            BpNode* hijo = splitchild(nodo, i);
            nodo->child_ptrs.insert(nodo->child_ptrs.begin() + i + 1, hijo);
            if (llave > nodo->key[i]) i++;
        }
                insertNonFull(nodo->child_ptrs[i], llave);
            }
        }
    


BpNode* ArbolBPlus::splitchild(BpNode* nodo, int indice) {

    BpNode* hijo = nodo->child_ptrs[indice];
    BpNode* nuevoNodo = new BpNode(hijo->isLeaf);

    int mitad = maxKeys / 2;
    nodo->key.insert(nodo->key.begin() + indice, hijo->key[mitad]);

    nuevoNodo->key.assign(hijo->key.begin() + mitad + 1, hijo->key.end());
    hijo->key.resize(mitad);

    if (!hijo->isLeaf) {
        nuevoNodo->child_ptrs.assign(hijo->child_ptrs.begin() + mitad + 1, hijo->child_ptrs.end());
        hijo->child_ptrs.resize(mitad + 1);
    }
    return nuevoNodo;
}

int ArbolBPlus::extraerClaveDesdeCondicion(const std::string& condicion){
    size_t pos = condicion.find("=");
    if(pos != std::string::npos){
        return std::stoi(condicion.substr(pos + 1));
    }
    return -1;
}

BpNode* ArbolBPlus::buscarNodo(BpNode* nodo, Dato* clave){
    if(!nodo) return nullptr;

    size_t i = 0;
    while (i < nodo->key.size() && clave->obtenerId() > nodo->key[i]->obtenerId()){
        i++;
    }
    if(i < nodo->key.size() && nodo->key[i]->obtenerId() == clave->obtenerId()){
        return nodo;
    }

    if(nodo->isLeaf){
        return nullptr;
    } else {
        return buscarNodo(nodo->child_ptrs[i], clave);
    }
}


void ArbolBPlus::mostrarArbol() {
    printTreeAux(root, "", true);
}

void ArbolBPlus::printTreeAux(BpNode* nodo, std::string prefix, bool esUltimo) {
    if (!nodo) return;

    std::cout << prefix;
    std::cout << (esUltimo ? "└── " : "├── ");

    for (size_t i = 0; i < nodo->key.size(); i++) {
        std::cout << "Nodo: " << nodo->key[i]->obtenerNombre() << " (" << nodo->key[i]->obtenerId() << ")";
        if (i != nodo->key.size() - 1) {
            std::cout << " , ";
        }
    }
    std::cout << std::endl;

    prefix += (esUltimo ? "    " : "|   ");
    for (size_t i = 0; i < nodo->child_ptrs.size(); i++) {
        printTreeAux(nodo->child_ptrs[i], prefix, i == nodo->child_ptrs.size() - 1);
    }
}