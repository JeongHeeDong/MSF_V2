


#ifndef __CORAHITRATIOCOLLECTOR_H__
#define __CORAHITRATIOCOLLECTOR_H__ 1

#include "CCollector.h"

//! Oracle buffer cache hit ratio, library cache hit ratio, data dictionary hit ratio ������ �����ϴ� Ŭ����.
class COraHitRatioCollector:public CCollector
{
	public:
		/** ������ */
		COraHitRatioCollector();
		/** �Ҹ��� */
		virtual ~COraHitRatioCollector();
		/**
		 * Oracle  buffer cache hit ratio, library cache hit ratio, data dictionary hit ratio ������ �����Ͽ� SMS Manager�� �����ϱ� ���� �޽��� ��������
		 * ��ȯ�Ͽ� �޽��� ť�� �����ϴ� �޽��.
		 */
		void collect();
		/**
		 *	Oracle�� SQL Query�� �����Ͽ� ����� ������ �޽��.
		 */
		bool collectOraData();
		/**
		 *	������ buffer cache hit ratio, library cache hit ratio, data dictionary hit ratio ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();

		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond);

		/**
		 *	OraHitRatio ���� �Ӱ�ġ ��ָ� �߻���Ű�� �޽��.
		 *	�Ӱ�ġ�� �ʰ��� ��쿡�� ��ָ� �߻���Ű��, 
		 *	������ ��ְ� �߻��� ���� �ְ�, �Ӱ�ġ�� �ʰ����� ���� ��쿡�� ��ָ� ������Ų��.
		 *
		 *	@param CItemCondition pointer.
		 *	@param character Item name.
		 *	@param ���� �Ӱ�ġ �ʰ� ����. �Ӱ�ġ�� ���� ���� true, �ʰ����� ���� ��� false.
		 */
		void checkAlarm(CItemCondition *cond, char *instname, bool b);

	private:
		double m_buf; /**< buffer cache */
		double m_lib; /**< library cache */
		double m_dic; /**< dictionary cache */
};

#endif /* __CORAHITRATIOCOLLECTOR_H__ */
