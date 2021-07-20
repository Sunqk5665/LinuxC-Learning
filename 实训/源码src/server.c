#include "server.h"

static int sockfd = -1;
static int clientfd = -1;
int addrlen = sizeof(struct sockaddr_in);

void *pthread_server (void *arg)
{
    int ret, nbytes;
    struct sockaddr_in clientaddr;
    // 5接收连接--accept
    printf("wait connecting...\n");
    printf("server = %d\n", sockfd);
    clientfd = accept(sockfd, (struct sockaddr *)&clientaddr, &addrlen);
    if(clientfd < 0) {
        perror("accept err");
        return NULL;
    } else {
        printf("client %s connecting\n", inet_ntoa(clientaddr.sin_addr));
    }

    while(1){
        struct control_cmd tmp_cmd;

        nbytes = recv(clientfd, &tmp_cmd, CONTROL_CMD_LEN, 0);
        if(nbytes > 0){
            recv_cmd = tmp_cmd.cmd;
            raise(CMD_ARRIVE);
        }else if(nbytes == 0){
            printf("client quit\n");
            clientfd = -1;
        }else{
            continue;
        }
    }
}


int init_network(uint16_t port)
{
    printf("prot = %d\n", port);
    struct sockaddr_in addr;
    pthread_t pid;

    // 1创建一个套接字--socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("socket err");
        return -1;
    }

    // 2定义套接字地址--sockaddr_in
    bzero(&addr, addrlen);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    // 3绑定套接字--bind
    if(bind(sockfd, (struct sockaddr *)&addr, addrlen) < 0) {
        perror("bind err");
        return -1;
    }

    // 4启动监听--listen
    if(listen(sockfd, 5) < 0) {
        perror("listen err");
        return -1;
    }

    return pthread_create(&pid, NULL, pthread_server, NULL);
}


/**
 * @brief 发送给客户端
 * @return 发送成功字节数 -1发送失败或者无客户端
 */
int send_data(struct conver_env_info *data)
{
    if(clientfd > 0){  //代表有连接了
        return send(clientfd, data, sizeof(struct conver_env_info), 0);
    }else{
        printf("no client connect\n");
        return -1;
    }
}
