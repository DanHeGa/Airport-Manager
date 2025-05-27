#include <iostream>
#include <vector>
using namespace std;

class Slot{
  private:
    int numero;
    float entrada;
    float salida;
  public:
    Slot();
    Slot(int numero, float entrada, float salida);
    int getNumero();
    float getEntrada();
    float getSalida();
    void setNumero(int);
    void setEntrada(float);
    void setSalida(float);
};

class Avion{
  private:
    string matricula;
    string aerolinea;
    string modelo;
    Slot espacio;

  public:
    Avion();
    Avion(string matricula, string aerolinea, string modelo, Slot espacio);
    string getMatricula();
    string getAerolinea();
    string getModelo();
    Slot getEspacio();
    void setMatricula(string);
    void setAerolinea(string);
    void setModelo(string);
    void setEspacio(Slot);
};

//CLASE SLOT
//constructor
Slot::Slot(int _numero, float _entrada, float _salida){
  numero = _numero;
  entrada = _entrada;
  salida = _salida;
}
//constructor default
Slot::Slot(){
  numero = 0;
  entrada = 0;
  salida = 0;
}
//getters 
int Slot::getNumero(){
  return numero;
}
float Slot::getEntrada(){
  return entrada;
}
float Slot::getSalida(){
  return salida;
}
//setters
void Slot::setNumero(int nuevo_num){
  numero = nuevo_num;
}
void Slot::setEntrada(float nuevo_ent){
  entrada = nuevo_ent;
}
void Slot::setSalida(float nuevo_sal){
  salida = nuevo_sal;
}
//CLASE AVIÓN
//constructor
Avion::Avion(string _matricula, string _aerolinea, string _modelo, Slot _espacio){
  matricula = _matricula;
  aerolinea = _aerolinea;
  modelo = _modelo;
  espacio = _espacio;
}
//constructor default
Avion::Avion(){
  matricula = " ";
  modelo = " ";
  aerolinea = " ";
  espacio = Slot();
}
//getters
string Avion::getMatricula(){
  return matricula;
}
string Avion::getAerolinea(){
  return aerolinea;
}
string Avion::getModelo(){
  return modelo;
}
Slot Avion::getEspacio(){
  return espacio;
}
//setters
void Avion::setMatricula(string nueva_matricula){
  matricula = nueva_matricula;
}
void Avion::setAerolinea(string nuevo_aerolinea){
  aerolinea = nuevo_aerolinea;
}
void Avion::setModelo(string nuevo_modelo){
  modelo = nuevo_modelo;
}
void Avion::setEspacio(Slot nuevoEspacio){
  espacio = nuevoEspacio;
}

//función que se usa dentro de la función "agregarSlots"
//función para ver si la entrada agregada es valida
bool verificar_slot(float agre_entrada, vector<Slot>& _lista_de_slots){
	bool horario_valido = true;
	for(int i=0;i<_lista_de_slots.size();i++){
		//en c++, if no tiene que tener else obligatoriamente
		if(_lista_de_slots[i].getEntrada() == agre_entrada){
			horario_valido = false;
		}
	}
	return horario_valido;
}
//función para ver si la salida agregada es valida
bool verificar_slot_salida(float _agre_salida, vector<Slot>& _lista_de_slots){
	bool horario_valido = true;
	for(int i=0;i<_lista_de_slots.size();i++){
		if(_lista_de_slots[i].getSalida() == _agre_salida){
			horario_valido = false;
		}
	}
	return horario_valido;
}

//FUNCIONES DEL MAIN
//se usa la dirección de memoria del vector con la lista de slots, para poder modificarla fuera de la función
//eso se hace con el signo &
//función que agrega slots al vector de objetos slot
void agregarSlots(vector<Slot>& _lista_de_slots){
  int agre_numero, seguir;
  float agre_entrada, agre_salida;
  Slot espacio_deseado;
  if (_lista_de_slots.size() >= 488){
    cout<<"No hay espacio para agregar mas slots"<<endl;
  }else{
  do{
    cout<<"Numero de slot a ocupar: "<<endl;
    cin>>agre_numero;
    cout<<"Hora de entrada: "<<endl;
    cin>>agre_entrada;
    if ((agre_entrada > 7 && agre_entrada < 23) || not verificar_slot(agre_entrada, _lista_de_slots)){
    	cout<<"Horario invalido"<<endl;
    	cout<<"Solo hay disponibilidad de registro en el horario de 23:00 a 7:00"<<endl;
	}else{
			cout<<"Hora de salida: "<<endl;
    		cin>>agre_salida;		
			if ((agre_salida > 7 && agre_salida < 23) || not verificar_slot_salida(agre_salida,_lista_de_slots)){
				cout<<"Horario invalido"<<endl;
    			cout<<"Solo hay disponibilidad de registro en el horario de 23:00 a 7:00"<<endl;
			}else{
				//funcion para verificar si no esta ocupada la hr salida
    			espacio_deseado = Slot(agre_numero, agre_entrada, agre_salida);
    			//agrega el slot al vector
    			_lista_de_slots.push_back(espacio_deseado);	
			}
			
	}		
   	cout<<"desea agregar otro slot? 1.si 2.no"<<endl;
    cin>>seguir;
    } while(seguir == 1);
  }
}

