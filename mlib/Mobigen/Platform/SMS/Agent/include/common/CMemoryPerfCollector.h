


#ifndef __CMEMORYPERFCOLLECTOR_H__
#define __CMEMORYPERFCOLLECTOR_H__ 1

#include "CCollector.h"


//! �޸� ���� ������ �����ϴ� Ŭ����.
/**
 *	������ �޸�(Total Memory size(MB), Free Memory(MB), Memory usage(%)),
 *	Swap �޷θ�(Total Swap Memory size(MB), Free Swap Memory size(MB), Swap Memory Usage(%)),
 *	������ ��ĵ, ������ �ƿ�, ���� �ƿ� ������ �����ϴ� Ŭ����.
 */
class CMemoryPerfCollector:public CCollector
{
	public:
		/** ������ */
		CMemoryPerfCollector();
		/** �Ҹ��� */
		~CMemoryPerfCollector();
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
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	Memory ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character CPU name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b);


	private:
		scCoreView *m_coreview;	/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scMemStatus m_memstat;	/**< �޸� ���� ������ ��ȸ�ϱ� ���� ���� */
		scVMStatus m_vmstat;	/**< Virtual Memory ���� ������ ��ȸ�ϱ� ���� ���� */
};

#endif /* __CMEMORYPERFCOLLECTOR_H__ */
