#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"

/*
 * NOMBRE: Matias Tebele
 * PADRON: 95372
 */

/******************************************************************
 *                        PRUEBAS UNITARIAS
 ******************************************************************/

// Funciones auxiliares para imprimir si estuvo OK o no
void print_test(char* name, bool result)
{
	printf("* %s: %s\n", name, result? "OK" : "ERROR");
}

void print_test_loop(char* name, int value, bool result)
{
	printf("* %s %d: %s\n", name, value, result? "OK" : "ERROR");
}

// Clono una cadena con memoria dinámica
char *strdup(const char *s)
{
    char *n = malloc(strlen(s) + 1);
    if(n == NULL) return NULL;
    strcpy(n, s);
    return n;
}

// Extra contiene la dirección de la variable 'cuenta'
// Devuelve true para seguir iterando
bool contar_elementos(void *dato, void *extra)
{
	int *suma = (int*)extra;
	(*suma)++;
	return true;
}

// Pruebas para una lista sin elementos
void pruebas_lista_nula()
{
	printf("-- INICIO DE PRUEBAS CON LISTA SIN ELEMENTOS -- \n");

	// Creo una lista
	lista_t* lista = lista_crear();
	
	// Inicio de pruebas
	print_test("Crear lista", lista != NULL);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("El primero es NULL", lista_ver_primero(lista) == NULL);
	print_test("El largo es 0", lista_largo(lista) == 0);
	print_test("No tengo elementos que borrar", lista_borrar_primero(lista) == NULL);
		
	// Destruyo la lista
	lista_destruir(lista, free);
	print_test("La lista fue destruida", true);
}

// Pruebas de guardar y obtener algunos elementos
void pruebas_lista_algunos_elementos()
{
	printf("-- INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS -- \n");
	
	// Creo una lista
	lista_t* lista = lista_crear();
	int vi[] = {0,5,22,-10,3,8};
	char vc[] = {'_','z','R','@','m','+'};
	
	// Defino la cantidad de elementos de los vectores vi y vc
	size_t size = 6;
	
	// Pruebo insertar y borrar
	print_test("Crear lista", lista != NULL);
	print_test("Inserto ultimo 22", lista_insertar_ultimo(lista, &vi[2]));
	print_test("Borro 22", lista_borrar_primero(lista) == &vi[2]);
	print_test("Inserto primero vc[]", lista_insertar_primero(lista, &vc));
	print_test("Borro vc[]", lista_borrar_primero(lista) == &vc);
	print_test("Borrar nuevamente es NULL", lista_borrar_primero(lista) == NULL);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	
	// Inserto
	for (int i = 0; i < size; i++)
		print_test_loop("Inserto", vi[i], lista_insertar_ultimo(lista, &vi[i]));

	// Borro y comparo
	for (int i = 0; i < size; i++)
		print_test_loop("Borro", vi[i], lista_borrar_primero(lista) == &vi[i]);
	
	print_test("El primero es NULL", lista_ver_primero(lista) == NULL);
	print_test("La lista esta vacia", lista_esta_vacia(lista));

	// Destruyo la lista
	lista_destruir(lista, free);
	print_test("La lista fue destruida", true);
}

// Pruebas de guardar y obtener elementos dinamicos
void pruebas_lista_elementos_dinamicos()
{
	printf("-- INICIO DE PRUEBAS CON ELEMENTOS DINAMICOS -- \n");
	
	// Creo una lista y punteros a char
	lista_t* lista = lista_crear();
	
	char* hola = strdup("hola");
	char* mundo = strdup("mundo");
	char* hello = strdup("hello");
	char* world = strdup("world");
	
	// Pruebo insertar_primero y ultimo
	print_test("Crear lista", lista != NULL);
	print_test("Inserto hola", lista_insertar_ultimo(lista, hola));
	print_test("Inserto mundo", lista_insertar_ultimo(lista, mundo));
	print_test("Inserto world", lista_insertar_primero(lista, world));
	print_test("Inserto hello", lista_insertar_primero(lista, hello));
	
	// Borro los datos y comparo
	print_test("Borro hello", lista_borrar_primero(lista) == hello);
	print_test("Borro world", lista_borrar_primero(lista) == world);
	print_test("Borro hola", lista_borrar_primero(lista) == hola);
	print_test("Borro mundo", lista_borrar_primero(lista) == mundo);
	
	// La lista esta vacia
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	
	// Libero la memoria de los char*
	free(hola);
	free(mundo);
	free(hello);
	free(world);
	
	// Destruyo la lista
	lista_destruir(lista, free);
	print_test("La lista fue destruida", true);
}

