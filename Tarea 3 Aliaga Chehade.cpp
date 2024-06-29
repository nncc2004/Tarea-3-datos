#include<iostream>
#include<string.h>
#include <stdexcept>
#include "metodos.h"
#include<fstream>
using namespace std;


/*****
* int main
******
* La función crea un objeto registro_cuentas, lee el archivo .txt y segun lo que esté escrito
* llama al método que corresponda del TDA.
******
* No hay inputs
******
* Retorna el entero 0 como es costumbre en el main.
*****/

int main() {
	registro_cuentas r;
	ifstream archivo;
	string lineaActual;
	archivo.open("prueba.txt", ios::in);
	string rol, nombre, descripcion;
	cuenta c;
	while(archivo>>lineaActual){
		if (lineaActual=="AGREGAR"){
			archivo>>c.rol;
			archivo>>c.nombre;
			archivo>>c.descripcion;
			//Funcionamiento
			r.agregar(c);
		}else if(lineaActual=="QUITAR"){
			archivo>>c.rol;
			r.eliminar(c.rol);
		}else if(lineaActual=="MODIFICAR"){
			archivo>>c.rol;
			archivo>>c.descripcion;
			r.modificar(c.rol, c.descripcion);
		}else if(lineaActual=="OBTENER"){
			archivo>>c.rol;
			c = r.obtener(c.rol);
			if(c.rol!="NOVALIDO"){
				cout<<c.nombre<<" "<<c.descripcion<<"\n";
			};
			
		}else if(lineaActual=="ESTADISTICAS"){
			r.estadisticas();
		}
	}
	return 0;
};

