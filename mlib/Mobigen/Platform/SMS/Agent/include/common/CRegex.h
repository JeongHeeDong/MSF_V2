
#ifndef __REGEX_H__
#define __REGEX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <regex.h>


//!	����ǥ������ ó���ϴ� Ŭ����.
/**
 *	Ư�� �޽������� ���� ǥ�������� �־��� �޽����� �м� �� �Ľ��ϴ� Ŭ����.
 */
class CRegex
{
	protected:
		regex_t	m_re; /**< ���� ���� ������ ���� Ű ���� */
		char	*m_pattern;	/**< ���� ���Ͻ� */
		/**
		 *	���� ���Ͻ��� �ʱ�ȭ�ϴ� �޽��.
		 *	@param ���� ���� Ű.
		 *	@param ���� ���� ��.
		 *	@return return 1 if success, else return -1.
		 */
		int initRegex(regex_t *re, char *msg);
		/**
		 *	�־��� �޽������� ���� ���ϰ� ��ġ�ϴ� �޽����� ������ �޽��.
		 *	���� �޽����� ��ȯ���� ��ü���� �޸𸮸� ������ �־�� �Ѵ�.
		 *	@param ���� ���� Ű.
		 *	@param �Ľ� ��� �޽���(���ڿ�)
		 *	@return �Ľ̵� �޽���.
		 */
		char* getMatchedString(regex_t *re, char *msg);
		/**
		 *	�־��� �޽������� ���� ���ϰ� ��ġ�ϴ� �޽����� ù ��° �����͸� ������ �޽��.
		 *	@param ���� ���� Ű.
		 *	@param �Ľ� ��� �޽���(���ڿ�).
		 *	@param ���� ���ϰ� ��ġ�ϴ� ù��° ������.
		 */
		char* getMatchedStartPoint(regex_t *re, char *msg);
		/**
		 *	�־��� �޽������� ���� ���ϰ� ��ġ�ϴ� �޽����� ������ �����͸� ������ �޽��.
		 *	@param ���� ���� Ű.
		 *	@param �Ľ� ��� �޽���(���ڿ�).
		 *	@param ���� ���ϰ� ��ġ�ϴ� ������ ������.
		 */
		char* getMatchedEndPoint(regex_t *re, char *msg);
		/**
		 *	�־��� �޽������� ���� ���ϰ� ��ġ�ϴ� �޽����� ������ ������ �޽��.
		 *	@param ���� ���� Ű.
		 *	@param �Ľ� ��� �޽���(���ڿ�)
		 *	@return ���� ���ϰ� ��ġ�ϴ� �޽����� ����
		 */
		regmatch_t* getRegMatch(regex_t *re, char *msg);
		/**
		 *	���� ���Ͻ��� �޸𸮿��� �����ϴ� �޽��.
		 *	@param ���� ���� Ű.
		 */
		void freeRegex(regex_t *re);

	public:
		/** ������ */
		CRegex(){};
		/**
		 *	������
		 *	@param ���� ���Ͻ�
		 */
		CRegex(char *pattern);
		/** �Ҹ��� */
		~CRegex();
		/**
		 *	�־��� �޽������� ���� ���ϰ� ��ġ�ϴ� �޽����� ������ �޽��.
		 *	���� �޽����� ��ȯ���� ��ü���� �޸𸮸� ������ �־�� �Ѵ�.
		 *	@param �Ľ� ��� �޽���(���ڿ�)
		 *	@return �Ľ̵� �޽���.
		 */
		char* getMatchedString(char *msg);
		/**
		 *	���� ���Ͻ��� �����ϴ� �޽��.
		 *	@param ���� ���Ͻ�
		 */
		void setPattern(char *pattern);
		/**
		 *	�־��� �޽����� ���� ���ϰ� ��ġ�ϴ� �޽����� �����ϴ��� ���θ� �Ǵ��ϴ� �޽��.
		 *	@param �޽���(���ڿ�)
		 *	@return true : ���� ���ϰ� ��ġ�ϴ� ���ڿ��� ����, false : ���� ���ϰ� ��ġ�ϴ� ���ڿ��� ����.
		 */
		bool isMatched(char *str);
		
};

#endif
