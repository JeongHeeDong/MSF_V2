


#ifndef __CITEMINSTANCE_H__
#define __CITEMINSTANCE_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "CQueue.h"


//! Item�� Instance ������ �����ϴ� Ŭ����.
/**
 *	Instance name, Instance value ������ �����Ѵ�.
 *	���� Instance name, Instance value�� ���� ������ ���� �����Ǿ�� �Ѵ�.
 *	scagent.xml ���Ͽ��� ������ ���� �������� ����� ������ ����Ѵ�.
 *	<instances>
 *		<instance name="test">test</instance>
 *	</instances>
 */
class CItemInstance
{
	public:
		/** ������ */
		CItemInstance();
		/** �Ҹ��� */
		virtual ~CItemInstance();
		/**
		 *	Instance ���� ��ȯ�ϴ� �޽��.
		 *	@return instance name.
		 */
		std::string getName() { return m_name; }
		/**
		 *	Instance ���� ��ȯ�ϴ� �޽��.
		 *	@return instance value.
		 */
		std::string getValue() { return m_value; }
		/**
		 *	������ ����Ҹ� ��ȯ�ϴ� �޽��.
		 *	@return CQueue pointer.
		 */
		CQueue *getDataQ() { return m_dataQ; }
		/**
		 *	Instance name�� �����ϴ� �޽��.
		 *	@param instance name.
		 */
		void setName(char *name) { m_name = name; }
		/**
		 *	Instance value�� �����ϴ� �޽��.
		 *	@param instance value.
		 */
		void setValue(char *value) { m_value = value; }
		/**
		 *	Instance name�� �����ϴ� �޽��.
		 *	@param instance name.
		 */
		void setName(std::string name) { m_name = name; }
		/**
		 *	Instance value�� �����ϴ� �޽��.
		 *	@param instance value.
		 */
		void setValue(std::string value) { m_value = value; }

	private:
		std::string m_name;		/**< instance name */
		std::string m_value;	/**< instance value */

		CQueue *m_dataQ; /**< ���������� �����͸� �����ϱ� ���� ������ ť */
};

void deleteCItemInstance(void *d);

#endif /* __CITEMINSTANCE_H__ */
