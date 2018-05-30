


#ifndef __CSHELLCOMMANDCOLLECTOR_H__
#define __CSHELLCOMMANDCOLLECTOR_H__ 1

#include "CCollector.h"

//! shell command�� ������ ������� �����ϴ� Ŭ����.

class CShellCommandCollector:public CCollector
{
	public:
		/** ������ */
		CShellCommandCollector();
		/** �Ҹ��� */
		~CShellCommandCollector();
		/**
		 * Shell command ����� ������ ������� �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	������ Shell command ����� ������ ������� SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();
		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

	private:
		scCoreView *m_coreview;	/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		char *m_result;	/**< Shell command ���� ����� */
};

#endif /* __CSHELLCOMMANDCOLLECTOR_H__ */
