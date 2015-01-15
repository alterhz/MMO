#include "teammodule.h"
#include "LogCore.h"

ITeamModule::ITeamModule()
	: m_nAllocTeamId(0)
{
}

ITeamModule::~ITeamModule()
{
	MapTeamInfo::iterator itTeamInfo = m_mapTeamInfo.begin();
	for (; itTeamInfo!=m_mapTeamInfo.end(); ++itTeamInfo)
	{
		if (nullptr != itTeamInfo->second)
		{
			delete itTeamInfo->second;
			itTeamInfo->second = nullptr;
		}
	}
	m_mapTeamInfo.clear();
}

ITeamInfo * ITeamModule::CreateTeam()
{
	int nNewTeamId = (++m_nAllocTeamId);

	ITeamInfo *pNewTeamInfo = OnCreateTeam(nNewTeamId);
	if (nullptr == pNewTeamInfo)
	{
		return nullptr;
	}

	m_mapTeamInfo.insert(std::make_pair(nNewTeamId, pNewTeamInfo));

	return pNewTeamInfo;
}

ITeamInfo * ITeamModule::FindTeam(int nTeamId)
{
	MapTeamInfo::iterator itTeamInfo = m_mapTeamInfo.find(nTeamId);
	if (itTeamInfo != m_mapTeamInfo.end())
	{
		return itTeamInfo->second;
	}

	return nullptr;
}

const ITeamInfo * ITeamModule::FindTeam(int nTeamId) const
{
	MapTeamInfo::const_iterator itTeamInfo = m_mapTeamInfo.find(nTeamId);
	if (itTeamInfo != m_mapTeamInfo.end())
	{
		return itTeamInfo->second;
	}

	return nullptr;
}

void ITeamModule::DestoryTeam(int nTeamId)
{
	ITeamInfo *pTeamInfo = FindTeam(nTeamId);
	if (nullptr == pTeamInfo)
	{
		return ;
	}

	m_mapTeamInfo.erase(nTeamId);

	OnDestoryTeam(pTeamInfo);
}

bool ITeamModule::EnterAutoMatchList(int nListId, int nTeamId)
{
	MapList2Teams::iterator itList = m_mapList2Teams.find(nListId);
	if (itList != m_mapList2Teams.end())
	{
		if (ExistTeamId(itList->second, nTeamId))
		{
			// ��ǰ�����Ѿ���ӵ�ƥ�����
			return false;
		}

		itList->second.push_back(nTeamId);

		// ����ƥ�����
		OnEnterAutoMatchList(nListId, nTeamId);

		// �����Զ�ƥ���߼�
		DoAutoMatch(nListId, itList->second);
	}
	else
	{
		VtInt vtList;
		vtList.push_back(nTeamId);

		m_mapList2Teams.insert(std::make_pair(nListId, vtList));

		// ����ƥ�����
		OnEnterAutoMatchList(nListId, nTeamId);
	}

	return true;
}

bool ITeamModule::LeaveAutoMatchList(int nListId, int nTeamId)
{
	MapList2Teams::iterator itList = m_mapList2Teams.find(nListId);
	if (itList != m_mapList2Teams.end())
	{
		VtInt &vtList = itList->second;

		VtInt::iterator itTeamId = vtList.begin();
		for (; itTeamId!=vtList.end(); ++itTeamId)
		{
			if (nTeamId == (*itTeamId))
			{
				vtList.erase(itTeamId);

				// �뿪�Զ�ƥ���¼�
				OnLeaveAutoMatchList(nListId, nTeamId);

				return true;
			}
		}
	}

	return false;
}

bool ITeamModule::ExistTeamId(const VtInt &vtList, const int &nTeamId) const
{
	for (const int &nExistTeamId : vtList)
	{
		if (nExistTeamId == nTeamId)
		{
			return true;
		}
	}

	return false;
}

