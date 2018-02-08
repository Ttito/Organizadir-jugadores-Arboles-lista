#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;


// CLASE JUGADOR
class Jugador {
public:
	int index;
	int Numero;
	string Apellido;
	string Posicion;
	int Edad;
	string Seleccion;
	Jugador() {}
	Jugador(int i, int N, string A, string P, int E, string S) {
		index = i;
		Numero = N;
		Apellido = A;
		Posicion = P;
		Edad = E;
		Seleccion = S;
	}

	void MostrarJugador() {
		cout << "Camiseta: " << Numero << " || ";
		cout << "Apellido: " << Apellido << " || ";
		cout << "Posicion: " << Posicion << " || ";
		cout << "Edad: " << Edad << " || ";
		cout << "Seleccion: " << Seleccion << "  ";
		cout << endl;
	}
};

// CLASE LISTA
template <class T>
class CNodoLista {
public:
	int m_indice;
	T m_estructura;

	CNodoLista<T> *next;
	CNodoLista(int data, T E) {
		m_indice = data;
		m_estructura = E;
	}
};

template <class T>
class Lista {
public:
	CNodoLista<T> *m_head;
	int NumeroNodos;
	Lista() { m_head = NULL; NumeroNodos = 0; }
	~Lista() { while (m_head)	remove(m_head->m_indice); }
	bool find(int dato, CNodoLista<T> **&p);
	bool add(int, T, CNodoLista<T> *&pos);
	bool remove(int dato);
	void print();
};

template <class T>
bool Lista<T>::find(int dato, CNodoLista<T> **&p) {
	for (p = &m_head; *p && (*p)->m_indice < dato; p = &((*p)->next));
	return (*p) && (*p)->m_indice == dato;
}
template <class T>
bool Lista<T>::add(int i, T E, CNodoLista<T> *&pos) {
	CNodoLista<T> **p;
	if (find(i, p)) return 0;
	CNodoLista<T> *temp = new CNodoLista<T>(i, E);
	pos = temp;
	temp->next = *p;
	*p = temp;
	//NoBorrar;
	NumeroNodos++;
	return 1;
}
template <class T>
bool Lista<T>::remove(int dato) {
	CNodoLista<T> **p;
	if (!find(dato, p)) return 0;
	CNodoLista<T> *temp = (*p);
	*p = (*p)->next;
	delete temp;
	return 1;
}
template <class T>
void Lista<T>::print() {
	for (CNodoLista<T> **p = &m_head; *p; p = &((*p)->next)) {
		cout << "Camiseta: " << (*p)->m_estructura.Numero << " || ";
		cout << "Apellido: " << (*p)->m_estructura.Apellido << " || ";
		cout << "Posicion: " << (*p)->m_estructura.Posicion << " || ";
		cout << "Edad: " << (*p)->m_estructura.Edad << " || ";
		cout << "Seleccion: " << (*p)->m_estructura.Seleccion << "  ";
		cout << endl;
	}
	cout << std::endl;
}

// CLASE AVL
template <class T>
class Node {
public:
	T dato;
	Node<T>* b_nodes[2];

	// Puntero a Jugador
	vector<CNodoLista<Jugador>*> vec;

	int height;
	int balance;
	Node(T _dato) { dato = _dato; b_nodes[0] = b_nodes[1] = NULL; height = 0; }
};

template <class T>
class Avl {
public:
	Node<T>* root;
	std::vector<Node<T>*> elements;

	void OH(Node<T> *p);
	void add_heights();
	bool v_b(Node<T>* &p);
	void InOrder(Node<T> *p);
	void pr(Node<T>* a, int n);
	void balancear();

	Avl() { root = NULL; }
	bool find(T dato, Node<T> **&p);
	bool add(T dato, CNodoLista<Jugador>* j);

	bool get_vec(T dato, Node<T>*& n_vec);

	bool remove_find(T dato, CNodoLista<Jugador>* j);
	bool remove_node(T dato);
	void print();

	bool imprimirPorDato(T);
};

template<class T>
inline bool Avl<T>::find(T dato, Node<T>**& p) {
	for (p = &root; *p && (*p)->dato != dato; p = &(*p)->b_nodes[(*p)->dato < dato]);
	return !!*p;
}

template<class T>
bool Avl<T>::imprimirPorDato(T dato) {
	Node<T> **p;

	if (!find(dato, p)) {
		cout << "No hay jugadores con este dato (" << dato << ")" <<endl;
		return 0;
	}
	for (int i = 0; i<(*p)->vec.size(); i++) {
		(*p)->vec[i]->m_estructura.MostrarJugador();
	}
	return 1;
}

template<class T>
inline bool Avl<T>::add(T dato, CNodoLista<Jugador>* j) {
	Node<T> **p;
	if (find(dato, p)) {
		(*p)->vec.push_back(j);
		return 1;
	};
	Node<T>* temp = new Node<T>(dato);
	temp->vec.push_back(j);
	(*p) = temp;
	balancear();
	return 1;
}


