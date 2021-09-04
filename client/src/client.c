#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger, "Hola! Soy un log");

	config = iniciar_config();

	char* clave;
	clave = config_get_string_value(config, "CLAVE");
	log_info(logger, "La clave es: %s", clave);


	// Usando el config creado previamente
	// Lee las variables de IP, Puerto y Valor

	//Loggear valor de config

	// leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");

	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servirdor

	paquete(conexion, clave);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	
	nuevo_logger = log_create("tp0.log", "TP0", true , LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("tp0.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	do {
	//El primero te lo dejo de yapa
	leido = readline(">");

	// Acá la idea es que imprimas por el log lo que recibis de la consola.
	log_info(logger, leido);

	} while (strcmp(leido,"\0")!=0);

}

void paquete(int conexion, char* clave)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete = crear_paquete();
	agregar_a_paquete(paquete, clave, strlen(clave) + 1);

	do {

	leido = readline(">");

	agregar_a_paquete(paquete, leido, strlen(leido) + 1);


	} while (strcmp(leido,"\0")!=0);

	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);


}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
