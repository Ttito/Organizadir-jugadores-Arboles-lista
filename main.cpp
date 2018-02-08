#include "clases.h"
#include <fstream>

class Selecciones {
public:

	Avl<int> ArbolNumero;
	Avl<string> ArbolApellido;
	Avl<string> ArbolPosicion;
	Avl<int> ArbolEdad;
	Avl<string> ArbolSeleccion;

	Lista <Jugador> Lista_de_Jugadores;

	bool Insertar(int i);
	bool CargarJugadores();
	bool Remover();
	void Mostrar_jugadores();
};

inline bool Selecciones::CargarJugadores() {
	fstream ficheroEntrada;
	int Numero, Edad, i, index;
	CNodoLista<Jugador> *p;
	string Apellido, Posicion, Seleccion, texto;
	string Datos[5];

	ficheroEntrada.open("datos.txt", ios::in);
	i = 0;
	index = 1;
	if (ficheroEntrada.is_open()) {
		while (!ficheroEntrada.eof()) {
			getline(ficheroEntrada, texto);
			if (texto != "\n" && texto != "") {
				Datos[i] = texto;
				i = i + 1;
			}
			if (i == 5) {
				Numero = atoi(Datos[0].c_str());
				Apellido = Datos[1];
				Posicion = Datos[2];
				Edad = atoi(Datos[3].c_str());
				Seleccion = Datos[4];
				Lista_de_Jugadores.add(index, Jugador(index, Numero, Apellido, Posicion, Edad, Seleccion), p);

				ArbolNumero.add(p->m_estructura.Numero, p);
				ArbolApellido.add(p->m_estructura.Apellido, p);
				ArbolPosicion.add(p->m_estructura.Posicion, p);
				ArbolEdad.add(p->m_estructura.Edad, p);
				ArbolSeleccion.add(p->m_estructura.Seleccion, p);
				i = 0;
				index = index + 1;
			}
		}
	}
	//ArbolNumero.print();
	return 1;
}

inline bool Selecciones::Insertar(int i) {
	int Numero, Edad;
	string Apellido, Posicion, Seleccion;

	CNodoLista<Jugador> *p;

	cout << "-------------------INGRESA UN NUEVO JUGADOR--------------------" << endl;
	cout << "Ingrese el Apellido del Jugador: ";
	cin >> Apellido;

	cout << "Ingrese el Numero del Jugador: ";
	cin >> Numero;

	cout << "Ingrese la Posicion del Jugador: ";
	cin >> Posicion;

	cout << "Ingrese la Edad del Jugador: ";
	cin >> Edad;

	cout << "Ingrese la Seleccion del Jugador: ";
	cin >> Seleccion;

	Lista_de_Jugadores.add(i, Jugador(i, Numero, Apellido, Posicion, Edad, Seleccion), p);

	ArbolNumero.add(p->m_estructura.Numero, p);
	ArbolApellido.add(p->m_estructura.Apellido, p);
	ArbolPosicion.add(p->m_estructura.Posicion, p);
	ArbolEdad.add(p->m_estructura.Edad, p);
	ArbolSeleccion.add(p->m_estructura.Seleccion, p);

	//ArbolNumero.root->vec[0]->m_estructura.MostrarJugador();
	//ArbolNumero.print();

	//p->m_estructura.MostrarJugador();

	system("PAUSE");
	system("cls");
	return 1;
}

