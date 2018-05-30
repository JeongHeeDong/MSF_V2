

#ifndef __CPOLICYITEM_H__
#define __CPOLICYITEM_H__ 1


#include "CAgentEnvVar.h"
#include "CMessageFormatter.h"


//! �����췯�� ���� ���� �����忡 ���� ��û�� �Ҷ� �ʿ��� ��å ������ �����ϴ� Ŭ����.
/**
 *	���� ��û item, ���� ����, ���� �ð�, ���� ��ɾ� ���� ������ ��� �ִ� ���� Ŭ�����̴�.
 */
class CPolicyItem 
{
	public:
		/** ������ */
		CPolicyItem() { m_instQ = new CQueue; }
		/** �Ҹ��� */
		~CPolicyItem() { delete m_instQ; }
		/** 
		 *	���� �ð� ������ �����ϴ� �޽�� 
		 *	@param ���� �ð�.
		 */
		void setPollTime(time_t t){ m_polltime = t; }
		/**
		 *	item ������ �����ϴ� �޽��.
		 *	@param CItem pointer.
		 */
		void setItem(CItem *item) { m_item = item; }
		/**
		 *	���� ���� ������ �����ϴ� �޽��. ���� ����(TYPE_PASSIVE, TYPE_ACTIVFE, TYPE_EVENT)
		 *	@param ���� ����(TYPE_PASSIVE, TYPE_ACTIVFE, TYPE_EVENT)
		 */
		void setPollType(unsigned int type) { m_polltype = type; }
		/**
		 *	�����ð� ������ ��ȸ�ϴ� �޽��.
		 *	@return ���� �ð�(seconds)
		 */
		time_t getPollTime() { return m_polltime; }
		/**
		 *	���� item Ŭ������ ��ȸ�ϴ� �޽��.
		 *	@return CItem pointer.
		 *	@see CItem
		 */
		CItem *getItem() { return m_item; }
		/**
		 *	���� ���� ������ ��ȸ�ϴ� �޽��.
		 *	@return ���� ����(TYPE_PASSIVE, TYPE_ACTIVFE, TYPE_EVENT)
		 */
		unsigned int getPollType() { return m_polltype; }
		/**
		 *	���� ��� �ν��Ͻ� ������ ��ȸ�ϴ� �޽��.\n
		 *	�ν��Ͻ��� ���� ���� ��ȸ ������ ��� �ν��Ͻ��� ��ȸ�Ѵ�.
		 *	@return CQueue pointer(instance queue)
		 */
		CQueue *getInstQ() { return m_instQ; }
		/**
		 *	SMS Manager�� ���� ���� ��û�� ��� ���� ��û�� ��ɾ �����ϴ� �޽��.
		 *	@param command(���� ��û ��ɾ�)
		 */
		void setCommand(char *cmd) { m_cmd = cmd; }
		/**
		 *	SMS Manager�� ���� ���� ��û�� ��� ���� ��û�� ��ɾ ��ȸ�ϴ� �޽��.
		 *	@return command(���� ��û ��ɾ�)
		 */
		std::string getCommand() { return m_cmd; }

	private:
		std::string m_cmd;			/**< ���� ��û ��ɾ� */
		time_t m_polltime;			/**< ���� �ð� */
		unsigned int m_polltype;	/**< ���� ���� */
		CItem *m_item;				/**< ���� item */
		CQueue *m_instQ;			/**< ���� ��� �ν��Ͻ� ���� ť */
};

#endif /* __CPOLICYITEM_H__ */
