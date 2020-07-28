#include "Fault.h"
#include "DataTypes.h"
#include <assert.h>

//----------------------------------------------------------------------------
// FaultHandler
//----------------------------------------------------------------------------
void FaultHandler(const char* file, unsigned short line)
{
	// If you hit this line, it means one of the ASSERT macros failed.
//    DebugBreak();
//    printf("Assert!")

	assert(0);
}
