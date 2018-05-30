
#ifndef __CSYSLOGMONITORTHREADH__
#define __CSYSLOGMONITORTHREADH__

#include "CAgentEnvVar.h"
#include "CMessageFormatter.h"
#include "SCThreadObserver.h"

//! �ý��α׸� ����͸��ϴ� Ŭ����
class CSyslogMonitorThread : public OpenThreads::Thread, public ThreadReporter {

public:
	/**
	 *	������
	 *	@param ������ �⵿�� �ʿ��� data pointer.
	 */
    CSyslogMonitorThread(void *_data, int numElts) : OpenThreads::Thread(), 
	ThreadReporter(),
        m_data(_data), _numElts(numElts), _quitflag(false) { pthread_mutex_init(&m_lock, NULL); };
	/** �Ҹ��� */
    virtual ~CSyslogMonitorThread() { pthread_mutex_destroy(&m_lock); };
	/** ������ �⵿ �޽�� */
    virtual void run();
	/** syslog file pointer�� ���� ��ġ ������ �Ǵ��ϴ� �޽�� */
	void checkFD();
	/**	
	 *	������ syslog �޽����� �־��� item condition�� ���ǿ� �����ϴ��� ���θ� Ȯ���ϴ� �޽��.
	 *	@param	syslog message
	 */
	void checkCondition(char *log);
	/**
	 *	������ syslog �޽����� SMS Manager�� �����ϱ� ���� ������ ���۷� �����ϴ� �޽��.
	 *	@param CItemCondition pointer.
	 *	@param syslog message.
	 *	@see CItemCondition.
	 */
	void sendEvent(CItemCondition *cond, char *log);
	/** ������ ��� �޽�� */
	void lock();
	/** ������ ��� ���� �޽�� */
	void unlock();
	/** ������ ���� ��û �޽�� */
    void quit();

private:
	FILE *m_fd;				/**< Syslog file pointer */
	void *m_data;			/**< data */
	CAgentEnvVar *m_envvar;	/**< SMS Agent ȯ�� ������ �����ϴ� Ŭ���� */ 
	CItem *m_item;			/**< syslog item ���� Ŭ���� */
    int _numElts;			/**< �ǹ� ����. */
	unsigned long m_offset;	/**< syslog file �����͸� ���� ���� ��ġ ���� */
    volatile bool _quitflag;	/**< ������ ���� ��û �÷��� */
	pthread_mutex_t m_lock;	/**< ������ ��� Ű */
	std::string m_filename;	/**< syslog ���ϸ� */
    //OpenThreads::Mutex _quitmutex;
};

void startSyslogThread(void *data, int thread_num);


#endif /* __CSYSLOGMONITORTHREADH__ */
