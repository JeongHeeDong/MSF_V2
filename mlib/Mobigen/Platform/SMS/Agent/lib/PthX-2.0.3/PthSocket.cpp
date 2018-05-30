// ---------------------------------------------------------------------------
// PthSocket.cpp --
//   GNU Pth ���̺귯���� pth_socket �� Ȯ���Ͽ�, C++�������̽��� �������.
//
// Author: All rights reserved. (c) Mobigen Co., Ltd.
//
// Updates:
//   2003/12/27 wait_socket_ready()�� EAGAIN �� ���� ���, true�� �����ϵ���
//              ������.
// ---------------------------------------------------------------------------

#include <unistd.h> // close()

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <fcntl.h> // fcntl()

#include <ctype.h> // isdigit()

#include <time.h>
#include <sys/types.h> // for ClsTCP Interface
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/poll.h>

#include <errno.h>
#include <netdb.h>   // gethostbyname()
#include <time.h> // time()

#include <map>

using namespace std;

#include "PthTask.h"
#include "PthSocket.h"

#ifndef DEBUG_PRINT
#  ifdef NDEBUG
#    define DEBUG_PRINT if (0) printf
#  else // NDEBUG
#    define DEBUG_PRINT printf("(%s,%d) ", __FILE__, __LINE__); printf
#  endif // NDEBUG
#endif // DEBUG_PRINT

typedef struct sockaddr_in SockAddrIn;
typedef struct sockaddr SockAddr;

typedef struct in_addr InAddr;
typedef struct hostent HostEnt;

#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

#ifdef __linux__
    #define SockLen socklen_t
#else
  #ifdef _SOCKLEN_T
    #define SockLen socklen_t
  #else
    #define SockLen int
    /* �ֶ󸮽�2.6������ �� socklen_t�� ���� �ž�!!! */
  #endif
#endif

static void __usleep(int micro_sec)
{
    struct timeval tval;
    tval.tv_sec = micro_sec / 1000000;
    tval.tv_usec = micro_sec % 1000000;

    ::select(0, (fd_set *)NULL, (fd_set *)NULL, (fd_set *)NULL, &tval);
}

bool PthSocket::is_Error()
{
    if (this->error) {
        this->errmsg_ = this->errstr;
    }
    return this->error;
}

int PthSocket::isError()
{
    if (this->error) {
        this->errmsg_ = this->errstr;
    }
    return (int) this->error;
}

string PthSocket::getErrMsg()
{
    return string(this->errstr);
}

char *PthSocket::getErrStr()
{
    return this->errstr;
}

int PthSocket::getSockFd()
{
    return this->sockfd;
}

void PthSocket::set_sockfd(int sockfd)
{
    this->sockfd = sockfd;
}

char *PthSocket::getIpAddr()
{
    return this->ip_addr;
}

void PthSocket::set_rlimit_max()
{
    struct rlimit rlim;

    rlim.rlim_cur = 256;
    rlim.rlim_max = 256;
    if (setrlimit(RLIMIT_NOFILE, &rlim) != 0) {
        fprintf(stderr, "(%s,%d) setrlimit fail(%s)\n", __FILE__, __LINE__,
            strerror(errno));
    }

    struct rlimit cur_rlim;
    if (getrlimit(RLIMIT_NOFILE, &cur_rlim) != 0 )
    {
       fprintf(stderr, "(%s,%d) getrlimit fail(%s)\n", __FILE__, __LINE__,
           strerror(errno));
    }

    fprintf(stderr, "(%s,%d) after open file(%d:%d)\n",
           __FILE__, __LINE__, 
           (int)cur_rlim.rlim_cur, (int)cur_rlim.rlim_max);
}

void PthSocket::init()
{
    this->error = false;
    this->errstr[0] = '\0';
    this->sockfd = -1;
    this->ip_addr[0] = '\0';

    this->lookahead_init();
}

PthSocket::~PthSocket()
{
    this->lookahead_destroy();
}

PthSocket::PthSocket()
{
    this->init();
}

int _set_NonBlock(int sock_fd)
{
    int ret = fcntl(sock_fd, F_SETFL, O_NDELAY);
    return ret;
}