void ITeamModule::DoAutoMatch(int nListId, const VtInt &vtList)
{
	// δ����ƥ��Ķ����б��б���������С�ڶ�����������������������ƥ��ɹ���
	VtVtInt vtMatchList;
	VtVtInt vtSuccessMatchList;

	// ƥ�����������٣��ɸߵ�������ƥ��
	for (int nSize = MAX_TEAM_MEMBER_SIZE; nSize >= 1; --nSize)
	{
		VtInt::const_iterator itTeamId = vtList.begin();
		for (; itTeamId != vtList.end(); ++itTeamId)
		{
			int nTeamId = (*itTeamId);
			// �����Ա����
			int nCurTeamMemberSize = TeamMemberSize(nTeamId);
			if (nSize == nCurTeamMemberSize)
			{
				bool bInsert = false;
				VtVtInt::iterator itTeamList = vtMatchList.begin();
				for (; itTeamList!=vtMatchList.end(); ++itTeamList)
				{
					VtInt &vtTeamList = (*itTeamList);
					int nMultMemberSize = MultTeamMemberSize(vtTeamList);

					if (nMultMemberSize + nCurTeamMemberSize < MAX_TEAM_MEMBER_SIZE)
					{
						// ��������
						vtTeamList.push_back(nTeamId);
						bInsert = true;
						break;
					}
					else if (nMultMemberSize + nCurTeamMemberSize == MAX_TEAM_MEMBER_SIZE)
					{
						vtTeamList.push_back(nTeamId);
						bInsert = true;

						// ƥ�������ƶ���ƥ��ɹ�����
						vtSuccessMatchList.push_back(vtTeamList);

						vtMatchList.erase(itTeamList);
						break;
					}	// else { �������� } 
				}

				if (!bInsert)
				{
					// �������б�
					VtInt vtNetTeamList;
					vtNetTeamList.push_back(nTeamId);

					vtMatchList.push_back(vtNetTeamList);
				}
			}
		}
	}

	// ����ƥ��ɹ��¼�
	for (VtInt &vtTeamList : vtSuccessMatchList)
	{
		OnSuccessMatched(nListId, vtTeamList);
	}
}

void ITeamModule::AllDoAutoMatch()
{
	MapList2Teams::iterator itTeamList = m_mapList2Teams.begin();
	for (; itTeamList!=m_mapList2Teams.end(); ++itTeamList)
	{
		DoAutoMatch(itTeamList->first, itTeamList->second);
	}
}

int ITeamModule::TeamMemberSize(const int &nTeamId) const
{
	const ITeamInfo *pTeamInfo = FindTeam(nTeamId);
	if (nullptr == pTeamInfo)
	{
		return 0;
	}

	return pTeamInfo->MemberSize();
}

int ITeamModule::MultTeamMemberSize(const VtInt &vtList) const
{
	int nMultMemberSize = 0;
	for (const int &nTeamId : vtList)
	{
		int nMemberSize = TeamMemberSize(nTeamId);
		nMultMemberSize += nMemberSize;
	}

	return nMultMemberSize;
}

