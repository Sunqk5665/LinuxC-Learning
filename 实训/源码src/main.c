#include "serial.h"
#include "server.h"

void data_handler(int signal)
{
    printf("conver temperature=%0.2f, humidity=%0.2f, ill=%0.2f, bet=%0.2f, adc=%0.2f\n", \
               env_msg.temperature, env_msg.humidity, env_msg.ill, env_msg.bet, env_msg.adc);

    send_data(&env_msg);
}

void cmd_handler(int signal)
{
    printf("recv cmd = 0x%x\n", recv_cmd);
    switch(recv_cmd){
        case FAN_OFF:
        fan_control(0);
        break;
        case FAN_1:
        fan_control(1);
        break;
        case FAN_2:
        fan_control(2);
        break;
        case FAN_3:
        fan_control(3);
        break;
        case BEEP_OFF:
        beep_control(0);
        break;
        case BEEP_ON:
        beep_control(1);
        break;        
        case LED_OFF:
        led_control(0);
        break;
        case LED_ON:
        led_control(1);
        break;
        default:
        break;
    }
}

int main(int argc, char *argv[])
{
    int ret;

    if(argc != 2){
        printf("usage: <%s> port\n", argv[0]);
        return -1;
    }

    //初始化服务器
    ret = init_network(atoi(argv[1]));
    if(ret < 0){
        puts("init_server err");
        return -1;
    }

    ret = init_usb();
    if(ret != 0){
        puts("init_serial err");
        return -1;
    }else{
        puts("init_serial success");
    }

    signal(DATA_ARRIVE, data_handler);  //数据接收处理
    signal(CMD_ARRIVE, cmd_handler);  //命令接收处理

    ret = start_recv();  //启动数据接收处理
    if(ret == 0){
        puts("start_recv success");
    }

    ret = wait_recv();  //等待接收

    return 0;
}