// Pruebas de la lista al trabajar con un volumen grande de elementos
void pruebas_lista_volumen()
{
	printf("-- INICIO DE PRUEBAS DE VOLUMEN -- \n");
	
	// Creo una lista
	lista_t* lista = lista_crear();
	
	// Creo la lista
	print_test("Crear lista", lista != NULL);
	
	// Defino la cantidad de elementos a insertar_primero
	int cant = 10000;
	int i;
	bool result = true;	
	
	// Inserto 10000 elementos
	for (i = 0; i < cant; i++)
		result &= lista_insertar_primero(lista, &i);
	print_test("Se insertaron todos los elementos", result);
	
	// Borro 10000 elementos y comparo con los insertados
	result = true;
	for (i = 0; i < cant; i++)
		result &= (lista_borrar_primero(lista) == &i);
	print_test("Se borrar todos los elementos y son identicos", result);
	
	print_test("El primero es nulo", lista_ver_primero(lista) == NULL);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
								
	// Destruyo la lista
	lista_destruir(lista, free);
	print_test("La lista fue destruida", true);
}

void pruebas_lista_iter_interno()
{
	printf("-- INICIO DE PRUEBAS CON ITERADOR INTERNO -- \n");
	
	// Creo una lista
	lista_t* lista = lista_crear();
	int vi[] = {-5,-1,8,12,45,1002};
	size_t size = 6;
	
	for (int i = 0; i < size; i++)
		lista_insertar_ultimo(lista, &vi[i]);
	int cuenta = 0;
	lista_iterar(lista, contar_elementos, &cuenta);	

	print_test_loop("La cuenta es", size, cuenta == size);
	
	// Borro todos los elementos
	while (!lista_esta_vacia(lista))
		lista_borrar_primero(lista);
	
	// Destruyo la lista
	lista_destruir(lista, free);
	print_test("La lista fue destruida", true);
}

void pruebas_lista_iter_externo()
{
	printf("-- INICIO DE PRUEBAS CON ITERADOR EXTERNO -- \n");
	
	// Creo una lista
	lista_t* lista = lista_crear();
	print_test("Crear lista", lista != NULL);
	
	// Creo un vector de enteros
	int vi[] = {-15,0,10,23,62,99};
	size_t size = 6;
	
	// Creo un iterador
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Crear iterador", iter != NULL);
	
	// Inserto los valores en la lista
	for (int i = 0; i < size; i++)
	{
		lista_insertar(lista, iter, &vi[i]);
		lista_iter_avanzar(iter);
	}
	
	// Itero la lista mientras sumo sus valores	
	int suma = 0;
	int n1 = 5;
	int n2 = 8;
	
	// Destruyo el iterador
	lista_iter_destruir(iter);
	print_test("El iterador fue destruido", true);
	
	// Vuelvo a crear un iterador
	iter = lista_iter_crear(lista);
	print_test("Crear iterador", iter != NULL);
	
	// Inserto un nuevo valor 5
	lista_insertar(lista, iter, &n1);
	// Itero una vez
	lista_iter_avanzar(iter);
	// Inserto un nuevo valor 8
	lista_insertar(lista, iter, &n2);
	
	// Itero y sumo
	while (!lista_iter_al_final(iter))
	{
		int *val = lista_iter_ver_actual(iter);
		suma += *val;
		lista_iter_avanzar(iter);
	}
	
	// Calculo la suma
	print_test_loop("La suma es", (8-15+0+10+23+62+99), suma == (8-15+0+10+23+62+99));		

	while (!lista_esta_vacia(lista))
		lista_borrar_primero(lista);
	
	// Destruyo el iterador
	lista_iter_destruir(iter);
	print_test("El iterador fue destruido", true);
	
	// Destruyo la lista
	lista_destruir(lista, free);
	print_test("La lista fue destruida", true);
}

