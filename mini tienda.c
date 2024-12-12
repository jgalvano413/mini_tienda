#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


//ESTADOS
#define EDOPRES  1
#define DESPACHANDO 2
#define CAMBIO 3
#define SLEEP  4    
#define DEBUG  5
#define PAY  6


//Variables Locales

unsigned char cadena[20];
const char *Productos[] = {"BARBACOA","HOCHO","HORCHATON","TACO DE CHORIZO","AGUA DE COCO"};
unsigned int Costos[] = {500,52,2500,25,12};
const char *carrito[100];
const char *History[100];
unsigned int debt = 0;
unsigned int choicePorduct = 0;
unsigned int indexcarrito = 0;
unsigned int estado,timerPress;
unsigned int userData,thread;
unsigned int thread2 = 0;
unsigned int threadRead = 1;
unsigned int thread_interrumpt = 1;
int main() {
    // Write C code here
    
    estado = EDOPRES;
    thread = 1;
    while(thread){
        switch(estado){
            case EDOPRES:
                edo_press();
                break;
            case CAMBIO:
                break;
            case SLEEP:
                thread = 0;
                break;
            case DEBUG:
                break;
            case PAY:
                pay();
                break;
        }
    }
}

void pay(){
    if (debt > 0){
        printf("--------------------------------- \n");
        printf("Proceso de Pago \n");
        printf("Monto a pagar: $%d MXN\n", debt);
        printf("Ingresa Cantidad:  \n");
        external_interrupt_readData();
        if (userData != 0) {
             if (userData > debt){
                 debt = userData - debt;
                 printf("Gracias Por tu Pago tome su cambio \n");
                 printf("Cambio: $%d MXN\n", debt);
                 printf("--------------------------------- \n");
                 thread2 = 0;
                 estado = EDOPRES;
             }else if (userData == debt){
                 debt = 0;
                 printf("Gracias Por su Compra \n");
                 printf("--------------------------------- \n");
                 thread2 = 0;
                 estado = EDOPRES;
             } else {
                 debt = debt -userData;
                 printf("Aun Me debes... \n");
                 printf("--------------------------------- \n");
             }
        }
    } else {
        printf("--------------------------------- \n");
        printf("No debes Nada \n");
        printf("--------------------------------- \n");
        thread2 = 0;
        estado = EDOPRES;
    }
     
    
}

void edo_press(){
    
    if (!thread2){
        printf("--------------------------------- \n");
        printf("Bienvenido Escoge una Opcion \n");
        printf("--------------------------------- \n");
        printf("  ");
        printf("---------------------------------\n");
        printf("1.- Barbacoa\n");
        printf("2.- Hochos Prrns\n");
        printf("3.- Un Horchaton\n");
        printf("4.- Tacos de Chorizo\n");
        printf("5.- Awita de Coco\n");
        printf("6.- Mostrar Carrito\n");
        printf("7.- Pagar\n");
        printf("8.- Historial de Compra\n");
        printf("9.- Salir\n");
        printf("---------------------------------\n");
        thread2 = 1;
    } else {
        external_interrupt_readData();
        if (userData != 0) {
            choice(userData);
        }
    }
}

void addBuy(int valor){
   switch(valor){
       case 1:
             debt = debt + Costos[choicePorduct];
             carrito[indexcarrito] = Productos[choicePorduct];
             indexcarrito++;
             printf("--------------------------------- \n");
            printf("Agregado con Exito\n");
            printf("--------------------------------- \n");
             break;
       case 2:
            printf("OK\n");
            break;
       default:
            printf("--------------------------------- \n");
            printf("Opcion no Valida\n");
            printf("--------------------------------- \n");
            break;
   }
   thread2 = 0;
}


void choice(int valor){
    switch(valor) {
        case 1:
            choicePorduct = valor;
            printf("--------------------------------- \n");
            printf("Escogiste: %s\n", Productos[valor - 1]);
            printf("con valor de: $%d MXN\n", Costos[valor - 1]);
            printf("¿Agregamos al Carrito? \n");
            printf("1.- Si \n");
            printf("2.- No \n");
            printf("--------------------------------- \n");
            external_interrupt_readData();
            if (userData != 0) {
                addBuy(userData);
            }
            break;
        case 2:
            choicePorduct = valor;
            printf("--------------------------------- \n");
            printf("Escogiste: %s\n", Productos[valor - 1]);
            printf("con valor de: $%d MXN\n", Costos[valor - 1]);
            printf("¿Agregamos al Carrito? \n");
            printf("1.- Si \n");
            printf("2.- No \n");
            printf("--------------------------------- \n");
            external_interrupt_readData();
            if (userData != 0) {
                addBuy(userData);
            }
            break;
        case 3:
            choicePorduct = valor;
            printf("--------------------------------- \n");
            printf("Escogiste: %s\n", Productos[valor - 1]);
            printf("con valor de: $%d MXN\n", Costos[valor - 1]);
            printf("¿Agregamos al Carrito? \n");
            printf("1.- Si \n");
            printf("2.- No \n");
            printf("--------------------------------- \n");
            external_interrupt_readData();
            if (userData != 0) {
                addBuy(userData);
            }
            break;
        case 4:
            choicePorduct = valor;
            printf("--------------------------------- \n");
            printf("Escogiste: %s\n", Productos[valor - 1]);
            printf("con valor de: $%d MXN\n", Costos[valor - 1]);
            printf("¿Agregamos al Carrito? \n");
            printf("1.- Si \n");
            printf("2.- No \n");
            printf("--------------------------------- \n");
            external_interrupt_readData();
            if (userData != 0) {
                addBuy(userData);
            }
            break;
        case 5:
            choicePorduct = valor;
            printf("--------------------------------- \n");
            printf("Escogiste: %s\n", Productos[valor - 1]);
            printf("con valor de: $%d MXN\n", Costos[valor - 1]);
            printf("¿Agregamos al Carrito? \n");
            printf("1.- Si \n");
            printf("2.- No \n");
            printf("--------------------------------- \n");
            external_interrupt_readData();
            if (userData != 0) {
                addBuy(userData);
            }
            break;
        case 6:
            break;
        case 7:
            estado = PAY;
            break;
        case 8:
            printf("Presionado: 8\n");
            break;
        case 9:
            printf("No vuelvas Jamas Qlero");
            estado = SLEEP;
            break;
        default:
            printf("Opcion no Valida\n");
            thread2 = 0;
            userData = 0;
            break;
    }
}

void showbuys(){
    
}

void external_interrupt_readData() {
    int resultadoScanf;
    userData = 0;
    threadRead =1;
    while (threadRead) {
        resultadoScanf = scanf("%d", &userData);
        sleep(1);
        if (resultadoScanf == 1) { // Verificar si se ha ingresado un valor válido
            threadRead = 0;
        } else { // Limpiar el búfer de entrada en caso de que la entrada no sea un número
            printf("Caracter No valido\n");
            while (getchar() != '\n'); // Leer y descartar caracteres del búfer hasta encontrar un salto de línea
        }
    }
}