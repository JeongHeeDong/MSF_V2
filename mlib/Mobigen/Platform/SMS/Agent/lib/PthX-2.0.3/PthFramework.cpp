#include <stdio.h>
#include <string.h>
#include <cassert>

#include "PthTask.h"
#include "PthSocket.h"
#include "PthServer.h"

using namespace std;

#ifndef DEBUG_PRINT
#  ifdef NDEBUG
#    define DEBUG_PRINT if (0) printf
#  else // NDEBUG
#    define DEBUG_PRINT printf("(%s,%d) ", __FILE__, __LINE__); printf
#  endif // NDEBUG
#endif // DEBUG_PRINT

extern void main_setup(); // ��ü ���α׷� ���� ���� ȣ���� �ڵ�
extern void main_teardown(); // ��ü ���α׷� ������ ȣ���� �ڵ�

extern void setup();    // ������ ���� �����ϱ� ���� ȣ���� �ڵ�
extern void teardown(); // thread ���� ������ ���� ȣ���� �ڵ�

extern int service_main(int sock_fd);

class MyGenericServer: public PthServer
{
  public:
    void service(PthSocket *sock)
    {
        assert(sock != NULL);
        setup();

        service_main(sock->getSockFd());

        teardown();
    }
};

int _max_service_per_child = 0;

void read_svc_conf(int &port, int &num_thread)
{
    extern int _process_num;

    FILE *fp = fopen("./svc.conf", "r");
    if (fp != NULL) {
        char buf[BUFSIZ];
        while (fgets(buf, BUFSIZ, fp) != NULL) {
            if (buf[0] == '#') { continue; }

            // -----------------------------------------------------------
            // 2003/12/27 _process_num ������ ����, svc.conf �κ��� �о�
            //            ���̵��� �Ѵ�. process_num 0 �̸� single process
            //            ���̰�, process_num 1 �̸�, ����͸� ���μ�����
            //            �ϳ� �� �ߴ� ���̴�.
            // -----------------------------------------------------------
            if (strncmp(buf, "process_num ", 12) == 0) {
                sscanf(&buf[12], "%d", &_process_num);
                continue;
            }

            // -----------------------------------------------------------
            // 2004/01/08 max_service_per_chiled ���� ����
            //            Ư�� process�� ��ȸ �̻� ���񽺸� �ϰ� ���� 
            //            �׵��� �Ѵ�.  �޸� ��ũ ������ �ذ��ϱ� ���ؼ�
            //            �Ǵ� ���� ��� ������ �ذ��ϱ� ���ؼ�
            //            process_num == 0�� ���� �������� �ʴ´�.
            //            max_service_per_child == 0�� ���� ������ �ݺ��Ѵ�.
            // -----------------------------------------------------------
            if (strncmp(buf, "max_service_per_child ", 22) == 0) {
                sscanf(&buf[22], "%d", &_max_service_per_child);
                continue;
            }

            char *p = strstr(buf, "-p ");
            if (p == NULL) {
                continue;
            }
            assert(p != NULL);
            port = ::atoi(p+3);

            char *n = strstr(buf, "-n ");
            if (n == NULL) {
                continue;
            }
            assert(n != NULL);
            num_thread = ::atoi(n+3);
        }
        fclose(fp);
    } else {
        DEBUG_PRINT("fopen(svc.conf, 'r') failed\n");
    }
}

int main()
{
DEBUG_PRINT("main_setup()\n");
    main_setup();

    MyGenericServer server;

    int port, num_thread;

DEBUG_PRINT("read_svc_conf()\n");
    read_svc_conf(port, num_thread);

DEBUG_PRINT("port: %d\n", port);
    server.set_port(port);

    extern int _process_num;
DEBUG_PRINT("process_num: %d\n", _process_num);
    server.set_max_children(_process_num);

DEBUG_PRINT("set_max_thread(%d)\n", num_thread);
    server.set_max_threads(num_thread);

DEBUG_PRINT("set_max_service_per_child(%d)\n", _max_service_per_child);
    if (_process_num == 0) {
        DEBUG_PRINT("process_num == 0: _max_service_per_child must be zero\n");
        _max_service_per_child = 0;
    }
    server.set_max_service_per_child(_max_service_per_child);

DEBUG_PRINT("server.start()\n");
    server.start();

DEBUG_PRINT("main_teardown()\n");
    main_teardown();

    return 0;
}


#ifdef PTH_FRAMEWORK_TEST

// global number to be specified
int _process_num = 2;

void main_setup()
{
    DEBUG_PRINT("main_setup() called\n");
}

void main_teardown()
{
    DEBUG_PRINT("main_teardown() called\n");
}

void setup()
{
    DEBUG_PRINT("setup() called\n");
}

void teardown()
{
    DEBUG_PRINT("teardown() called\n");
}

int service_main(int sock_fd)
{
    MSocket sock;
    sock.set_sockfd(sock_fd);

    string hello = "hello service_main()\r\n";
    sock.write(hello.c_str(), hello.size());
    if (sock.isError()) {
        DEBUG_PRINT("isError()\n");
        sock.close();
        return 0;
    }

    while (1)
    {
        string line;
        sock.read_line(line);
        if (sock.isError()) {
            DEBUG_PRINT("error\r\n");
            break;
        }

        if (strncasecmp(line.c_str(), "QUIT", 4) == 0) {
            break;
        }

        line = "OK " + line;
        sock.write(line.c_str(), line.size());
        if (sock.isError()) {
            DEBUG_PRINT("error\n");
            break;
        }
    }

    sock.close();
    return 1;
}

#endif // PTH_FRAMEWORK_TEST
