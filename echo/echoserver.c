#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <getopt.h>

#if 0
/* Internet style socket address */
struct sockaddr_in  {
  unsigned short int sin_family; /* Address family */
  unsigned short int sin_port;   /* Port number */
  struct in_addr sin_addr;	 /* IP address */
  unsigned char sin_zero[...];   /* Pad to size of 'struct sockaddr' */
};

/* 
 * Structs exported from netinet/in.h (for easy reference)
 */

/* Internet address */
struct in_addr {
  unsigned int s_addr; 
};

/*
 * Struct exported from netdb.h
 */

/* Domain name service (DNS) host entry */
struct hostent {
  char    *h_name;        /* official name of host */
  char    **h_aliases;    /* alias list */
  int     h_addrtype;     /* host address type */
  int     h_length;       /* length of address */
  char    **h_addr_list;  /* list of addresses */
}
#endif

#define BUFSIZE 1024

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  echoserver [options]\n"                                                    \
"options:\n"                                                                  \
"  -h                  Show this help message\n"                              \
"  -n                  Maximum pending connections (default: 8)\n"            \
"  -p                  Port (Default: 8086)\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
  {"help",          no_argument,            NULL,           'h'},
  {"maxnpending",   required_argument,      NULL,           'n'},
  {"port",          required_argument,      NULL,           'p'},
  {NULL,            0,                      NULL,             0}
};


int main(int argc, char **argv) {
  int option_char;
  int portno = 8086; /* port to listen on */
  int maxnpending = 8;
  
  // Parse and set command line arguments
  while ((option_char = getopt_long(argc, argv, "hn:p:", gLongOptions, NULL)) != -1) {
   switch (option_char) {
      case 'p': // listen-port
        portno = atoi(optarg);
        break;                                        
      case 'n': // server
        maxnpending = atoi(optarg);
        break; 
      case 'h': // help
        fprintf(stdout, "%s", USAGE);
        exit(0);
        break;           
      default:
        fprintf(stderr, "%s", USAGE);
        exit(1);
    }
  }

    if (maxnpending < 1) {
        fprintf(stderr, "%s @ %d: invalid pending count (%d)\n", __FILE__, __LINE__, maxnpending);
        exit(1);
    }

    if ((portno < 1025) || (portno > 65535)) {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }

  /* Socket Code Here */

}
