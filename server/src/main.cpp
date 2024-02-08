#include <iostream>
#include <string>
#include <cstring>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

/**
 * @author https://gist.github.com/jdah/08eb80c74b13176027c08cbf48b239c9 (based entirely off of this, just changed up to suit my needs)
 */
int main (int argc, char **argv) {
    // create socket
    const int fd = socket(PF_INET, SOCK_STREAM, 0);

    // bind to open port
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd, (struct sockaddr*) &addr, sizeof(addr))) {
        perror("bind error:");
        return 1;
    }

    // read port
    socklen_t addr_len = sizeof(addr);
    getsockname(fd, (struct sockaddr*) &addr, &addr_len);
    printf("server is on port %d\n", (int) ntohs(addr.sin_port));

disconnected:
    printf("waiting for connection...\n");
    if (listen(fd, 1)) {
        perror("listen error:");
        return 1;
    }

    // accept incoming connection
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    const int cfd = accept(fd, (struct sockaddr*) &caddr, &caddr_len);

    printf("connected!\n");
    std::string prev = "";
    int spam_count = 0;
loop:

    // read from client with recv!
    char buf[1024];
    recv(cfd, buf, sizeof(buf), 0);

    if (!strcmp(prev.c_str(), buf)) spam_count++;
    if (spam_count > atoi(argv[1])) goto disconnected;
    prev = buf;
    

    // print without looking
    printf("recieved:\n%s\n", buf);
    goto loop;

    close(cfd);
    close(fd);
}
