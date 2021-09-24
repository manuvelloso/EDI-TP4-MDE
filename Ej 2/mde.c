#include "mde.h"
#include "driver_Motor.h"
#include "driver_Sensor.h"
#include "driver_Boton.h"
#include "driver_Porton.h"

void InicializarMDEPorton()
{
	estado = CERRADO;
	InicializarPorton(); //lo inicializa
	ManejoMotor(HORARIO); //lo cierra
}

int32_t mdePorton()
{
	switch (estado)
	{
	case ABIERTO:
		if (DetectarTecla()) //si se presionó el boton
		{
			ManejoMotor(HORARIO); //arranca el mecanismo
			estado = CERRANDO; //el porton se esta cerrando
		}
		break;
	case ABRIENDO:
		if (DetectorAbierto()) //si el sensor detecto que la puerta se esta abriendo
		{
			estado = ABIERTO;
		}
		break;
	case CERRADO:
		if (DetectarTecla()) //si se presionó el boton
		{
			ManejoMotor(ANTIHORARIO); //arranca el mecanismo
			estado = ABRIENDO; //el porton se esta cerrando
		}
		break;
	case CERRANDO:
		if (DetectorCerrado()) //si el sensor detecto que la puerta se esta abriendo
		{
			estado = CERRADO;
		}
		break;

	default:
		InicializarMDEPorton();
		return 1;
	}
	return 0;
}