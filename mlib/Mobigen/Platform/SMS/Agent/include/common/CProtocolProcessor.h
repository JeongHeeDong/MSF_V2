
#ifndef __CPROTOCOLPROCESSOR_H__
#define __CPROTOCOLPROCESSOR_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "CAgentEnvVar.h"
#include "CRegex.h"
#include "CMisc.h"
#include "CMessageFormatter.h"
#include "CPolicyItem.h"

#define OPCODE_COL 1
#define OPCODE_GET 2
#define OPCODE_SET 3
#define OPCODE_GETCOND 4
#define OPCODE_SETCOND 5
#define OPCODE_ADDCOND 6
#define OPCODE_DELCOND 7
#define OPCODE_COLINST 8
#define OPCODE_GETINST 9
#define OPCODE_SETINST 10
#define OPCODE_ADDINST 11
#define OPCODE_DELINST 12

#define MAX_ATTRIBUTE_NUM 20

#define STR_COMMAND_PATTERN "((COL)|(GET)|(SET)|(COLINST)|(GETINST)|(SETINST)|(ADDINST)|(DELINST)|(GETCOND)|(SETCOND)|(ADDCOND)|(DELCOND)):CODE=[0-9a-zA-Z]+.*"

#define SC_ITEM_CODE_USERINFO				"UserInfo"
#define SC_ITEM_ATTR_USERID 				"userid"
#define SC_ITEM_ATTR_PASSWD 				"passwd"
#define SC_ITEM_ATTR_ACCESSIP 				"accessip"

#define SC_ITEM_ATTR_SCHEDULE 				"schedule"
#define SC_ITEM_ATTR_EVENT_SCHEDULE 		"eschedule"
#define SC_ITEM_ATTR_ENABLE 				"enable"
#define SC_ITEM_ATTR_METHOD 				"method"
#define SC_ITEM_ATTR_LEVEL 					"level"
#define SC_ITEM_ATTR_ELEMENT 				"element"
#define SC_ITEM_ATTR_INSTANCE 				"INST"
#define SC_ITEM_ATTR_CONDITION 				"COND"
#define SC_ITEM_ATTR_CONDITIONID 			"CONDID"

/**
 *	���� ��û ��ɾ��� ���� ���� �Ķ���Ͱ�(param_name=value)�� �����ϴ� ����ü
 */
typedef struct _st_attribute {
	std::string name;
	std::string value;
}st_attribute;

/**
 *	���� ��û ��ɾ �Ľ��Ͽ� ��� �ڵ�, item �ڵ�, item parameter�� ���� ������ �����ϴ� ����ü.
 */
typedef struct _st_cmd {
	unsigned int opcode;
	std::string itemcode;
	int attr_num;
	st_attribute attr[MAX_ATTRIBUTE_NUM];
}st_cmd;

//!	SMS Manager�κ��� ���ŵ� ��� �ڵ带 ���� �м��ϰ� ó���ϴ� Ŭ����.
/**
 *	SMS Manager�κ��� ���ŵ� ��� �ڵ尡 ������ syntax�� �´��� �˻��ϰ�,
 *	������ �Ծ࿡ ���� ��� �ڵ带 �м��Ͽ�, ��û �Ǿ��� ��ɾ ó���ϴ� Ŭ����.
 */
class CProtocolProcessor
{
	public:
		/**
		 *	������\n
		 *	��� �ڵ忡 ���� ���� ǥ������ �ʱ�ȭ�Ѵ�.
		 */
		CProtocolProcessor(){ m_reg = new CRegex(STR_COMMAND_PATTERN); }
		/**
		 * �Ҹ���
		 */
		~CProtocolProcessor(){ delete m_reg; }
		/**
		 *	SMS Manager�κ��� ��û�� ��� �ڵ带 �м� �� ó���ϴ� �ֻ��� �޽��.
		 *	@param command message(���ŵ� ��ɾ�).
		 */
		void process(char *pcmd);
		/**
		 *	SMS Manager�κ��� ���ŵ� ��� �ڵ忡 ���� �б� ó���ϴ� �޽��.
		 *	@param command message(���ŵ� ��ɾ�).
		 */
		void execute(char *pcmd);
		/**
		 *	SMS Manager�κ��� "COL" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execCOL(char *pcmd);
		/**
		 *	SMS Manager�κ��� "GET" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execGET(char *pcmd);
		/**
		 *	SMS Manager�κ��� "SET" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execSET(char *pcmd);
		/**
		 *	SMS Manager�κ��� "GETINST" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execGETINST(char *pcmd);
		/**
		 *	SMS Manager�κ��� "SETINST" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execSETINST(char *pcmd);
		/**
		 *	SMS Manager�κ��� "ADDINST" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execADDINST(char *pcmd);
		/**
		 *	SMS Manager�κ��� "DELINST" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execDELINST(char *pcmd);
		/**
		 *	SMS Manager�κ��� "GETCOND" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execGETCOND(char *pcmd);
		/**
		 *	SMS Manager�κ��� "SETCOND" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execSETCOND(char *pcmd);
		/**
		 *	SMS Manager�κ��� "ADDCOND" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execADDCOND(char *pcmd);
		/**
		 *	SMS Manager�κ��� "DELCOND" ��� �ڵ�� ��û�� ��� �̸� ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void execDELCOND(char *pcmd);
		/**
		 *	SMS Manager�κ��� "SET" ��� �߿��� ITEM CODE�� "UserInfo"�� ���\n
		 *	SMS Agent ���� ������ ó���ϴ� �޽��.
		 *	@param command message(���ŵ�  ��ɾ�).
		 */
		void setUserInfo(char *pcmd);
		/**
		 *	SMS Manager�κ��� ���ŵ� ��ɾ ������ �Ծ࿡ �´��� �˻��ϰ�\n
		 *	�Ľ��ϴ� �޽��.
		 *	@param command message(���ŵ� ��ɾ�)
		 *	@return �Ľ̵� ��ɾ�.
		 */
		char * parse(char *pcmd);
		/**
		 *	SMS Agent�� �⵿�ϴµ� �ʿ��� ȯ�� ���� �� item ������ �����ϴ� ��ü�� �����ϴ� �޽��.
		 *	@param CAgentEnvVar pointer.
		 *	@see CAgentEnvVar, CAgentConfigVar.
		 */
		void setEnvVar(CAgentEnvVar *var){ m_envvar = var; }
		/**
		 *	SMS Agent�� �⵿�ϴµ� �ʿ��� ȯ�� ���� �� item ������ �����ϴ� ��ü�� ��ȸ�ϴ� �޽��.
		 *	@return CAGentEnvVar pointer.
		 *	@see CAgentEnvVar, CAgentConfigVar.
		 */
		CAgentEnvVar* getEnvVar(){ return m_envvar; }

	private:
		CRegex *m_reg;				/**< ��ɾ �Ľ��� ���� ǥ���Ŀ� ���� ������ �����ϴ� ��ü */
		CAgentEnvVar *m_envvar;		/**< ȯ�� ������ �����ϴ� ��ü */
		st_cmd m_cmd;				/**< ���� �м��� ��ɾ� ����ü */
		std::string m_itemcode;		/**< item code ���� */
		/**
		 *	��ɾ �Ľ��Ͽ� ���� �м��� ��ɾ� ����ü�� �����ϴ� �޽��.
		 *	@param command message(���ŵ� ��ɾ�).
		 *	@return false : syntax error, else true
		 */
		bool parseCommand(char *);
};

#endif /* __CPROTOCOLPROCESSOR_H__ */
