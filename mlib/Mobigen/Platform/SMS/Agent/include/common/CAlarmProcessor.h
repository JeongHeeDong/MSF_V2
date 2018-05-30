
#ifndef __CALARMPROCESSOR_H__
#define __CALARMPROCESSOR_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "CCollector.h"

//! ������ ������ �̿��Ͽ� ��� ó���� ����ϴ� Ŭ����
class CAlarmProcessor
{
	public:
		/** ������ */
		CAlarmProcessor(){};
		/**
		 *	������
		 *	@param CCollector pointer
		 */
		CAlarmProcessor(CCollector *collector){ m_collector = collector; }
		/**	�Ҹ��� */
		~CAlarmProcessor(){};
		/**	�Ӱ�ġ ��ָ� �Ǵ��ϴ� �޽�� */
		void check();
		/**
		 *	������(CCollector)���� ������ �����Ϳ� CItemCondition�� ������ �Ӱ�ġ ���ǽ��� �м��Ͽ�
		 *	��ָ� �߻���Ű�� �޽��.
		 *	@param CItemCondition pointer.
		 *	@see CItemCondition, CCollector
		 */
		void checkAlarm(CItemCondition *cond);

	private:
		CCollector *m_collector; /**< ���� ������ */
};

#endif /* __CALARMPROCESSOR_H__ */
