#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
struct Nodo {
    T data;
    Nodo<T>* derecha;
    Nodo<T>* izquierda;
    Nodo<T>* padre;
    Nodo<T>* hijo;
    bool mark; // indica si perdió o no un hijo
    int rank; // cantidad de hijos
    Nodo(): data(0), derecha(nullptr), izquierda(nullptr), padre(nullptr), hijo(nullptr), mark(false), rank(0){};
    Nodo(T valor): data(valor), derecha(nullptr), izquierda(nullptr), padre(nullptr), hijo(nullptr), mark(false), rank(0){};
};

//Función opcional para realizar impresión. Definición más abajo
template<typename T>
void print_nodo(Nodo<T> *nodo);

template<typename T>
class FHeap{
    private:
    Nodo<T>* rootlist; // lista raiz del heap
    Nodo<T>* ptr_min; // puntero al nodo min de rootlist
    int cont; // contador de la cantidad de nodos en el heap

    void visualizar_heap(Nodo<T>* nodo, int nivel);
    public:
    FHeap(): rootlist(nullptr), ptr_min(nullptr), cont(0){};
    
    // declaración de los métodos de la clase principal
    void insert(T valor);
    T valor_min();
    bool empty();
    int size();
    FHeap Union(FHeap<T>);
    Nodo<T>* extractMin();
    void consolidate();
    
    void print() {
        print_nodo(rootlist);
    }

    
    void visualizar();
};

template<typename T>
void print_nodo(Nodo<T> *nodo) {
    std::cout << "Se van a imprimir los valores del nodo.\n";
    auto temp = nodo;
    while (true) {
        std::cout << temp->data << ' ';
        if (temp->derecha == nodo) break;
        temp = temp->derecha;
    }
    std::cout << '\n';
}

//Función que compara los valores de dos nodos raíz, y el mayor de los dos se vuelve hijo del otro.
template<typename T>
Nodo<T> *linking(Nodo<T> *N1, Nodo<T> *N2) {
    Nodo<T> *NDown = N1->data >= N2->data ? N1 : N2;
    Nodo<T> *NUp = NDown == N1 ? N2 : N1;

    if (NUp->hijo == nullptr) { //Si el menor no tiene hijos, el mayor se vuelve su hijo único
        NUp->hijo = NDown;
        NDown->izquierda = NDown;
        NDown->derecha = NDown;
    } else {
        Nodo<T> *primerHijo = NUp->hijo;
        Nodo<T> *ultimoHijo = primerHijo->izquierda;

        NDown->izquierda = ultimoHijo;
        NDown->derecha = primerHijo;
        ultimoHijo->derecha = NDown;
        primerHijo->izquierda = NDown;
    }
    NDown->padre = NUp;
    NUp->rank++; //Se aumenta la cantidad de hijos del nodo menor
    return NUp;
}

template <typename T>
void FHeap<T>::insert(T valor){
    // creamos una pequeña lista circular con el nodo a insertar
    Nodo<T>* nnodo = new Nodo<T>(valor);
    nnodo->derecha = nnodo->izquierda = nnodo;

    // preguntamos si el rootlist esta vacío o no
    if(rootlist == nullptr){
        // en caso lo sea, el nuevo nodo ocupada ese lugar
        rootlist = nnodo;
        // al igual que el puntero mínimo
        ptr_min = nnodo;
    } else {
        // en caso rootlist no sea vacío
        nnodo->derecha = rootlist;
        nnodo->izquierda = rootlist->izquierda;
        rootlist->izquierda->derecha = nnodo;
        rootlist->izquierda = nnodo;
        // actualizamos el puntero mínimo si es el caso
        if (nnodo->data < ptr_min->data){
            ptr_min = nnodo;
        }
    }
    // incrementamos en 1 la cantidad de nodos en el Heap
    cont++;
}

template <typename T>
T FHeap<T>::valor_min(){
    return ptr_min->data;
}

template <typename T>
bool FHeap<T>::empty(){
    return rootlist == nullptr;
}

template <typename T>
int FHeap<T>::size(){
    return cont;
}

//Función para unir dos FHeap. Se vacía el otro FHeap
template<typename T>
FHeap<T> FHeap<T>::Union(FHeap<T> FH2) {
    if (FH2.rootlist != nullptr) {
        if (this->rootlist == nullptr) {
            this->rootlist = FH2.rootlist;
            this->ptr_min = FH2.ptr_min;
            this->cont = FH2.cont;
        } else {
            this->ptr_min = this->valor_min() <= FH2.valor_min() ? this->ptr_min : FH2.ptr_min; //Obtenemos el nodo con menor valor

            //Empezamos con la unión
            auto temp = rootlist->izquierda;
            this->rootlist->izquierda->derecha = FH2.rootlist;
            this->rootlist->izquierda = FH2.rootlist->izquierda;
            FH2.rootlist->izquierda->derecha = this->rootlist;
            FH2.rootlist->izquierda = temp;

            this->cont += FH2.cont;
        }

        //Eliminamos FH2
        FH2.rootlist = nullptr;
        FH2.ptr_min = nullptr;
        FH2.cont = 0;
    }
    return *this;
}

