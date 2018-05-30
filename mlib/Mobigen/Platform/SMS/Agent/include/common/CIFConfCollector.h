


#ifndef __CIFCONFCOLLECTOR_H__
#define __CIFCONFCOLLECTOR_H__ 1

#include "CCollector.h"


//! Interface ���� ������ �����ϴ� Ŭ����.
/**
 *	Interface device name, speed, Mac Address, IP address ������ �����ϴ� Ŭ����.
 */
class CIFConfCollector:public CCollector
{
	public:
		/**
		 * ������.
		 */
		CIFConfCollector();

		/**
		 * �Ҹ���.
		 */
		~CIFConfCollector();

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
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

	private:
		scCoreView *m_coreview;			/**< system kernel ������ ��ȸ�ϱ� ���� core ����ü */
		scInterfaceStatus *m_ifstat;	/**< Interface ���� ������ ��ȸ�ϱ� ���� ����ü */
		v_list_t *m_list;				/**< scInterfaceStatus ����ü�� �����ϰ� �ִ� ����Ʈ */
};

#endif /* __CIFCONFCOLLECTOR_H__ */