inline bool Selecciones::Remover() {
	// 1 = Camiseta		2 = Apellido	3 = Posicion
	// 4 = Edad			5 = Seleccion


	cout << "Borrar por Numero Camiseta            : [1]" << endl;
	cout << "Borrar por Apellido                   : [2]" << endl;
	cout << "Borrar por Posicion en la que juegan  : [3]" << endl;
	cout << "Borrar por Edad                       : [4]" << endl;
	cout << "Borrar por Seleccion                  : [5]" << endl;

	int valor;
	cin >> valor;

	if (valor == 1) {
		int Numero;
		cout << "Ingrese Numero de Camiseta: ";
		cin >> Numero;

		Node<int>* n_vec;
		if (!ArbolNumero.get_vec(Numero, n_vec)) {
			system("PAUSE");
			system("cls");
			return false;
		}
		int tam_vec = n_vec->vec.size();
		for (int i = 0; i < tam_vec; i++) {

			ArbolApellido.remove_find(n_vec->vec[i]->m_estructura.Apellido, n_vec->vec[i]);
			ArbolPosicion.remove_find(n_vec->vec[i]->m_estructura.Posicion, n_vec->vec[i]);
			ArbolEdad.remove_find(n_vec->vec[i]->m_estructura.Edad, n_vec->vec[i]);
			ArbolSeleccion.remove_find(n_vec->vec[i]->m_estructura.Seleccion, n_vec->vec[i]);

			Lista_de_Jugadores.remove(n_vec->vec[i]->m_indice);
		}
		ArbolNumero.remove_node(Numero);
	}
	else if (valor == 2) {
		string Apellido;
		cout << "Ingrese Apellido: ";
		cin >> Apellido;


		Node<string>* n_vec;
		if (!ArbolApellido.get_vec(Apellido, n_vec)) {
			system("PAUSE");
			system("cls");
			return false;
		}
		int tam_vec = n_vec->vec.size();
		for (int i = 0; i < tam_vec; i++) {

			ArbolNumero.remove_find(n_vec->vec[i]->m_estructura.Numero, n_vec->vec[i]);
			ArbolPosicion.remove_find(n_vec->vec[i]->m_estructura.Posicion, n_vec->vec[i]);
			ArbolEdad.remove_find(n_vec->vec[i]->m_estructura.Edad, n_vec->vec[i]);
			ArbolSeleccion.remove_find(n_vec->vec[i]->m_estructura.Seleccion, n_vec->vec[i]);

			Lista_de_Jugadores.remove(n_vec->vec[i]->m_indice);

		}
		ArbolApellido.remove_node(Apellido);

	}
	else if (valor == 3) {
		string Posicion;
		cout << "Ingrese Posicion: ";
		cin >> Posicion;

		Node<string>* n_vec;
		if (!ArbolPosicion.get_vec(Posicion, n_vec)) {
			system("PAUSE");
			system("cls");
			return false;
		}
		int tam_vec = n_vec->vec.size();
		for (int i = 0; i < tam_vec; i++) {

			ArbolNumero.remove_find(n_vec->vec[i]->m_estructura.Numero, n_vec->vec[i]);
			ArbolApellido.remove_find(n_vec->vec[i]->m_estructura.Apellido, n_vec->vec[i]);
			ArbolEdad.remove_find(n_vec->vec[i]->m_estructura.Edad, n_vec->vec[i]);
			ArbolSeleccion.remove_find(n_vec->vec[i]->m_estructura.Seleccion, n_vec->vec[i]);

			Lista_de_Jugadores.remove(n_vec->vec[i]->m_indice);
		}
		ArbolPosicion.remove_node(Posicion);

	}
	else if (valor == 4) {
		int Edad;
		cout << "Ingrese Edad: ";
		cin >> Edad;

		Node<int>* n_vec;
		if (!ArbolEdad.get_vec(Edad, n_vec)) {
			system("PAUSE");
			system("cls");
			return false;
		}
		int tam_vec = n_vec->vec.size();
		for (int i = 0; i < tam_vec; i++) {

			ArbolNumero.remove_find(n_vec->vec[i]->m_estructura.Numero, n_vec->vec[i]);
			ArbolApellido.remove_find(n_vec->vec[i]->m_estructura.Apellido, n_vec->vec[i]);
			ArbolPosicion.remove_find(n_vec->vec[i]->m_estructura.Posicion, n_vec->vec[i]);
			ArbolSeleccion.remove_find(n_vec->vec[i]->m_estructura.Seleccion, n_vec->vec[i]);

			Lista_de_Jugadores.remove(n_vec->vec[i]->m_indice);
		}
		ArbolEdad.remove_node(Edad);
	}
	else if (valor == 5) {
		string Seleccion;
		cout << "Ingrese Seleccion: ";
		cin >> Seleccion;

		Node<string>* n_vec;
		if (!ArbolSeleccion.get_vec(Seleccion, n_vec)) {
			system("PAUSE");
			system("cls");
			return false;
		}
		int tam_vec = n_vec->vec.size();
		for (int i = 0; i < tam_vec; i++) {

			ArbolNumero.remove_find(n_vec->vec[i]->m_estructura.Numero, n_vec->vec[i]);
			ArbolApellido.remove_find(n_vec->vec[i]->m_estructura.Apellido, n_vec->vec[i]);
			ArbolPosicion.remove_find(n_vec->vec[i]->m_estructura.Posicion, n_vec->vec[i]);
			ArbolEdad.remove_find(n_vec->vec[i]->m_estructura.Edad, n_vec->vec[i]);

			Lista_de_Jugadores.remove(n_vec->vec[i]->m_indice);
		}
		ArbolSeleccion.remove_node(Seleccion);
	}

	system("PAUSE");
	system("cls");
	return true;
}

