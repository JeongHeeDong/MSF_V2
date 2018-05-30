


#ifndef __CPROCESSHEALTHCOLLECTOR_H__
#define __CPROCESSHEALTHCOLLECTOR_H__ 1

#include "CCollector.h"


//! ���μ��� ���� ���� ���� ������ �����ϴ� Ŭ����
/**
 *	���μ��� �̸�, ���� ���� ������ �����Ͽ� �����Ѵ�.
 */
class CProcessHealthCollector:public CCollector
{
	public:
		/** ������ */
		CProcessHealthCollector();
		/** �Ҹ��� */
		~CProcessHealthCollector();
		/**
		 *	���μ��� ���� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	������ ���μ��� ���� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();
		/**
		 *	��� �Ǵ��� ���� �޽��.
		 */
		void isOverThreshold(CItemCondition *cond);

		void initInstance();

		void checkAlarm(CItemCondition *cond, scPSInfo *psinfo, bool ialarm);

	private:
		scCoreView *m_coreview;	/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scPSInfo *m_psinfo;		/**< ���� ���μ��� ���� ������ ��ȸ�ϱ� ���� ���� */
		v_list_t *m_list;		/**< �ý��ۿ� �⵿�� ��� ���μ��� ������ �����ϴ� ����Ʈ */
		CQueue *m_procQ;		/**< process count Queue */
};

#endif /* __CPROCESSHEALTHCOLLECTOR_H__ */
