
#ifndef __CDBSESSION_H__
#define __CDBSESSION_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <pthread.h>

#include "CQueue.h"

//! Database ���� ���� ������ �����ϴ� Ŭ����(Thread safe).
class CDBSession
{
	public:
		/** ������ */
		CDBSession();
		/** �Ҹ��� */
		virtual ~CDBSession();
		/**
		 *	����Ŭ �����ͺ��̽��� ������ �õ��ϴ� �޽��.
		 *	@return return 1 if success, else return -1
		 */
		int connect();
		/**
		 *	����Ŭ �����ͺ��̽��� ������ �õ��ϴ� �޽��.
		 *	@param ���� ����(userid/passwd@sid)
		 *	@return return 1 if success, else return -1
		 */
		int connect(char *account);
		/**
		 *	����Ŭ �����ͺ��̽��� ������ �õ��ϴ� �޽��.
		 *	@param userid
		 *	@param password
		 *	@param oracle sid
		 *	@return return 1 if success, else return -1
		 */
		int connect(char *userid, char *password, char *sid);
		/**
		 *	����Ŭ ���ӿ� �ʿ��� ���� ������ �����ϴ� �޽��.
		 *	@param oracle sid.
		 *	@param userid.
		 *	@param password.
		 */
		void setOraInfo(const char * sid, const char * userid, const char * password);
		/**
		 *	Oracle connection�� ������ �޽��. ����Ŭ ���� ����ȭ �޽��.
		 *	@return sql_context pointer.
		 */
		void * getConnection();
		/**
		 *	Oracle connection�� close�ϴ� �޽��.
		 */
		void closeConnection();
		/**
		 *	Oracle session�� �ݳ��ϴ� �޽��. ����Ŭ ���� ����ȭ �޽��.
		 */
		void returnConnection();
		/**
		 *	����Ŭ ���� Ű�� ����ϴ� �޽��. ���� Ű�� "userid/password@sid"�� �̷������.
		 *	@param userid
		 *	@param password
		 *	@param sid
		 */
		void setKey(char *userid, char *password, char *sid);
		/**
		 *	����Ŭ ���� Ű�� ����ϴ� �޽��. ���� Ű�� "userid/password@sid"�� �̷������.
		 *	@param userid/password@sid
		 */
		void setKey(char *account);
		/**
		 *	����Ŭ ���� Ű�� ������ �޽��.
		 *	@return Oracle session key(userid/password@sid)
		 */
		char *getKey();
		/**
		 *	Oracle database session�� ����Ǿ� �ִ��� Ȯ���ϴ� �޽��.
		 *	@return return true if database is open, else return false.
		 */
		bool isOpen();

	private:
		pthread_mutex_t m_mutex;	/**< db session lock key */
		char orasid[32];			/**< oracle sid */
		char oradba[32];			/**< oracle user id */
		char orapw[32];				/**< oracle password */
		char m_key[128];			/**< userid/password@sid */
		int m_count;				/**< �ǹ� ����. */
		CQueue *m_dbq;				/**< �ǹ� ����. */
		void *m_session;			/**< database session (sql_context) */
		int m_idx[10];				/**< �ǹ� ����. */
		bool m_status;				/**< database session status */
};

#endif
