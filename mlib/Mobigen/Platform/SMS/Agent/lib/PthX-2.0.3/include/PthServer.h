#ifndef __PthServer_h__
#define __PthServer_h__

#include <stdlib.h>
#include <unistd.h>

#include <vector>
#include <algorithm>

using namespace std;

// #include "MSocket.h"

#include "PthTask.h"
#include "PthSocket.h"

#ifndef MSocket
#define MSocket PthSocket
#endif

class MultiProc
{
  private:
    vector<pid_t> *children;

  public:
    pid_t pid;

  private:
    int fork_delay;      // fork�� �ѹ� �ϰ�, ���ο� fork�ϱ� �������� �ֱ�
    int check_period;    // child proc �� ��Ҵ����� üũ�ϴ� �ֱ�
    int max_children;    // ���ÿ� ���� �� �ִ� ���μ��� ����

  public:
	int heartbeat_time;  // child process�� �ƹ��� �۾��� ���� �ʰ�
						 // ���� �ִ� ���, �ִ��� ������ �ʰ�,
						 // ������ �� �ִ� �ð�
    string heartbeat_key; // children/monitoring parent ���̿� 
						  // ���� heartbeat�� ��ȯ�� Ű


  public:
    void set_check_period(int check_period);
    void set_fork_delay(int fork_delay);
    void set_max_children(int max_children);
	void set_heartbeat(const string &key, int time);


  public:
    MultiProc();

    virtual ~MultiProc();

  public:
    virtual void before_loop();
    virtual void init_child();
    virtual void main_service();

  public:
    void start();
};

class PthServer: public MultiProc
{
  public:
    PthSocket *listen_sock;

    int port;                  // ��� ��Ʈ��ȣ

    int max_service_per_child; // �� ���μ��� ������, �� ���� ���񽺸�
                               // ó���� �Ŀ� �ڻ��� ���ΰ�... ( <= 0�̸� ����!)

    int max_threads;           // �� ���μ��� ���� �ִ� ���� ������ ��
                               // ( <= 0)�̸� ������

  public:
    PthServer();
    ~PthServer();

  public:
    inline void set_max_service_per_child(int max_service_per_child)
    {
        this->max_service_per_child = max_service_per_child;
    }

    inline void set_max_threads(int max_threads)
    {
        this->max_threads = max_threads;
    }

    inline void set_port(int port)
    {
        this->port = port;
    }

  private:
    void before_loop();
    void main_service();

  public:
    virtual void service(MSocket *sock);

    // void start()�� �� �� ����.
};

#endif // __PthServer_h__
