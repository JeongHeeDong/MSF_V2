
#ifndef _CITEM_H__
#define _CITEM_H__ 1


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <iostream>

#include "CQueue.h"
#include "CItemInstance.h"
#include "CItemCondition.h"

typedef struct _st_item_alarm {
	char instance[128];
	int condid;
} st_item_alarm;

//! ���� ��� item ���� ��ü.
/**
 *	item code, ���� �ֱ�(schedule), ��� ���� �ֱ�(eschedule), ��������(enable), �󼼼�������(method)
 *	���� ��� instance, ��� �Ӱ�ġ �Ǵ� condition ���� ���� �����Ѵ�.
 */

class CItem
{
	public:
		/** ������ */
		CItem();
		/** �Ҹ��� */
		virtual ~CItem();
		/**
		 *	method for getting item code.
		 *	@return item code.
		 */
		std::string getCode() { return m_code; }
		/**
		 *	method for getting item description.
		 *	@return item code description.
		 */
		std::string getName() { return m_name; }

		/**
		 *	method for getting schedule(���� ���� �ֱ�) period.
		 *	@return schedule period.
		 */
		unsigned long getSchedule() { return m_schedule; }

		/**
		 *	method for getting event schedule period(��� ���� �ֱ�).
		 *	@return event schedule period.
		 */
		unsigned long getEventSchedule() { return m_eventSchedule; }
		/**
		 *	���� ���� ���θ� ��ȯ�ϴ� �޽��.
		 *	@return ���� ���� ����('O', 'X')
		 */
		std::string getEnable() { return m_enable; }
		/**
		 *	������ ���� ���� ���θ� ��ȯ�ϴ� �޽��(ACTIVE/PASSIVE/EVENT).
		 *	@return ���� ���� ����('OOO', 'XXX', ...)
		 */
		std::string getMethod() { return m_method; }
		/**
		 *	���� ���� �ð��� ��ȯ�ϴ� �޽��.
		 *	@return ���� ���� �ð�.
		 */
		time_t getCollectTime() { return m_collect; }
		/**
		 *	��� ���� �ð��� ��ȯ�ϴ� �޽��.
		 *	@return ���� ���� �ð�.
		 */
		time_t getEventCollectTime() { return m_eventCollect; }
		/**
		 *	item���� ���� ��ϵ� instance(CItemInstance) ��ü�� �����ϰ� �ִ� ����Ʈ�� ��ȯ�ϴ� �޽��.
		 *	@return instance(CItemInstance) ��ü�� �����ϰ� �ִ� ����Ʈ Queue
		 */
		CQueue *getInstanceQ() { return m_instQ; }
		/**
		 *	item���� ��� �Ǵ� �Ӱ�ġ �� ��� ���� ��� instance ������
		 *	�����ϴ� condition(CItemCondition) ��ü�� �����ϰ� �ִ� ����Ʈ�� ��ȯ�ϴ� �޽��.
		 *	@return condition(CItemCondition) ��ü�� �����ϰ� �ִ� ����Ʈ Queue
		 */
		CQueue *getConditionQ() { return m_condQ; }
		/**
		 *	condition id�� instance ���� Ű���Ͽ� ��� �߻� ���� ������ �����ϰ� �ִ� ����Ʈ�� ��ȯ�ϴ� �޽��.
		 *	@return ��� �߻� ���� ����.
		 */
		CQueue *getAlarmInstanceQ() { return m_alarmInstanceQ; }

		/**
		 *	item code ������ �����ϴ� �޽��.
		 *	@param item code.
		 */
		void setCode(std::string code) { m_code = code; }
		/**
		 *	item description ������ �����ϴ� �޽��.
		 *	@param	item description.
		 */
		void setName(std::string name) { m_name = name; }
		/**
		 *	���� ���� �ֱ⸦ �����ϴ� �޽��.
		 *	@param ���� ���� �ֱ�(��:seconds)
		 */
		void setSchedule(unsigned long schedule) { m_schedule = schedule; }
		/**
		 *	��� ���� ���� �ֱ⸦ �����ϴ� �޽��.
		 *	@param ��� ���� ���� �ֱ�(��:seconds)
		 */
		void setEventSchedule(unsigned long eventSchedule) { m_eventSchedule = eventSchedule; }
		/**
		 *	���� ���� ���θ� �����ϴ� �޽��('0' or 'X')
		 *	@param ���� ���� ����('O' or 'X')
		 */
		void setEnable(std::string enable) { m_enable = enable; }
		/**
		 *	���� ���� �� ���θ� �����ϴ� �޽��.
		 *	@param ���� ���� �� ����(ACTIVE/PASSIVE/EVENT)
		 */
		void setMethod(std::string method) { m_method = method; }
		/**
		 *	���� ���� ���� �ð��� �����ϴ� �޽��.
		 *	@param ���� ���� ���� �ð�.
		 */
		void setCollectTime(time_t collect) { m_collect = collect; }
		/**
		 *	���� ��� ���� �ð��� �����ϴ� �޽��.
		 *	@param ���� ��� ���� �ð�.
		 */
		void setEventCollectTime(time_t eventCollect) { m_eventCollect = eventCollect; }
		/**
		 *	���� ������ �����ϰ� �ִ��� ���θ� �Ǵ��ϴ� �޽��.
		 *	���� ������ �����ϰ� �ִ� item�� scheduler�� ���� ��û�� ���� �ʴ´�.
		 *	@param ���� ���� ����(true : ���� ���� ���� ��, false : ������ �����ϰ� ���� ����).
		 */
		void setIsCollect(bool b) { m_isCollect = b; }

