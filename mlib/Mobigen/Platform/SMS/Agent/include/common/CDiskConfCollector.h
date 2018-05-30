


#ifndef __CDISKCONFCOLLECTOR_H__
#define __CDISKCONFCOLLECTOR_H__ 1

#include "CCollector.h"


//! Disk ���� ������ �����ϴ� Ŭ����.
/**
 *	Disk device, mount point, total size(MB) ������ �����ϴ� Ŭ����.
 */
class CDiskConfCollector:public CCollector
{
	public:
		/** ������ */
		CDiskConfCollector();
		/** �Ҹ��� */
		~CDiskConfCollector();

		/**
		 * Disk ���� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();

		/**
		 *	������ Disk ���� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

	private:
		scCoreView *m_coreview;	/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scFSInfo *m_fsinfo;		/**< file system ������ ��ȸ�ϱ� ���� ���� */
		v_list_t *m_list;		/**< scFSInfo ����ü�� �ý��� mount point ������ŭ �����ϰ� �ִ� ����Ʈ */
};

#endif /* __CDISKCONFCOLLECTOR_H__ */
