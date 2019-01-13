#include "pipe_networking.h"
#include "definitions.h"


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
	  printf(MAGENTA "[server] Public pipe already made: %s\n", strerror(errno));
	  exit(0);
	}
  else {
	  printf(MAGENTA "[server] wkp, recieving from client\n");
	}
  int wkpd = open("wkp", O_RDONLY);
  char pid[HANDSHAKE_BUFFER_SIZE];
  read(wkpd, pid, sizeof(pid));
  printf("24\n");
  printf(MAGENTA "[server] Message recieved from wkp: %s\n", pid);
	remove("wkp");

	*to_client = open(pid, O_WRONLY);
	if(*to_client <= -1){
	  printf(MAGENTA "[server] Error opening %d: %s\n", *to_client, strerror(errno));
	  exit(0);
	}
  else {
	  printf(MAGENTA "[server] Opened pipe to client\n");
	}
	write(*to_client, ACK , sizeof(ACK));
	printf(MAGENTA "[server] Sending message %s to client\n", ACK);

  printf(MAGENTA "[server] Receiving from client...\n" );
  char client_buf[HANDSHAKE_BUFFER_SIZE];
  read(wkpd, client_buf, sizeof(client_buf));
  printf(MAGENTA "[server] Message received: %s\n", client_buf);

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
  printf(MAGENTA "[client] Creating private pipe \n");
  char pid[HANDSHAKE_BUFFER_SIZE];
  sprintf(pid, "%d", getpid());
  mkfifo(pid, 0644);
  printf(MAGENTA "[client] PID: %d\n", getpid());

  *to_server = open("wkp", O_WRONLY);
  write(*to_server, pid, sizeof(pid));
  printf(MAGENTA "[client] sending pid through wkp: %s\n", pid);

  int response = open(pid, O_RDONLY);
  char buf[HANDSHAKE_BUFFER_SIZE];
  read(response, buf, sizeof(buf));
  printf(MAGENTA "[client] Message received: %s\n", buf);

  printf(MAGENTA "[client] Removing private pipe...\n");
  remove(pid);

  printf(MAGENTA "[client] Writing %s to server...\n", ACK);
  write(*to_server, ACK, sizeof(ACK));

  return response;
}
