


#ifndef __CORASESSIONCOUNTCOLLECTOR_H__
#define __CORASESSIONCOUNTCOLLECTOR_H__ 1

#include "CCollector.h"

//! ���� Oracle�� ����� Oracle session�� ������ �����ϴ� Ŭ����

class COraSessionCountCollector:public CCollector
{
	public:
		/** ������ */
		COraSessionCountCollector();
		/** �Ҹ��� */
		virtual ~COraSessionCountCollector();
		/**
		 * Oracle database session ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	Oracle�� SQL Query�� �����Ͽ� ����� ������ �޽��.
		 */
		bool collectOraData();
		/**
		 *	������ Oracle database session ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	OraSessionCount ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character item name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b);


	private:
		int m_scount;	/**< Oracle session count */
};

#endif /* __CORASESSIONCOUNTCOLLECTOR_H__ */
