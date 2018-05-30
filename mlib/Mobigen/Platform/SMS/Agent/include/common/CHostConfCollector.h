


#ifndef __CHOSTCONFCOLLECTOR_H__
#define __CHOSTCONFCOLLECTOR_H__ 1

#include "CCollector.h"

//! ȣ��Ʈ�� �⺻ ���� ������ �����ϴ� Ŭ����.
/**
 *	HostName, IP Address, OSType, OSVersion, Model, Hostid ������ �����ϴ� Ŭ����.
 */
class CHostConfCollector:public CCollector
{
	public:
		/**
		 * ������.
		 */
		CHostConfCollector();
		/**
		 * �Ҹ���.
		 */
		~CHostConfCollector();

		/**
		 * ȣ��Ʈ�� �⺻ ���� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();

		/**
		 *	������ �⺻ ���� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

	private:
		scCoreView *m_coreview;	/**< system kernel ������ ��ȸ�ϱ� ���� core ����ü */
		scSysInfo m_sysinfo;	/**< system �⺻ ������ �����ϱ� ���� ����ü */
		char m_ipaddr[64];		/**< host ip address */
		long m_hostid;			/**< hostid */
};

#endif /* __CHOSTCONFCOLLECTOR_H__ */