template<class T>
bool Avl<T>::get_vec(T dato, Node<T>*& n_vec) {
	Node<T> ** p;
	if (!find(dato, p)) return false;
	n_vec = (*p);
	return true;
}


template<class T>
inline bool Avl<T>::remove_find(T dato, CNodoLista<Jugador>* j) {
	Node<T> ** p, ** q;
	if (!find(dato, p)) return 0;

	if ((*p)->vec.size() > 1) {
		int tam_vec = (*p)->vec.size();
		int i;
		for (i = 0; i < tam_vec && (*p)->vec[i] != j; i++);
		(*p)->vec.erase((*p)->vec.begin() + i);
		return 1;
	}

	if ((*p)->b_nodes[0] && (*p)->b_nodes[1]) {
		if ((*p)->b_nodes[0])
			for (q = &(*p)->b_nodes[0]; (*q)->b_nodes[1]; q = &(*q)->b_nodes[1]);
		else
			for (q = &(*p)->b_nodes[1]; (*q)->b_nodes[0]; q = &(*q)->b_nodes[0]);
		(*p)->dato = (*q)->dato;
		p = q;
	}
	Node<T> *t = *p;
	(*p) = (*p)->b_nodes[(*p)->b_nodes[1] != 0];
	balancear();
	delete t;
	return 1;
}

template<class T>
inline bool Avl<T>::remove_node(T dato) {
	Node<T> ** p, ** q;
	if (!find(dato, p)) return 0;
	if ((*p)->b_nodes[0] && (*p)->b_nodes[1]) {
		if ((*p)->b_nodes[0])
			for (q = &(*p)->b_nodes[0]; (*q)->b_nodes[1]; q = &(*q)->b_nodes[1]);
		else
			for (q = &(*p)->b_nodes[1]; (*q)->b_nodes[0]; q = &(*q)->b_nodes[0]);
		(*p)->dato = (*q)->dato;
		p = q;
	}
	Node<T> *t = *p;
	(*p) = (*p)->b_nodes[(*p)->b_nodes[1] != 0];
	balancear();
	delete t;
	return 1;
}


template<class T>
inline void Avl<T>::OH(Node<T>* p) {
	if (!p)	return;
	OH(p->b_nodes[0]);
	elements.push_back(p);
	OH(p->b_nodes[1]);
}

template<class T>
inline void Avl<T>::add_heights() {
	OH(root);
	int tam_elements = elements.size();
	for (int i = 0; i < tam_elements; i++)
		elements[i]->height = 0;
	while (tam_elements > 0) {
		tam_elements = elements.size();
		for (int i = tam_elements - 1; i > -1; i--) {

			if (!elements[i]->b_nodes[0] && !elements[i]->b_nodes[1]) {
				elements[i]->height = 1;
				elements[i]->balance = 0;
			}
			else if (!elements[i]->b_nodes[0] && elements[i]->b_nodes[1] && elements[i]->b_nodes[1]->height) {
				elements[i]->height = elements[i]->b_nodes[1]->height + 1;
				elements[i]->balance = 0 - elements[i]->b_nodes[1]->height;
			}
			else if (!elements[i]->b_nodes[1] && elements[i]->b_nodes[0] && elements[i]->b_nodes[0]->height) {
				elements[i]->height = elements[i]->b_nodes[0]->height + 1;
				elements[i]->balance = elements[i]->b_nodes[0]->height;
			}
			else if (elements[i]->b_nodes[0] && elements[i]->b_nodes
				[1] && elements[i]->b_nodes[0]->height && elements[i]->b_nodes[1]->height) {
				if (elements[i]->b_nodes[0]->height > elements[i]->b_nodes[1]->height)
					elements[i]->height = elements[i]->b_nodes[0]->height + 1;
				else
					elements[i]->height = elements[i]->b_nodes[1]->height + 1;
				elements[i]->balance = elements[i]->b_nodes[0]->height - elements[i]->b_nodes[1]->height;
			}
			if (elements[i]->height != 0) elements.erase(elements.begin() + i);
		}
	}
	OH(root);
}

template<class T>
inline bool Avl<T>::v_b(Node<T>* &p) {
	int tam_elements = elements.size();
	vector<Node<T>*> menores;
	for (int i = tam_elements - 1; i > -1; i--) {
		if (elements[i]->balance > 1 || elements[i]->balance < -1)  menores.push_back(elements[i]);
	}
	if (menores.size() == 0)	return false;
	int tam_menores = menores.size();
	p = menores[0];
	for (int i = 0; i < tam_menores; i++) {
		if (p->height > menores[i]->height)
			p = menores[i];
	}
	return true;
}

