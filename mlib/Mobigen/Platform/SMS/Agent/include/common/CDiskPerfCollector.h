


#ifndef __CDISKPERFCOLLECTOR_H__
#define __CDISKPERFCOLLECTOR_H__ 1

#include "CCollector.h"


//! Disk ���� ������ �����ϴ� Ŭ����.
/**
 *	File System(Device name, Mount Point, Total size(MB), Used(MB), Free(MB), Usage(%)) ������ �����ϴ� Ŭ����.
 */
class CDiskPerfCollector:public CCollector
{
	public:
		/** ������ */
		CDiskPerfCollector();
		/** �Ҹ��� */
		~CDiskPerfCollector();

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
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	Disk ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character CPU name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 *	@param Disk ���� ������ �����ϰ� �ִ� ����ü.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b, scFSInfo *status);

	private:
		scCoreView *m_coreview;		/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scFSInfo *m_fsinfo;			/**< file system ������ ��ȸ�ϱ� ���� ���� */
		v_list_t *m_list;			/**< scFSInfo ����ü�� �ý��� mount point ������ŭ �����ϰ� �ִ� ����Ʈ */
};

#endif /* __CDISKPERFCOLLECTOR_H__ */
