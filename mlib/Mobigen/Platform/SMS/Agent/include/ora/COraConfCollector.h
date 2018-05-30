
#ifndef __CORACONFCOLLECTOR_H__
#define __CORACONFCOLLECTOR_H__ 1

#include "CCollector.h"

/**
 * Oracle ���� ������ �����ϱ� ���� ����ü
 */
typedef struct _st_oraconf {
	char 		dbname[64];
	char 		status[20];
	char		version[20];
	char		db_uptime[20];
	char		service_name[20];
	long		sga_max_size;
	int			sessions;
	int			processes;
	int			db_files;
	int			session_max_files;
	int			open_cursors;
	char		character_set[64];
	int			db_block_size;
	long		shared_pool_size;
	long		shared_pool_reserved_size;
	long		sort_area_size;
	int			dbwr_io_slaves;
	int			log_archive_mode;
}st_oraconf;

class COraConfCollector:public CCollector
{
	public:
		/** ������ */
		COraConfCollector();
		/** �Ҹ��� */
		virtual ~COraConfCollector();
		/**
		 * Oracle oraconf segment status ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	Oracle�� SQL Query�� �����Ͽ� ����� ������ �޽��.
		 */
		bool collectOraData();
		/**
		 *	������ Oracle oraconf ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		bool collectOraVersion(st_oraconf *);
		bool collectOraParameter(st_oraconf *);
		void makeMessage();

	private:
		v_list_t *m_list;			/**< oraconf segment ������ �����ϴ� ����Ʈ */
		st_oraconf *m_oraconf;	/**< oraconf segment ������ ��ȸ�ϱ� ���� ����ü */
};

#endif /* __CORACONFCOLLECTOR_H__ */
