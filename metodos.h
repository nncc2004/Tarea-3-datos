#ifndef metodos
#define metodos
#include<iostream>
#include<string.h>
using namespace std;

struct cuenta {
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
		} 
		cuenta obtener(string rol); 
		void agregar(cuenta c); // (listo)
		void eliminar(string rol); // (listo)
		void modificar(string rol, string descripcion); //(listo)
		void redimensionar(int n); //(listo)
		void estadisticas(); //(listo)
		
		int encontrarIndice(string rol); //(listo)

};



int registro_cuentas::hash(string rol){
	/*****
	* int hash
	******
	* Corresponde a la funcion de hash de la tabla de hash. Funciona sumando todos los dígitos anteriores al guión "-".
	* Luego suma el valor ASCII del último caracter, sea numerico o no. Por último hace mod con la cantidad de ranuras para
	* obtener un entero en el rango entre 0 y la cantidad de ranuras-1. 
	******
	* string rol: Recibe un string con el valor del rol que es la llave sobre la cual hacerle hash.
	******
	* Retorna el entero indice. Corresponde al entero resultante de la operacion anterior.
	*****/
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
	/*****
	* int p
	******
	* Es la lógica de resolución de colisiones. Se basa en sumarle +1 al indice ingresado para usar el sigueinte espacio disponible.
	* En caso de llegar al ultimo espacio del arreglo, se reinicia el contador a 0. 
	******
	* string rol: Recibe un string con el valor del rol (aunque con esta implementacion no se use, se optó por dejarlo como venía por defecto)
	* int i: Recibe un entero i que corresponde al indice en el que se encontó la colisión.
	******
	* Retorna el entero i que corresponde al numero modificado como descrito anteriormente.
	*****/
	if (i == ranuras-1){
		i = 0;
	}else{
		i++;
	}
	return i;
}
int registro_cuentas::encontrarIndice(string rol){
	/*****
	* int encontrarIndice
	******
	* Es la funcion encargada de encontrar el indice en el que se almacena el valor a partir del rol  (llave).
	* Funciona encontrando en un inicio el valor del indice original del rol con la funcion hash y a partir de ahí va recorriendo
	* las posiciones del arreglo con el salto indicado por la funcion p. Si se da una vuelta completa o encuentra un espacio al que nunca
	* Se le asignó un valor retorna -1 indicando que no se encuentra el rol en la tabla.
	******
	* string rol: Recibe un string con el valor del rol a buscar.
	******
	* Retorna el entero indice que corresponde a un -1 si no se encontró el rol o la posición en el arreglo en el que se encntró.
	*****/
	int indiceOriginal = hash(rol);
	int indice = indiceOriginal;
	while (tabla[indice].rol != rol){
		if(indice == indiceOriginal || tabla[indice].rol =="Nunca Usada"){
			return -1;
		}
		indice = p(rol, indice);
	}
	return indice;
}
void registro_cuentas::agregar(cuenta c){
	/*****
	* void agregar
	******
	* Es lla función encargada de agregar registros a la tabla. Lo primero que hace es obtener el rol del struc dado y obtener la posición 
	* correspondiende por medio de la funcion hash. Luego vreifica si es que hay colisión (Mientras el espacio no esté ni en liberada ni en nunca usada)
	* Mientras haya colisión llama a la función p para revisar el siguiente espacio disponible con el salto programado en p. Si en el intertanto se topa con
	* un registro con el mismo rol, lo imprime y detiene la función.
	* Cuando encuentra un espacio disponible, asigna los valores de rol, nombre y descripcion. 
	* Por último, actualiza la cantidad de espacios usados y verifica si hay usados mas de un 60% de la tabla por si hay que redimensionar (60% por lo visto en clases)
	* Si es así, llama a la funcion redimensionar. 
	******
	* cuenta c: es un struct cuenta con toda la informació a almacenar.
	******
	* tipo void. No hay retorno
	*****/
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
	/*****
	* cuenta obtener
	******
	* Usando la función encontrarIndice, encuentra el índice del rol dado. Si el retorno es -1 se imprime por pantalla que no se encontró el rol.
	* Si no es -1, se asigna el valor de la posición de la tabla a el struct de tipo cuenta c y se retorna.
	******
	* string rol: Recibe un strgin con el valor del rol a buscar
	******
	* Retorna el struc c de tipo cuenta con el valor encontrado. 
	*****/
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
	/*****
	* void eliminar
	******
	* Encunetra el índice con la funcion encontrarIndice y el rol asoicado al registro lo transforma en "Liberada" de forma que el espacio pueda ser reutilizado
	* Luego descuenta 1 de los espacios usados y actualiza el factor de carga. 
	* Si no se encontró el rol, se imprime el mensaje por pantalla. 
	******
	* string rol: Recibe un strgin con el valor del rol que se quiere eliminar
	******
	* Función tipo void. No hay retorno
	*****/
	int indice = encontrarIndice(rol);
	if(indice != -1){
		tabla[indice].rol = "Liberada";
		espUsados--;
		factor_de_carga = (float)espUsados/ranuras;
	}else{
		cout<<"Rol no existente\n";
	}
	
}
void registro_cuentas::modificar(string rol, string descripcion){
	/*****
	* void emodificar
	******
	* Encuentra el índice del rol con la funcion encontrarIndice y reemplaza el valor de la descripción con la pasada como parámetro
	* Si no se encontró el rol, se imprime el mensaje por pantalla. 
	******
	* string rol: Recibe un string con el valor del rol cuya descripción se quiere modificar
	******
	* Función tipo void. No hay retorno
	*****/
	int indice = encontrarIndice(rol);
	if(indice == -1){
		cout<<"Rol no existente\n";
		return;
	}
	tabla[indice].descripcion = descripcion;
	
}
void registro_cuentas::estadisticas(){
	/*****
	* void estadisticas
	******
	* imprime el valor de las ranuras usadas, las totales y el factor de carga. 
	******
	* No recibe parámetros
	******
	* Función tipo void. No hay retorno
	*****/
	cout<<"RANURAS USADAS: "<<espUsados<<"\n";
	cout<<"RANURAS TOTALES: "<<ranuras<<"\n";
	cout<<"FACTOR DE CARGA: "<<factor_de_carga<<"\n";
	
}

void registro_cuentas::redimensionar(int n){
	cuenta* tablaAUX = new cuenta[espUsados];
	
	int i =0;
	for(int x = 0; x<ranuras; x++){

		if(tabla[x].rol!="Nunca Usada" and tabla[x].rol !="Liberada"){
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
		agregar(tablaAUX[x]);
	}
	delete[] tablaAUX;	
}


#endif
