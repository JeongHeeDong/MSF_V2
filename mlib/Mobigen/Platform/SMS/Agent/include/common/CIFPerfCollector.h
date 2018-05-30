


#ifndef __CIFPERFCOLLECTOR_H__
#define __CIFPERFCOLLECTOR_H__ 1

#include "CCollector.h"


//! Interface ���� ������ �����ϴ� Ŭ����.
/**
 *	Interface packet in, packet out, packet in error, packet out error, collisions ������ �����ϴ� Ŭ����.
 */
class CIFPerfCollector:public CCollector
{
	public:
		/**
		 * ������.
		 */
		CIFPerfCollector();
		/** �Ҹ��� */
		~CIFPerfCollector();

		/**
		 * Interface ���� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();

		/**
		 *	������ Interface ���� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	������ Interface ���� ������ CItemCondition�� �־��� �Ӱ�ġ ������ ���Ͽ�
		 *	��� �Ǵ��� �Ͽ� ��ָ� �߻���Ű�� �޽��.
		 *	@param CItemCondition pointer.
		 *	@see CItemCondition
		 */
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	Interface ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character interface name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 *	@param Interface ���� ������ �����ϰ� �ִ� ����ü.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b, scInterfaceStatus *status);

	private:
		scCoreView *m_coreview;			/**< system kernel ������ ��ȸ�ϱ� ���� core ����ü */
		scInterfaceStatus *m_ifstat;	/**< Interface ���� ������ ��ȸ�ϱ� ���� ����ü */
		v_list_t *m_list;				/**< scInterfaceStatus ����ü�� �����ϰ� �ִ� ����Ʈ */
};

#endif /* __CIFPERFCOLLECTOR_H__ */
