//----------------------------------------
// 创建时间 : 2015-1-5
// 作者 : hanzhe
// 说明 : 组队

#ifndef _TEAMMODULE_H_
#define _TEAMMODULE_H_

#include "Header.h"

class ITeamModule;

#define MAX_TEAM_MEMBER_SIZE	3

class ITeamInfo
{
public:
	ITeamInfo(ITeamModule &teamModule, int nTeamId);
	virtual ~ITeamInfo();

public:
	int GetTeamId() const { return m_nTeamId; }

	// 队伍成员数量
	int MemberSize() const { return m_vtActorId.size(); }

	// 加入队伍
	bool JoinInTeam(const int nActorId);
	// 离开队伍
	bool LeaveTeam(const int nActorId);
	// Actor存在队伍中
	bool ExistInTeam(const int nActorId) const;

	// 同意准备
	bool DoAgree(int nActorId, bool bAgree);
	// 重置准备
	void ClearAgree();

	// 队伍成员列表
	VtInt MemberList() const { return m_vtActorId; }

private:
	bool IsAllRoleAgree();
	bool IsActorAgree(int nActorId);

protected:	//事件
	// 是否可以加入队伍[返回值为false，则不能加入队伍。]
	virtual bool OnIsCanJoinInTeam(int nActorId);
	// 加入队伍
	virtual bool OnJoinInTeam(int nActorId);
	// 离开队伍
	virtual bool OnLeaveTeam(const int nActorId);
	// 同意准备事件
	virtual bool OnAgree(int nActorId, bool bAgree);
	// 全部同意准备
	virtual bool OnAllAgree();


protected:
	VtInt m_vtActorId;	//角色列表
	ITeamModule &m_teamModule;

private:
	int m_nTeamId;
	// 同意标识
	typedef std::set<int> SetActorAgree;
	SetActorAgree m_SetActorAgree;
};

class ITeamModule
{
public:
	ITeamModule();
	virtual ~ITeamModule();

public:
	// 创建一个队伍
	ITeamInfo * CreateTeam();
	// 查找队伍
	ITeamInfo * FindTeam(int nTeamId);
	const ITeamInfo * FindTeam(int nTeamId) const;
	// 销毁队伍
	void DestoryTeam(int nTeamId);

	// 进入自动匹配队列
	bool EnterAutoMatchList(int nListId, int nTeamId);
	// 离开自动匹配队列
	bool LeaveAutoMatchList(int nListId, int nTeamId);
	
	// 全部自动匹配
	void AllDoAutoMatch();

private:
	// 是否存在队伍
	bool ExistTeamId(const VtInt &vtList, const int &nTeamId) const;
	// 自动匹配逻辑执行
	void DoAutoMatch(int nListId, const VtInt &vtList);
	// 队伍成员数量
	int TeamMemberSize(const int &nTeamId) const;
	// 多个队伍的成员总数量
	int MultTeamMemberSize(const VtInt &vtList) const;

protected:	//事件
	// 创建队伍事件
	virtual ITeamInfo * OnCreateTeam(int nTeamId);
	// 销毁队伍
	virtual void OnDestoryTeam(ITeamInfo *pTeamInfo);
	// 添加到匹配队列
	virtual void OnEnterAutoMatchList(int nListId, int nTeamId);
	// 离开匹配队列
	virtual void OnLeaveAutoMatchList(int nListId, int nTeamId);
	// 匹配队伍
	virtual void OnSuccessMatched(int nListId, const VtInt &vtTeamList);
	
private:
	int m_nAllocTeamId;
	typedef std::map<int, ITeamInfo *> MapTeamInfo;
	MapTeamInfo m_mapTeamInfo;
	// List与队伍列表(自动匹配队伍)
	typedef std::map<int, VtInt> MapList2Teams;
	MapList2Teams m_mapList2Teams;
};

#endif