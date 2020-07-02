#pragma once
typedef struct SendMemberInfo {
	int type,id, password;
}SendMemberInfo;

typedef struct MemberInfo {
	int id, password;
}MemberInfo;

SendMemberInfo MemInfoToSendMemInfo(int type, MemberInfo minfo);