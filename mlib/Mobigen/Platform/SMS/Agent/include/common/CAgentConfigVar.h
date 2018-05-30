
#ifndef _CAGENTCONFIGVAR_H__
#define _CAGENTCONFIGVAR_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <string>

#include "MD5LIB.h"
#include "MD5.h"

#include "tinyxml.h"
#include "CItem.h"

//! scagent.xml ���Ϸκ��� ȯ�� ���� ���� �� Item Code ������ �ε��Ͽ� �����ϴ� Ŭ����
/*!
 *	Item Code ������ �о CItem class�� �����ϰ� �����ϸ�, 
 *	��Ÿ ����Ŭ �α��ο� �ʿ��� ����, 
 *	SMS Manager�� ����ϱ� ���� ���� ��Ʈ �� 
 *	SMS Agent�� �α����ϱ� ���� ���� �� ���� ��� ������ ������ �����Ѵ�.
*/
class CAgentConfigVar
{
	public:
		//! ������
		/*! Detail : */
		CAgentConfigVar();
		//! �Ҹ���.
		/*! Detail : */
		virtual ~CAgentConfigVar();
		//! scagent.xml ������ �ε��ϴ� �Լ�.
		/*! xml ���Ϸκ��� Item Code �� ��Ÿ ȯ�� ������ �ε��Ѵ�. */
		void loadXMLConfigVar();
		//! �־��� Item Code�� �ش��Ѵ� Item ������ ������ �Լ�.
		/*!
			\param a charater pointer.
			\return return CItem class, if failed return NULL.
			\sa CItem
		*/
		CItem *getItem(char *code){
			std::string strcode = code;
			return getItem(strcode); }

		//! �־��� Item Code�� �ش��Ѵ� Item ������ ������ �Լ�.
		/*!
			\param a string value
			\return return CItem class, if failed return NULL.
			\sa CItem class.
		*/
		CItem *getItem(std::string code);

		//! Ư�� Item�� �߰��ϴ� �Լ�.
		/*!
			\param CItem pointer.
			\sa CItem.
		*/
		void addItem(CItem *item);
		//! Ư�� Item�� ������ �����ϴ� �Լ�.
		/*!
			\param CItem pointer.
			\sa CItem.
		*/
		void setItem(CItem *item);
		//! Ư�� Item�� ������ �����ϴ� �Լ�.
		/*!
			\param string item code name.
		*/
		void delItem(std::string code);
		/** Item list�� ��ȯ�ϴ� �Լ�.
		 *	���� SMS Agent�� �����ϰ� �ִ� CItem class(item code)�� �����ϰ� �ִ� ����Ʈ ť.�� ��ȯ�Ͽ� �ش�.
		 *	@return CQueue pointer.
		*/
		CQueue *getItemQ();
		//! scagent.xml ������ ������Ʈ�ϴ� �Լ�.
		/*!
			���� SMS Agent�� �����ϰ� �ִ� item code �� ȯ�� ���� ������ scagent.xml���Ϸ� �����ϴ� �Լ��̴�.
		*/
		void unloadXMLConfigVar();

		/**
		 *	XML Document(m_doc)�� Ư�� item code�� �߰��ϴ� �Լ�.
		 *	@param CItem class
		 *	@return �߰��� XML Element pointer.
		 */
		TiXmlElement *makeXmlElement(CItem *item);

		/**
		 *	�־��� name�� �ش��ϴ� XML Element�� �����Ͽ�, 
		 *	�ش� element�� ù��° ������ str XML Text�� �����Ͽ� �߰��� ��
		 *	XML Element XML Document(m_doc)�� �߰��Ѵ�.
		 *	example) <instance name="test" /> �� ���, name = name, test = str �� �ȴ�.
		 *	@param �߰��� XML Text�� �� ����(string).
		 *	@param �� ������ �߰��� XML Element.
		 *	@param �߰��� XML Element�� Title. 
		 */
		void linkEndChild(std::string str, TiXmlElement *elem, const char *name);

