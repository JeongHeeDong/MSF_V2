

#ifndef __CAGENTCONFCOLLECTOR_H__
#define __CAGENTCONFCOLLECTOR_H__ 1

#include "CCollector.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class CAgentConfCollector:public CCollector
{
	public:
		/** ������ */
		CAgentConfCollector();
		/** �Ҹ��� */
		~CAgentConfCollector();
		/**
		 *	Agent Configuration ������ �����ϴ� �޽�带 overriding�Ѵ�.
		 *	Port, Oracle uid, pwd, sid ���� ������ �����Ͽ� SMS Manager�� �����Ѵ�.
		 *	@see CCollector.
		 */
		void collect();
		/**
		 *	��� �Ǵ��� ���� �޽��. ���� ������ ����.
		 */
		void isOverThreshold(CItemCondition *cond){};

		void makeMessage();
	private:
};

#endif /* __CAGENTCONFCOLLECTOR_H__ */
