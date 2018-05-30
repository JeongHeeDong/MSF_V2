


#ifndef __CSWCONFCOLLECTOR_H__
#define __CSWCONFCOLLECTOR_H__ 1

#include "CCollector.h"

//! �ý��ۿ� ��ġ�� S/W(Application) ������ �����ϴ� Ŭ����.
class CSWConfCollector:public CCollector
{
	public:
		/** ������ */
		CSWConfCollector();
		/** �Ҹ��� */
		~CSWConfCollector();
		/**
		 * �ý��ۿ� ��ġ�� S/W(Application) ���� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	������ �ý��ۿ� ��ġ�� S/W(Application) ���� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();
		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

	private:
		scCoreView *m_coreview;		/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scSysPkgInfo *m_pkg;		/**< S/W ������ ��ȸ�ϱ� ���� ���� */
		v_list_t *m_list;			/**< �ý��ۿ� ��ġ�� S/W ������ �����ϱ� ���� ����Ʈ */
};

#endif /* __CSWCONFCOLLECTOR_H__ */