		/**
		 *	�־��� name�� �ش��ϴ� XML Element�� �����Ͽ�, 
		 *	�ش� element�� ù��° ������ str XML Text�� �����Ͽ� �߰��� ��
		 *	XML Element XML Document(m_doc)�� �߰��Ѵ�.
		 *	example) <instance name="0" /> �� ���, name = name, 0 = l �� �ȴ�.
		 *	@param �߰��� XML Text�� �� ����(unsigned long).
		 *	@param �� ������ �߰��� XML Element.
		 *	@param �߰��� XML Element�� Title. 
		 */
		void linkEndChild(unsigned long l, TiXmlElement *elem, const char *name);

		/**
		 *	�־��� �ڵ忡 �ش��ϴ� item�� XML Document���� �����Ѵ�.
		 *	@param ������ item code.
		 */
		void removeDocItem(std::string code);
		
		/**
		 *	SMS Agent�� �����ϴ� ��� ������ SMS Manager�� �����ϱ� ���� ���� ��Ʈ�� ��ȯ�ϴ� �Լ�.
		 *	@return TCP/IP Alarm listen port.
		 */
		int getEventPort(){ return m_eventport; }

		/**
		 *	SMS Agent�� �����ϴ� �ܱ�(1�ð� ����) ���� ������ SMS Manager�� �����ϱ� ���� ���� ��Ʈ�� ��ȯ�ϴ� �Լ�.
		 *	@return TCP/IP short period Performance listen port.
		 */
		int getShortPerfPort() { return m_shortperfport; }

		/**
		 *	SMS Agent�� �����ϴ� �����(1�ð� �̻�) ���� ������ SMS Manager�� �����ϱ� ���� ���� ��Ʈ�� ��ȯ�ϴ� �Լ�.
		 *	@return TCP/IP long period Performance listen port.
		 */
		int getLongPerfPort() { return m_longperfport; }

		/**
		 *	SMS Manager�κ��� ���޹��� ����� ������ ������� SMS Manager�� �����ϱ� ���� ���� ��Ʈ�� ��ȯ�ϴ� �Լ�.
		 *	@return TCP/IP command response listen port.
		 */
		int getRespPort() { return m_respport; }

		/**
		 *	SMS Manager�κ��� ����� ���޹ޱ� ���� ���� ��Ʈ�� ��ȯ�ϴ� �Լ�.
		 *	@return TCP/IP command listen port.
		 */
		int getCmdPort() { return m_cmdport; }

		/**
		 *	SMS Manager�� SMS Agent���� ����� ���� ���� �� �� ���Ǻ� ���� �޽��� ������ �����ϱ� ���� ���� ��Ʈ�� ��ȯ�ϴ� �Լ�.
		 *	@return TCP/IP listen port to get session status.
		 */
		int getSessionPort() { return m_sessionport; }
		
		/**
		 *	SMS Agent�� �����ϱ� ���� ���� ������ ��ȯ�ϴ� �Լ�.
		 *	@return SMS Agent user id.
		 */
		std::string getUserid() { return m_userid; }

		/**
		 *	SMS Agent�� �����ϱ� ���� �н����� ������ ��ȯ�ϴ� �Լ�.
		 *	@return SMS Agent access password.
		 */
		std::string getPasswd() { return m_passwd; }

		/**
		 *	SMS Agent�� ������ ���� IP �뿪 ������ ��ȯ�ϴ� �Լ�.
		 *	@return permmitted access ip address.
		 */
		std::string getAccessIP() { return m_accessip; }
		
		/**
		 *	Database Type ������ ��ȯ�ϴ� �Լ�.
		 *	@return Database type
		 */
		std::string getDBType() { return m_dbtype; }

		/**
		 *	Oracle system ������ ��ȯ�ϴ� �Լ�.
		 *	@return Oracle system account.
		 */
		std::string getOraUID() { return m_orauid; }

