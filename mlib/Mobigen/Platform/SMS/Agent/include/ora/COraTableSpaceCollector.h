


#ifndef __CORATABLESPACECOLLECTOR_H__
#define __CORATABLESPACECOLLECTOR_H__ 1

#include "CCollector.h"

/** oracle tablespace ������ �����ϴ� ����ü */
typedef struct _st_tspace {
	char name[32];
	char status[12];
	long total;
	long _free;
	long largest;
	double usage;
}st_tspace;

//! Oracle tablespace ������ �����ϴ� Ŭ����.
/**
 *	tablespace�� name, status, total size, free size, usage ���� ������ �����ϴ� Ŭ����.
 */
class COraTableSpaceCollector:public CCollector
{
	public:
		/** ������ */
		COraTableSpaceCollector();
		/** �Ҹ��� */
		virtual ~COraTableSpaceCollector();
		/**
		 * Oracle tablespace ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	Oracle�� SQL Query�� �����Ͽ� ����� ������ �޽��.
		 */
		bool collectOraData();
		/**
		 *	������ Oracle tablespace ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	OraTableSpace ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character item name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 *	@param OraTableSpace ���� ������ �����ϰ� �ִ� ����ü.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b, st_tspace *status);

	private:
		v_list_t *m_list;		/**< tablespace ������ ������ ����Ʈ */
		st_tspace *m_tspace;	/**< tablespace ������ ��ȸ�ϱ� ���� ����ü */
};

#endif /* __CORATABLESPACECOLLECTOR_H__ */
