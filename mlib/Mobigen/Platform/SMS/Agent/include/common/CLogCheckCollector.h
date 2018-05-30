

#ifndef __CLOGCHECKCOLLECTOR_H__
#define __CLOGCHECKCOLLECTOR_H__ 1

#include "CCollector.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 *	�α� ������ instance�� �� �ش� �ν��Ͻ��� ���� ���� ������ �����ϴ� ����ü.
 */
typedef struct _st_loginst {
	char instance[256];
	char fmt_instance[256];
	struct stat sbuf;
}st_loginst;

//! �α� ������ ������ �����Ͽ� �����ϴ� Ŭ����.
/**
 *	�α� ���ϸ�(instance name)�� �Ϲ� ���� �� ������ ���� ������ ���� ���°� �� �� �ִ�.
 *	%Y : 4�ڸ� �⵵.
 *	%y : 2�ڸ� �⵵.
 *	%m : 2�ڸ� ��.
 *	%d : 2�ڸ� ��.
 *	%H : 2�ڸ� �ð�.
 *	%M : 2�ڸ� ��.
 *	%S : 2�ڸ� ��.
 *	ex) instance�� "logfile_%Y-%m-%d"���, ���� ���ϸ��� "logfile_2006-04-25"�� ����ȴ�.
 */
class CLogCheckCollector:public CCollector
{
	public:
		/** ������ */
		CLogCheckCollector();
		/** �Ҹ��� */
		~CLogCheckCollector();
		/**
		 *	�α� ������ �����ϴ� �޽��. CCollector Ŭ������ �޽�带 overriding�Ѵ�.
		 *	@see CCollector.
		 */
		void collect();
		/**
		 *	���� �α� ������ �����ϴ� �޽��.
		 */
		void collectLog();
		/**
		 *	��ϵ� �ν��Ͻ�(�α� ����) ������ �α� ������ �����ϴ� �޽��.
		 *	ó�� �⵿�ÿ��� ������ �������� �ʰ�, �� ��° ���� �ֱ����, �߻��ϴ� �α� ������ �����Ͽ�,
		 *	CItemCondition�� ��ϵ� ��� �߻� ���ǰ� ���Ͽ� event�� �߻���Ų��.
		 *	@param �α� ����(instance) ����.
		 */
		void collectLogInstance(st_loginst *loginst);
		/**
		 *	�ð� ������ ����Ǿ� �α� ���ϸ��� ���ο� �ð����� ���� ���� ��쿡 �̸� Ȯ���ϱ� ���� �޽��.
		 *	���� ��� Instace�� "log.%Y-%m-%d"�� ��ϵǾ� �������� "log.2006-04-20"������ ������ �����ϴٰ�,
		 *	�ý����� ���� �ð��� 2006�� 4�� 21�Ϸ� �ٲ� ���� "log.2006-04-21"���Ϸ� ����Ǿ��� ������ �̿� ���� Ȯ���� �ʿ��Ѵ�.
		 */
		void checkFmtInstance();
		/**
		 *	����� ���ο� �α� ���ϸ����� �����ϴ� �޽��.
		 */
		void setFmtInstance();
		/**
		 *	�־��� ���ڿ��� ������ ��� �߻� ���ǽ�(CItemCondition)�� �����ϴ��� ���θ� �Ǵ��ϰ�,
		 *	��ָ� �߻���Ű�� �޽��.
		 *	@param �α� ���� ����(instance).
		 *	@param �α� ����(���ڿ�).
		 */
		void checkCondition(st_loginst *loginst, char *log);
		/**
		 *	��� �޽����� �����Ͽ� ��� �޽��� ���۷� �����ϴ� �޽��.
		 *	@param ��� �Ǵ� ���� ������ �����ϴ� CItemCondition pointer.
		 *	@param �α� ���� ����(Instance).
		 *	@param �α� ����(���ڿ�).
		 */
		void sendEvent(CItemCondition *cond, st_loginst *loginst, char *log);
		/**
		 *	������ �α� ������ SMS Manager�� �����ϱ� ���� �޽��� �������� ��ȯ�ϴ� �޽��.
		 */
		void makeMessage();
		/**
		 *	�α� ������ �� ������ ��ȸ�Ͽ� �����ϴ� �޽��.
		 *	@param �α� ���� ����(Instance).
		 *	@param �α� ó�� ���� ����. true : ó�� �⵿�Ͽ� �α׸� ����, false : ������ �α׸� ������ ���� ����.
		 */
		void setLogFileInfo(st_loginst *loginst, bool b);
		/** ��� �Ӱ�ġ �Ǵ��� �ϴ� �޽��. �� Ŭ���������� �ǹ̾���. */
		void isOverThreshold(CItemCondition *cond){};

	private:
		CQueue m_instq;		/**< �ν��Ͻ�(�α�����) ����Ʈ */
};

#endif /* __CLOGCHECKCOLLECTOR_H__ */
