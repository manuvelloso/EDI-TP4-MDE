#pragma once
class cFSM
{
private:
	enum class eEstados{
		ESTADO_A,
		ESTADO_B,
		ESTADO_C
	};
	eEstados var_de_estado;

public:
	cFSM() { inicializar(); }
	~cFSM() {};

	int inicializar() { var_de_estado = eEstados::ESTADO_A; }
	int mde() {}
};

/*
EN MAIN...

{
	cFSM fsm1; //si creamos más de un objeto, todos terminan apuntando a los mismos drivers
	la maquina envés de llamar a drivers, tiene punteros a funciones
	Cuando inicializo le tengo que indicar con que fucnion en particular trabajar
	COn esto puedo crear la cantidad de objetos que quiera pero le tengo que pasar con que funciones debe trabajar
}
*/