//función para mostrar en pantalla los objetos del vector de slots
void espacios_disponibles(vector<Slot>& _lista_de_slots){
	if(_lista_de_slots.size()<=0){
		cout<<"No hay slots registrados, favor de ingresar al apartado 'Agregar Slots' en el menu principal"<<endl;
		system("pause");
	} else{
		for(int i=0; i<_lista_de_slots.size();i++){
			cout<<"\nNumero de Slot: "<<_lista_de_slots[i].getNumero()<<endl;
			cout<<"Hora de Entrada: "<<_lista_de_slots[i].getEntrada()<<" hrs"<<endl;
			cout<<"Hora de Salida: "<<_lista_de_slots[i].getSalida()<<" hrs"<<endl;
		}
	//evita que muestre los cout's durante milisegundos y los deja visibles hasta que se especifique
		system("pause");
	}
	
}

//función para eliminar elementos del vector de slots
void eliminaSlot(vector<Slot>& _lista_de_slots){
	int elim_num;
	float elim_entrada;
	if(_lista_de_slots.size()<=0){
		cout<<"No hay slots registrados, favor de ingresar al apartado 'Agregar Slots' en el menu principal"<<endl;
		system("pause");
	}else{
		cout<<"Introduzca los siguientes datos para eliminar un slot"<<endl;
		cout<<"ADVERTENCIA La eliminacion de un slot es permanente"<<endl;
		cout<<"En caso de querer volver a registrarlo, se requerira hacerlo a traves del menu principal"<<endl;
		cout<<"\nNumero de slot: "<<endl;
		cin>>elim_num;
		cout<<"Horario de entrada: "<<endl;
		cin>>elim_entrada;
		for(int i=0; i<_lista_de_slots.size();i++){
			if (_lista_de_slots[i].getNumero() == elim_num && _lista_de_slots[i].getEntrada() == elim_entrada){
				cout<<"El slot num "<<_lista_de_slots[i].getNumero()<<" con horario de "<<_lista_de_slots[i].getEntrada()<<" - "<<_lista_de_slots[i].getSalida()<<endl;
				cout<<"Ha sido eliminado"<<endl;
				_lista_de_slots.erase(_lista_de_slots.begin() + i);
				system("pause");
				break;
			}	
		}
	}

	
}
//función para crear objetos de tipo avión y guardarlos en un vector
void registrarVuelo(vector<Slot>& _lista_de_slots, vector<Avion>& _lista_de_aviones){
	string matri_reg, aero_reg, mode_reg;
	int numSlotAvion;
	float entryAvion, outAvion;
	Slot slotApartado;
	bool slotExiste = false;
	system("cls");
	cout<<"Favor de consultar los slots disponibles antes de registrar un vuelo"<<endl;
	cout<<"Introduzca los siguientes datos con relación a la aeronave que desea registrar"<<endl;
	cout<<"Matricula: "<<endl;
	cin>>matri_reg;
	cout<<"Aerolinea: "<<endl;
	cin>>aero_reg;
	cout<<"Modelo: "<<endl;
	cin>>mode_reg;
	cout<<"Numero de slot a ocupar: "<<endl;
	cin>>numSlotAvion;
	cout<<"Hora de entrada: "<<endl;
	cin>>entryAvion;
	cout<<"Hora de salida: "<<endl;
	cin>>outAvion;
	system("cls");
	//verifica que la lista de slots no este vacia
	if (_lista_de_slots.size() <= 0){
		cout<<"No hay slots registrados o disponibles por el momento"<<endl;
		cout<<"Puede registrar un nuevo slot desde el menu principal"<<endl;
		cout<<"a traves del apartado 'Agregar slots'"<<endl;
		system("pause");
} else {
	//se asegura que no este la capacidad llena, considerando operaciones por noche.
	if(_lista_de_aviones.size() >= 488){
		cout<<"El máximo de aviones registrados ha sido rebasado"<<endl;
		system("pause");
	}else{
		for(int i=0; i<_lista_de_slots.size(); i++){
		if(numSlotAvion == _lista_de_slots[i].getNumero() && entryAvion == _lista_de_slots[i].getEntrada() && outAvion == _lista_de_slots[i].getSalida()){
			//indicamos al usuario que el slot esta disponible
			cout<<"Slot dispoible"<<endl;
			slotApartado = Slot(numSlotAvion, entryAvion, outAvion);
			Avion nuevoAvion(matri_reg, aero_reg, mode_reg, slotApartado);
			_lista_de_slots.erase(_lista_de_slots.begin() + i);
			_lista_de_aviones.push_back(nuevoAvion);
			cout<<"El avion "<<matri_reg<<" modelo "<<mode_reg<<" de "<<aero_reg<<endl;
			cout<<"Se ha registrado exitosamente en el slot seleccionado"<<endl;
			cout<<"Puede consultar la aeronave ingresada atravez del apartado 'Consulta de vuelos' en el menu principal"<<endl;
			system("pause");
			slotExiste = true;
			break;
		}
	}	
	}

	if (slotExiste = false){
		cout<<"Slot NO disponible"<<endl;
		cout<<"Favor de consultar los disponibilidad desde el menu principal"<<endl;
		cout<<"A traves del apartado 'Consultar slots'"<<endl;
	}
}

}

