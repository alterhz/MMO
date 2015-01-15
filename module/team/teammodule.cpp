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
			// 当前队伍已经添加到匹配队列
			return false;
		}

		itList->second.push_back(nTeamId);

		// 进入匹配队列
		OnEnterAutoMatchList(nListId, nTeamId);

		// 调用自动匹配逻辑
		DoAutoMatch(nListId, itList->second);
	}
	else
	{
		VtInt vtList;
		vtList.push_back(nTeamId);

		m_mapList2Teams.insert(std::make_pair(nListId, vtList));

		// 进入匹配队列
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

				// 离开自动匹配事件
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
	// 未满足匹配的队伍列表，列表总人数都小于队伍最大人数，等于最大人数匹配成功。
	VtVtInt vtMatchList;
	VtVtInt vtSuccessMatchList;

	// 匹配由人数多少，由高到低优先匹配
	for (int nSize = MAX_TEAM_MEMBER_SIZE; nSize >= 1; --nSize)
	{
		VtInt::const_iterator itTeamId = vtList.begin();
		for (; itTeamId != vtList.end(); ++itTeamId)
		{
			int nTeamId = (*itTeamId);
			// 队伍成员数量
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
						// 人数不足
						vtTeamList.push_back(nTeamId);
						bInsert = true;
						break;
					}
					else if (nMultMemberSize + nCurTeamMemberSize == MAX_TEAM_MEMBER_SIZE)
					{
						vtTeamList.push_back(nTeamId);
						bInsert = true;

						// 匹配满人移动到匹配成功队列
						vtSuccessMatchList.push_back(vtTeamList);

						vtMatchList.erase(itTeamList);
						break;
					}	// else { 人数超了 } 
				}

				if (!bInsert)
				{
					// 插入新列表
					VtInt vtNetTeamList;
					vtNetTeamList.push_back(nTeamId);

					vtMatchList.push_back(vtNetTeamList);
				}
			}
		}
	}

	// 触发匹配成功事件
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
// ITeamModule事件列表
ITeamInfo * ITeamModule::OnCreateTeam(int nTeamId)
{
	ITeamInfo *pNewTeamInfo = new ITeamInfo(*this, nTeamId);
	if (nullptr == pNewTeamInfo)
	{
		return nullptr;
	}

	LOGDebug("创建队伍事件触发。");

	return pNewTeamInfo;
}
void ITeamModule::OnDestoryTeam(ITeamInfo *pTeamInfo)
{
	LOGDebug("解散队伍事件触发：teamid:" + pTeamInfo->GetTeamId());

	// 所有成员离队
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
	LOGDebug("队伍[teamid:" + nTeamId + "]进入匹配队列[listid:" + nListId + "]");
}
void ITeamModule::OnLeaveAutoMatchList(int nListId, int nTeamId)
{
	LOGDebug("队伍[teamid:" + nTeamId + "]离开匹配队列[listid:" + nListId + "]");
}
void ITeamModule::OnSuccessMatched(int nListId, const VtInt &vtTeamList)
{
	LOGDebug("队伍匹配成功:");

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

		// 离开匹配队列
		LeaveAutoMatchList(nListId, nTeamId);

		LOGDebug("TeamId:" + nTeamId);
	}

	// 创建新队伍
	LOGDebug("创建新队伍>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>:");
	ITeamInfo *pNewTeam = CreateTeam();
	if (pNewTeam)
	{
		for (int &nActorId : vtActor)
		{
			pNewTeam->JoinInTeam(nActorId);
			LOGDebug("加入成员：" + nActorId);
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
		// 已经在队伍中
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
			// 删除
			m_vtActorId.erase(itActorId);

			// 离开队伍
			OnLeaveTeam(nRoleActorId);

			// 重置所有准备
			ClearAgree();

			// 解散队伍
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
				// 准备
				m_SetActorAgree.insert(nActorId);

				// 同意事件
				OnAgree(nActorId, bAgree);

				bool bAllAgree = IsAllRoleAgree();

				if (bAllAgree)
				{
					// 同意进入副本
					OnAllAgree();
				}

				return true;
			}
			else
			{
				// 取消
				m_SetActorAgree.erase(nActorId);

				// 同意事件
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
		// 同意事件
		OnAgree(nMemberActorId, false);
	}

	m_SetActorAgree.clear();
}

bool ITeamInfo::IsAllRoleAgree()
{
	//if (m_vtActorId.size() != m_SetActorAgree.size())
	//{
	//	// 数量不一致，肯定没有全部同意
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
// ITeamInfo事件列表
bool ITeamInfo::OnIsCanJoinInTeam(int nActorId)
{
	LOGDebug("是否可以进入队伍判定");
	return true;
}
bool ITeamInfo::OnJoinInTeam(int nActorId)
{
	LOGDebug("Actor[actorid:" + nActorId + "]加入队伍事件");
	return true;
}
bool ITeamInfo::OnLeaveTeam(const int nActorId)
{
	LOGDebug("Actor[actorid:" + nActorId + "]离开队伍事件");
	return true;
}
bool ITeamInfo::OnAgree(int nActorId, bool bAgree)
{
	LOGDebug("Actor[actorid:" + nActorId + "]同意准备：" + bAgree);
	return true;
}
bool ITeamInfo::OnAllAgree()
{
	LOGDebug("全部同意准备");

	return true;
}