void pruebas_lista_iter_externo_lineal()
{
	printf("-- INICIO DE PRUEBAS CON ITERADOR EXTERNO LINEAL -- \n");
	
	// Creo una lista
	lista_t* lista = lista_crear();
	print_test("Crear lista", lista != NULL);
	
	// Creo un vector de enteros
	int vi[] = {-15,0,10,23,62,99};
	size_t size = 6;
	
	// Inserto los valores en la lista
	for (int i = 0; i < size; i++)
		lista_insertar_ultimo(lista, &vi[i]);
	
	// Creo un iterador
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Crear iterador", iter != NULL);
	int suma = 0;
	
	// Itero la lista mientras sumo sus valores
	while (!lista_iter_al_final(iter))
	{
		int *val = lista_iter_ver_actual(iter);
		suma += *val;
		lista_iter_avanzar(iter);
	}
	
	// Verifico la suma
	print_test_loop("La suma es", (-15+0+10+23+62+99), suma == (-15+0+10+23+62+99));	
	
	// Borro todos los elementos
	while (!lista_esta_vacia(lista))
		lista_borrar_primero(lista);

	// Destruyo el iterador
	lista_iter_destruir(iter);
	print_test("El iterador fue destruido", true);
	
	// Destruyo la lista
	lista_destruir(lista, free);
	print_test("La lista fue destruida", true);
}

void pruebas_lista_iter_externo_borrando()
{
	printf("-- INICIO DE PRUEBAS CON ITERADOR EXTERNO BORRANDO -- \n");
	
	// Creo una lista
	lista_t* lista = lista_crear();
	print_test("Crear lista", lista != NULL);
	
	// Creo un vector de enteros
	int vi[] = {-15,0,10,23,62,99};
	size_t size = 6;
	
	// Inserto los valores en la lista
	int i = 0;	
	for (i = 0; i < size; i++)
		lista_insertar_ultimo(lista, &vi[i]);
	
	// Itero la lista mientras sumo sus valores
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Crear iterador", iter != NULL);
	
	// Itero una vez
	lista_iter_avanzar(iter);
	
	// Borro un elemento
	print_test("El elemento borrado es 0", lista_borrar(lista, iter) == &vi[1]);
	size--;
	print_test_loop("La cantidad de elementos es", size, lista_largo(lista) == size);
	// Borro otro elemento
	print_test("El elemento borrado es 10", lista_borrar(lista, iter) == &vi[2]);
	size--;
	print_test_loop("La cantidad de elementos es", size, lista_largo(lista) == size);
	
	// Borro todos los elementos
	while (!lista_esta_vacia(lista))
		lista_borrar_primero(lista);
	
	// Destruyo el iterador
	lista_iter_destruir(iter);
	print_test("El iterador fue destruido", true);
	
	// Destruyo la lista
	lista_destruir(lista, free);
	print_test("La lista fue destruida", true);
}

