#include <Windows.h>
#include <iostream>

#include "Vectors.h"
#include "VirtualMethod.h"

typedef struct player_info_s {
	long long int Version;
	union
	{
		long long int xuid;
		struct
		{
			int xuidLow;
			int xuidHigh;
		};
	};
	char name[128];
	int userId;
	char guid[33];
	int friendsId;
	char friendsName[128];
	bool fakeplayer;
	bool hltv;
	int customfiles[4];
	unsigned char filesdownloaded;
	int entityIndex;
} player_info_t;

class IVEngineClient013 {
public:
		VIRTUAL_METHOD(void, getScreenSize, 5, (int& w, int& h), (this, std::ref(w), std::ref(h)))
		VIRTUAL_METHOD(bool, getPlayerInfo, 8, (int entityIndex, player_info_t& playerInfo), (this, entityIndex, std::ref(playerInfo)))
		VIRTUAL_METHOD(int, getPlayerForUserID, 9, (int userId), (this, userId))
		VIRTUAL_METHOD(void, getViewAngles, 18, (Vec3& angles), (this, std::ref(angles)))
		VIRTUAL_METHOD(void, setViewAngles, 19, (const Vec3& angles), (this, std::cref(angles)))
		VIRTUAL_METHOD(int, getMaxClients, 20, (), (this))
		VIRTUAL_METHOD(bool, isInGame, 26, (), (this))
		VIRTUAL_METHOD(bool, isConnected, 27, (), (this))
		VIRTUAL_METHOD(void*, getBSPTreeQuery, 43, (), (this))
		VIRTUAL_METHOD(const char*, getLevelName, 53, (), (this))
		VIRTUAL_METHOD(const Matrix4x4&, worldToScreenMatrix, 37, (), (this))
		VIRTUAL_METHOD(void, clientCmdUnrestricted, WIN32_LINUX(114, 113), (const char* cmd, bool fromConsoleOrKeybind = false), (this, cmd, fromConsoleOrKeybind))
};