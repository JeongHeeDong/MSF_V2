
#ifndef _CAGENTENVVAR_H__
#define _CAGENTENVVAR_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string>

#include "CAgentConfigVar.h"
#include "CQueue.h"
#include "CKernelCore.h"

#if defined(ORACLE_ENABLE)
#include "CDBPool.h"
#endif /* ORACLE_ENABLE */


//! SMS Agent�� �⵿�ϸ鼭 �ʿ��� ��� ȯ�� ���� ���� �� item ������ �����ϴ� Ŭ����
/**
 *	system kernel ������ ��ȸ�ϱ� ���� �������̽�(CKernelCore)\n
 *	item code ������ �����ϴ� �������̽�(CAgentConfigVar)\n
 *	SMS Agent ���������� �����͸� �ְ�ޱ� ���� ���� �޽��� ť\n
 *	SMS Agent session ���� ����\n
 *	Database session pool ���� ���� �����Ѵ�.
 *	@see CKernelCore, CAgentConfig, CDBPool.
 */
class CAgentEnvVar 
{
	public :
		/**
		 *	������
		 *	���� ������ �ʱ�ȭ�Ѵ�.
		 */
		CAgentEnvVar(){
			m_kernel = new CKernelCore;
			m_configVar = new CAgentConfigVar;
			m_eventQ = new CQueue;
			m_shortPerfQ = new CQueue;
			m_longPerfQ = new CQueue;
			m_respQ = new CQueue;
			m_cmdQ = new CQueue;
			m_policyQ = new CQueue;
#if defined(ORACLE_ENABLE)
			m_dbpool = new CDBPool;
#endif /* ORACLE_ENABLE */
			m_session_event = false;
			m_session_shortperf = false;
			m_session_longperf = false;
			m_session_resp = false;
			m_session_cmd = false;
		}
		/** �Ҹ��� */
		~CAgentEnvVar(){
			delete m_configVar;
			delete m_eventQ;
			delete m_shortPerfQ;
			delete m_longPerfQ;
			delete m_respQ;
			delete m_cmdQ;
			delete m_policyQ;
			delete m_kernel;
#if defined(ORACLE_ENABLE)
			delete m_dbpool;
#endif /* ORACLE_ENABLE */
		}
		/**
		 *	������� Event �޽��� ó�� ���� ������� ����ѱ� ���� �޽��� ť�� ������ �޽��.
		 *	@return Event(Alarm) message Queue.
		 */
		CQueue *getEventQ(){ return m_eventQ; }
		/**
		 *	������� �ܱ� ���� �޽��� ó�� ���� ������� ����ѱ� ���� �޽��� ť�� ������ �޽��.
		 *	@return �ܱ� ���� message Queue.
		 */
		CQueue *getShortPerfQ(){ return m_shortPerfQ; }
		/**
		 *	������� ����� ���� �޽��� ó�� ���� ������� ����ѱ� ���� �޽��� ť�� ������ �޽��.
		 *	@return ����� ���� message Queue.
		 */
		CQueue *getLongPerfQ(){ return m_longPerfQ; }
		/**
		 *	������� ��� ���� �޽��� ó�� ���� ������� ����ѱ� ���� �޽��� ť�� ������ �޽��.
		 *	@return ��� ���� message Queue.
		 */
		CQueue *getRespQ(){ return m_respQ; }
		/**
		 *	��ɾ� ó����(CProtocolProcessor)�� ��� �ڵ� ó�� ���� ������(CSocketWorkerThread)�� ����ѱ� ���� �޽��� ť�� ������ �޽��.
		 *	@return ��� �޽��� Queue.
		 *	@see CProtocolProcessor, CSocketWorkerThread, CQueue.
		 */
		CQueue *getCmdQ(){ return m_cmdQ; }
		/**
		 *	�����췯(CScheduler)�� ���� ���� ������(SCThread)�� ����ѱ� ���� ��å ť�� ������ �޽��.
		 *	@return ���� ��å Queue.
		 *	@see CScheduler, SCThread, CPolicyItem, CQueue
		 */
		CQueue *getPolicyQ(){ return m_policyQ; }
		/**
		 *	system kernel core interface class(CKernelCore)�� ������ ���� �޽��.
		 *	@return CKernelCore pointer.
		 *	@see CKernelCore
		 */
		CKernelCore *getKernelCore(){ return m_kernel; }
		/**
		 *	item code ������ �����ϴ� Ŭ����(CAgentConfigVar)�� ������ ���� �޽��.
		 *	@return CAgentConfigVar pointer.
		 *	@see CAgentConfigVar
		 */
		CAgentConfigVar *getAgentConfigVar() { return m_configVar; }
#if defined(ORACLE_ENABLE)
		/**
		 *	ORACLE Database session pool�� �����ϴ� Ŭ����(CDBPool)�� ������ ���� �޽��.
		 *	@return CDBPool pointer
		 *	@see CDBPool, CDBSession
		 */
		CDBPool *getDBPool() { return m_dbpool; }
#endif /* ORACLE_ENABLE */
		/**
		 *	SMS Agent�� SMS Manager���� ��� ���� ���� ���� ������ ������ �޽��.
		 *	@return session status pointer.
		 */
		bool *getEventSession(){ return &m_session_event; }
		/**
		 *	SMS Agent�� SMS Manager���� �ܱ� ���� ���� ���� ���� ������ ������ �޽��.
		 *	@return session status pointer.
		 */
		bool *getShortPerfSession(){ return &m_session_shortperf; }
		/**
		 *	SMS Agent�� SMS Manager���� ����� ���� ���� ���� ������ ������ �޽��.
		 *	@return session status pointer.
		 */
		bool *getLongPerfSession(){ return &m_session_longperf; }
		/**
		 *	SMS Agent�� SMS Manager���� ��� ���� ���� ���� ���� ������ ������ �޽��.
		 *	@return session status pointer.
		 */
		bool *getRespSession(){ return &m_session_resp; }
		/**
		 *	SMS Agent�� SMS Manager���� ��ɾ� ó�� ���� ���� ���� ������ ������ �޽��.
		 *	@return session status pointer.
		 */
		bool *getCmdSession(){ return &m_session_cmd; }

	private :
		CKernelCore *m_kernel;			/**< system kernel interface class */
		CAgentConfigVar *m_configVar;	/**< item code ������ �����ϴ� Ŭ���� */
		CQueue *m_eventQ;				/**< ��� �޽��� ť */
		CQueue *m_shortPerfQ;			/**< �ܱ� ���� �޽��� ť */
		CQueue *m_longPerfQ;			/**< ����� ���� �޽��� ť */
		CQueue *m_respQ;				/**< ��ɾ� ���� �޽��� ť */
		CQueue *m_cmdQ;					/**< ��ɾ� ť */
		CQueue *m_policyQ;				/**< ���� ��å ���� ť */
#if defined(ORACLE_ENABLE)
		CDBPool *m_dbpool;				/**< Database session pool */
#endif /* ORACLE_ENABLE */
		bool m_session_event;			/**< ��� ���� ���� */
		bool m_session_shortperf;		/**< �ܱ� ���� ���� ���� */
		bool m_session_longperf;		/**< ����� ���� ���� ���� */
		bool m_session_resp;			/**< ��� ���� ���� ���� */
		bool m_session_cmd;				/**< ��� ���� ���� */
};

#endif /* _CAGENTENVVAR_H__ */
