


#ifndef __CMEMORYCONFCOLLECTOR_H__
#define __CMEMORYCONFCOLLECTOR_H__ 1

#include "CCollector.h"


//! �޸� ���� ������ �����ϴ� Ŭ����.
/**
 *	Total memory size(MB), Total Swap Memory size(MB) ������ �����ϴ� Ŭ����.
 */
class CMemoryConfCollector:public CCollector
{
	public:
		/** ������ */
		CMemoryConfCollector();
		/** �Ҹ��� */
		~CMemoryConfCollector();
		/**
		 * �޸� ���� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	������ �޸� ���� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();
		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

	private:
		scCoreView *m_coreview;	/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scMemStatus m_mem;		/**< �޸� ���� ���� ��ȸ ���� */
};

#endif /* __CMEMORYCONFCOLLECTOR_H__ */
