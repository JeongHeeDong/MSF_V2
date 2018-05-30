

#ifndef _CITEMCONDITION_H__
#define _CITEMCONDITION_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>

#define MAX_COND_COUNT 20

#define COND_OPCODE_EGT '1'
#define COND_OPCODE_GT	'2'
#define COND_OPCODE_ELT	'3'
#define COND_OPCODE_LT	'4'
#define COND_OPCODE_NEQ	'5'
#define COND_OPCODE_EQ	'6'
#define COND_OPCODE_SUBSTR	'7'
#define COND_OPCODE_NSUBSTR	'8'


/**
 *	���(�Ӱ�ġ) �Ǵ� ���� �� ���� ���� �����ϴ� ����ü.
 *	OPCODE : >=, >, <=, <, !=, ==, <<, >>���� OPERATION CODE.
 *	TYPE : double, string ���� ���� �� ����.
 *	val : ���� �Ǵ� ���ذ�.
 */
typedef struct st_conditem
{
	char opcode;
	char type;
	union {
		double d;
		char s[1024];
	}val;
}st_conditem;

/**
 *	��� �Ǵ� ������ �����ϴ� ����ü.
 *	COUNT : ��� �Ǵ� ���� ����.
 *	C : AND, OR ���� ���� ����.
 *	ITEM : �� �Ǵ� ����. st_conditem ��.
 */
typedef struct st_condition
{
	int count;
	char c[MAX_COND_COUNT];
	st_conditem item[MAX_COND_COUNT];
}st_condition;


//! ��� �Ӱ�ġ�� �Ǵ��ϴ� ������ �����ϴ� ���� ��ü.
/**
 *	condition id, ��� ���(severity or level), �Ӱ�ġ �Ǵ� ���(element), instance(�Ǵ� ��� instance)
 *	�Ӱ�ġ �Ǵ� ����(condition) ������ �����ϴ� Ŭ����.
 *	����� CPUPerf, NetworkPerf��, LogCheck item�� ���ؼ��� ���밡���Ѵ�.
 *	scagent.xml ���Ͽ��� ������ ���� �������� ����� ������ ����Ѵ�.
 *	<conditions>
 *		<condition id="1" instance="ALL" element="1" level="Major">&gt;=5</condition>
 *	</conditions>
 */
class CItemCondition
{
	public:
		/** ������ */
		CItemCondition();
		/** �Ҹ��� */
		virtual ~CItemCondition();
		/**
		 *	condition id�� ������ �޽��.
		 *	@return condition id.
		 */
		unsigned int getIndex() { return m_index; }
		/**
		 *	element ��ȣ�� ������ �޽��.
		 *	element�� ��� �Ǵ� ��� �׸��� ��ȣ�� �ǹ��ϸ�, 
		 *	�� �׸��� ��ȣ�� COL������� �����͸� ��ȸ�� ��쿡
		 *	������� �������� ���̺��� ��� ������� �ο��ȴ�.
		 *	@return element number.
		 */
		unsigned int getElement() { return m_element; }
		/**
		 *	��� �Ӱ�ġ �Ǵ� ��� ��ü���� ��ȯ�ϴ� �޽��.
		 *	@return instance name.
		 */
		std::string getInstanceName() { return m_instName; }
		/**
		 *	��� �Ӱ�ġ �Ǵ� ������ ��ȯ�ϴ� �޽��.
		 *	��ü instance�� "ALL"�� �����ϸ� �ȴ�.
		 *	@return �Ӱ�ġ �Ǵ� ����.
		 */
		std::string getCondition() { return m_condition; }
		/**
		 *	��� ��� ������ ��ȯ�ϴ� �޽.
		 *	������ ��� ���('Critical', 'Major', 'Minor', 'Warning', 'Undeterminate')�� ��ȯ�Ѵ�.
		 *	@return alarm severity.
		 */
		std::string getSeverity() { return m_severity; }

