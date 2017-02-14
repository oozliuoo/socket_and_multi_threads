#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <getopt.h>

/* Be prepared accept a response of this length */
#define BUFSIZE 1024

#define USAGE                                                                      \
    "usage:\n"                                                                     \
    "  echoclient [options]\n"                                                     \
    "options:\n"                                                                   \
    "  -h                  Show this help message\n"                               \
    "  -m                  Message to send to server (Default: \"Hello World!\"\n" \
    "  -p                  Port (Default: 8086)\n"                                 \
    "  -s                  Server (Default: localhost)\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"help", no_argument, NULL, 'h'},
    {"message", required_argument, NULL, 'm'},
    {"port", required_argument, NULL, 'p'},
    {"server", required_argument, NULL, 's'},
    {NULL, 0, NULL, 0}};

/* Main ========================================================= */
int main(int argc, char **argv)
{
    int option_char = 0;
    char *hostname = "localhost";
    unsigned short portno = 8086;
    char *message = "Hello World!";

    // Parse and set command line arguments
    while ((option_char = getopt_long(argc, argv, "hm:p:s:", gLongOptions, NULL)) != -1)
    {
        switch (option_char)
        {
        case 'h': // help
            fprintf(stdout, "%s", USAGE);
            exit(0);
            break;
        case 'm': // server
            message = optarg;
            break;
        case 'p': // listen-port
            portno = atoi(optarg);
            break;
        case 's': // server
            hostname = optarg;
            break;
        default:
            fprintf(stderr, "%s", USAGE);
            exit(1);
        }
    }

    if (NULL == message)
    {
        fprintf(stderr, "%s @ %d: invalid message\n", __FILE__, __LINE__);
        exit(1);
    }

    if ((portno < 1025) || (portno > 65535))
    {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }

    if (NULL == hostname)
    {
        fprintf(stderr, "%s @ %d: invalid host name\n", __FILE__, __LINE__);
        exit(1);
    }

    /* Socket Code Here */
    fprint(stdout, "%s", hostname);
}
