


#ifndef __CPATCHCONFCOLLECTOR_H__
#define __CPATCHCONFCOLLECTOR_H__ 1

#include "CCollector.h"

//! OS(Kernel) Patch ������ �����ϴ� Ŭ����.

class CPatchConfCollector:public CCollector
{
	public:
		/** ������ */
		CPatchConfCollector();
		/** �Ҹ��� */
		~CPatchConfCollector();
		/**
		 * OS Patch ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	������ OS Patch ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();
		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

	private:
		scCoreView *m_coreview;		/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scSysPatchInfo *m_patch;	/**< OS Patch ���� ��ȸ ���� */
		v_list_t *m_list;			/**< system�� ��ġ�� os patch ������ŭ scSysPatchInfo ������ �����ϴ� ����Ʈ */
};

#endif /* __CPATCHCONFCOLLECTOR_H__ */