PthSocket::PthSocket(int port)
{
    assert(port > 0);

    this->init();

    if ((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        DEBUG_PRINT("PthSocket: socket() fail: %d:%s\n", errno, 
            strerror(errno));
        this->error = true;
        strcpy(this->errstr, "ServerSock: socket() fail");
        return;
    }

    _set_NonBlock(this->sockfd);

    SockAddrIn serv_addr;
    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    // Set an option on the socket to enable local address reuse
    int opt = 1;
    if (setsockopt(this->sockfd,
       SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        DEBUG_PRINT("setsockopt(SO_REUSEADDR) error.\n");
        this->error = true;
        strcpy(this->errstr, "setsockopt(SO_REUSEADDR) error");
        return;
    }

  if (0) // �� �ʿ��Ѱ�?
  {
    // setsockopt(SO_KEEPALIVE) introduced
    opt = 0;
    if (setsockopt(this->sockfd, SOL_SOCKET, SO_KEEPALIVE,
           (char *)&opt, sizeof(opt)) < 0)
    {
        DEBUG_PRINT("setsockopt(SO_KEEPALIVE) error.\n");
        this->error = true;
        strcpy(this->errstr, "setsockopt(SO_KEEPALIVE)");
        return;
    }
  }

    if (bind(this->sockfd, (SockAddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        DEBUG_PRINT("PthSocket: bind() fail\n");
        this->error = true;
        strcpy(this->errstr, "PthSocket: bind() fail");
        return;
    }

    strcpy(this->ip_addr, inet_ntoa(serv_addr.sin_addr));

    if (listen(this->sockfd, 64) < 0) {
        DEBUG_PRINT("PthSocket: listen() fail\n");
        this->error = true;
        strcpy(this->errstr, "PthSocket: listen() fail");
        return;
    }
}

static bool __isNumeric(const char *hostAddr)
{
    assert(hostAddr != NULL);

    char *host = (char*) hostAddr;
    if (host == NULL) return (false);
    while (*host != '\0') {
        if (! isdigit((int)(*host)) && *host != '.')
            return (false);
        host++;
    }
    return (true);
}

#define __READ_FLAG 0
#define __WRITE_FLAG 1

static
bool wait_socket_ready_POLL(int sockfd, int timeout, int read_write_flag)
{
    assert(sockfd > 0);
    assert(timeout >= 0);
    assert(read_write_flag == __READ_FLAG || read_write_flag == __WRITE_FLAG);

    if (timeout == 0) {
    return false; // TIMEOUT!
    }

    struct pollfd wait_fd;
    wait_fd.fd = sockfd;

    if (read_write_flag == __READ_FLAG) { // read wait
        wait_fd.events = POLLIN;
    } else if (read_write_flag == __WRITE_FLAG) { // write wait
        wait_fd.events = POLLOUT;
    }

    errno = 0;
    int r = ::poll(&wait_fd, 1, timeout*1000);

    if (r == 0) {
        return false;  // TIMEOUT, A value of 0 indicates
                       // that the call timed out and
                       // no file descriptors have  been selected.
    }

    if (r < 0) {
        return false;  // ERROR, On  error,  -1  is  returned, 
                       // and errno is set appropriately
    }

    // 2004.05.27 
    if (wait_fd.revents & (POLLERR | POLLHUP)) {
        return false;
    }

    if ((read_write_flag == __READ_FLAG && (wait_fd.revents & POLLIN)) ||
    (read_write_flag == __WRITE_FLAG && (wait_fd.revents & POLLOUT)))
    {
        if (wait_fd.revents & POLLERR) {
            return false;
        }

    return true; 
    }

    assert(0); // ������� �� �Ǵµ�...

    return false;
}

static
bool wait_socket_ready_SELECT(int sockfd, int timeout, int read_write_flag)
{
    assert(sockfd > 0);
    assert(timeout >= 0);
    assert(read_write_flag == __READ_FLAG || read_write_flag == __WRITE_FLAG);

    // connect ������, write_select�� �ؼ� connect�� ���� ������ ��ٸ�.
    fd_set wfds; FD_ZERO(&wfds);
    fd_set rfds; FD_ZERO(&rfds);
    fd_set efds; FD_ZERO(&efds);

    if (timeout == 0) {
// DEBUG_PRINT("timeout\n");
        return false; // TIMEOUT!
    }

    if (read_write_flag == __READ_FLAG) { // read wait
        FD_SET(sockfd, &rfds);
    } else if (read_write_flag == __WRITE_FLAG) { // write wait
        FD_SET(sockfd, &wfds);
    }
    FD_SET(sockfd, &efds);

    struct timeval tv;
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

//    int EAGAIN_count = 0;
// try_select_again:

    errno = 0;
    int r = ::select(sockfd+1, &rfds, &wfds, &efds, &tv); // WAIT
    // int r = ::select(sockfd+1, &rfds, &wfds, &efds, &tv); // WAIT

    if ((read_write_flag == __READ_FLAG && FD_ISSET(sockfd, &rfds)) ||
        (read_write_flag == __WRITE_FLAG && FD_ISSET(sockfd, &wfds)))
    {
        // --------------------------------------------------------------
        // 2003/12/27 EAGAIN �� ��Ȳ�� ������ ��Ȳ�̹Ƿ�, read/write ��
        //            �õ��� �� �ֵ��� true�� �����Ѵ�.
        // --------------------------------------------------------------
        if (FD_ISSET(sockfd, &efds) == 0 && errno == EAGAIN /* 11 */) {
            // ������ �ƴϸ鼭, Resource temporarily unavailable �� ������
            // DEBUG_PRINT("try_select_again: errno=%d\n", errno);

         // if (EAGAIN_count++ > 10) {
         //     return false;
         // }

         // pth_yield(NULL);
         // goto try_select_again;
  
            return true;
        }

        // 2003/12/02 exception handling added
        if (FD_ISSET(sockfd, &efds) || errno != 0) {
            DEBUG_PRINT("efds is set:%d, errno:%d, r:%d\n",
               (int) FD_ISSET(sockfd, &efds), errno, r);
            return false;
        }

    // assert(r == 1);

        if (errno != 0) {
            DEBUG_PRINT("errno[%d] != 0, r:%d\n", errno, r);
        }

        return true; 
    }

    if (r == 0 && errno == 0) {
        // DEBUG_PRINT("r == 0 && errno == 0, return false\n");
        return false;
    }

    // printf("r:%d, errno:%d, errstr:%s\n", r, errno, strerror(errno));
    if (! ((r == 0  && errno == 11) || (r == -1 && errno != 0))) {
        DEBUG_PRINT("r=%d, errno=%d, error=%s\n", r, errno, strerror(errno));
    }
    assert((r == 0  && errno == 11) || (r == -1 && errno != 0));

    // DEBUG_PRINT("return false; // TIMEOUT\n");

    return false; // TIMEOUT
}


static
bool wait_socket_ready(int sockfd, int timeout, int read_write_flag)
{
  if (0) {
    return wait_socket_ready_SELECT(sockfd, timeout, read_write_flag);
  }

  if (1) {
    return wait_socket_ready_POLL(sockfd, timeout, read_write_flag);
  }
}


void PthSocket::create(const char *remoteHost, int port,
                       int timeout) // default = 0
{
    assert(remoteHost != NULL);
    assert(port >= 0);

    // DEBUG_PRINT("Client ClsTCP(%s,%d)\n", remoteHost, port);

    this->init();

    InAddr addr;
  if (! __isNumeric(remoteHost)) {
    HostEnt *hostptr = gethostbyname(remoteHost);
    if (hostptr == NULL) {
        DEBUG_PRINT("ClientClsTCP: gethostbyname(%s) fail\n", remoteHost);
        this->error = true;
        strcpy(this->errstr, "ClientClsTCP: gethostbyname() fail");
        return;
    }
    (void) memcpy(&addr.s_addr, hostptr->h_addr, sizeof (addr.s_addr));
  } else {
    addr.s_addr = inet_addr(remoteHost);
  }

    SockAddrIn serv_addr;
    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, &addr.s_addr, 4);
    serv_addr.sin_port = htons(port);

    if ((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    DEBUG_PRINT("ClientClsTCP: socket() fail: %d:%s\n",
             errno, strerror(errno));
    this->error = true;
    strcpy(this->errstr, "PthSocket: socket() fail");
    return;
    }

    _set_NonBlock(this->sockfd);

  if (0) { // Client Socket������ SO_REUSEADDR�� �ʿ� ����. (??)
    int opt = 1;
    if (setsockopt(this->sockfd,
       SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
    DEBUG_PRINT("setsockopt(SO_REUSEADDR) error.\n");
    this->error = true;
    strcpy(this->errstr, "setsockopt(SO_REUSEADDR) error");
    return;
    }
  }

  if (0) { // �� �ʿ��Ѱ�?
    // setsockopt(SO_KEEPALIVE) introduced
    int opt = 0;
    if (setsockopt(this->sockfd, SOL_SOCKET, SO_KEEPALIVE,
       (char *)&opt, sizeof(opt)) < 0)
    {
    DEBUG_PRINT("setsockopt(SO_KEEPALIVE) error.\n");
    this->error = true;
    strcpy(this->errstr, "setsockopt(SO_KEEPALIVE)");
    return;
    }
  }

    errno = 0;

    // int r = pth_connect(this->sockfd,
    //     (SockAddr *)&serv_addr,sizeof(serv_addr));
    int r = ::connect(this->sockfd, (SockAddr *)&serv_addr,sizeof(serv_addr));

    if (r == 0) {
// DEBUG_PRINT("ready\n");
        // ��ٷ� connect ����
        this->error = false;
        strcpy(this->ip_addr, inet_ntoa(serv_addr.sin_addr));
        return;
    } else if (r < 0 && errno == EINPROGRESS) {
        bool ready = false;

        if (timeout == 0) {
            ready = wait_socket_ready(this->sockfd, 1000000, __WRITE_FLAG);
        } else {
            ready = wait_socket_ready(this->sockfd, timeout, __WRITE_FLAG);
        }

        if (ready) {
            // ��ٷȴٰ� connect ����
// DEBUG_PRINT("errno:%d, r:%d\n", errno, r);
            this->error = false;
            strcpy(this->ip_addr, inet_ntoa(serv_addr.sin_addr));
            return;
        } else {
            // pth_yield(NULL);
            // ������ ���
            this->error = true;
            ::close(this->sockfd);
            this->sockfd = -1;
            strcpy(this->errstr, "pth_connect() timeout");
            return;
        }
    } else {
        // ������ �� ������.
        ::close(this->sockfd);
        this->error = true;
        strcpy(this->errstr, "pth_connect() failed\n");
    }
}

PthSocket::PthSocket(const string &remoteHost, int port,
                    int timeout) // default = 0
{
    this->create(remoteHost.c_str(), port, timeout);
}

PthSocket::PthSocket(char *remoteHost, int port,
                    int timeout) // default = 0
{
    this->create(remoteHost, port, timeout);
}

int _set_Linger(int sock_fd, int sec)
{
    int optval[2];
        optval[0] = 1;        // LINGER_ON
        optval[1] = sec;        // SEC

    int ret = setsockopt(sock_fd, SOL_SOCKET,
        SO_LINGER, (const char *)optval, (size_t)2 * sizeof(int));

    return ret;
}

#ifdef TIME_DEBUG
std::map<int,int> time_count;

time_t TIME(int line)
{
    if (time_count.find(line) == time_count.end()) {
        time_count[line] = 0;
    } else {
        time_count[line] += 1;

        if (time_count[line] % 5) {
            DEBUG_PRINT("line:%d, count:%d\n", line, time_count[line]);
        }
    }

    return time(NULL);
}
#else
  #define TIME(x) time(NULL)
#endif // TIME_DEBUG

PthSocket *PthSocket::accept(int timeout) // default = 0
{
    // DEBUG_PRINT("Listening...\n");

    SockAddrIn cli_addr;

    SockLen cli_len = sizeof(cli_addr);

    time_t t_start = TIME(__LINE__);
    int new_sockfd = -1;

    int t_rest = timeout; // timeout�� �����Ͽ� ��ٸ� �� �ִ� �ʱ���
    while (1) {
        bool ready = false;
        if (timeout > 0) { // timeout == 0 �̸�, ������ ��ٸ����� ��.
            ready = wait_socket_ready(this->sockfd, t_rest, __READ_FLAG);
        } else {
            ready = wait_socket_ready(this->sockfd, 1000000, __READ_FLAG);
        }

        if (! ready) { // TIMEOUT
            // pth_yield(NULL);
            return NULL;
        }

        errno = 0;

        //static PthLock accept_lock;
        
        //accept_lock.lock();

        //new_sockfd = pth_accept(this->sockfd,(SockAddr*)&cli_addr,&cli_len);
        new_sockfd = ::accept(this->sockfd, (SockAddr *)&cli_addr, (socklen_t*)&cli_len);

        //accept_lock.unlock();

        if (new_sockfd < 0 && errno == EAGAIN) {
            t_rest = timeout - (TIME(__LINE__) - t_start);
            if (timeout > 0 && t_rest <= 0) {
                DEBUG_PRINT("PthSocket: accept() fail: %s\n", strerror(errno));
                // pth_yield(NULL);
                return NULL;
            }
            else {
                // Pth:yield();
                // pth_yield(NULL);
                continue;
            }
        } else if (new_sockfd < 0) {
            DEBUG_PRINT("PthSocket: accept() fail: %s\n", strerror(errno));
            // pth_yield(NULL);
            return NULL;
        } else if (new_sockfd > 0) {
            break; 
        }
    }

    _set_NonBlock(this->sockfd);
    _set_Linger(new_sockfd, 0);

    PthSocket *pNewSock = new PthSocket();
    if (pNewSock == NULL || pNewSock->error) {
        DEBUG_PRINT("ServerPthSocket: new child PthSocket() fail\n");
        return NULL;
    }

    pNewSock->sockfd = new_sockfd;
    strcpy(pNewSock->ip_addr, inet_ntoa(cli_addr.sin_addr));

    return pNewSock;
}

// -----------------------------

void PthSocket::lookahead_init()
{
    this->LookAhead_len = 0;
    this->LookAhead_capacity = 512;

    // capacityũ�� ��ŭ �޸𸮸� ��Ƶд�.
    this->LookAhead_bytes =
        (char *) malloc(this->LookAhead_capacity * sizeof(char) + 1);

    assert(this->LookAhead_len == 0);
    assert(this->LookAhead_capacity > 0);
}

void PthSocket::lookahead_destroy()
{
     free(this->LookAhead_bytes);
}

int PthSocket::lookahead_find_eol()
{
    // Ư�� ������ ������ ���ۿ��� '\n'�� ã�Ƴ���.
    // ������ ���۳��� ù��° '\n'�� ������� ��ġ�� �����Ѵ�
    // '\n'�� ������ -1�� ����

    // ����: LookAhead_bytes���� '\0'�� �ƴ� ���ڸ� ����.

    assert(this->LookAhead_capacity > 0);
    assert(this->LookAhead_bytes != NULL);
    assert(this->LookAhead_len >= 0);
    assert(this->LookAhead_capacity >= this->LookAhead_len);

    // ��Ʈ�� �˻����� '\0'������ �ؾ� ��. ��Ʈ���� ���� ��ŷ��.

// DEBUG_PRINT("this->LookAhead_len:%d, this->LookAhead_capacity:%d\n",
//      this->LookAhead_len, this->LookAhead_capacity);

    this->LookAhead_bytes[this->LookAhead_len] = '\0';

    char *p = strchr(this->LookAhead_bytes, '\n');

    if (p == NULL) { /* '\n' �߰ߵ��� �ʾ��� */
        return -1;
    }

    assert((p - this->LookAhead_bytes) >= 0);
    assert((p - this->LookAhead_bytes) <= this->LookAhead_len);

    // '\n'�� ������� ��ġ�� �����Ѵ� 
    return (p - this->LookAhead_bytes);
}

char *PthSocket::lookahead_ptr0()
{
    return this->LookAhead_bytes;
}

int PthSocket::lookahead_len()
{
    return this->LookAhead_len;
}

void PthSocket::lookahead_del_front(int n)
{
    // Ư�� ���Ͽ� �Ҵ��  ������ ���ۿ���, ó�� n����Ʈ�� �����. 
    assert(n > 0);
    assert(n <= this->LookAhead_len);
    assert(this->LookAhead_capacity > 0);

    memmove(this->LookAhead_bytes,
            this->LookAhead_bytes + n,
            this->LookAhead_len - n);

    this->LookAhead_len -= n; // ������ ���̰� �پ�� 

    assert(this->LookAhead_capacity > 0);
}

void PthSocket::lookahead_add(char *ptr, int n)
{

    // Ư�� ������ ������ ���ۿ� ptr�� ����Ű�� �ִ� n����Ʈ�� �߰��ϱ� 
    assert(ptr != NULL);
    assert(n > 0);

    assert(this->LookAhead_capacity > 0);

    // '\0'���� 
    if (1) {
        int null_count = 0;
        // �Էµ� ptr[0..n]�ӿ� '\0'��  ��� ����. �װ͵��� �������� �ٲ�.
        for (int i = 0; i < n; i++) {
            if (ptr[i] == '\0') {
                ptr[i] = ' ';
                null_count++;
            }
        }
        if (null_count > 0) {
            ptr[n] = '\0';
        }
    }

    if (this->LookAhead_len + n <= this->LookAhead_capacity) {
        // ���� ������ ���� ������ ����ϸ�, �ڿ� �ٷ� �߰��Ѵ�. 
        assert(this->LookAhead_capacity > 0);

        memcpy(this->LookAhead_bytes + this->LookAhead_len, ptr, n);

        assert(this->LookAhead_capacity > 0);

        this->LookAhead_len += n;

        assert(this->LookAhead_capacity > 0);
    } else {
        // ������ �����ϸ� realloc()���� ������ �Ҵ�ް� �߰��Ѵ�. 

        assert(this->LookAhead_capacity > 0);

        this->LookAhead_bytes = (char*)
             realloc(this->LookAhead_bytes, this->LookAhead_len + n + 1);

        assert(this->LookAhead_capacity > 0);

        this->LookAhead_capacity = this->LookAhead_len + n;

        assert(this->LookAhead_capacity > 0);

        memcpy(this->LookAhead_bytes + this->LookAhead_len, ptr, n);

        this->LookAhead_len += n;

        assert(this->LookAhead_capacity > 0);
     }

     assert(this->LookAhead_len >= n);
     assert(this->LookAhead_capacity >= this->LookAhead_len);
}

int PthSocket::lookahead_eol_count()
{
    // Ư�� ������ ������ ���ۿ��� '\n'�� ������ ����
    // ����: LookAhead[].bytes���� '\0'�� �ƴ� ���ڸ� ����.

    int count = 0;
    for (int i = 0; i < this->LookAhead_len; i++) {
        if (this->LookAhead_bytes[i] == '\n') {
            count++;
        }
    }

    return count;
}

int PthSocket::read(char *buf, int size,
                   int timeout) // default = 0
{
    // ����: buf���� �ݵ�� size��ŭ �޸𸮰� �Ҵ�Ǿ� �־�� ��.

    assert(this->sockfd >= 0);
    assert(buf != NULL);

    time_t t_start = TIME(__LINE__);

    int curSize = 0;
    while (1) {
        bool ready = false;

        // DEBUG_PRINT("is_ready()\n");

        if (timeout == 0) {
            ready = wait_socket_ready(this->sockfd, 1000000, __READ_FLAG);
        } else {
            int t_rest = timeout - (TIME(__LINE__) - t_start);
            if (t_rest <= 0) {
                // eek add 
                this->error = true;
                return -1;
            }
            ready = wait_socket_ready(this->sockfd, t_rest, __READ_FLAG);
        }

        if (! ready) {
            this->error = true;
            return -1;
        }

        errno = 0;

        assert(curSize >= 0 && curSize < size);

        // int n = // pth_read(this->sockfd, &buf[curSize], size - curSize);
        int n = ::read(this->sockfd, &buf[curSize], size - curSize);

        if (n <= 0 && errno == EAGAIN) {
            assert(curSize == 0);
            // Pth::yield();
            // pth_yield(NULL);
            continue;
        }

        if (n == 0 || /* read()�� ����� n == 0�̸� EOF�� �ǹ��Ѵ�. */
            errno == EBADF || /* Bad File Descriptor */
            errno == ECONNRESET || /* Connection reset by peer */
            errno == ENOTCONN ||   /* Transport endpoint is not connected */
            errno == ECONNABORTED || /* Software caused connection abort */
            errno == EINVAL || /* Invalid */
            errno == EIO || /* IO FAIL */
            errno == EPIPE || /* PIPE FAIL */
            0
           )
        {
           this->error = true;
            n = 0;
            return n;
        }

        if (n < 0) {
            // n�� 0���� ������ � �����ε� errno�� ���� �ִ�.
            // errno == EAGAIN�̸� ���� �а� �׷��� ������ ������ close�ϸ� ��.
            this->error = true;
            return -1;
        }

        // ���� n ����Ʈ��ŭ�� �о� �� ������.
        assert(n > 0);

        curSize = curSize + n;

        assert(curSize >= 0 && curSize <= size);

        this->error = false;
        return curSize;
    }
}

string PthSocket::read_line(int timeout) // default = 0
{
    string result = "";

    char buf[BUFSIZ];

    int r = this->readline(buf, timeout);

    if (r >= 0) {
        result = buf;
    }

    return result;
}

int PthSocket::read_line(string &result, int timeout)
{
    char buf[BUFSIZ];
    int r = this->readline(buf, timeout);

    if (r >= 0) {
        buf[r] = '\0';
        result = buf;
    }

    return r;    
}

void PthSocket::write_line(const string &line,
                       int timeout) // default = 0
{
    assert(timeout == timeout); // unused timeout

    this->write((char*) line.c_str(), line.size(), timeout);
}

size_t PthSocket::write_line(const void *buf, size_t size, int timeout)
{
    assert(timeout == timeout); // unused timeout

    return this->write((char*) buf, size, timeout);
}

int PthSocket::readline(char *buf, int timeout /*= 0*/) 
{
    /* sizeof(buf) == BUFSIZ */

    // ����: buf���� �ݵ�� BUFSIZ��ŭ �޸𸮰� �Ҵ�Ǿ� �־�� ��.

    // Ư�� �������� ���� �ڷḦ �о ���� �� ������
    // buf�� strcpy()�� �ְ�, �� ���̸� �����Ѵ�.

    static char buf_tmp[BUFSIZ+1]; // static �ؾ� ��. ���ÿ� ������ �ʰ� 

    assert(this->sockfd >= 0);
    assert(buf != NULL);

    int eol_pos = this->lookahead_find_eol();
    if (eol_pos >= 0) {
        memcpy(buf, this->lookahead_ptr0(), eol_pos+1);
        buf[eol_pos+1] = '\0';

        assert(this->lookahead_len() >= eol_pos+1);
        this->lookahead_del_front(eol_pos+1);

        // DEBUG_PRINT("read from lookahead: [%s]\n", buf);
 
        this->error = false;
        return eol_pos+1;
    }

    assert(this->lookahead_eol_count() == 0);

  {
    // '\n'���� ���� ��ü�� �� á�� ���, ���� read���� �ʰ�,
    //  ������ ������ '\n'���� �����Ѵ�.

    if (this->lookahead_len() >= BUFSIZ) {
        // ������ ������ �߶� �����ؾ� ��
        // �߸� ���ο��� '\n'�� ��� ���� ����
        eol_pos = BUFSIZ/2 - 1; /* 2048 - 1 == 2047 */

        memcpy(buf, this->lookahead_ptr0(), eol_pos+1);
        buf[eol_pos+1] = '\0';

        assert(this->lookahead_len() >= eol_pos+1);
        this->lookahead_del_front(eol_pos+1);

        this->error = false;
        return eol_pos+1;
    }
  }

    // ������ ���ۿ� ������ ä ������, ���� �о �� �� �̻���
    // ���ۿ� ä�� �������� �õ��Ѵ�.
    // BUFSIZ�̻��� LookAhead ���ۿ� �׾� ���� �ʴ´�.
    // �о���� ���ۿ� '\0'�� ���� �� ����. --> �������� �ٲ�.

    assert(timeout == timeout);
    time_t t_start = TIME(__LINE__);

    while (1) {
        bool ready = false;
        //  ready = wait_socket_ready(this->sockfd, 1000000, __READ_FLAG);

/// ????? �̺κ��� �� �ּ� ó�� �ߴ°�??????????
        if (timeout == 0) {
            // ������ ��ٸ��� ���, ���� wait_ready�� �� �ʿ� ����.
            ready = wait_socket_ready(this->sockfd, 1000000, __READ_FLAG);
        } else {
            int t_rest = timeout - (TIME(__LINE__) - t_start);
            if (t_rest <= 0) {
                // eek add 
                this->error = true;
                return -1;
            }
            ready = wait_socket_ready(this->sockfd, t_rest, __READ_FLAG);
        }
/// ????? �̺κ��� �� �ּ� ó�� �ߴ°�??????????

      {
        // 2003/03/17 ���� ũ�� üũ 
        //   '\n'���� ���� ��ü�� �� á�� ���, ���� read���� �ʰ�,
        //   ������ �Ϻθ� '\n'���� �����Ѵ�.

        if (this->lookahead_len() >= BUFSIZ-1) {
            // ������ ������ �߶� �����ؾ� ��
            // �߸� ���ο��� '\n'�� ��� ���� ����
            eol_pos = BUFSIZ-2; /* 1024 - 2 == 1022 */

            memcpy(buf, this->lookahead_ptr0(), eol_pos+1); // 0 ~ 1022
            buf[eol_pos+1] = '\0'; //1023

            assert(this->lookahead_len() >= eol_pos+1);
            this->lookahead_del_front(eol_pos+1);

            this->error = false;
            return eol_pos+1;
        }
      }

        assert(BUFSIZ-this->lookahead_len() > 0);

        if (! ready) {
            this->error = true;
            return -1;
        }

        errno = 0;
        // int n = pth_read(this->sockfd,buf_tmp,BUFSIZ-this->lookahead_len());
        int n = ::read(this->sockfd, buf_tmp, BUFSIZ-this->lookahead_len());

        if (n <= 0 && errno == EAGAIN && this->lookahead_len() > 0) {
            int t_diff1 = (int)(TIME(__LINE__) - t_start);

            // timeout�� �̳��� '\n'���� ����Ÿ�� ���ۿ�
            // ��� �׿� ���� ��쿡��, �� �� ���� flush�� ���� �ش�. 
            if (timeout > 0 && t_diff1 > timeout) {
                this->error = true; // eek
                return -1; // �� �о���.
            } else if (timeout == 0) {
                // Pth::yield();
                // pth_yield(NULL);
                continue;
            } else {
                // �̶��� ���?
            }
        }


        if (n == 0 || /* read()�� ����� n == 0�̸� EOF�� �ǹ��Ѵ�. */
            errno == EBADF || /* Bad File Descriptor */
            errno == ECONNRESET || /* Connection reset by peer */
            errno == ENOTCONN ||   /* Transport endpoint is not connected */
            errno == ECONNABORTED || /* Software caused connection abort */
            errno == EINVAL || /* Invalid */
            errno == EIO || /* IO FAIL */
            errno == EPIPE || /* PIPE FAIL */
            0
           )
        {
            // 2004/08/03 ������ �����µ�, buffer�� ���� ������...
            if (this->lookahead_len() > 0) {
                // lookahead ��ü�� ������.

                int lookahead_len = this->lookahead_len();
                memcpy(buf, this->lookahead_ptr0(), lookahead_len);
                buf[lookahead_len] = '\0';

                this->lookahead_del_front(lookahead_len);

                this->error = false;
                return lookahead_len;
            }

            this->error = true;
            n = 0;
            return n;
        }

        if (n < 0) {
            // n�� 0���� ������ � �����ε� errno�� ���� �ִ�.
            // errno == EAGAIN�̸� ���� �а� �׷��� ������ ������ close�ϸ� ��.
            this->error = true;
            return -1;
        }

        // ���� n ����Ʈ��ŭ�� �о� �� ������.
        assert(n > 0);

        // �о n����Ʈ�� �켱 ������ ���ۿ� �ְ�, �� �Ŀ� ù �� ���� 
        // ã�Ƽ� buf�� �����ϰ� �� ���̸� �����Ѵ�. 

        assert(buf != NULL); // ���Ͻ�������� ���� 
        assert(this->lookahead_ptr0() != NULL);
        assert(this->lookahead_len() >= 0);
        assert(buf_tmp != NULL);

        assert(this->LookAhead_capacity > 0);
        this->lookahead_add(buf_tmp, n);

        // ���� ���� ���ۿ��� newline�� ã���� �� ���θ� �߶� ���� 
        int eol_pos = this->lookahead_find_eol();
        if (eol_pos >= 0) {
            memcpy(buf, this->lookahead_ptr0(), eol_pos+1);
            buf[eol_pos+1] = '\0';

            assert(this->lookahead_len() >= eol_pos+1);
            this->lookahead_del_front(eol_pos+1);

            this->error = false;
            return eol_pos+1;
        }
    }
}

int PthSocket::write(const char *buf, int len, int timeout)
{
    assert(buf != NULL);
    assert(len >= 0);

    int len_tmp = len;
    int n = 0;

    // time_t t1 = time(NULL);
    // time_t t2 = time(NULL);
    // time_t t3 = time(NULL);
    // time_t t4 = time(NULL);
    errno = 0;
    // int n = pth_write(this->sockfd, buf, len);

    char *pBuf = (char *)&buf[0];

    time_t t0 = time(NULL);

  write_again:
    assert(pBuf < (&buf[0] + len));
    int n_tmp = ::write(this->sockfd, pBuf, len_tmp); // Non-Block Socket��.

    if (n_tmp > 0) {
        assert(len_tmp >= n_tmp);
        n += n_tmp;
    }

    // time_t t5 = time(NULL);
    // time_t t6 = time(NULL);
    // time_t t7 = time(NULL);
    // time_t t8 = time(NULL);

    if (n_tmp != len_tmp) {
        if (
            errno == EBADF || /* Bad File Descriptor */
            errno == ECONNRESET || /* Connection reset by peer */
            errno == ENOTCONN ||   /* Transport endpoint is not connected */
            errno == ECONNABORTED || /* Software caused connection abort */
            errno == EINVAL || /* Invalid */
            errno == EIO || /* IO FAIL */
            errno == EPIPE || /* PIPE FAIL */
            0
           )
        {
            /* ERROR */
            this->error = true;
            // goto write_end; // �ʿ� ����.
        } else if (n_tmp == -1 && errno == EAGAIN) {
            /* EAGAIN */
            // assert(len_tmp > n_tmp);
            // len_tmp -= n_tmp;
            // Pth::yield();
            int t_diff = (int) (time(NULL) - t0);

            // 2003-05-27 Write ���н� timeout��ŭ ��õ� ��.
            if (timeout == 0) {
                // Timeout�� 0�̸�, ������ �ݺ��Ǵ� ���� �ִ��� ��õ�
                // pth_yield(NULL);
                __usleep(1);
                goto write_again;
            } else if (timeout != 0 && t_diff <= timeout) {
                // Timeout�� ���õǾ� ������, ������ �ð���ŭ ��õ�
                // pth_yield(NULL);
                __usleep(1);
                goto write_again;
            } else {
                // �׿��� ���� ������� �Ǵ�.
                this->error = true; // FIXME: �� �̰��� ������?
                goto write_end;
            }
        } else {
            /* Is it normal or strange?? */
            assert(len_tmp > n_tmp);
            len_tmp -= n_tmp;

            // n����Ʈ��ŭ �� ��Ȳ��.
            assert(len_tmp == len - n);

            pBuf = (char*) buf + n;

            int t_diff = (int) (time(NULL) - t0);

            // 2003-05-27 Write ���н� timeout��ŭ ��õ� ��.
            if (timeout == 0) {
                // Timeout�� 0�̸�, ������ �ݺ��Ǵ� ���� �ִ��� ��õ�
                // pth_yield(NULL);
                __usleep(1);
                goto write_again;
            } else if (timeout != 0 && t_diff <= timeout) {
                // Timeout�� ���õǾ� ������, ������ �ð���ŭ ��õ�
                // pth_yield(NULL);
                __usleep(1);
                goto write_again;
            } else {
                // �׿��� ���� ������� �Ǵ�.
                this->error = true; // FIXME: �� �̰��� ������?
                goto write_end;
            }
        }
    } else {
        /* OK. Sent n bytes */
        assert(n == len);
    }

  write_end:

    return n;
}

void PthSocket::close()
{
    if (this->sockfd >= 0) {
        ::close(this->sockfd);
     // ::shutdown(this->sockfd, 2);
         this->sockfd = -1;
    }
}

char *PthSocket::peer_addr()
{
    return this->peer_name(); // FIXME: �޸� ��ũ�� ����.
}

string PthSocket::peeraddr()
{
    char buf[128];
    return string((char*) this->peer_name(buf));
}

typedef union _SockAddr {
    struct sockaddr s;
    struct sockaddr_in i;
} SockAddr_t;

string PthSocket::peername()
{
    char buf[128];
    return string(this->peer_name(buf));
}

// peername()���� ȣ�������� free�� �� ��� �ϰ�,
// peername(buf) �� ȣ�� ������ free���� �ʿ䰡 ����.
char *PthSocket::peer_name(char *ipaddr_buf) // default = NULL
{
    // Ư�� ���Ͽ� ����� ���� ȣ��Ʈ�� IP�� �����Ѵ�.

    char *ipaddr = (ipaddr_buf == NULL) ?
                       (char *) malloc(32): ipaddr_buf;

    ipaddr[0] = '\0';

    SockAddr_t peer;
    SockLen peerlen; /* int peerlen; */
    peerlen = (sizeof(struct sockaddr) > sizeof(struct sockaddr_in)) ?
              sizeof(struct sockaddr): sizeof(struct sockaddr_in);

    int r = getpeername(sockfd, &(peer.s), (socklen_t*)&peerlen);
    if (r != 0) {
       if (
            errno == EBADF || /* Bad File Descriptor */
            errno == ECONNRESET || /* Connection reset by peer */
            errno == ENOTCONN ||   /* Transport endpoint is not connected */
            errno == ECONNABORTED || /* Software caused connection abort */
            errno == EINVAL || /* Invalid */
            errno == EIO || /* IO FAIL */
            errno == EPIPE || /* PIPE FAIL */
            0
          )
        {
             /* DO NOTHING */
        }

        return NULL;
    }

    strcpy(ipaddr, inet_ntoa(peer.i.sin_addr));

    return ipaddr;
}

int sock_get_port(SockAddr_t *sa)
{
    struct sockaddr_in *sin = (struct sockaddr_in *) sa;
    return(sin->sin_port);
}

int PthSocket::peerport()
{
    /* Ư�� ���Ͽ� ����� ���� ȣ��Ʈ�� ��Ʈ ��ȣ�� �����Ѵ�. */
    SockAddr_t peer;

    SockLen peerlen = (sizeof(struct sockaddr) > sizeof(struct sockaddr_in)) ?
              sizeof(struct sockaddr): sizeof(struct sockaddr_in);

    int r = getpeername(sockfd, &(peer.s), (socklen_t*)&peerlen);

    if (r != 0) {
        return 0;
    }

    int port = sock_get_port(&peer);

    return port;
}

int PthSocket::myport()
{
    /* Ư�� ���Ͽ� ����� �ڱ� �ڽ��� ��Ʈ ��ȣ�� �����Ѵ�. */
    SockAddr_t peer;

    SockLen peerlen = (sizeof(struct sockaddr) > sizeof(struct sockaddr_in)) ?
              sizeof(struct sockaddr): sizeof(struct sockaddr_in);

    int r = getsockname(sockfd, &(peer.s), (socklen_t*)&peerlen);

    if (r != 0) {
        return 0;
    }

    int port = sock_get_port(&peer);

    return port;
}

#ifdef PTHSOCKET_TEST

int main()
{
    PthSocket sock("wallstmarketnews.biz", 25, 100);
    if (sock.isError()) {
        DEBUG_PRINT("error: %s\n", sock.errstr);
    } else {
        DEBUG_PRINT("connect success\n");
    }
    return 0;
}

#endif // PTHSOCKET_TEST

#ifdef _PTHSOCKET_TEST
int main()
{
    int port = 9110;

    DEBUG_PRINT("new PthSocket(%d)\n", port);

    PthSocket *server_sock = new PthSocket(port);

    while (1) {
        PthSocket *client_sock = server_sock->accept(5);
        if (client_sock == NULL || client_sock->isError()) {
            DEBUG_PRINT("try accept again\n");
            // Pth::sleep(1);
            if (client_sock != NULL) { delete client_sock; }
            continue;
        }

        client_sock->write("WELCOME\n", 8);
        if (client_sock->isError()) {
            client_sock->close();
            delete client_sock;
            continue;
        }

        while (1) {
            char buf[BUFSIZ];
            int r = client_sock->readline(buf, 10);
            if (client_sock->isError()) {
                DEBUG_PRINT("timeout or socket_error\n");
                client_sock->close();
                break;
            }

            for (int i = 0; i < r; i++) {
                buf[i] = toupper(buf[i]);
            }

            client_sock->write(buf, r);
            if (client_sock->isError()) {
                client_sock->close();
                break;
            }

            if (strncmp(buf, "QUIT", 4) == 0) {
                client_sock->close();
                break;
            }
        }

        delete client_sock;
    }

    return 0;
}
#endif // PTHSOCKET_TEST