template<class T>
inline void Avl<T>::balancear() {

	add_heights();
	int tam_elements = elements.size();
	Node<T>* t;
	while (v_b(t)) {
		Node<T>** x;
		find(t->dato, x);
		if (!(*x)->b_nodes[0]) {
			if (!(*x)->b_nodes[1]->b_nodes[0]) {
				(*x)->b_nodes[1]->b_nodes[0] = (*x);
				(*x) = (*x)->b_nodes[1];
				(*x)->b_nodes[0]->b_nodes[1] = NULL;
			}
			else {
				(*x)->b_nodes[1]->b_nodes[0]->b_nodes[0] = (*x);
				(*x)->b_nodes[1]->b_nodes[0]->b_nodes[1] = (*x)->b_nodes[1];
				(*x) = (*x)->b_nodes[1]->b_nodes[0];
				(*x)->b_nodes[0]->b_nodes[1] = NULL;
				(*x)->b_nodes[1]->b_nodes[0] = NULL;
			}
		}
		else if (!(*x)->b_nodes[1]) {
			if (!(*x)->b_nodes[0]->b_nodes[1]) {
				(*x)->b_nodes[0]->b_nodes[1] = (*x);
				(*x) = (*x)->b_nodes[0];
				(*x)->b_nodes[1]->b_nodes[0] = NULL;
			}
			else {
				(*x)->b_nodes[0]->b_nodes[1]->b_nodes[1] = (*x);
				(*x)->b_nodes[0]->b_nodes[1]->b_nodes[0] = (*x)->b_nodes[0];
				(*x) = (*x)->b_nodes[0]->b_nodes[1];
				(*x)->b_nodes[1]->b_nodes[0] = NULL;
				(*x)->b_nodes[0]->b_nodes[1] = NULL;
			}
		}
		else if ((*x)->b_nodes[0]->height < (*x)->b_nodes[1]->height) {
			if ((*x)->b_nodes[1]->b_nodes[1]->height >(*x)->b_nodes[1]->b_nodes[0]->height) {
				Node<T>* z = (*x);
				(*x) = (*x)->b_nodes[1];
				z->b_nodes[1] = (*x)->b_nodes[0];
				(*x)->b_nodes[0] = z;
			}
			else {
				Node<T>* z = (*x)->b_nodes[1]->b_nodes[0];
				(*x)->b_nodes[1]->b_nodes[0] = z->b_nodes[1];
				z->b_nodes[1] = (*x)->b_nodes[1];
				(*x)->b_nodes[1] = z->b_nodes[0];
				z->b_nodes[0] = (*x);
				(*x) = z;
			}
		}
		else if ((*x)->b_nodes[0]->height > (*x)->b_nodes[1]->height) {
			if ((*x)->b_nodes[0]->b_nodes[0]->height > (*x)->b_nodes[0]->b_nodes[1]->height) {
				Node<T>* z = (*x);
				(*x) = (*x)->b_nodes[0];
				z->b_nodes[0] = (*x)->b_nodes[1];
				(*x)->b_nodes[1] = z;
			}
			else {
				Node<T>* z = (*x)->b_nodes[0]->b_nodes[1];
				(*x)->b_nodes[0]->b_nodes[1] = z->b_nodes[0];
				z->b_nodes[0] = (*x)->b_nodes[0];
				(*x)->b_nodes[0] = z->b_nodes[1];
				z->b_nodes[1] = (*x);
				(*x) = z;
			}
		}
		add_heights();
	}
}

template<class T>
inline void Avl<T>::pr(Node<T>* a, int n) {
	if (a != NULL) { // Si el arbol no esta vacio
		pr(a->b_nodes[1], n + 1);
		for (int i = 0; i < n; i++)
			cout << "  ";
		//cout << a->dato << endl;
		cout << "------------------------- DATOS DE LOS JUGADORES -------------------------" << endl;
		for (int i = 0; i < a->vec.size(); i++) {
			a->vec[i]->m_estructura.MostrarJugador();
			cout << "\n" << endl;
		}
		pr(a->b_nodes[0], n + 1);
	}
}

template<class T>
void Avl<T>::print() {

	//InOrder(root);	// SOlo imprime todos los datos
	//std::cout << std::endl;
	int n = 2;	// Imprime en arbol solo datos
	pr(root, n);
}

template<class T>
void Avl<T>::InOrder(Node<T>* p) {
	if (!p)	return;
	InOrder(p->b_nodes[0]);
	cout << p->dato << " SON:" << endl;
	for (int i = 0; i < p->vec.size(); i++) {
		cout << "Datos CNodoLista<Jugador> " << i + 1 << endl;
		cout << p->vec[i]->index << " -> ";
		cout << p->vec[i]->Numero << " -> ";
		cout << p->vec[i]->Apellido << " -> ";
		cout << p->vec[i]->Posicion << " -> ";
		cout << p->vec[i]->Edad << " -> ";
		cout << p->vec[i]->Seleccion << endl;
	}
	cout << endl;
	InOrder(p->b_nodes[1]);
}