		/**
		 *	condition id�� �����ϴ� �޽��.
		 *	@param condition id.
		 */
		void setIndex(unsigned int index) { m_index = index; }
		/**
		 *	element number�� �����ϴ� �޽��.
		 *	@param element number.
		 */
		void setElement(unsigned int element) { m_element = element; }
		/**
		 *	Instance ���� �����ϴ� �޽��.
		 *	��� Instance�� ��쿡�� "ALL"�� �����ϸ� �ȴ�.
		 *	@param instance name.
		 */
		void setInstanceName(std::string instName) { m_instName = instName; }
		/**
		 *	�Ӱ�ġ �Ǵ� ������ �����ϴ� �޽��.
		 *	��� �߻� ����(�Ӱ�ġ)�� �����Ѵ�.
		 *	@param �Ӱ�ġ �Ǵ� ����.
		 */
		void setCondition(std::string condition) { m_condition = condition; }
		/**
		 *	��� ����� �����ϴ� �޽��.
		 *	��� ���('Critical', 'Major', 'Minor', 'Warning', 'Undeterminate' ��)�� �����Ѵ�.
		 *	@param alarm severity.
		 */
		void setSeverity(std::string severity) { m_severity = severity; }
		/**
		 *	��� �߻� ���θ� �Ǵ��ϴ� �޽��.
		 *	�־��� ���� �Ӱ�ġ �Ǵ� ���ǰ� ���Ͽ� ��� �߻� ���θ� �Ǵ��Ѵ�.
		 *	@param ������ ���� unsigned integer value.
		 *	@return true : �Ӱ�ġ �ʰ� Ȥ�� ��� �߻�, false : �Ӱ�ġ �̴� Ȥ�� ��� ����. 
		 */
		bool isOverThreshold(unsigned int value) { return isOverThreshold((unsigned long) value); }
		/**
		 *	��� �߻� ���θ� �Ǵ��ϴ� �޽��.
		 *	�־��� ���� �Ӱ�ġ �Ǵ� ���ǰ� ���Ͽ� ��� �߻� ���θ� �Ǵ��Ѵ�.
		 *	@param ������ ���� unsigned long value.
		 *	@return true : �Ӱ�ġ �ʰ� Ȥ�� ��� �߻�, false : �Ӱ�ġ �̴� Ȥ�� ��� ����. 
		 */
		bool isOverThreshold(unsigned long value);
		/**
		 *	��� �߻� ���θ� �Ǵ��ϴ� �޽��.
		 *	�־��� ���� �Ӱ�ġ �Ǵ� ���ǰ� ���Ͽ� ��� �߻� ���θ� �Ǵ��Ѵ�.
		 *	@param ������ ���� integer value.
		 *	@return true : �Ӱ�ġ �ʰ� Ȥ�� ��� �߻�, false : �Ӱ�ġ �̴� Ȥ�� ��� ����. 
		 */
		bool isOverThreshold(int value);
		/**
		 *	��� �߻� ���θ� �Ǵ��ϴ� �޽��.
		 *	�־��� ���� �Ӱ�ġ �Ǵ� ���ǰ� ���Ͽ� ��� �߻� ���θ� �Ǵ��Ѵ�.
		 *	@param ������ ���� long value.
		 *	@return true : �Ӱ�ġ �ʰ� Ȥ�� ��� �߻�, false : �Ӱ�ġ �̴� Ȥ�� ��� ����. 
		 */
		bool isOverThreshold(long value);
		/**
		 *	��� �߻� ���θ� �Ǵ��ϴ� �޽��.
		 *	�־��� ���� �Ӱ�ġ �Ǵ� ���ǰ� ���Ͽ� ��� �߻� ���θ� �Ǵ��Ѵ�.
		 *	@param ������ ���� double value.
		 *	@return true : �Ӱ�ġ �ʰ� Ȥ�� ��� �߻�, false : �Ӱ�ġ �̴� Ȥ�� ��� ����. 
		 */
		bool isOverThreshold(double value);
		/**
		 *	��� �߻� ���θ� �Ǵ��ϴ� �޽��.
		 *	�־��� ���� ��� �Ǵ� ���ǰ� ���Ͽ� ��� �߻� ���θ� �Ǵ��Ѵ�.
		 *	@param ������ ���� string value.
		 *	@return true : ��� �߻�, false : ��� ����. 
		 */
		bool isOverThreshold(std::string cond);
		/**
		 *	��� �߻� ���θ� �Ǵ��ϴ� �޽��.
		 *	�־��� ���� ��� �Ǵ� ���ǰ� ���Ͽ� ��� �߻� ���θ� �Ǵ��Ѵ�.
		 *	@param ������ ���� character value.
		 *	@return true : ��� �߻�, false : ��� ����. 
		 */
		bool isOverThreshold(char *value);
		/**
		 *	�־��� ���ڿ����� ������(>=, >, <=, <, ==, !=, <<, >>)�� �Ľ��Ѵ�.
		 *	@param �Ӱ�ġ �Ǵ� ���ǽ�.
		 *	@return true : parsing success, false : parsing fail.
		 */
		bool checkOperator(char *pcmd);
		/**
		 *	�־��� ��(double)�� �Ӱ�ġ ����(st_conditem)�� ���Ͽ� ��� �߻� ���θ� �Ǵ��ϴ� �޽��.
		 *	@param ���� ��� �Ӱ�ġ �Ǵ� ����.
		 *	@param ������ ����(double)
		 *	@return true : ��� �߻�, false : ��� ����.
		 */
		bool checkCondition(st_conditem *item, double val);
		/**
		 *	�־��� ���ڿ��� �Ӱ�ġ ����(st_conditem)�� ���Ͽ� ��� �߻� ���θ� �Ǵ��ϴ� �޽��.
		 *	@param ���� ��� �Ӱ�ġ �Ǵ� ����.
		 *	@param ������ ����(���ڿ�)
		 *	@return true : ��� �߻�, false : ��� ����.
		 */
		bool checkCondition(st_conditem *item, char *val);
		/**
		 *	�Ӱ�ġ �Ǵ� ������ ���� ������ �� ����(AND, OR)�� �������� �̷���� ���
		 *	�־��� ��(double)�� �Ӱ�ġ ������ �� �Ǵ��� ������� ������ ���� ����� �� ����(AND, OR)�� ����� ��ȯ�ϴ� �޽��.
		 *	@param ���� �Ӱ�ġ �Ǵ� �����.
		 *	@param �� ������(AND, OR).
		 *	@param �Ӱ�ġ �Ǵ� ����.
		 *	@param ������ ����(double).
		 *	@return true : ��� �߻�, false : ��� ����.
		 */
		bool checkCondition(bool b, char op, st_conditem *item, double val);
		/**
		 *	�Ӱ�ġ �Ǵ� ������ ���� ������ �� ����(AND, OR)�� �������� �̷���� ���
		 *	�־��� ���ڿ��� �Ӱ�ġ ������ �� �Ǵ��� ������� ������ ���� ����� �� ����(AND, OR)�� ����� ��ȯ�ϴ� �޽��.
		 *	@param ���� �Ӱ�ġ �Ǵ� �����.
		 *	@param �� ������(AND, OR).
		 *	@param �Ӱ�ġ �Ǵ� ����.
		 *	@param ������ ����(���ڿ�).
		 *	@return true : ��� �߻�, false : ��� ����.
		 */
		bool checkCondition(bool b, char op, st_conditem *item, char *val);
		/**
		 *	�־��� �Ӱ�ġ �Ǵ� ������ parsing�Ͽ� m_parsecondition ������ �� ������ ����ϴ� �޽��.
		 *	���� ��� �Ǵ��� m_parsecondition�� �־��� ���ǰ� �� �Ǵ��Ͽ� ��� �߻� ���θ� �Ǵ��Ѵ�.
		 *	@param �Ӱ�ġ �Ǵ� ���ǽ�.
		 */
		void parseCondition(char *msg);

		/**
		 *	�Ǵ����ǽ��� ����Ǵ� ��� �ٽ� �Ľ��ϵ��� reset�Ѵ�.
		 *	@param void
		 *  @return void
		 */
		void setChange() { isChange = true; }

	private:
		unsigned int m_index;				/**< condition id */
		unsigned int m_element;				/**< element number */
		std::string m_instName;				/**< instance name */
		std::string m_condition;			/**< �Ӱ�ġ �Ǵ� ���ǽ� */
		std::string m_severity;				/**< ��� ��� */
		st_condition m_parsecondition;		/**< ���� �м��� �Ӱ�ġ �Ǵ� ���ǽ� */
		bool isChange;						/**< �Ӱ�ġ�� ����� ��� �ٽ� �м��ϴ� �÷��� */
};

void deleteCItemCondition(void *d);

#endif /* _CITEMCONDITION_H__ */
