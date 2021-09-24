#include "fsm.h"

int main() {
	
	inicializar_fsm(); 
	//puedo llamar a muchas maquinas de estado

	while (1) //bucle infinito -> superloop (nunca sale)
	{
		fsm();
	}
	return 0;
}