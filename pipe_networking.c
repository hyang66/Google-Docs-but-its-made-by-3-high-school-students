#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int make = mkfifo("wkp", 0644);
	if(make < 0){
	  printf("[server] Error opening Public Pipe: %s\n", strerror(errno));
	  exit(0);
	}
  else {
	  printf("[server] wkp opened, recieving from client\n");
	}
  int wkpd = open("wkp", O_RDONLY);
  char pid[HANDSHAKE_BUFFER_SIZE];
  read(wkpd, pid, sizeof(pid));
  printf("[server] Message recieved from wkp: %s\n", pid);
	remove("wkp");

	*to_client = open(pid, O_WRONLY);
	if(*to_client <= -1){
	  printf("[server] Error opening %d: %s\n", *to_client, strerror(errno));
	  exit(0);
	}
  else {
	  printf("[server] Opened pipe to client\n");
	}
	write(*to_client, ACK , sizeof(ACK));
	printf("[server] Sending message %s to client\n", ACK);

  printf("[server] Receiving from client...\n" );
  char client_buf[HANDSHAKE_BUFFER_SIZE];
  read(wkpd, client_buf, sizeof(client_buf));
  printf("[server] Message received: %s\n", client_buf);

  return wkpd;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  printf("[client] Creating private pipe \n");
  char pid[HANDSHAKE_BUFFER_SIZE];
  sprintf(pid, "%d", getpid());
  mkfifo(pid, 0644);
  printf("[client] pid: %d", getpid());

  *to_server = open("wkp", O_WRONLY);
  write(*to_server, pid, sizeof(pid));
	printf("[client] sending pid through wkp: %s\n", pid);

  int response = open(pid, O_RDONLY);
  char buf[HANDSHAKE_BUFFER_SIZE];
  read(response, buf, sizeof(buf));
  printf("[client] Message received: %s\n", buf);

  printf("[client] Removing private pipe...\n");
  remove(pid);

  printf("[client] Writing %s to server...\n", ACK);
  write(*to_server, ACK, sizeof(ACK));

  return response;
}
