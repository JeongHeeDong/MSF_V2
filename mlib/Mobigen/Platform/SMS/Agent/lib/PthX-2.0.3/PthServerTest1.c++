#include "PthServer.h++"

int main()
{
    // �ƹ��� ��� ���� �׳� ����, Echo ������ �����ȴ�.
    PthServer *server = new PthServer();

    server->setPort(9994);

    // server->setMaxChildren(2);
    // server->setMaxThreads(2);

    server->start();

    delete server;

    return 0;
}

