#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int ServerCreateConnection(unsigned short port, char *host, int connections)
{
  int mysocket, option;
  struct sockaddr_in sa;
  struct hostent * hp;

  memset(&sa, 0, sizeof(struct sockaddr_in));       //colocar zeros na estrutura
  if ((hp = gethostbyname(host)) == NULL)                      // obter endereco
    return(-1);

  sa.sin_family = hp->h_addrtype;
  sa.sin_port = htons(port);
  if ((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return(-1);

  setsockopt(mysocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
  if (bind(mysocket, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) < 0)
   {
    close(mysocket);
    return(-1);
   }

  listen(mysocket, connections);
  return(mysocket);
}

int ClientCreateConnection(unsigned short port, char *host)
{
  int mysocket;
  struct sockaddr_in sa;
  struct hostent * hp;

  memset(&sa, 0, sizeof(struct sockaddr_in));       //colocar zeros na estrutura
  if ((hp = gethostbyname(host)) == NULL)                      // obter endereco
    return(-1);

  sa.sin_family = AF_INET;
  bcopy(hp->h_addr, &(sa.sin_addr.s_addr), hp->h_length);
  sa.sin_port = htons(port);
  if ((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return(-2);

  if (connect(mysocket ,(struct sockaddr *)&sa, sizeof(struct sockaddr_in)) < 0)
   {
    close(mysocket);
    return(-3);
   }

  return(mysocket);
}
