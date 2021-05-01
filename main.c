/*
 * main.c
 *
 *  Created on: Apr 30, 2021
 *      Author: ppellegrini
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BACKLOG 2
#define IP "127.0.0.1"
#define PORT 5555

int main(){

	// Declaro las estructuras necesarias
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	// Defino la estructura del server
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(server_addr.sin_zero), '\0', 8);

	// Creacion de Sockets
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	int client_socket;

	if(server_socket != -1) {
		printf("Socket creado correctamente!\n");
	} else {
		printf("Hubo un problema en la creacion del socket\n");
	}

	// Reservar puerto
	int port_is_reserved = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	if(port_is_reserved != -1){
		printf("Se reservo correctamente el puerto %i!\n", PORT);
	} else {
		printf("Hubo un problema en la reserva de puerto...\n");
	}

	// Ponerse a la espera y mandar conexiones entrantes a la cola de espera para ser aceptados.
	listen(server_socket, BACKLOG);

	// Aceptar las conexiones entrantes que se encuentran en cola
	socklen_t client_socket_len = sizeof(sizeof(client_addr));

	client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_socket_len);
	printf("Se conecto un cliente!\n");

	close(client_socket);
	close(server_socket);

	return 0;
}












