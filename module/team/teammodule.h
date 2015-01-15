//----------------------------------------
// ����ʱ�� : 2015-1-5
// ���� : hanzhe
// ˵�� : ���

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

	// �����Ա����
	int MemberSize() const { return m_vtActorId.size(); }

	// �������
	bool JoinInTeam(const int nActorId);
	// �뿪����
	bool LeaveTeam(const int nActorId);
	// Actor���ڶ�����
	bool ExistInTeam(const int nActorId) const;

	// ͬ��׼��
	bool DoAgree(int nActorId, bool bAgree);
	// ����׼��
	void ClearAgree();

	// �����Ա�б�
	VtInt MemberList() const { return m_vtActorId; }

private:
	bool IsAllRoleAgree();
	bool IsActorAgree(int nActorId);

protected:	//�¼�
	// �Ƿ���Լ������[����ֵΪfalse�����ܼ�����顣]
	virtual bool OnIsCanJoinInTeam(int nActorId);
	// �������
	virtual bool OnJoinInTeam(int nActorId);
	// �뿪����
	virtual bool OnLeaveTeam(const int nActorId);
	// ͬ��׼���¼�
	virtual bool OnAgree(int nActorId, bool bAgree);
	// ȫ��ͬ��׼��
	virtual bool OnAllAgree();


protected:
	VtInt m_vtActorId;	//��ɫ�б�
	ITeamModule &m_teamModule;

private:
	int m_nTeamId;
	// ͬ���ʶ
	typedef std::set<int> SetActorAgree;
	SetActorAgree m_SetActorAgree;
};

class ITeamModule
{
public:
	ITeamModule();
	virtual ~ITeamModule();

public:
	// ����һ������
	ITeamInfo * CreateTeam();
	// ���Ҷ���
	ITeamInfo * FindTeam(int nTeamId);
	const ITeamInfo * FindTeam(int nTeamId) const;
	// ���ٶ���
	void DestoryTeam(int nTeamId);

	// �����Զ�ƥ�����
	bool EnterAutoMatchList(int nListId, int nTeamId);
	// �뿪�Զ�ƥ�����
	bool LeaveAutoMatchList(int nListId, int nTeamId);
	
	// ȫ���Զ�ƥ��
	void AllDoAutoMatch();

private:
	// �Ƿ���ڶ���
	bool ExistTeamId(const VtInt &vtList, const int &nTeamId) const;
	// �Զ�ƥ���߼�ִ��
	void DoAutoMatch(int nListId, const VtInt &vtList);
	// �����Ա����
	int TeamMemberSize(const int &nTeamId) const;
	// �������ĳ�Ա������
	int MultTeamMemberSize(const VtInt &vtList) const;

protected:	//�¼�
	// ���������¼�
	virtual ITeamInfo * OnCreateTeam(int nTeamId);
	// ���ٶ���
	virtual void OnDestoryTeam(ITeamInfo *pTeamInfo);
	// ��ӵ�ƥ�����
	virtual void OnEnterAutoMatchList(int nListId, int nTeamId);
	// �뿪ƥ�����
	virtual void OnLeaveAutoMatchList(int nListId, int nTeamId);
	// ƥ�����
	virtual void OnSuccessMatched(int nListId, const VtInt &vtTeamList);
	
private:
	int m_nAllocTeamId;
	typedef std::map<int, ITeamInfo *> MapTeamInfo;
	MapTeamInfo m_mapTeamInfo;
	// List������б�(�Զ�ƥ�����)
	typedef std::map<int, VtInt> MapList2Teams;
	MapList2Teams m_mapList2Teams;
};

#endif