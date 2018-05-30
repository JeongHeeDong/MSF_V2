


#ifndef __CTOPMEMORYPROCESSPERFCOLLECTOR_H__
#define __CTOPMEMORYPROCESSPERFCOLLECTOR_H__ 1

#include "CCollector.h"

//! �޸� ������ ������ Top N���� ���μ��� ������ �����ϴ� Ŭ����.
/**
 *	scagent.xml ���Ͽ� ������ ���� �����Ǿ� �ִٸ�,\n
 *	<instances>\n
 *		<instance name="memory|5">memory|5</instance>\n
 *  </instances>\n
 *	�޸� ������ ���� 5���� ���μ��� ������ �����Ͽ� ó���Ѵ�.
 */
class CTopMemoryProcessPerfCollector:public CCollector
{
	public:
		/** ������ */
		CTopMemoryProcessPerfCollector();
		/** �Ҹ��� */
		~CTopMemoryProcessPerfCollector();
		/**
		 * �޸� ������ ������ Top N���� ���μ��� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	������ �޸� ������ ������ Top N���� ���μ��� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();
		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

	private:
		scCoreView *m_coreview;	/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scPSInfo *m_psinfo;		/**< ���μ��� �� ������ ��ȸ�ϱ� ���� ���� */
		v_list_t *m_list;		/**< ���μ��� �� ������ �����ϱ� ���� ����Ʈ */
};

#endif /* __CTOPMEMORYPROCESSPERFCOLLECTOR_H__ */
