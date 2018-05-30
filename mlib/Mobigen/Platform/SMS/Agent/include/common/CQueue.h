
#ifndef __CQUEUE_H__
#define __CQUEUE_H__ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <string>

#define MAX_QUEUE_SIZE	10000

/**
 *	����ť�� ��� ������ �����ϴ� ����ü.
 */
typedef struct __elem__
{
	void *d;
	void (*handler)(void *);
	struct __elem__ *next;
	struct __elem__ *prev;
}elem;


//!	���� �����͸� �����ϱ� ���� ����Ʈ ť Ŭ����.
/**
 *	SMS Agent�� �⵿�ϸ鼭 �ʿ��� ���� �����͸� �����ϰ�, �����ϴ� ����Ʈ ť Ŭ����.
 */
class CQueue
{
	private:
		bool m_writable;			/**< ť�� ���� �������� ���� */
		int m_count;				/**< ť�� ����� ������ ���� */
		std::string m_name;			/**< ť �̸� */
		elem *m_head;				/**< ������ ť�� head */
		elem *m_tail;				/**< ������ ť�� tail */
		pthread_mutex_t m_lockkey;	/**< ������ ť�� ����ȭ Ű */
		int type;					/**< ������ ť Ÿ�� */
		/** ť ��� �޽�� */
		void lock();
		/** ť ��� ���� �޽�� */
		void unlock();
		/** ť�� ���� ���� ���� */
		bool isRemove;
	
	public:
		/** ������ */
		CQueue();
		/**
		 *	������.
		 *	@param ť �̸�.
		 */
		CQueue(std::string);
		/** �Ҹ��� */
		virtual ~CQueue();
		/**
		 *	ť �ʱ�ȭ �޽��.
		 */
		void initialize();
		/**
		 *	ť�� ���� ���� ���� ������ ��ȸ�ϴ� �޽��.
		 *	@return true : ���� ����, false : ���� �Ұ���.
		 */
		bool isWritable();
		/**
		 *	ť�� ù��° ��带 ��ȸ�ϴ� �޽��.
		 *	@return ù��° ��� ������.
		 */
		elem *frontNode();
		/**
		 *	�־��� ����� ���� ��� ������ ��ȸ�ϴ� �޽��.
		 *	@param ��� ������.
		 *	@return ��� ������.
		 */
		elem *getNext(elem *e);
		/**
		 *	ť�� ���� ���� ���θ� �����ϴ� �޽��.
		 *	@param true : ���� ����, false : ���� �Ұ���.
		 */
		void setWritable(bool b);
		/**
		 *	ť�� �����ϴ� ��� ��� �� �����͸� �����ϴ� �޽��.
		 */
		void removeAll();
		/**
		 *	ť�� �����͸� �ְ��ϴ� �޽��. FIFOó�� ���� �� ��忡 �߰��Ѵ�.
		 *	@param ������ ������.
		 *	@param �����͸� ������ �� ȣ���� �Լ� ������.
		 */
		void enqueue(void *d, void (*h)(void *));
		/**
		 *	ť�� �����͸� �ְ��ϴ� �޽��. ����ó�� ���� ó�� ��忡 �߰��Ѵ�.
		 *	@param ������ ������.
		 *	@param �����͸� ������ �� ȣ���� �Լ� ������.
		 */
		void push(void *d, void (*h)(void *));
		/**
		 *	ť���� ���� ó���� ���� �����͸� �������� �޽��.
		 *	@param data pointer.
		 */
		void *dequeue();
		//void *front();
		/**
		 *	ť���� Ư�� ��带 �����ϴ� �޽��. ��� ������ �����ǰ� �� ������ ������ ��ȯ�ȴ�.
		 *	��ȯ�� �����ʹ� ��ȯ���� ��ü�� �޸𸮿��� �������־�� �Ѵ�.
		 *	@param �����ϰ��� �ϴ� ���.
		 *	@return ������ ��尡 �����ϰ� �ִ� ������.
		 */
		void *deleteNode(elem *e);
		/**
		 *	ť���� Ư�� ��� �� ������ ������ �����ϴ� �޽��.
		 *	@param �����ϰ��� �ϴ� ���.
		 */
		void removeNode(elem *e, bool isLock=false);
		/**
		 *	ù��° ����� ������ ������ �������� �޽��. ���� �ǹ̾���.
		 */
		void *getData();
		/**
		 *	ť�� ����� ������ ������ ��ȸ�ϴ� �޽��.
		 *	@return data count.
		 */
		int size();
		/**
		 *	ť�� ��� �ִ��� ���θ� �Ǵ��ϴ� �޽��.
		 *	@return true if queue is empty, else return false.
		 */
		bool isEmpty();
		/**
		 *	ť �̸��� ��ȸ�ϴ� �޽��.
		 *	@return queue name.
		 */
		std::string getName();
		/**
		 *	ť �̸��� �����ϴ� �޽��.
		 *	@param queue name.
		 */
		void setName(std::string name);
		/**
		 *	ť�� ������ ���� ���θ� �����ϴ� �޽��. ���� �ǹ� ����.
		 */
		void setIsRemove(bool);
};

#endif /* __CQUEUE_H__ */
