


#ifndef __CCPUCONFCOLLECTOR_H__
#define __CCPUCONFCOLLECTOR_H__ 1

#include "CCollector.h"

//! CPU ���� ������ �����ϴ� Ŭ����.
/**
 *	cpu index("cpu0", "cpu1", ...) �� CPU Clock Hz ������ �����ϴ� Ŭ����.
 *	CPU Naming Rule : cpu0, cpu1, cpu2, ...., total
 */
class CCPUConfCollector:public CCollector
{
	public:
		/**
		 * ������.
		 */
		CCPUConfCollector();
		/**
		 * �Ҹ���.
		 */
		~CCPUConfCollector();

		/**
		 * CPU ���� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();

		/**
		 *	������ CPU ���� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

	private:
		scCoreView *m_coreview;		/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scSysInfo m_sysinfo;		/**< system �⺻ ������ ��ȸ�ϱ� ���� ����. cpu ���� �� Hz���� ���� */
		scCpuStatus m_ucpu, m_mcpu[SC_MAX_CPU_NUM];	/**< total cpu, ���� cpu ������ ��ȸ�ϱ� ���� ���� */
		int m_ncpu;					/**< cpu ���� */
};

#endif /* __CCPUCONFCOLLECTOR_H__ */
