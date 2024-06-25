#include<iostream>
#include<string.h>
#include <stdexcept>
#include "metodos.h"
using namespace std;




int main() {
	registro_cuentas r;
	cuenta c, c2, c3;
	c.rol = "11111111-1";
	c.nombre = "Juan";
	c.descripcion = "1era insercion";
	r.agregar(c);
	c2.rol = "11111111-2";
	c2.nombre = "Juana";
	c2.descripcion = "2da insercion";
	r.agregar(c2);
	r.estadisticas();
	c3.rol = "11111111-3";
	c3.nombre = "Juanes";
	c3.descripcion = "3era insercion";
	r.agregar(c3);
	r.estadisticas();
	
};
