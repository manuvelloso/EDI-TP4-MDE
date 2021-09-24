#include <stdint.h>
#include <stdbool.h>

void InicializarBoton();
int8_t Press(); //devuelve cuantas veces fue presionado
int StartReading(); //empieza a leer
bool FinishReding(); //pregunta si termino de leer
float time(); //devuelve el tiempo en segundos