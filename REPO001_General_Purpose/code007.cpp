/* DESCRIPTION
    Topic: POO
    Goal: Learn POO in c++
    Author: Luis Barahoana
    Date: Aug 27, 2024
    Status:


*/


/*
//EXAMPLE 1: Class and Object
#include <iostream>
using namespace std;

class Car {
private:
    int speed;
    float factor;

public:
    Car() : speed(0) {}  // Constructor
    void setSpeed(int s) { speed = s; } //Método para setear las variables
    int getSpeed() { return speed; }    //Método para retornar variables
                                        //Método adicional
};

//EXAMPLE 2: Inheritance
class Vehicle {
public:
    void start() { cout << "Vehicle started." << endl; }
};

class Car2 : public Vehicle {
public:
    void honk() { cout << "Car honking." << endl; }
};

int main() {

    //EXAMPLE 1:
    Car myCar;
    myCar.setSpeed(100);
    cout << "Speed: " << myCar.getSpeed() << endl;
  
    //EXAMPLE 2:
    Car2 myCar2;
    myCar2.start();  // Inherited from Vehicle
    myCar2.honk();
    return 0;
}

*/


/* EXAMPLE 3: Objects and class
    #include <iostream>
    #include <string>

    class Car {
    private:
        int speed;
        std::string brand;
        std::string model;

    public:
        // Constructor
        Car(std::string b, std::string m, int s) : brand(b), model(m), speed(s) {
            std::cout << "Car " << brand << " " << model << " is created." << std::endl;
        }

        // Destructor
        ~Car() {
            std::cout << "Car " << brand << " " << model << " is destroyed." << std::endl;
        }

        // Setters
        void setSpeed(int s) { speed = s; }
        void setBrand(std::string b) { brand = b; }
        void setModel(std::string m) { model = m; }

        // Getters
        int getSpeed() const { return speed; }
        std::string getBrand() const { return brand; }
        std::string getModel() const { return model; }

        // Other methods
        void printDetails() const {
            std::cout << "Brand: " << brand << ", Model: " << model << ", Speed: " << speed << " km/h" << std::endl;
        }
    };

    int main() {
        // Creating an object of Car
        Car myCar("Toyota", "Corolla", 120);

        // Using member functions
        myCar.printDetails();
        myCar.setSpeed(140);
        std::cout << "Updated Speed: " << myCar.getSpeed() << " km/h" << std::endl;

        // The destructor is automatically called when the object goes out of scope
        return 0;
    }





*/


/* EXAMPLE 4: Example with Dynamic Memory Allocation
    class Car {
    private:
        int* speed;  // Dynamically allocated
        std::string brand;
        std::string model;

    public:
        // Constructor
        Car(std::string b, std::string m, int s) : brand(b), model(m) {
            speed = new int(s);  // Allocate memory for speed
            std::cout << "Car " << brand << " " << model << " is created." << std::endl;
        }

        // Destructor
        ~Car() {
            delete speed;  // Free the allocated memory
            std::cout << "Car " << brand << " " << model << " is destroyed." << std::endl;
        }

        // Getter
        int getSpeed() const { return *speed; }

        // Other methods
        void printDetails() const {
            std::cout << "Brand: " << brand << ", Model: " << model << ", Speed: " << *speed << " km/h" << std::endl;
        }
    };



*/
#include <iostream>
using namespace std;

class Felino { // CLASE MADRE (base)
private:
    std::string name;
    std::string color;
    int* id;  // Puntero para almacenar el ID dinámicamente

public:
    // Constructor
    Felino(std::string nombre, std::string color, int idd) : name(nombre), color(color) {
        id = new int(idd);  // Asignar memoria dinámica para 'id' e inicializarla con 'idd'
    }

    // Getters y Setters
    void setName(string otro_name) { name = otro_name; }
    void setColor(string otro_color) { color = otro_color; }
    string getName() const { return name; }
    string getColor() const { return color; }

    // Método para emitir un sonido
    void maullar() {
        cout << "Miau" << endl;
    }

    // Destructor
    ~Felino() {
        delete id;  // Liberar la memoria asignada dinámicamente para 'id'
        cout << "ID successfully deleted." << endl;
    }
};

class Gato : public Felino { // CLASE HIJA (derivada)
private:
    string* raza;  // Puntero para almacenar la raza del gato dinámicamente

public:
    // Constructor
    Gato(string nombre, string color, string razaa, int idd) : Felino(nombre, color, idd) {
        // Invocamos al constructor de Felino para inicializar los miembros heredados
        raza = new string(razaa);  // Asignar memoria dinámica para 'raza' e inicializarla con 'razaa'
    }

    // Método para obtener la raza
    string getRaza() const { return *raza; }

    // Destructor
    ~Gato() {
        delete raza;  // Liberar la memoria asignada dinámicamente para 'raza'
        cout << "Raza successfully deleted." << endl;
        // El destructor de Felino se llama automáticamente después, eliminando 'id'
    }
};

int main() {
    // Crear un objeto de la clase Gato
    Gato miGato("Michi", "Negro", "Siamés", 101);

    // Usar los métodos de la clase Gato
    cout << "Nombre: " << miGato.getName() << endl;
    cout << "Color: " << miGato.getColor() << endl;
    cout << "Raza: " << miGato.getRaza() << endl;
    miGato.maullar();

    // El destructor se llama automáticamente cuando 'miGato' sale del alcance (al final de main)
    return 0;
}