//////////////////////////////////////////////////////////////////////////
// ITeamModule�¼��б�
ITeamInfo * ITeamModule::OnCreateTeam(int nTeamId)
{
	ITeamInfo *pNewTeamInfo = new ITeamInfo(*this, nTeamId);
	if (nullptr == pNewTeamInfo)
	{
		return nullptr;
	}

	LOGDebug("���������¼�������");

	return pNewTeamInfo;
}
void ITeamModule::OnDestoryTeam(ITeamInfo *pTeamInfo)
{
	LOGDebug("��ɢ�����¼�������teamid:" + pTeamInfo->GetTeamId());

	// ���г�Ա���
	VtInt vtTempMember = pTeamInfo->MemberList();
	for (int &nMemberActorId : vtTempMember)
	{
		pTeamInfo->LeaveTeam(nMemberActorId);
	}

	delete pTeamInfo;
	pTeamInfo = nullptr;
}
void ITeamModule::OnEnterAutoMatchList(int nListId, int nTeamId)
{
	LOGDebug("����[teamid:" + nTeamId + "]����ƥ�����[listid:" + nListId + "]");
}
void ITeamModule::OnLeaveAutoMatchList(int nListId, int nTeamId)
{
	LOGDebug("����[teamid:" + nTeamId + "]�뿪ƥ�����[listid:" + nListId + "]");
}
void ITeamModule::OnSuccessMatched(int nListId, const VtInt &vtTeamList)
{
	LOGDebug("����ƥ��ɹ�:");

	VtInt vtActor;
	for (const int &nTeamId : vtTeamList)
	{
		ITeamInfo *pTeamInfo = FindTeam(nTeamId);
		if (nullptr == pTeamInfo)
		{
			continue;
		}

		for (int &nActorId : pTeamInfo->MemberList())
		{
			vtActor.push_back(nActorId);

			pTeamInfo->LeaveTeam(nActorId);
		}

		// �뿪ƥ�����
		LeaveAutoMatchList(nListId, nTeamId);

		LOGDebug("TeamId:" + nTeamId);
	}

	// �����¶���
	LOGDebug("�����¶���>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>:");
	ITeamInfo *pNewTeam = CreateTeam();
	if (pNewTeam)
	{
		for (int &nActorId : vtActor)
		{
			pNewTeam->JoinInTeam(nActorId);
			LOGDebug("�����Ա��" + nActorId);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// TeamInfo
ITeamInfo::ITeamInfo(ITeamModule &teamModule, int nTeamId)
	: m_teamModule(teamModule)
	, m_nTeamId(nTeamId)
{
}

ITeamInfo::~ITeamInfo()
{
}

bool ITeamInfo::JoinInTeam(const int nActorId)
{
	if (ExistInTeam(nActorId))
	{
		// �Ѿ��ڶ�����
		return false;
	}

	bool bCanEnterTeam = OnIsCanJoinInTeam(nActorId);
	if (bCanEnterTeam)
	{
		if (m_vtActorId.size() < MAX_TEAM_MEMBER_SIZE)
		{
			m_vtActorId.push_back(nActorId);

			return OnJoinInTeam(nActorId);
		}
	}

	return false;
}

bool ITeamInfo::LeaveTeam(const int nRoleActorId)
{
	for (VtInt::iterator itActorId = m_vtActorId.begin(); 
		itActorId != m_vtActorId.end(); ++itActorId)
	{
		if (nRoleActorId == (*itActorId))
		{
			// ɾ��
			m_vtActorId.erase(itActorId);

			// �뿪����
			OnLeaveTeam(nRoleActorId);

			// ��������׼��
			ClearAgree();

			// ��ɢ����
			if (0 == m_vtActorId.size())
			{
				m_teamModule.DestoryTeam(m_nTeamId);
			}

			return true;
		}
	}

	return false;
}

bool ITeamInfo::ExistInTeam(const int nActorId) const
{
	for (const int nMemberActorId : m_vtActorId)
	{
		if (nMemberActorId == nActorId)
		{
			return true;
		}
	}

	return false;
}

bool ITeamInfo::DoAgree(int nActorId, bool bAgree)
{
	for (const int &nMemberActorId : m_vtActorId)
	{
		if (nActorId == nMemberActorId)
		{
			if (bAgree)
			{
				// ׼��
				m_SetActorAgree.insert(nActorId);

				// ͬ���¼�
				OnAgree(nActorId, bAgree);

				bool bAllAgree = IsAllRoleAgree();

				if (bAllAgree)
				{
					// ͬ����븱��
					OnAllAgree();
				}

				return true;
			}
			else
			{
				// ȡ��
				m_SetActorAgree.erase(nActorId);

				// ͬ���¼�
				OnAgree(nActorId, bAgree);
			}
		}
	}

	return false;
}

void ITeamInfo::ClearAgree()
{
	for (const int &nMemberActorId : m_vtActorId)
	{
		// ͬ���¼�
		OnAgree(nMemberActorId, false);
	}

	m_SetActorAgree.clear();
}

bool ITeamInfo::IsAllRoleAgree()
{
	//if (m_vtActorId.size() != m_SetActorAgree.size())
	//{
	//	// ������һ�£��϶�û��ȫ��ͬ��
	//	return false;
	//}

	for (const int &nMemberActorId : m_vtActorId)
	{
		if (!IsActorAgree(nMemberActorId))
		{
			return false;
		}
	}

	return true;
}

bool ITeamInfo::IsActorAgree(int nActorId)
{
	SetActorAgree::iterator it = m_SetActorAgree.find(nActorId);
	if (it != m_SetActorAgree.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
// ITeamInfo�¼��б�
bool ITeamInfo::OnIsCanJoinInTeam(int nActorId)
{
	LOGDebug("�Ƿ���Խ�������ж�");
	return true;
}
bool ITeamInfo::OnJoinInTeam(int nActorId)
{
	LOGDebug("Actor[actorid:" + nActorId + "]��������¼�");
	return true;
}
bool ITeamInfo::OnLeaveTeam(const int nActorId)
{
	LOGDebug("Actor[actorid:" + nActorId + "]�뿪�����¼�");
	return true;
}
bool ITeamInfo::OnAgree(int nActorId, bool bAgree)
{
	LOGDebug("Actor[actorid:" + nActorId + "]ͬ��׼����" + bAgree);
	return true;
}
bool ITeamInfo::OnAllAgree()
{
	LOGDebug("ȫ��ͬ��׼��");

	return true;
}


