
#ifndef __CSOCKETWORKERTHREADH__
#define __CSOCKETWORKERTHREADH__

#include "termio.h"
#include "CAgentEnvVar.h"
#include "CSocketWorker.h"
#include "CProtocolProcessor.h"
#include "CMisc.h"
#include "SCThreadObserver.h"


extern pthread_mutex_t g_session_lock;

#define SC_STREAM_TYPE_EVENT 1
#define SC_STREAM_TYPE_COMMAND 2
#define SC_STREAM_TYPE_SESSION 3

#define TELNET_SE               240 
#define TELNET_NOP              241 
#define TELNET_DATA_MARK        242 
#define TELNET_BRK              243 
#define TELNET_IP               244 
#define TELNET_AO               245 
#define TELNET_AYT              246 
#define TELNET_EC               247 
#define TELNET_EL               248 
#define TELNET_GA               249 
#define TELNET_SB               250 
#define TELNET_WILL             251 
#define TELNET_WONT             252 
#define TELNET_DO               253 
#define TELNET_DONT             254 
#define TELNET_IAC              255 


#define TELNET_ECHO               1 
#define TELNET_SUPPRESS_GO_AHEAD  3 


//! SMS Manager�� SMS Agent�� ����� ����ϴ� Ŭ����
class CSocketWorkerThread : public OpenThreads::Thread, public ThreadReporter, public CSocketWorker {

public:
	/**
	 *	������
	 *	@param SMS Agent ȯ�� ���� ���� Ŭ����.
	 *	@param void data pointer.
	 *	@param ���� ������ ���� ������ �����ϴ� pointer.
	 *	@param element number. �ǹ̾���.
	 *	@param �޽��� ó�� Ÿ��(EVENT REPORT, ACCEPT COMMAND, SESSION STATUS REPORT)
	 */
    CSocketWorkerThread(CAgentEnvVar *envvar, void *_data, bool *_session, int port, int numElts, int type) : OpenThreads::Thread(), ThreadReporter(),
        m_envvar(envvar), m_data(_data), m_session_status(_session), m_port(port), _numElts(numElts), _quitflag(false), m_type(type) { pthread_mutex_init(&m_lock, NULL); };
	/** �Ҹ��� */
    virtual ~CSocketWorkerThread() { pthread_mutex_destroy(&m_lock); };
	/** ������ �⵿ �޽�� */
    virtual void run();
	/**	EVENT REPOPRT METHOD */
	void processEventMessage();
	/** ACCEPT COMMAND FROM SMS MANAGER */
	void processCommandMessage();
	/** REPORT AGENT SESSION STATUS */
	void processSessionStatus();
	/** ������ ��� �޽�� */
	void lock();
	/** ������ ��� ���� �޽�� */
	void unlock();
	/** ������ ���� ��û �޽�� */
    void quit();
	/**
	 *	SMS Manager�� SMS Agent�� �����ϱ� ���� �ʿ��� �α��� ���� ������ ó���ϴ� �޽��.
	 *	@return true if login success, else return false.
	 */
	bool login();

private:
	bool *m_session_status;	/**< socket session status */
	int m_port;	/**< socket listen port */
	int m_type;	/**< �޽��� ó�� Ÿ��(EVENT REPORT, ACCEPT COMMAND, SESSION STATUS REPORT) */
	void *m_data;	/**< data */
	CAgentEnvVar *m_envvar;	/**< SMS Agent ȯ�� ������ �����ϴ� Ŭ���� */

    int _numElts;	/**< �ǹ̾���. */
    volatile bool _quitflag;	/**< ������ ���Ῡ�� �÷��� */
	pthread_mutex_t m_lock;		/**< ������ ��� Ű */
    //OpenThreads::Mutex _quitmutex;
};

void startSocketWorkerThread(CAgentEnvVar *envvar, void *data, bool *b, int port, int type);


#endif /* __CSOCKETWORKERTHREADH__ */
