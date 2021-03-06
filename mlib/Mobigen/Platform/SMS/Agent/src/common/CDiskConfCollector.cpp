

#include "CDiskConfCollector.h"


CDiskConfCollector::CDiskConfCollector()
{
	m_list = NULL;
}

CDiskConfCollector::~CDiskConfCollector()
{
	if(m_list!=NULL)
		scCoreViewRelease(&m_list);
}

void CDiskConfCollector::collect()
{
	char *msg=NULL;

	if(m_pollitem->getPollType() == TYPE_EVENT) {
		return;
	}

	m_coreview = m_envvar->getKernelCore()->getCoreView();
	if(	(m_list = scCoreViewFSInfo(m_coreview))==NULL ) {
		m_envvar->getKernelCore()->returnCoreView(m_coreview);
		return;
	}
	m_envvar->getKernelCore()->returnCoreView(m_coreview);

	makeMessage();
	msg = m_msgfmt.makeMessage();

	if(m_pollitem->getPollType() == TYPE_PASSIVE){
		m_envvar->getRespQ()->enqueue(msg, NULL);		
	}else{
		if(isShortPerf()==true){
			m_envvar->getShortPerfQ()->enqueue(msg, NULL);		
		}else{
			m_envvar->getLongPerfQ()->enqueue(msg, NULL);		
		}
	}
}

void CDiskConfCollector::makeMessage()
{
	int i=0, at=0;
	char buf[1024], temp[32], tab=0x09;
	CQueue *instQ = m_pollitem->getInstQ();
	elem *e=NULL;

	m_msgfmt.setItem(m_pollitem->getItem());
	m_msgfmt.setPollTime(m_pollitem->getPollTime());
	m_msgfmt.setType(m_pollitem->getPollType());
	if(m_pollitem->getPollType()==TYPE_PASSIVE)
		m_msgfmt.setCommand((char *)m_pollitem->getCommand().c_str());

	memset(buf, 0x00, sizeof(buf));

	// KB로 변경함.. MB로 표현하는 경우 각 장비에서 1024로 나누어야하는데 그런 고려가 되어있지않음.
	sprintf(buf, "Instance%cDiskName%cDiskSize(KB)\n", tab, tab);
	m_msgfmt.setTitle(buf);

	if(m_list!=NULL){
		while((m_fsinfo = (scFSInfo *)ll_element_at(m_list, at++))!=NULL){
			if(!instQ->isEmpty()){
				for(e=instQ->frontNode();e!=NULL;e=instQ->getNext(e)){
					char *instname = (char *)e->d;
					if(strcmp(instname, m_fsinfo->mntpoint)==0){
						memset(buf, 0x00, sizeof(buf));
						sprintf(buf, "%s%c%s%c%lu\n",
							m_fsinfo->mntpoint, tab, m_fsinfo->device, tab,
							m_fsinfo->sizetotal);
						m_msgfmt.addMessage(strdup(buf));
					}
				}
			}else{
				memset(buf, 0x00, sizeof(buf));
				sprintf(buf, "%s%c%s%c%lu\n",
					m_fsinfo->mntpoint, tab,
					m_fsinfo->device, tab, m_fsinfo->sizetotal);
				m_msgfmt.addMessage(strdup(buf));
			}
		}
	}

	return;
}
