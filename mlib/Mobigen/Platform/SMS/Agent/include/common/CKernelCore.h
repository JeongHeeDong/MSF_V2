
#ifndef __CKERNELCORE_H__
#define __CKERNELCORE_H__ 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <string>

#include "u_time.h"
#include "u_debug.h"
#include "u_dlist.h"
#include "u_process.h"
#include "u_operate.h"
#include "u_file.h"
#include "u_tokenize.h"
#include "u_bfsearch.h"
#include "u_user.h"

#include "sc_core.h"

//! System kernel �����͸� ��ȸ�ϱ� ���� interface class.
/**
 *	System kernel�� �����ϱ� ���� �������̽�(scCoreView) ������ �����ϸ�,
 *	Multi Thread�� ���� ������ ���� ������ �Ѵ�.
 */
class CKernelCore
{
	public:
		/** ������ */
		CKernelCore();
		/** �Ҹ��� */
		~CKernelCore();
		/**
		 *	kernel interface ����ü�� ��ȯ�ϴ� �޽��.
		 *	@return kernel interface pointer.
		 */
		scCoreView *getCoreView();
		/**
		 *	���� kernel interface ����ü�� �ݳ��ϴ� �޽��.
		 *	@param kernel interface pointer.
		 */
		void returnCoreView(scCoreView *coreview);
		/**
		 *	kernel ���� ��� �޽��.
		 */
		void lock();
		/**
		 *	kernel ���� ��� ���� �޽��.
		 */
		void unlock();

	private:
		scCoreView *m_coreview;	/**< kernel interface */
		pthread_mutex_t m_lock;	/**< ��� Ű */
};

#endif /* __CKERNELCORE_H__ */
