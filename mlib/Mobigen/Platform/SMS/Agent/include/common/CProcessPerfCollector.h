


#ifndef __CPROCESSPERFCOLLECTOR_H__
#define __CPROCESSPERFCOLLECTOR_H__ 1

#include "CCollector.h"


//! ���μ��� ���� ������ �����ϴ� Ŭ����.
/**
 *	���μ��� �̸�, ���μ��� CPU ������, ���μ��� �޸� ������ ������ ��ȸ�ϴ� Ŭ����.
 */
class CProcessPerfCollector:public CCollector
{
	public:
		/** ������ */
		CProcessPerfCollector();
		/** �Ҹ��� */
		~CProcessPerfCollector();
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
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	Process ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character CPU name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 *	@param Process ���� ������ �����ϰ� �ִ� ����ü.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b, scPSInfo *status);

	private:
		scCoreView *m_coreview;	/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scPSInfo *m_psinfo;		/**< ���� ���μ��� ���� ������ ��ȸ�ϱ� ���� ���� */
		v_list_t *m_list;		/**< �ý��ۿ� �⵿�� ��� ���μ��� ������ �����ϴ� ����Ʈ */
};

#endif /* __CPROCESSPERFCOLLECTOR_H__ */
