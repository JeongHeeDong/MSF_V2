

#ifndef __CCOLLECTOR_H__
#define __CCOLLECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <errno.h>

#include "CMisc.h"

#include "CAgentEnvVar.h"
#include "CPolicyItem.h"


//! ���� ���� Ŭ����
/**
 *	��� ���� ������� �� Ŭ������ ����Ͽ� �����ȴ�.
 */
class CCollector
{
	public:
		/** ������ */
		CCollector();
		/** �Ҹ��� */
		virtual ~CCollector(){};
		/**
		 *	���� ���� ������(SCThread)�� ���� ���� ������ ��û�ϴ� �޽��
		 *	@see SCThread
		 */
		virtual void collect(){};
		/**
		 *	������ ������ SMS Manager�� �����ϱ� ���� �Ծ�� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		virtual void makeMessage(){};
		/**
		 *	������ ������ �Ӱ�ġ(CItemCondition)�� ���� �Ǵ��� ���θ� �Ǵ��Ͽ� ��ָ� �߻���Ű�� �޽��.
		 *	@see CItemCondition, CAalarmProcessor
		 */
		virtual void isOverThreshold(CItemCondition *cond) {};
		/**
		 *	���� ���� ��å Ŭ����(CPolicyItem)�� �����ϴ� �޽��.
		 *	@param ���� ���� ��å Ŭ����.
		 *	@see CPolicyItem
		 */
		void setPolicyItem(CPolicyItem *pollitem){ m_pollitem = pollitem; }
		/**
		 *	���� ��å ������ ������ ���� �޽��
		 *	@return CPolicyItem pointer.
		 */
		CPolicyItem *getPolicyItem(){ return m_pollitem; }
		/**
		 *	SMS Agent ȯ�� ������ �����ϴ� Ŭ������ �����ϴ� �޽��
		 *	@param CAgentEnvVar pointer
		 *	@see CAgentEnvVar
		 */
		void setEnvVar(CAgentEnvVar *envvar){ m_envvar = envvar; }
		/**
		 *	SMS Agent ȯ�� ������ �����ϴ� Ŭ������ ������ �޽��
		 *	@return CAgentEnvVar pointer
		 *	@see CAgentEnvVar
		 */
		CAgentEnvVar *getEnvVar(){ return m_envvar; }
		/**
		 *	���� ��å�� �ܱ� �������� ���θ� �Ǵ��ϴ� �޽��
		 *	@return true if short period, else return false
		 */
		bool isShortPerf();

	protected:
		CAgentEnvVar *m_envvar;		/**< SMS Agent ȯ�� ������ �����ϴ� Ŭ���� */
		CPolicyItem *m_pollitem;	/**< ���� ��å */
		CMessageFormatter m_msgfmt;	/**< �޽��� ��ȯ�� */
};

#endif /* __CCOLLECTOR_H__ */

