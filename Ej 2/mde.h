#pragma once
#include <stdint.h>

typedef enum { ABIERTO, ABRIENDO, CERRADO, CERRANDO } eEstado;

eEstado estado;

void InicializarMDEPorton();

int32_t mdePorton();