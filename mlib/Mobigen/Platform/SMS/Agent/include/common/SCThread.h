
#ifndef __SCTHREADH__
#define __SCTHREADH__

#include "CPolicyItem.h"

#include "CCollectorHeader.h"

#include "SCThreadObserver.h"

//! �����췯�� ���� ��û�� item�� ���� ���� ������ �����ϴ� ������.
class SCThread : public OpenThreads::Thread, public ThreadReporter {

public:
	/**
	 *	������
	 *	@param	data pointer.
	 *	@param �ǹ̾���.
	 */
    SCThread(void *_data, int numElts) : OpenThreads::Thread(), 
	ThreadReporter(),
        m_data(_data), _numElts(numElts), _quitflag(false) { pthread_mutex_init(&m_lock, NULL); };
	/** �Ҹ��� */
    virtual ~SCThread() { pthread_mutex_destroy(&m_lock); };
	/** ������ �⵿ ��û �޽�� */
    virtual void run();
	/** ������ ��� �޽�� */
	void lock();
	/** ������ ��� ���� �޽�� */
	void unlock();
	/** ������ ���� ��û �޽�� */
    void quit();
	/**
	 *	���� ������(CCollector)�� �⵿�� ��û�ϴ� �޽��.
	 *	@param ���� ��� ��å item ����.
	 *	@see CCollector, CPolicyItem
	 */
    void invokeCollector(CPolicyItem *pitem);

private:
	void *m_data;	/**< data poiner */

    int _numElts;	/**< �ǹ̾��� */
    volatile bool _quitflag;	/**< ������ ���� ��û �÷��� */
	pthread_mutex_t m_lock;		/**< ������ ��� Ű */
    //OpenThreads::Mutex _quitmutex;
};

void startThreadWorker(void *data, int thread_num);


#endif /* __SCTHREADH__ */
