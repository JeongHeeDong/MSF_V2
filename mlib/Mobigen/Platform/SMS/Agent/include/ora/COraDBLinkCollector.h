


#ifndef __CORADBLINKCOLLECTOR_H__
#define __CORADBLINKCOLLECTOR_H__ 1

#include "CCollector.h"

/**
 * Oracle database link ������ �����ϴ� ����ü
 */
typedef struct _st_dblink {
	char db_link[132];
	int owner_id;
	char logged_on[4];
	char protocol[8];
}st_dblink;

//! Oracle Database Link ������ �����ϴ� Ŭ����.
/**
 *	Oracle database link, owner id, login status, protocol ������ �����ϴ� Ŭ����.
 */
class COraDBLinkCollector:public CCollector
{
	public:
		/** ������ */
		COraDBLinkCollector();
		/** �Ҹ��� */
		virtual ~COraDBLinkCollector();
		/**
		 * Oracle database link ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	Oracle�� SQL Query�� �����Ͽ� ����� ������ �޽��.
		 */
		bool collectOraData();
		/**
		 *	������ Oracle database link ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	OraDBLink ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character item name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 *	@param dblink ���� ������ �����ϰ� �ִ� ����ü.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b, st_dblink *status);

	private:
		v_list_t *m_list;		/**< Oracle database link ������ �����Ͽ� �����ϰ� �� ����Ʈ */
		st_dblink *m_dblink;	/**< Oracle database link ������ ��ȸ�ϱ� ���� ����ü */
};

#endif /* __CORADBLINKCOLLECTOR_H__ */
