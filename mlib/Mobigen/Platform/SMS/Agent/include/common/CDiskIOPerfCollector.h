


#ifndef __CDISKIOPERFCOLLECTOR_H__
#define __CDISKIOPERFCOLLECTOR_H__ 1

#include "CCollector.h"


//! Disk IO ���� ������ �����ϴ� Ŭ����.
/**
 *	Device name, Disk IO(Read, Write) ���� ������ �����ϴ� Ŭ����.
 */
class CDiskIOPerfCollector:public CCollector
{
	public:
		/** ������ */
		CDiskIOPerfCollector();
		/** �Ҹ��� */
		~CDiskIOPerfCollector();

		/**
		 * Disk IO ���� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();

		/**
		 *	������ Disk IO ���� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
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
		void checkAlarm(CItemCondition *cond, char *instname, bool b, scIOStatus *status);

	private:
		scCoreView *m_coreview;		/**< system kernel ������ ��ȸ�ϱ� ���� kernel core ���� */
		scIOStatus *m_iostat;		/**< disk io ���� ������ ��ȸ�ϱ� ���� ���� */
		v_list_t *m_list;			/**< disk io ���� ������ device������ŭ �����ϰ� �ִ� ����Ʈ */
};

#endif /* __CDISKIOPERFCOLLECTOR_H__ */
