#ifndef metodos
#define metodos
#include<iostream>
#include<string.h>
using namespace std;

struct cuenta {
	// El rol es el identificador de la persona.
	// El nombre y la descripcion son valores asociados al rol
	string rol, nombre, descripcion;
};
class registro_cuentas {
	private:
		float factor_de_carga = 0.0; 
		cuenta* tabla; 
		int ranuras = 15; 
		int hash(string rol); 
		int p(string rol, int i);
		int espUsados = 0;
	public:
		registro_cuentas() {
			tabla = new cuenta[ranuras];
    		for (int i = 0; i < ranuras; i++) {
        		tabla[i].rol = "Nunca Usada";
    		}
		} // (Recuerde que puede crear con distintos parametros)
		cuenta obtener(string rol); 
		void agregar(cuenta c); // (listo)
		void eliminar(string rol); // (listo)
		void modificar(string rol, string descripcion); //(listo)
		void redimensionar(int n); //(listo)
		void estadisticas(); //(listo)
		
		int encontrarIndice(string rol); //(listo)

};



int registro_cuentas::hash(string rol){
	string recorte = "";
	int indice;
	for (int x = 0; x<rol.length()-2;x++){
		recorte+=rol[x];
	}
	indice = stoi(recorte)+rol[rol.length()-1];
	indice %=ranuras;
	return indice;
}
int registro_cuentas::p(string rol, int i){
	if (i == ranuras-1){
		i = 0;
	}else{
		i++;
	}
	return i;
}

void registro_cuentas::agregar(cuenta c){
	int indice = hash(c.rol);
	while (tabla[indice].rol != "Nunca Usada" and tabla[indice].rol != "Liberada"){
		if(tabla[indice].rol == c.rol){
			cout<<"Rol ya existente \n";
			return;
		}
		indice = p(c.rol, indice);
	}
	tabla[indice] = c;
	
	//Logica posterior
	espUsados++;
	factor_de_carga = (float)espUsados/ranuras;
	
	if(factor_de_carga>=0.6){
		cout<<"Redimensionar!! Pendiente\n";
		int n = ranuras + 15;
		redimensionar(n);
	}
}

cuenta registro_cuentas::obtener(string rol){
	cuenta c;
	c.rol = "NOVALIDO";
	int indice = encontrarIndice(rol);
	if(indice == -1){
		cout<<"Rol no existente\n";
		return c;
	}
	c = tabla[indice];
	return c;
}

void registro_cuentas::eliminar(string rol){
	int indice = encontrarIndice(rol);
	if(indice != -1){
		tabla[indice].rol = "Liberada";
		espUsados--;
		factor_de_carga = (float)espUsados/ranuras;
	}else{
		cout<<"Rol no existente\n";
	}
	
}

int registro_cuentas::encontrarIndice(string rol){
	int indiceOriginal = hash(rol);
	int indice = indiceOriginal;
	while (tabla[indice].rol != rol){
		if(indice == indiceOriginal || tabla[indice].rol =="Nunca Usada"){
			//cout<<"Rol ya existente\n";
			return -1;
				
		}
		indice = p(rol, indice);
	}
	return indice;
}

void registro_cuentas::modificar(string rol, string descripcion){
	int indice = encontrarIndice(rol);
	if(indice == -1){
		cout<<"Rol no existente\n";
		return;
	}
	tabla[indice].descripcion = descripcion;
	
}

void registro_cuentas::estadisticas(){
	cout<<"RANURAS USADAS: "<<espUsados<<"\n";
	cout<<"RANURAS TOTALES: "<<ranuras<<"\n";
	cout<<"FACTOR DE CARGA: "<<factor_de_carga<<"\n";
	
}

void registro_cuentas::redimensionar(int n){
	cuenta* tablaAUX = new cuenta[espUsados];
	
	int i =0;
	for(int x = 0; x<ranuras; x++){

		if(tabla[x].rol!="Nunca Usada" and tabla[x].rol !="Liberada"){
			//cout<<tabla[x].nombre<<"\n";
			tablaAUX[i] = tabla[x];
			i++;	
		}
	}
	ranuras = n;
	espUsados =0;
	delete[] tabla;
	tabla = new cuenta[ranuras];
		for (int j = 0; j < ranuras; j++) {
    		tabla[j].rol = "Nunca Usada";
		}
		
	for(int x = 0; x<i; x++){
		//cout<<tablaAUX[x].nombre<<"\n";
		agregar(tablaAUX[x]);
	}
	delete[] tablaAUX;	
}


#endif
