
#ifndef __CSCHEDULERTHREADH__
#define __CSCHEDULERTHREADH__

#include "CPolicyItem.h"
#include "SCThreadObserver.h"

//! item�� ��å�� �����ϴ� �����췯 ������ Ŭ����
/**
 *	item�� ���� ���� �ֱ� �� ��� ���� ���� �ֱ⸦ �˻��Ͽ�, ���� �ֱⰡ �� item�� ���ؼ�
 *	���� ���� �����忡�� ���� ������ ��û�ϰ�, �ش� �����ۿ� ���� ��å�� �����ϴ� Ŭ����.
 */
class CSchedulerThread : public OpenThreads::Thread, public ThreadReporter {

public:
	/**
	 *	������
	 *	@param ������ ������.
	 *	@param element number �ǹ� ����.
	 */
    CSchedulerThread(void *_data, int numElts) : OpenThreads::Thread(), 
	ThreadReporter(),
        m_data(_data), _numElts(numElts), _quitflag(false) { pthread_mutex_init(&m_lock, NULL); };
	/** �Ҹ��� */
    virtual ~CSchedulerThread() { pthread_mutex_destroy(&m_lock); };
	/**
	 *	������ �⵿ �޽��. �� �����Ͻ� ������ �����ϴ� �޽���̴�.
	 */
    virtual void run();
	/** thread ��� �޽�� */
	void lock();
	/**	thread ��� ���� �޽��. */
	void unlock();
	/** 
	 *	CItem�� �����ϴ� �ν��Ͻ� ������ instance name queue�� �����Ͽ�
	 *	item ��å Ŭ����(CPolicyItem)�� �����ϴ� �޽��
	 *	@param instance name queue�� ������ CPolicyItem pointer.
	 *	@param �ν��Ͻ� ������ �����ϴ� CItem pointer.
	 */
	void addInstanceToPollItem(CPolicyItem *pollitem, CItem *item);
	/**
	 *	thread ���� ��û �޽��.
	 */
    void quit();

private:
	void *m_data;	/**< ������ �⵿�� �ʿ��� ������ */

    int _numElts;	/**< �ǹ̾���. */
    volatile bool _quitflag;	/**< ������ ���� �÷��� */
	pthread_mutex_t m_lock;	/**< ������ ��� Ű */
};

void startSchedulerThread(void *data);


#endif /* __CSCHEDULERTHREADH__ */
