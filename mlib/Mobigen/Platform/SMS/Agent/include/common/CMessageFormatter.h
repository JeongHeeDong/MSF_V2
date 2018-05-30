

#ifndef __CMESSAGEFORMATTER_H__
#define __CMESSAGEFORMATTER_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>


#include "CItem.h"


#define TYPE_PASSIVE 1
#define TYPE_EVENT 2
#define TYPE_ACTIVE 3


//! ������ �޽����� SMS Manager�� �Ծ�� �޽��� �������� ��ȯ�ϴ� Ŭ����.
/**
 *	�޽��� ������ ���� ���� 3���� �������� ��ȯ��Ų��.
 *		-# PASSIVE :\n
 *			${HOSTNAME} YYYY-MM-DD HH:MI:SS\n
 *			${ITEM_CODE} ${ITEM_DESCRIPTION}\n
 *			PASSIVE	${COMMAND}\n
 *			${DATA HEADER}\n
 *			${DATA}\n
 *			COMPLETED\n
 *		-# ACTIVE :\n
 *			${HOSTNAME} YYYY-MM-DD HH:MI:SS\n
 *			${ITEM_CODE} ${ITEM_DESCRIPTION}\n
 *			ACTIVE\n
 *			${DATA HEADER}\n
 *			${DATA}\n
 *			COMPLETED\n
 *		-# EVENT :\n
 *			${HOSTNAME} YYYY-MM-DD HH:MI:SS\n
 *			${ITEM_CODE} ${ITEM_DESCRIPTION}\n
 *			EVENT ${CONDITION} ${ELEMENT} ${SEVERITY} ${START/END}\n
 *			${DATA HEADER}\n
 *			${DATA}\n
 *			COMPLETED\n
 */
class CMessageFormatter
{
	public:
		/** ������ */
		CMessageFormatter();
		/** �Ҹ��� */
		~CMessageFormatter();
		/**
		 *	���� �ð��� �����ϴ� �޽��.
		 *	@param ���� �ð�.
		 */
		void setPollTime(time_t polltime) { m_polltime = polltime; }
		/**
		 *	�����ϴ� item(CItem) ������ �����ϴ� �޽��.
		 *	@param CItem pointer.
		 *	@see CItem.
		 */
		void setItem(CItem *item){ m_item = item; }
		/**
		 *	�������� ���� �׸� ���� Header ������ �����ϴ� �޽��.
		 *	@param ���� �׸� header ����.
		 */
		void setTitle(char *title) { m_title = title; }
		/**
		 *	PASSIVE�� ���� ������ ������ ���, SMS Manager�κ��� ���۹��� ���� ��ɾ �����ϴ� �޽��.
		 *	@param ���� ��û ��ɾ�.
		 */
		void setCommand(char *cmd) { m_cmd = cmd; }
		/**
		 *	���� ������ �����ϴ� �޽��.
		 *	@param ���� ����(TYPE_PASSIVE/TYPE_ACTIVE/TYPE_EVENT)
		 */
		void setType(unsigned int type){ m_type = type; }
		/**
		 *	������ �����Ͱ� ��� �������� ��쿡 ��� �Ǵ� ������ �����ϴ� �޽��.
		 *	@param ��� �Ǵ� ���� Ŭ����(CItemCondition) pointer.
		 *	@see CItemCondition
		 */
		void setItemCondition(CItemCondition *);
		/**
		 *	������ item code ������ �����ϴ� �޽��.
		 *	@param item code(character).
		 */
		void setItemCode(char *code);
		/**
		 *	������ item code ������ �����ϴ� �޽��.
		 *	@param item code(string).
		 */
		void setItemCode(std::string );
		/**
		 *	������ ������ ��� ������ ��� ��� �߻� ����.
		 *	@param true : START, end : END.
		 */
		void setEventStatus(bool b) { m_alarm = b; }
		/**
		 *	������ ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 *	@return ��ȯ�� �޽���.
		 */
		char * makeMessage();
		/**
		 *	���� �޽����� �����ϱ� ���� �޽��.
		 *	���� �ǹ� ����.
		 */
		std::string makeErrorMessage(char *msg);
		/**
		 *	���� �޽����� �����ϱ� ���� �޽��.
		 *	���� �ǹ� ����.
		 */
		std::string makeErrorMessage(std::string msg );
		/**
		 *	���� ���� ������ ��ȯ�ϴ� �޽��.
		 *	@return ���� ����(TYPE_ACTIVE/TYPE_PASSIVE/TYPE_EVENT)
		 */
		std::string getTypeCode();
		/**
		 *	�ۼ��� �޽����� �߰��ϴ� �޽��.
		 *	@param �߰� �޽���.
		 */
		void addMessage(char *msg) { m_msgQ.enqueue(msg, NULL); }

	private:
		bool m_alarm;			/**< ��� �߻�/����(START/END) ���� */
		unsigned int m_type;	/**< ������ ���� ����(TYPE_ACTIVE/TYPE_PASSIVE/TYPE_EVENT) */
		time_t m_polltime;		/**< ������ ���� �ð� */
		std::string m_code;		/**< ITEM CODE */
		std::string m_title;	/**< Message Title */
		std::string m_cmd;		/**< PASSIVE�� ��� ���� ��û ��ɾ�. */
		CItem *m_item;			/**< CItem */
		CItemCondition *m_cond;	/**< ��� �Ǵ� ���� */
		CQueue m_msgQ;			/**< �޽���(������) ť */	
};

#endif /* __CMESSAGEFORMATTER_H__ */