		/**
		 *	item�� ���� ��� instance�� �߰��ϴ� �޽��.
		 *	@param	���� ��� instance(CItemInstance) pointer.
		 */
		void addInstance(CItemInstance *inst);
		/**
		 *	item�� �Ӱ�ġ �Ǵ� ������ �߰��ϴ� �޽��.
		 *	@param �Ӱ�ġ �Ǵ� ����(CItemCondition) pointer.
		 */
		void addCondition(CItemCondition *cond);
		/**
		 *	item�� ���� �߻��� ��� ����.
		 *	@param condition id, instance name�� Ű�� �ϴ� ���� ��� ��� ����.
		 */
		void delAlarm(st_item_alarm *alarm);
		/**
		 *	item�� �߻��� ��ָ� ���.
		 *	@param condition id, instance name�� Ű�� �ϴ� �߰� ��� ��� ����.
		 */
		void addAlarm(st_item_alarm *alarm);
		/**
		 *	condition id, instance name�� Ű�� �ϴ� ��ְ� �߻��� ���� �ִ����� �Ǵ��ϴ� �޽��. ��� �ߺ� ó���� ���� ����.
		 *	@param condition id, instance name�� Ű�� �ϴ� ��� ����.
		 */
		bool isAlarm(st_item_alarm *alarm);
		
		/**
		 *	���� item�� ���� ������ ���������� �ƴ��� ���θ� �Ǵ��ϴ� �޽��.
		 *	@return true : ������, false : ���� ����.
		 */
		bool isCollect() { return m_isCollect; }
		/**
		 *	���� ���� ���� ���θ� �Ǵ��ϴ� �޽��.
		 *	@return true : ���� ����,  false : ���� �Ұ�.
		 */
		bool isEnable();
		/**
		 *	SMS Manager�κ��� command�� �����޾Ƽ� ���� �ϴ� ��� ���� ����.
		 *	@return true : ���� ����, false : ���� ����.
		 */
		bool isPassive();
		/**
		 *	ACTIVE �޽��� ���� ���θ� �Ǵ��ϴ� �޽��.
		 *	@return true : ����, false : ���� ����.
		 */
		bool isReportable();
		/**
		 *	EVENT ���� ���θ� �Ǵ��ϴ� �޽��.
		 *	@return true : ����, false : ���� ����.
		 */
		bool isEnableEvent();

		/**
		 *	item ��ü ������ ����Ʈ�ϴ� �޽��
		 */
		void printItem()
		{
			std::cout << "code : " << m_code ;
			std::cout << ", name : " << m_name ;
			std::cout << ", schedule : " << m_schedule ;
			std::cout << ", eschedule : " << m_eventSchedule ;
			std::cout << ", enable : " << m_enable ;
			std::cout << ", method : " << m_method << std::endl;
		}

	private:
		std::string m_code;				/**< item code */
		std::string m_name;				/**< item description */
		unsigned long m_schedule;		/**< ���� ���� �ֱ� */
		unsigned long m_eventSchedule;	/**< ��� ���� ���� �ֱ� */
		std::string m_enable;			/**< ���� ���� ���� ���� */
		std::string m_method;			/**< ���� ���� ���� �� ����(ACTIVE/PASSIVE/EVENT) */
		CQueue *m_instQ;				/**< ITEM INSTANCE�� �����ϴ� ����Ʈ ť */
		CQueue *m_condQ;				/**< ITEM CONDITION�� �����ϴ� ����Ʈ ť */
		CQueue *m_alarmInstanceQ;		/**< ���� ��� ���� ������ �����ϴ� ����Ʈ ť */

		time_t m_collect;				/**< ���� ���� �ð� */
		time_t m_eventCollect;			/**< ��� ���� ���� �ð� */

		bool m_isCollect;				/**< ���� ���� ���� ���� */
};


void deleteCItem(void *d);

#endif /* _CITEM_H__ */