//Función que imprime en pantalla los elemntos de los objetos tipo avión del vector de aviones.
void consultaVuelos(vector<Avion>& _lista_de_aviones){
	if(_lista_de_aviones.size()<=0){
		cout<<"No hay aviones registrados, favor de dirigirse al apartado 'Registrar un vuelo' en el menu"<<endl;
		system("pause");
	} else{
		for(int i = 0; i < _lista_de_aviones.size(); i++){
			cout<<"Vuelos Registrados"<<endl;
			cout<<"\nMatricula: "<<_lista_de_aviones[i].getMatricula()<<endl;
			cout<<"Modelo: "<<_lista_de_aviones[i].getModelo()<<endl;
			cout<<"Aerolinea: "<<_lista_de_aviones[i].getAerolinea()<<endl;
			cout<<"Tiempo reservado: "<<_lista_de_aviones[i].getEspacio().getEntrada()<<" - "<<_lista_de_aviones[i].getEspacio().getSalida()<<endl;
		}
		system("pause");
	}

}
int main() {
  int opcion;
  vector<Slot> lista_de_slots;//almacenamiento de los slots disponibles
  vector<Avion> lista_de_aviones;//almacenamiento de aviones registrados
  system("Title Administración del AICM");
  do{
    system("cls");
    cout<<"---------Menu---------"<<endl;
    cout<<"1. Agregar slots"<<endl;
    cout<<"2. Consultar slots"<<endl;
    cout<<"3. Registrar un vuelo"<<endl;
    cout<<"4. Consultar vuelos"<<endl;
    cout<<"5. Borrar slot"<<endl;
    cout<<"6. Salir"<<endl;
    cout<<"----------------------"<<endl;
    cout<<"Ingrese una opcion: "<<endl;
    cin>>opcion;
    system("cls");
    switch(opcion){
      case 1:
        cout<<"Agregando slots"<<endl;
        agregarSlots(lista_de_slots);
        break;
      case 2:
        cout<<"Consulta de slots"<<endl;
        espacios_disponibles(lista_de_slots);
        break;
      case 3:
        cout<<"Registrando vuelo"<<endl;
        registrarVuelo(lista_de_slots,lista_de_aviones);
        break;
      case 4:
        cout<<"Consulta de vuelos"<<endl;
       	consultaVuelos(lista_de_aviones);//función que itera en el vector de objetos tipo "Avión" y los muestra en pantalla
        break;
      case 5:
      	cout<<"Eliminacion de slot"<<endl;
      	eliminaSlot(lista_de_slots);
      	break;
      case 6: 
    	cout<<"Gracias por usar el servicio administrativo del Aeropuerto Internacional de la Ciudad de Mexico"<<endl;
        cout<<"Saliendo del programa..."<<endl;
        break;
      default:
        cout<<"Opcion invalida"<<endl;
    } 
  }while (opcion != 6);
  return 0; 
}
