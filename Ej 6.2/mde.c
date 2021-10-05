
#include "mde.h"
#include "driver_boton.h"
typedef enum {APAGADO, ENCENDIDO, MIDIENDO, MEDICION_C} eEstado;

eEstado state; 

void Inicializar()
{
	state = APAGADO;
	InicializarBoton();
}

int mde()
{
	switch (state)
	{
	case APAGADO:
		if (press())
			state = ENCENDIDO;
		break;

	case ENCENDIDO:
		if (press())
			state = MIDIENDO;
		if (doble_click())
			state = APAGADO;
		if (mantenido())
			state = MEDICION_C;
		break;

	case MIDIENDO:
		if (suelto())
			state = ENCENDIDO;
		break;

	case MEDICION_C:
		if (suelto())
			state = ENCENDIDO;
		break;

	default: 
		Inicializar();
		return 1;
		break;
	}
	return 0;
}