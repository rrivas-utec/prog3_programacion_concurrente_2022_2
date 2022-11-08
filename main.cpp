#include <iostream>
#include <thread>
using namespace std;

void f1() {
    cout << "Hola F1" << endl;
}

void f2() {
    cout << "Hola F2" << endl;
}

void f3() {
    cout << "Hola F3" << endl;
}

int sumar(int a, int b) {
    return a + b;
}

void ejemplo_hilo_simple() {
    thread t1;
    t1 = thread(f1);
    t1.join();
}

void ejemplo_hilo_con_parametros() {
    thread t1(sumar, 10, 20);
    t1.join();
}

void sumar_ref(int a, int b, int& resultado) {
    resultado = a + b;
}

void ejemplo_hilo_con_parametros_por_referencia() {
    int total = 0;
    thread t1(sumar_ref, 15, 20, ref(total));
    t1.join();
    cout << total << endl;
}

void ejemplo_hilo_con_parametros_lambdas() {
    int total = 0;
    thread t1([&total]() {
        total = sumar(30, 50);
    });
    t1.join();
    cout << total << endl;
}

struct A {
    int sumar(int a, int b) {
        return a + b;
    }
    void sumar_ref(int a, int b, int& resultado) {
        resultado = a + b;
    }
};

void ejemplo_hilo_metodo_de_clase_lambda() {
    A a;
    int resultado = 0;
    thread t1([&a, &resultado]{
        resultado = a.sumar(10, 40);
    });
    t1.join();
    cout << resultado << endl;
}

void ejemplo_hilo_metodo_de_clase() {
    A a;
    int resultado = 0;
    thread t1(&A::sumar_ref,    // Direccion del metodo
              &a,               // Direccion del objeto
              12, 26, ref(resultado) // Parametros del metodo
              );
    t1.join();
    cout << resultado << endl;
}

template<typename T>
auto restar(T a, T b) {
    return a - b;
}

template<typename T>
void restar_ref(T a, T b, T& resultado) {
    resultado = a - b;
}

void ejemplo_hilos_template() {
    int total = 0;
    thread t1(restar_ref<int>, 10, 20, ref(total));
    t1.join();
    cout << total << endl;
}

void ejemplo_hilos_template_lambda() {
    int total = 0;
    thread t1([&total](){
        total = restar(20, 7);
    });
    t1.join();
    cout << total << endl;
}


int main(int argc, char **argv) {
//    ejemplo_hilo_simple();
//    ejemplo_hilo_con_parametros();
//    ejemplo_hilo_con_parametros_por_referencia();
//    ejemplo_hilo_con_parametros_lambdas();
//    ejemplo_hilo_metodo_de_clase_lambda();
//    ejemplo_hilo_metodo_de_clase();
//    ejemplo_hilos_template();
    ejemplo_hilos_template_lambda();
    return 0;
}