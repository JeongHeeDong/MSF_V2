


#ifndef __CCPULOADPERFCOLLECTOR_H__
#define __CCPULOADPERFCOLLECTOR_H__ 1

#include "CCollector.h"

//! CPU Load ������ �����ϴ� Ŭ����.
/**
 *	CPU Load average 1��/5��/15�� ������ �����ϴ� Ŭ����.
 */
class CCPULoadPerfCollector:public CCollector
{
	public:
		/** ������ */
		CCPULoadPerfCollector();
		/** �Ҹ��� */
		~CCPULoadPerfCollector();
		/**
		 * CPU Load average ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();

		/**
		 *	������ Load average ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	CPULoad ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character CPU name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b);

	private:
		scCoreView *m_coreview;		/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scVMStatus m_vmstat;		/**< vmstatus ������ �����ϱ� ���� ����. cpu load average ����(la_1min, la_5min, la_15min)�� �����Ѵ�. */
};

#endif /* __CCPULOADPERFCOLLECTOR_H__ */
