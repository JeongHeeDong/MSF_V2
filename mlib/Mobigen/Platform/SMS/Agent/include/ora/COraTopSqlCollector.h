


#ifndef __CORATOPSQLCOLLECTOR_H__
#define __CORATOPSQLCOLLECTOR_H__ 1

#include "CCollector.h"

/** �ֱٿ� ����Ŭ���� ����� SQL ������ �����ϱ� ���� ����ü */
typedef struct _st_topsql {
	char _sqltext[1024];
	int executions;
	int buffergets;
	int diskreads;
	int rowsprocessed;
}st_topsql;

//! EXECUTIONS, BUFFER_GETS, DISK_READS, ROWS_PROCESSED ���� �ֱٿ� ����� SQL�� ������ �����ϴ� Ŭ����.
class COraTopSqlCollector:public CCollector
{
	public:
		/** ������ */
		COraTopSqlCollector();
		/** �Ҹ��� */
		virtual ~COraTopSqlCollector();
		/**
		 *  EXECUTIONS, BUFFER_GETS, DISK_READS, ROWS_PROCESSED ���� �ֱٿ� ����� SQL�� ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	Oracle�� SQL Query�� �����Ͽ� ����� ������ �޽��.
		 */
		bool collectOraData();
		/**
		 *	EXECUTIONS, BUFFER_GETS, DISK_READS, ROWS_PROCESSED ���� �ֱٿ� ����� SQL�� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	OraTopSql ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character CPU name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 *	@param Process ���� ������ �����ϰ� �ִ� ����ü.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b, st_topsql *status);

	private:
		v_list_t *m_list;		/**< ����� SQL ������ �����ϱ� ���� ����Ʈ */
		st_topsql *m_topsql;	/**< SQL ������ ��ȸ�ϱ� ���� ����ü */
		int m_topn;				/**< ��ȸ�� ���� TOP N */
		int m_sort;				/**< ���� ����. 1 : EXECUTIONS, 2 : BUFFER_GETS, 3 : DISK_READS, 4 : ROWS_PROCESSED, else DISK_READS */
};

#endif /* __CORATOPSQLCOLLECTOR_H__ */
