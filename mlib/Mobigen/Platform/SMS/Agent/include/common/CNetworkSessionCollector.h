


#ifndef __CNETWORKSESSIONCOLLECTOR_H__
#define __CNETWORKSESSIONCOLLECTOR_H__ 1

#include "CCollector.h"


//!  ��Ʈ��ũ ���� ������ �����ϴ� Ŭ����.
/**
 *	Local IP, Local Port, Remote IP, Remote Port ������ ��ȸ�ϴ� Ŭ����.
 */
class CNetworkSessionCollector:public CCollector
{
	public:
		/** ������ */
		CNetworkSessionCollector();
		/** �Ҹ��� */
		~CNetworkSessionCollector();
		/**
		 *	��Ʈ��ũ ���� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	������ ��Ʈ��ũ ���� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();
		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

	private:
		scCoreView *m_coreview;	/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scTCPInfo *m_tcpinfo;		/**< ���� �׵��ũ ����  ������ ��ȸ�ϱ� ���� ���� */
		v_list_t *m_list;		/**< TCP ��Ʈ��ũ ����  ������ �����ϴ� ����Ʈ */
};

#endif /* __CNETWORKSESSIONCOLLECTOR_H__ */