void pruebas_lista_iter_insertar_avanzando()
{
	printf("-- INICIO DE PRUEBAS CON ITERADOR EXTERNO AVANZANDO -- \n");
	
	// Creo una lista
	lista_t* lista = lista_crear();
	print_test("Crear lista", lista != NULL);
	
	// Creo un vector de enteros
	int vi[] = {-15,0,10,23,62,99};
	size_t size = 6;
	
	// Creo un iterador
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Crear iterador", iter != NULL);
	
	// Inserto los valores en la lista
	for (int i = 0; i < size; i++)
	{
		lista_insertar(lista, iter, &vi[i]);
		lista_iter_avanzar(iter);
	}
	
	// Destruyo el iterador
	lista_iter_destruir(iter);
	print_test("El iterador fue destruido", true);
	
	// Creo de nuevo el iterador
	iter = lista_iter_crear(lista);
	print_test("Crear iterador", iter != NULL);
	int i = 0;
	
	// Comparo elementos
	while(!lista_iter_al_final(iter))
	{
		print_test_loop("El elemento actual es", vi[i], lista_iter_ver_actual(iter) == &vi[i]);
		lista_iter_avanzar(iter);
		i++;
	}
	
	// Destruyo el iterador
	lista_iter_destruir(iter);
	print_test("El iterador fue destruido", true);
	
	// Creo de nuevo el iterador
	iter = lista_iter_crear(lista);
	print_test("Crear iterador", iter != NULL);
	i = 0;
	
	// Borro elementos
	while(!lista_iter_al_final(iter))
	{
		print_test_loop("El elemento borrado es", vi[i], lista_borrar(lista, iter) == &vi[i]);
		i++;
	}
	
	// Destruyo el iterador
	lista_iter_destruir(iter);
	print_test("El iterador fue destruido", true);
	
	print_test("La lista esta vacia", lista_esta_vacia(lista) == true);
	
	// Destruyo la lista
	lista_destruir(lista, free);
	print_test("La lista fue destruida", true);
}

void pruebas_lista_insertar_y_borrar()
{
	printf("-- INICIO DE PRUEBAS INSERTANDO Y BORRANDO -- \n");
	
	// Creo una lista
	lista_t* lista = lista_crear();
	int vi[] = {1,5,22,-10,3,8};
	
	// Pruebo insertar ultimo y borrar
	print_test("Crear lista", lista != NULL);
	// Inserto-Borro
	print_test("Inserto ultimo 1", lista_insertar_ultimo(lista, &vi[0]));
	print_test("Borro 1", lista_borrar_primero(lista) == &vi[0]);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("Borrar nuevamente es NULL", lista_borrar_primero(lista) == NULL);
	// Inserto-Inserto-Borro-Borro
	print_test("Inserto ultimo 1", lista_insertar_ultimo(lista, &vi[0]));
	print_test("Inserto ultimo 5", lista_insertar_ultimo(lista, &vi[1]));
	print_test("Borro 1", lista_borrar_primero(lista) == &vi[0]);
	print_test("Borro 5", lista_borrar_primero(lista) == &vi[1]);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("Borrar nuevamente es NULL", lista_borrar_primero(lista) == NULL);
	// Inserto-Inserto-Borro-Inserto-Borro-Borro
	print_test("Inserto ultimo 1", lista_insertar_ultimo(lista, &vi[0]));
	print_test("Inserto ultimo 5", lista_insertar_ultimo(lista, &vi[1]));
	print_test("Borro 1", lista_borrar_primero(lista) == &vi[0]);
	print_test("Inserto ultimo 22", lista_insertar_ultimo(lista, &vi[2]));
	print_test("Borro 5", lista_borrar_primero(lista) == &vi[1]);
	print_test("Borro 22", lista_borrar_primero(lista) == &vi[2]);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("Borrar nuevamente es NULL", lista_borrar_primero(lista) == NULL);
	
	// Pruebo insertar primero y borrar
	print_test("Crear lista", lista != NULL);
	// Inserto-Borro
	print_test("Inserto primero 1", lista_insertar_primero(lista, &vi[0]));
	print_test("Borro 1", lista_borrar_primero(lista) == &vi[0]);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("Borrar nuevamente es NULL", lista_borrar_primero(lista) == NULL);
	// Inserto-Inserto-Borro-Borro
	print_test("Inserto primero 1", lista_insertar_primero(lista, &vi[0]));
	print_test("Inserto primero 5", lista_insertar_primero(lista, &vi[1]));
	print_test("Borro 5", lista_borrar_primero(lista) == &vi[1]);
	print_test("Borro 1", lista_borrar_primero(lista) == &vi[0]);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("Borrar nuevamente es NULL", lista_borrar_primero(lista) == NULL);
	// Inserto-Inserto-Borro-Inserto-Borro-Borro
	print_test("Inserto primero 1", lista_insertar_primero(lista, &vi[0]));
	print_test("Inserto primero 5", lista_insertar_primero(lista, &vi[1]));
	print_test("Borro 5", lista_borrar_primero(lista) == &vi[1]);
	print_test("Inserto primero 22", lista_insertar_primero(lista, &vi[2]));
	print_test("Borro 22", lista_borrar_primero(lista) == &vi[2]);
	print_test("Borro 1", lista_borrar_primero(lista) == &vi[0]);
	print_test("La lista esta vacia", lista_esta_vacia(lista));	
	print_test("Borrar nuevamente es NULL", lista_borrar_primero(lista) == NULL);
	
	// Pruebo insertar primero/ultimo y borrar
	print_test("Crear lista", lista != NULL);
	// Inserto-Inserto-Borro-Borro
	print_test("Inserto ultimo 1", lista_insertar_ultimo(lista, &vi[0]));
	print_test("Inserto primero 5", lista_insertar_primero(lista, &vi[1]));
	print_test("Borro 5", lista_borrar_primero(lista) == &vi[1]);
	print_test("Borro 1", lista_borrar_primero(lista) == &vi[0]);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("Borrar nuevamente es NULL", lista_borrar_primero(lista) == NULL);
	// Inserto-Inserto-Borro-Inserto-Borro-Borro
	print_test("Inserto primero 1", lista_insertar_primero(lista, &vi[0]));
	print_test("Inserto ultimo 5", lista_insertar_ultimo(lista, &vi[1]));
	print_test("Borro 1", lista_borrar_primero(lista) == &vi[0]);
	print_test("Inserto ultimo 22", lista_insertar_ultimo(lista, &vi[2]));
	print_test("Borro 5", lista_borrar_primero(lista) == &vi[1]);
	print_test("Borro 22", lista_borrar_primero(lista) == &vi[2]);
	print_test("La lista esta vacia", lista_esta_vacia(lista));	
	print_test("Borrar nuevamente es NULL", lista_borrar_primero(lista) == NULL);	
	
	// Creo un iterador
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Crear iterador", iter != NULL);
	int i;
	
	// Inserto i = 0..9
	for (i = 0; i < 10; i++)
	{
		lista_insertar(lista, iter, &i);
		print_test_loop("Inserto", i, *(int*)lista_iter_ver_actual(iter) == i);
	}
	
	print_test("El iterador no esta al final", !lista_iter_al_final(iter));
	while (!lista_iter_al_final(iter))
		print_test("Avanzo el iterador", lista_iter_avanzar(iter));
	print_test("El elemento actual es NULL", lista_iter_ver_actual(iter) == NULL);	
	
	// Destruyo el iterador
	lista_iter_destruir(iter);
	print_test("El iterador fue destruido", true);
	
	// Borro todos los elementos
	while (!lista_esta_vacia(lista))
		lista_borrar_primero(lista);
	
	// Destruyo la lista
	lista_destruir(lista, free);
	print_test("La lista fue destruida", true);
}

