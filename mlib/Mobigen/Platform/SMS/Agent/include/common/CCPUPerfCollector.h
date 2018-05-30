


#ifndef __CCPUPERFCOLLECTOR_H__
#define __CCPUPERFCOLLECTOR_H__ 1

#include "CCollector.h"

extern scCpuStatus g_ucpu, g_mcpu[SC_MAX_CPU_NUM];
extern int g_ncpu;
extern time_t g_cputime;


//! CPU ���� ������ �����ϴ� Ŭ����.
/**
 *	���� cpu �� Total CPU�� system, user, cpu, wait, idle ������ �����ϴ� Ŭ����.
 *	CPU Naming Rule : cpu0, cpu1, cpu2, ...., total
 */
class CCPUPerfCollector:public CCollector
{
	public:
		/** ������ */
		CCPUPerfCollector();
		/** �Ҹ��� */
		~CCPUPerfCollector();

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
		 *	������ CPU ���� ������ CItemCondition�� �־��� �Ӱ�ġ ������ ���Ͽ�
		 *	��� �Ǵ��� �Ͽ� ��ָ� �߻���Ű�� �޽��.
		 *	@param CItemCondition pointer.
		 *	@see CItemCondition
		 */
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	CPU ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character CPU name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 *	@param CPU ���� ������ �����ϰ� �ִ� ����ü.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b, scCpuStatus *status);

	private:
		scCoreView *m_coreview;		/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scCpuStatus m_ucpu, m_mcpu[SC_MAX_CPU_NUM]; /**< total cpu �� ���� cpu�� ���� ������ ��ȸ�ϱ� ���� ���� */
		int m_ncpu;					/**< Total CPU ���� */
};

#endif /* __CCPUPERFCOLLECTOR_H__ */
