


#ifndef __CTOPCPUPROCESSPERFCOLLECTOR_H__
#define __CTOPCPUPROCESSPERFCOLLECTOR_H__ 1

#include "CCollector.h"

//! CPU ������ ������ Top N���� ���μ��� ������ �����ϴ� Ŭ����.
/**
 *	scagent.xml ���Ͽ� ������ ���� �����Ǿ� �ִٸ�,\n
 *	<instances>\n
 *		<instance name="cpu|5">cpu|5</instance>\n
 *  </instances>\n
 *	CPU ������ ���� 5���� ���μ��� ������ �����Ͽ� ó���Ѵ�.
 */
class CTopCPUProcessPerfCollector:public CCollector
{
	public:
		/** ������ */
		CTopCPUProcessPerfCollector();
		/** �Ҹ��� */
		~CTopCPUProcessPerfCollector();
		/**
		 * CPU ������ ������ Top N���� ���μ��� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	������ CPU ������ ������ Top N���� ���μ��� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
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

#endif /* __CTOPCPUPROCESSPERFCOLLECTOR_H__ */
