#include "VirtualMethod.h"
#include "IClientEntity.h"

class IClientEntityList
{
public:
	virtual void* GetClientNetworkable(int entnum) = 0;
	virtual void* GetClientNetworkableFromHandle(int hEnt) = 0;
	virtual void* GetClientUnknownFromHandle(int hEnt) = 0;

	virtual IClientEntity* GetClientEntity(int entnum) = 0;
	virtual IClientEntity* GetClientEntityFromHandle(int hEnt) = 0;

	virtual int	NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	virtual int	GetHighestEntityIndex(void) = 0;

	virtual int	GetMaxEntities() = 0;
};