#include "mde.h"
#include "driver_boton.h"
#include "driver_medicion.h"
#include "driver_sensor.h"

typedef enum {PRESIONADO, SUELTO, LEIDO, MANTENIDO, DOBLECLICK}t_boton;
t_boton estado;

void InicializarMDE()
{
	estado = SUELTO;
	InicializarBoton();
}

int mdeBoton()
{
	switch (estado)
	{
	case PRESIONADO:
		if (FinishReding())
			estado = LEIDO;
		
		break;
	case SUELTO:
		if (Press())
		{
			StartReading();
			estado = PRESIONADO;
			if(Apagado())
				EncenderSensor();
			if (Encendido())
				EnviarMedicion(Medir());
		}
		else if (time() > 1)
		{
			StartReading();
			estado = MANTENIDO;
			if (Encendido())
			{
				do //tomo mediciones cada segundo hasta que se suelte el boton
				{
					EnviarMedicion(Medir());
					wait(1);
				} while (estado == MANTENIDO);
			}
		}
		else if (Press() == 2 && time() < 0.5)
		{
			StartReading();
			estado = DOBLECLICK;
			if (Encendido())
				ApagarSensor();
		}

		break;
	case LEIDO: //???
		wait(5); //espero 5 segundos
		break;
	case MANTENIDO:
		if (FinishReding())
			estado = LEIDO;
		break;
	case DOBLECLICK:
		if (FinishReding())
			estado = LEIDO;
		break;

	default:
		InicializarMDE();
		return 1;
	}
	return 0;
}