void pruebas_lista_iter_lista_vacia()
{
	printf("-- INICIO DE PRUEBAS CON ITERADOR Y LISTA VACIA -- \n");
	
	// Creo una lista
	lista_t* lista = lista_crear();
	print_test("Crear lista", lista != NULL);
	
	// Creo un iterador
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Crear iterador", iter != NULL);
	
	print_test("El elemento actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("El iterador esta al final", lista_iter_al_final(iter));   
    
    // Destruyo el iterador
	lista_iter_destruir(iter);
	print_test("El iterador fue destruido", true);
	
	// Destruyo la lista
	lista_destruir(lista, NULL);
	print_test("La lista fue destruida", true);
}

// Ejecuto todas las pruebas
void pruebas_lista()
{
	pruebas_lista_nula();
	pruebas_lista_algunos_elementos();
	pruebas_lista_elementos_dinamicos();
	pruebas_lista_volumen();
	pruebas_lista_iter_interno();
	pruebas_lista_iter_externo();
	pruebas_lista_iter_externo_lineal();
	pruebas_lista_iter_externo_borrando();
	pruebas_lista_iter_insertar_avanzando();
	pruebas_lista_insertar_y_borrar();
	pruebas_lista_iter_lista_vacia();
}

// Programa principal
int main(int argc, char **argv)
{	
	pruebas_lista();
	return 0;
}