template<typename T>
void FHeap<T>::consolidate() {
    // Máxima cantidad de hijos de un árbol
    int D = static_cast<int>(std::log(this->cont) / std::log(2)) + 1;
    auto **lista = new Nodo<T> *[D]; // Puntero de punteros a Nodo de largo log_2(n_nodos en FHeap) + 1
    for (int i = 0; i < D; i++) {
        *(lista + i) = nullptr;
    }

    // Recorremos toda la rootList
    auto temp = rootlist;
    Nodo<T> *temp2 = temp;
    do {
        auto temp3 = temp2->derecha; // Guarda lo que estaba originalmente a la derecha de temp2

        // Mientras el rango de temp2 ya esté ocupado en la lista
        while (*(lista + temp2->rank) != nullptr) {
            int d = temp2->rank;   // Guardas el rank actual
            temp2 = linking(temp2, *(lista + d));  // Unes los árboles con el mismo rango
            *(lista + d) = nullptr;  // Limpias la entrada
        }

        *(lista + temp2->rank) = temp2;  // Asigna temp2 a su rango en lista
        temp2 = temp3;  // Mueve temp2 a la derecha

    } while (temp != temp2);  // Continúa hasta que completes el ciclo

    // Creamos un nuevo heap con cada valor de la lista.
    this->rootlist = nullptr;
    for (int i = 0; i < D; i++) {
        if (*(lista + i) != nullptr) {
            if (rootlist == nullptr) {
                rootlist = *(lista + i);
                rootlist->izquierda = rootlist->derecha = rootlist;
            } else {
                (*(lista + i))->izquierda = rootlist->izquierda;
                (*(lista + i))->derecha = rootlist;
                rootlist->izquierda->derecha = *(lista + i);
                rootlist->izquierda = *(lista + i);
            }
            if ((*(lista + i))->data < ptr_min->data) ptr_min = *(lista + i);
        }
    }
    delete[] lista;
}

//Función para eliminar el nodo con menor valor de un FHeap.
template<typename T>
Nodo<T>* FHeap<T>::extractMin() {
    auto z = this->ptr_min;
    if (this->rootlist != nullptr) {
        if (cont == 1) { //Si solo hay un nodo, lo eliminamos
            ptr_min = nullptr;
            rootlist = nullptr;
            cont--;
            return z;
        }

        if (z->hijo != nullptr) {
            // Añadir los hijos del nodo mínimo a la lista raíz
            z->hijo->derecha->izquierda = rootlist;
            z->hijo->derecha = rootlist->derecha;
            rootlist->derecha->izquierda = z->hijo;
            rootlist->derecha = z->hijo->derecha;

            auto y = z->hijo;
            do{
                y->padre = nullptr;
                y = y->derecha;
            } while(y != z->hijo);
            z->hijo = nullptr;
        }

        // Eliminar el nodo mínimo
        ptr_min->izquierda->derecha = ptr_min->derecha;
        ptr_min->derecha->izquierda = ptr_min->izquierda;
        ptr_min = ptr_min->derecha; // Esto de forma momentánea.
        this->cont--;

        // Llamamos a la función consolidate
        consolidate();
    }
    return z;
}

template <typename T>
void FHeap<T>::visualizar_heap(Nodo<T>* nodo, int nivel) {
    if (nodo == nullptr) return;

    Nodo<T>* temp = nodo;
    do {
        // Imprimir el valor del nodo con una indentación basada en el nivel
        for (int i = 0; i < nivel; ++i) {
            std::cout << "  "; // 2 espacios por cada nivel de profundidad
        }
        std::cout << "└─ Nodo: " << temp->data << " (rank: " << temp->rank << ")" << std::endl;

        // Si el nodo tiene hijos, llamamos recursivamente para imprimirlos
        if (temp->hijo != nullptr) {
            visualizar_heap(temp->hijo, nivel + 1);
        }

        temp = temp->derecha;
    } while (temp != nodo);
}

template <typename T>
void FHeap<T>::visualizar() {
    std::cout << "Visualización del Fibonacci Heap:" << std::endl;
    if (rootlist == nullptr) {
        std::cout << "Heap vacío." << std::endl;
        return;
    }
    visualizar_heap(rootlist, 0);
}


int main() {
    FHeap<int> heap;

    // Insertar elementos en el heap
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    heap.insert(30);

    heap.visualizar();
    cout << "Heap después de las inserciones:" << endl;
    heap.print();
    
    // Obtener el valor mínimo
    cout << "El valor mínimo es: " << heap.valor_min() << endl;

    // Extraer el valor mínimo
    Nodo<int>* minNode = heap.extractMin();
    cout << "El valor mínimo extraído es: " << minNode->data << endl;
    
    // Mostrar el heap después de extraer el valor mínimo
    cout << "Heap después de extraer el mínimo:" << endl;
    heap.print();
    heap.visualizar();

    // Unir dos heaps
    FHeap<int> heap2;
    heap2.insert(25);
    heap2.insert(7);

    cout << "Segundo heap:" << endl;
    heap2.print();

    cout << "Uniendo los dos heaps..." << endl;
    heap = heap.Union(heap2);

    // Mostrar el heap unido
    cout << "Heap después de la unión:" << endl;
    heap.print();
    heap.visualizar();

    // Extraer el valor mínimo de nuevo
    minNode = heap.extractMin();
    cout << "El valor mínimo extraído es: " << minNode->data << endl;
    
    // Mostrar el heap después de extraer el mínimo de nuevo
    cout << "Heap después de extraer el mínimo nuevamente:" << endl;
    heap.print();

    return 0;
}

