//#define ESTADO_A
//#define ESTADO_B
//#define ESTADO_C

#include "driver_alarma.h"
#include "driver_luz.h"
#include "driver_sensor.h"

typedef enum { ESTADO_A, ESTADO_B, ESTADO_C } estado_t;

estado_t var_de_estado = ESTADO_A; //solo para la primera vez

//si la variable de estado la puede ver cualquiera -> observable (util para el testing)
// para cuidar el programa, es mejor que solo lo vea fsm porque sino se puede romper
//Finite State Machine
/*
	CAPAS
	1. fsm - app
	2. drivers - caja con funciones
	3. hal
*/

int inicializar_fsm()
{
	var_de_estado = ESTADO_A; //asignación dentro de función
	return 0;
}

int fsm()
{
	switch (var_de_estado)
	{
	case ESTADO_A:
		if (Estado_Sensor()) //eventos en if's
		{
			Apagar_Alarma(); //si el evento ocurrio, apago la alarma
			var_de_estado = ESTADO_B; //transición
		}
		else if (!Estado_Sensor) //si no esta activo, me quedo en A
			var_de_estado = ESTADO_A;
		break;

	case ESTADO_B:
		if (!Estado_Sensor())
		{
			Encender_Alarma();
			var_de_estado = ESTADO_A;
		}
		else if (Medicion_Sensor() < 100)
		{
			Apagar_Luz(ROJO);
			Encender_Luz(VERDE);

			var_de_estado = ESTADO_B;
		}
		else if (Medicion_Sensor() >= 100)
		{
			Apagar_Luz(VERDE);
			Encender_Luz(ROJO);

			var_de_estado = ESTADO_C;
		}
		break; 


	case ESTADO_C:
		if (Medicion_Sensor() < 100)
		{
			Apagar_Luz(ROJO);
			Encender_Luz(VERDE);
			var_de_estado = ESTADO_B;
		}
		else if (Estado_Sensor())
		{
			Encender_Alarma();
			var_de_estado = ESTADO_A;
		}
		else if (Medicion_Sensor() >= 100)
		{
			Apagar_Luz(VERDE);
			Encender_Luz(ROJO);
			var_de_estado = ESTADO_C;
		}
		break;

	default:
		inicializar_fsm(); //si hubo un error reinicializo
		return 1; //devuelvo 1 por que algo falló
	}
	return 0; //si funcó
}