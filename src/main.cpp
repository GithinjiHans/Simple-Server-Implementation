#include <cstddef>
#include <iostream>
#include <netdb.h>
#include <unistd.h>

int main() {
//Create a socket
int network_socket= socket(AF_INET, SOCK_STREAM, 0);
//connect to an ip address and port
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(9002);
server_address.sin_addr.s_addr = INADDR_ANY;
int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));
//check for error with the connection
if(connection_status == -1){
std::cout << "There was an error making a connection with the server";
}
//bind the socket to an IP address and port
int bind_status = bind(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));
//check for error with the binding 
if(bind_status == -1){
    std::cout << "There was an error binding the socket to an IP address";
}
//listen for connections
int listen_status = listen(network_socket, 5);
//check for error with the listening
if(listen_status == -1){
    std::cout << "There was an error listening for connections";
}
//accept a connection
int client_socket = accept(network_socket,NULL,NULL);
//check for error with the accepting
if(client_socket == -1){
    std::cout << "There was an error accepting a connection";
}
//send data to the client
char server_message[256]="You have reached the server";
send(client_socket,server_message,sizeof(server_message),0);
//receive data from the client
char client_response[256];
recv(client_socket,&client_response,sizeof(client_response),0);
//print out the client's response
std::cout << "Client response "<< client_response << std::endl;
//close the socket
close(network_socket);
}