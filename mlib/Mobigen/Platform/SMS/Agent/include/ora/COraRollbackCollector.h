


#ifndef __CORAROLLBACKCOLLECTOR_H__
#define __CORAROLLBACKCOLLECTOR_H__ 1

#include "CCollector.h"

/**
 * Oracle Rollback status ������ �����ϴ� ����ü
 */
typedef struct _st_rollback {
	char 		name[32];
	char 		status[20];
	int			extends;
	int			shrinks;
	int			wraps;
	int			aveshrink;
	long		aveactive;
	long		waits;
	long		gets;
	unsigned long long		writes;
	int			active_trans;
}st_rollback;

//! Rollback ���� ����(Rollback segment name, status)�� �����ϴ� Ŭ����
class COraRollbackCollector:public CCollector
{
	public:
		/** ������ */
		COraRollbackCollector();
		/** �Ҹ��� */
		virtual ~COraRollbackCollector();
		/**
		 * Oracle rollback segment status ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	Oracle�� SQL Query�� �����Ͽ� ����� ������ �޽��.
		 */
		bool collectOraData();
		/**
		 *	������ Oracle rollback segment status ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	OraRollback ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character item name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 *	@param st_rollback ���� ������ �����ϰ� �ִ� ����ü.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b, st_rollback *status);

	private:
		v_list_t *m_list;			/**< rollback segment ������ �����ϴ� ����Ʈ */
		st_rollback *m_rollback;	/**< rollback segment ������ ��ȸ�ϱ� ���� ����ü */
};

#endif /* __CORAROLLBACKCOLLECTOR_H__ */