		/**
		 *	Oracle system ������ ��ȣ�� ��ȯ�ϴ� �Լ�.
		 *	@return Oracle system account password.
		 */
		std::string getOraPasswd() { return m_orapasswd; }
		
		/**
		 *	Oracle SID ������ ��ȯ�ϴ� �Լ�.
		 *	@return Oracle SID.
		 */
		std::string getOraSID() { return m_orasid; }

		/**
		 *	method for setting database type
		 *	@param database type name
		 */
		void setDBType(char *dbtype) { m_dbtype = dbtype; }

		/**
		 *	method for setting oracle system account.
		 *	@param oracle system account user id.
		 */
		void setOraUID(char *uid) { m_orauid = uid; }

		/**
		 *	method for setting oracle SID.
		 *	@param oracle SID.
		 */
		void setOraSID(char *sid) { m_orasid = sid; }

		/**
		 *	method for setting oracle system account password.
		 *	@param oracle system account password.
		 */
		void setOraPasswd(char *passwd) { m_orapasswd = passwd; }

		/**
		 *	method for setting SMS Agent account user id.
		 *	@param SMS Agent account user id.
		 */
		void setUserid(char *userid) { m_userid = userid; }

		/**
		 *	method for setting SMS Agent account password.
		 *	@param SMS Agent password.
		 */
		void setPasswd(char *passwd) { m_passwd = passwd; }

		/** 
		 *	method for setting permmitted ip address to access SMS Agent.
		 *	@param permmitted ip address range(ex : 127.0.0.*)
		 */
		void setAccessIP(char *accessip) { m_accessip = accessip; }
		
		/**
		 *	�־��� userid�� �ش��ϴ� SMS Agent�� password �� ���� ��� ip address�� �����ϴ� �Լ�.
		 *	@param SMS Agent account user id.
		 *	@param SMS Agent account password.
		 *	@param permmitted ip address range.
		 */
		bool setUserInfo(std::string sid, std::string userid, std::string password);
		
		/**
		 * method for locking.
		 */
		void lock();

		/** method for unlocking */
		void unlock();

	private:
		TiXmlDocument *m_doc;	/**< scagent.xml ���Ϸκ��� �ε��� item �� ȯ�� ���� ������ �����ϰ� �ִ� XML Document */
		CQueue *m_itemQ;		/**< �ε��� CItem class�� �����ϰ� �ִ� ����Ʈ Ŭ���� */
		int m_eventport;		/**< SMS Agent���� �߻��ϴ� ��� ������ �����ϱ� ���� ��Ʈ */
		int m_shortperfport;	/**< SMS Agent���� �����Ǵ� �ܱ�(1�ð� ����) ���� ������ �����ϱ� ���� ��Ʈ */
		int m_longperfport;		/**< SMS Agent���� �����Ǵ� �����(1�ð� �̻�) ���� ������ �����ϱ� ���� ��Ʈ */
		int m_respport;			/**< SMS Manager�κ��� ���޹��� ����� ������ ����� �����ϱ� ���� ��Ʈ */
		int m_cmdport;			/**< SMS Manager�κ��� ��� �ڵ带 ���޹޴� ��Ʈ */
		int m_sessionport;		/**< ���� SMS Agent�� ���ӵ� ���� ���� �� �� ���Ǻ� ���� �޽��� ������ ��ȸ�ϱ� ���� ��Ʈ */
		std::string m_dbtype;	/**< Database type ���� */
		std::string m_orauid;	/**< ����Ŭ ���� user id(system ����) */
		std::string m_orapasswd; /**< ����Ŭ ���� �н����� */
		std::string m_orasid;	/**< ����Ŭ SID */
		std::string m_userid;	/**< SMS Agent ���� ���� */
		std::string m_passwd;	/**< SMS Agent ���� �н����� */
		std::string m_accessip; /**< SMS Manager�� ���� ��� IP �ּ� */
		pthread_mutex_t m_lock; /**< CAgentConfigVar Ŭ���� ���� ������ ���� ����ȭ ���� */

};

#endif /* _CAGENTCONFIGVAR_H__ */
