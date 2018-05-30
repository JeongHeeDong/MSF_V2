

#ifndef __CDBPOOL_H__
#define __CDBPOOL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "CQueue.h"
#include "CDBSession.h"

#define USERID   "system"
#define PASSWORD "manager"


//! Database pool class.
/**
 *	���� �����忡�� ������ ���̽� ���ٿ� �ʿ��� �����ͺ��̽� connect session�� �����ϴ� Ŭ����.
 */
class CDBPool
{
	public:
		/** ������ */
		CDBPool();
		/** �Ҹ��� */
		virtual ~CDBPool();
		/**
		 *	���ο� �����ͺ��̽� ���� ������ �߰��ϴ� �޽��.
		 *	@param CDBSession pointer.
		 *	@see CDBSession
		 */
		void putSession(CDBSession *session);
		/**
		 *	�־��� User ID, password, SID�� �ش��ϴ� Database session�� ������ �޽��.
		 *	@param oracle user id.
		 *	@param password.
		 *	@param Oracle SID.
		 *	@return CDBSession pointer.
		 *	@see CDBSession
		 */
		CDBSession *getSession(char *userid, char *passwd, char *sid);
		/**
		 *	�־��� key�� �ش��ϴ� Database session�� ������ �޽��.
		 *	@param database session key(character string).
		 *	@return CDBSession pointer.
		 *	@see CDBsession
		 */
		CDBSession *getSession(char *key);
		/**
		 *	���� Database session�� Database pool�� �ݳ��ϴ� �޽��.
		 *	@param CDBSession pointer.
		 *	@see CDBSession
		 */
		void returnSession(CDBSession *);
		/**
		 *	���� �����ͺ��̽� pool�� ����� Database ���� ���� ������ ���´� �޽��.
		 *	@return database session count.
		 */
		int size();

	private:
		pthread_mutex_t m_mutex;	/**< db pool lock key */
		CQueue *m_pool;				/**< db pool queue */
};

#endif