inline void Selecciones::Mostrar_jugadores() {
	if (Lista_de_Jugadores.m_head == NULL)
		cout << "No hay ni un Jugador Agregado" << endl;
	else
		Lista_de_Jugadores.print();
}

int main() {
	Selecciones S;
	int op, v = 0;
	int cont, n, i = 0;
	cout << "                     _________________________________________________               " << endl;
	cout << "                    |___________JUGADORES MUNDIAL RUSIA 2018__________|              " << endl;
	cout << "                    |_________________________________________________|              " << endl;

	while (1)
	{
		cout << " Cargar Datos de los jugadores [1]\n Insertar datos Manualmente    [2] \n Remover Jugadores             [3] \n Mostrar Jugadores             [4] \n Salir                         [0]" << endl;
		cin >> op;

		if (op == 1)
		{
			system("cls");
			if (v == 0)
			{
				S.CargarJugadores();
				v = 1;
			}
			else if (v == 1)
			{
				cout << "El Archivo ya esta cargado!!" << endl;
			}


		}
		else if (op == 2)
		{
			if (S.Lista_de_Jugadores.NumeroNodos == 0)
			{
				system("cls");
				S.Insertar(i);
			}
			i++;
			if (S.Lista_de_Jugadores.NumeroNodos != 1)
			{
				system("cls");
				S.Insertar(S.Lista_de_Jugadores.NumeroNodos + i);
			}
		}
		else if (op == 3)
		{
			system("cls");
			S.Remover();
		}
		else if (op == 4)
		{
			system("cls");
			int op1;
			cout << "Mostrar por Numero Camiseta            : [1]" << endl;
			cout << "Mostrar por Apellido                   : [2]" << endl;
			cout << "Mostrar por Posicion en la que juegan  : [3]" << endl;
			cout << "Mostrar por Edad                       : [4]" << endl;
			cout << "Mostrar por Rango de Edades            : [5]" << endl;
			cout << "Mostrar por Seleccion                  : [6]" << endl;
			cout << "Mostrar por Todos Los Jugadores        : [7]" << endl;
			cin >> op1;

			if (op1 == 1)
			{
				int C;
				system("cls");
				cout << "Ingrese el Numero de Camiseta: ";
				cin >> C;
				S.ArbolNumero.imprimirPorDato(C);
				system("PAUSE");
				system("cls");
			}
			else if (op1 == 2)
			{
				string Ap;
				system("cls");
				cout << "Ingrese el Apellido del Jugador: ";
				cin >> Ap;
				S.ArbolApellido.imprimirPorDato(Ap);
				system("PAUSE");
				system("cls");
			}
			else if (op1 == 3)
			{
				system("cls");
				string posJ;
				cout << "Ingrese la posicion del Jugador: ";
				cin >> posJ;
				S.ArbolPosicion.imprimirPorDato(posJ);
				system("PAUSE");
				system("cls");
			}
			else if (op1 == 4)
			{
				int edad;
				system("cls");
				cout << "Ingrese la edad del Jugador: ";
				cin >> edad;

				S.ArbolEdad.imprimirPorDato(edad);
				system("PAUSE");
				system("cls");
			}
			else if (op1 == 5)
			{
				int edad1, edad2;
				system("cls");
				cout << "Ingrese la Rango de Edad MENOR: ";
				cin >> edad1;
				cout << "Ingrese la Rango de Edad MAYOR: ";
				cin >> edad2;
				if (edad1 <= edad2) {
					while (edad1 <= edad2) {
						cout << "Jugadores con " << edad1 << " de edad" << endl;
						S.ArbolEdad.imprimirPorDato(edad1);
						cout << endl;
						edad1++;
					}
				}
				else	cout << "Ingreso mal el rango" << endl;
				system("PAUSE");
				system("cls");
			}
			else if (op1 == 6)
			{
				string Se;
				system("cls");
				cout << "Ingrese la Seleccion del Jugador: ";
				cin >> Se;
				S.ArbolSeleccion.imprimirPorDato(Se);
				system("PAUSE");
				system("cls");
			}
			else if (op1 == 7)
			{
				S.Mostrar_jugadores();
				system("PAUSE");
				system("cls");
			}

		}
		else if (op == 0)
		{
			break;
		}
	}
	return 0;
}

