
// LuaState_Implementation.cpp

// This file is generated along with the Lua bindings by ToLua. Do not edit manually, do not commit to repo.
// Implements a Push() and GetStackValue() function for each class exported to the Lua API.
// This file expects to be compiled as a separate translation unit





#include "Globals.h"
#include "LuaState.h"
#include "tolua++/include/tolua++.h"





void cLuaState::Push(cArrowEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cArrowEntity");
}





void cLuaState::Push(cBeaconEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cBeaconEntity");
}





void cLuaState::Push(cBedEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cBedEntity");
}





void cLuaState::Push(cBlockArea * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cBlockArea");
}





void cLuaState::Push(cBlockEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cBlockEntity");
}





void cLuaState::Push(cBlockEntityWithItems * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cBlockEntityWithItems");
}





void cLuaState::Push(cBlockInfo * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cBlockInfo");
}





void cLuaState::Push(cBoat * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cBoat");
}





void cLuaState::Push(cBoundingBox * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cBoundingBox");
}





void cLuaState::Push(cBrewingstandEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cBrewingstandEntity");
}





void cLuaState::Push(cChatColor * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cChatColor");
}





void cLuaState::Push(cChestEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cChestEntity");
}





void cLuaState::Push(cChunkDesc * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cChunkDesc");
}





void cLuaState::Push(cClientHandle * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cClientHandle");
}





void cLuaState::Push(cColor * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cColor");
}





void cLuaState::Push(cCommandBlockEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cCommandBlockEntity");
}





void cLuaState::Push(cCompositeChat * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cCompositeChat");
}





void cLuaState::Push(cCraftingGrid * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cCraftingGrid");
}





void cLuaState::Push(cCraftingRecipe * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cCraftingRecipe");
}





void cLuaState::Push(cCuboid * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cCuboid");
}





void cLuaState::Push(cDispenserEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cDispenserEntity");
}





void cLuaState::Push(cDropperEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cDropperEntity");
}





void cLuaState::Push(cDropSpenserEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cDropSpenserEntity");
}





void cLuaState::Push(cEnchantments * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cEnchantments");
}





void cLuaState::Push(cEntityEffect * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cEntityEffect");
}





void cLuaState::Push(cExpBottleEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cExpBottleEntity");
}





void cLuaState::Push(cExpOrb * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cExpOrb");
}





void cLuaState::Push(cFallingBlock * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cFallingBlock");
}





void cLuaState::Push(cFile * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cFile");
}





void cLuaState::Push(cFireChargeEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cFireChargeEntity");
}





void cLuaState::Push(cFireworkEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cFireworkEntity");
}





void cLuaState::Push(cFloater * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cFloater");
}





void cLuaState::Push(cFlowerPotEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cFlowerPotEntity");
}





void cLuaState::Push(cFurnaceEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cFurnaceEntity");
}





void cLuaState::Push(cGhastFireballEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cGhastFireballEntity");
}





void cLuaState::Push(cHangingEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cHangingEntity");
}





void cLuaState::Push(cHopperEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cHopperEntity");
}





void cLuaState::Push(cIniFile * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cIniFile");
}





void cLuaState::Push(cInventory * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cInventory");
}





void cLuaState::Push(cItem * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cItem");
}





void cLuaState::Push(cItemFrame * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cItemFrame");
}





void cLuaState::Push(cItemGrid * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cItemGrid");
}





void cLuaState::Push(cItems * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cItems");
}





void cLuaState::Push(cJukeboxEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cJukeboxEntity");
}





void cLuaState::Push(cLeashKnot * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cLeashKnot");
}





void cLuaState::Push(cLuaWindow * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cLuaWindow");
}





void cLuaState::Push(cMap * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cMap");
}





void cLuaState::Push(cMapManager * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cMapManager");
}





void cLuaState::Push(cMobHeadEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cMobHeadEntity");
}





void cLuaState::Push(cMobSpawnerEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cMobSpawnerEntity");
}





void cLuaState::Push(cMojangAPI * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cMojangAPI");
}





void cLuaState::Push(cMonster * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cMonster");
}





void cLuaState::Push(cNoteEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cNoteEntity");
}





void cLuaState::Push(cObjective * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cObjective");
}





void cLuaState::Push(cPainting * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cPainting");
}





void cLuaState::Push(cPawn * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cPawn");
}





void cLuaState::Push(cPickup * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cPickup");
}





void cLuaState::Push(cPlayer * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cPlayer");
}





void cLuaState::Push(cPlugin * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cPlugin");
}





void cLuaState::Push(cPluginLua * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cPluginLua");
}





void cLuaState::Push(cPluginManager * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cPluginManager");
}





void cLuaState::Push(cProjectileEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cProjectileEntity");
}





void cLuaState::Push(cRoot * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cRoot");
}





void cLuaState::Push(cScoreboard * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cScoreboard");
}





void cLuaState::Push(cServer * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cServer");
}





void cLuaState::Push(cSignEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cSignEntity");
}





void cLuaState::Push(cSplashPotionEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cSplashPotionEntity");
}





void cLuaState::Push(cStatManager * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cStatManager");
}





void cLuaState::Push(cTeam * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cTeam");
}





void cLuaState::Push(cThrownEggEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cThrownEggEntity");
}





void cLuaState::Push(cThrownEnderPearlEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cThrownEnderPearlEntity");
}





void cLuaState::Push(cThrownSnowballEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cThrownSnowballEntity");
}





void cLuaState::Push(cTNTEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cTNTEntity");
}





void cLuaState::Push(cTracer * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cTracer");
}





void cLuaState::Push(cUUID * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cUUID");
}





void cLuaState::Push(cWebAdmin * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cWebAdmin");
}





void cLuaState::Push(cWindow * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cWindow");
}





void cLuaState::Push(cWitherSkullEntity * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cWitherSkullEntity");
}





void cLuaState::Push(cWorld * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "cWorld");
}





void cLuaState::Push(HTTPFormData * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "HTTPFormData");
}





void cLuaState::Push(HTTPRequest * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "HTTPRequest");
}





void cLuaState::Push(HTTPTemplateRequest * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "HTTPTemplateRequest");
}





void cLuaState::Push(TakeDamageInfo * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "TakeDamageInfo");
}





void cLuaState::Push(Vector3<double> * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "Vector3<double>");
}





void cLuaState::Push(Vector3<float> * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "Vector3<float>");
}





void cLuaState::Push(Vector3<int> * a_Value)
{
	ASSERT(IsValid());
	tolua_pushusertype(m_LuaState, a_Value, "Vector3<int>");
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcArrowEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cArrowEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cArrowEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcArrowEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cArrowEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cArrowEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcBeaconEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cBeaconEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cBeaconEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcBeaconEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cBeaconEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cBeaconEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcBedEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cBedEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cBedEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcBedEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cBedEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cBedEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcBlockArea & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cBlockArea", false, &err))
	{
		a_ReturnedVal = *(static_cast<cBlockArea **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcBlockArea & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cBlockArea", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cBlockArea **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcBlockEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cBlockEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cBlockEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcBlockEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cBlockEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cBlockEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcBlockEntityWithItems & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cBlockEntityWithItems", false, &err))
	{
		a_ReturnedVal = *(static_cast<cBlockEntityWithItems **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcBlockEntityWithItems & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cBlockEntityWithItems", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cBlockEntityWithItems **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcBlockInfo & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cBlockInfo", false, &err))
	{
		a_ReturnedVal = *(static_cast<cBlockInfo **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcBlockInfo & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cBlockInfo", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cBlockInfo **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcBoat & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cBoat", false, &err))
	{
		a_ReturnedVal = *(static_cast<cBoat **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcBoat & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cBoat", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cBoat **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcBoundingBox & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cBoundingBox", false, &err))
	{
		a_ReturnedVal = *(static_cast<cBoundingBox **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcBoundingBox & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cBoundingBox", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cBoundingBox **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcBrewingstandEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cBrewingstandEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cBrewingstandEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcBrewingstandEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cBrewingstandEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cBrewingstandEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcChatColor & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cChatColor", false, &err))
	{
		a_ReturnedVal = *(static_cast<cChatColor **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcChatColor & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cChatColor", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cChatColor **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcChestEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cChestEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cChestEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcChestEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cChestEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cChestEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcChunkDesc & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cChunkDesc", false, &err))
	{
		a_ReturnedVal = *(static_cast<cChunkDesc **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcChunkDesc & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cChunkDesc", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cChunkDesc **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcClientHandle & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cClientHandle", false, &err))
	{
		a_ReturnedVal = *(static_cast<cClientHandle **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcClientHandle & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cClientHandle", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cClientHandle **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcColor & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cColor", false, &err))
	{
		a_ReturnedVal = *(static_cast<cColor **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcColor & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cColor", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cColor **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcCommandBlockEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cCommandBlockEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cCommandBlockEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcCommandBlockEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cCommandBlockEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cCommandBlockEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcCompositeChat & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cCompositeChat", false, &err))
	{
		a_ReturnedVal = *(static_cast<cCompositeChat **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcCompositeChat & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cCompositeChat", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cCompositeChat **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcCraftingGrid & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cCraftingGrid", false, &err))
	{
		a_ReturnedVal = *(static_cast<cCraftingGrid **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcCraftingGrid & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cCraftingGrid", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cCraftingGrid **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcCraftingRecipe & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cCraftingRecipe", false, &err))
	{
		a_ReturnedVal = *(static_cast<cCraftingRecipe **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcCraftingRecipe & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cCraftingRecipe", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cCraftingRecipe **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcCuboid & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cCuboid", false, &err))
	{
		a_ReturnedVal = *(static_cast<cCuboid **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcCuboid & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cCuboid", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cCuboid **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcDispenserEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cDispenserEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cDispenserEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcDispenserEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cDispenserEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cDispenserEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcDropperEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cDropperEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cDropperEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcDropperEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cDropperEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cDropperEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcDropSpenserEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cDropSpenserEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cDropSpenserEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcDropSpenserEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cDropSpenserEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cDropSpenserEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcEnchantments & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cEnchantments", false, &err))
	{
		a_ReturnedVal = *(static_cast<cEnchantments **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcEnchantments & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cEnchantments", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cEnchantments **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcEntityEffect & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cEntityEffect", false, &err))
	{
		a_ReturnedVal = *(static_cast<cEntityEffect **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcEntityEffect & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cEntityEffect", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cEntityEffect **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcExpBottleEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cExpBottleEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cExpBottleEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcExpBottleEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cExpBottleEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cExpBottleEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcExpOrb & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cExpOrb", false, &err))
	{
		a_ReturnedVal = *(static_cast<cExpOrb **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcExpOrb & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cExpOrb", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cExpOrb **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcFallingBlock & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cFallingBlock", false, &err))
	{
		a_ReturnedVal = *(static_cast<cFallingBlock **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcFallingBlock & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cFallingBlock", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cFallingBlock **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcFile & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cFile", false, &err))
	{
		a_ReturnedVal = *(static_cast<cFile **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcFile & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cFile", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cFile **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcFireChargeEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cFireChargeEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cFireChargeEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcFireChargeEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cFireChargeEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cFireChargeEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcFireworkEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cFireworkEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cFireworkEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcFireworkEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cFireworkEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cFireworkEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcFloater & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cFloater", false, &err))
	{
		a_ReturnedVal = *(static_cast<cFloater **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcFloater & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cFloater", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cFloater **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcFlowerPotEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cFlowerPotEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cFlowerPotEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcFlowerPotEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cFlowerPotEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cFlowerPotEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcFurnaceEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cFurnaceEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cFurnaceEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcFurnaceEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cFurnaceEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cFurnaceEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcGhastFireballEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cGhastFireballEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cGhastFireballEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcGhastFireballEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cGhastFireballEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cGhastFireballEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcHangingEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cHangingEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cHangingEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcHangingEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cHangingEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cHangingEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcHopperEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cHopperEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cHopperEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcHopperEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cHopperEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cHopperEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcIniFile & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cIniFile", false, &err))
	{
		a_ReturnedVal = *(static_cast<cIniFile **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcIniFile & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cIniFile", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cIniFile **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcInventory & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cInventory", false, &err))
	{
		a_ReturnedVal = *(static_cast<cInventory **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcInventory & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cInventory", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cInventory **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcItem & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cItem", false, &err))
	{
		a_ReturnedVal = *(static_cast<cItem **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcItem & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cItem", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cItem **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcItemFrame & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cItemFrame", false, &err))
	{
		a_ReturnedVal = *(static_cast<cItemFrame **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcItemFrame & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cItemFrame", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cItemFrame **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcItemGrid & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cItemGrid", false, &err))
	{
		a_ReturnedVal = *(static_cast<cItemGrid **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcItemGrid & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cItemGrid", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cItemGrid **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcItems & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cItems", false, &err))
	{
		a_ReturnedVal = *(static_cast<cItems **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcItems & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cItems", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cItems **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcJukeboxEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cJukeboxEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cJukeboxEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcJukeboxEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cJukeboxEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cJukeboxEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcLeashKnot & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cLeashKnot", false, &err))
	{
		a_ReturnedVal = *(static_cast<cLeashKnot **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcLeashKnot & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cLeashKnot", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cLeashKnot **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcLuaWindow & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cLuaWindow", false, &err))
	{
		a_ReturnedVal = *(static_cast<cLuaWindow **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcLuaWindow & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cLuaWindow", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cLuaWindow **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcMap & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cMap", false, &err))
	{
		a_ReturnedVal = *(static_cast<cMap **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcMap & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cMap", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cMap **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcMapManager & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cMapManager", false, &err))
	{
		a_ReturnedVal = *(static_cast<cMapManager **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcMapManager & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cMapManager", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cMapManager **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcMobHeadEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cMobHeadEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cMobHeadEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcMobHeadEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cMobHeadEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cMobHeadEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcMobSpawnerEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cMobSpawnerEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cMobSpawnerEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcMobSpawnerEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cMobSpawnerEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cMobSpawnerEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcMojangAPI & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cMojangAPI", false, &err))
	{
		a_ReturnedVal = *(static_cast<cMojangAPI **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcMojangAPI & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cMojangAPI", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cMojangAPI **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcMonster & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cMonster", false, &err))
	{
		a_ReturnedVal = *(static_cast<cMonster **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcMonster & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cMonster", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cMonster **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcNoteEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cNoteEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cNoteEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcNoteEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cNoteEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cNoteEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcObjective & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cObjective", false, &err))
	{
		a_ReturnedVal = *(static_cast<cObjective **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcObjective & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cObjective", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cObjective **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcPainting & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cPainting", false, &err))
	{
		a_ReturnedVal = *(static_cast<cPainting **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcPainting & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cPainting", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cPainting **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcPawn & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cPawn", false, &err))
	{
		a_ReturnedVal = *(static_cast<cPawn **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcPawn & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cPawn", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cPawn **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcPickup & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cPickup", false, &err))
	{
		a_ReturnedVal = *(static_cast<cPickup **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcPickup & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cPickup", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cPickup **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcPlayer & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cPlayer", false, &err))
	{
		a_ReturnedVal = *(static_cast<cPlayer **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcPlayer & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cPlayer", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cPlayer **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcPlugin & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cPlugin", false, &err))
	{
		a_ReturnedVal = *(static_cast<cPlugin **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcPlugin & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cPlugin", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cPlugin **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcPluginLua & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cPluginLua", false, &err))
	{
		a_ReturnedVal = *(static_cast<cPluginLua **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcPluginLua & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cPluginLua", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cPluginLua **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcPluginManager & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cPluginManager", false, &err))
	{
		a_ReturnedVal = *(static_cast<cPluginManager **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcPluginManager & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cPluginManager", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cPluginManager **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcProjectileEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cProjectileEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cProjectileEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcProjectileEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cProjectileEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cProjectileEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcRoot & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cRoot", false, &err))
	{
		a_ReturnedVal = *(static_cast<cRoot **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcRoot & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cRoot", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cRoot **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcScoreboard & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cScoreboard", false, &err))
	{
		a_ReturnedVal = *(static_cast<cScoreboard **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcScoreboard & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cScoreboard", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cScoreboard **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcServer & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cServer", false, &err))
	{
		a_ReturnedVal = *(static_cast<cServer **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcServer & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cServer", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cServer **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcSignEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cSignEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cSignEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcSignEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cSignEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cSignEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcSplashPotionEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cSplashPotionEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cSplashPotionEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcSplashPotionEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cSplashPotionEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cSplashPotionEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcStatManager & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cStatManager", false, &err))
	{
		a_ReturnedVal = *(static_cast<cStatManager **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcStatManager & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cStatManager", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cStatManager **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcTeam & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cTeam", false, &err))
	{
		a_ReturnedVal = *(static_cast<cTeam **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcTeam & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cTeam", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cTeam **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcThrownEggEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cThrownEggEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cThrownEggEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcThrownEggEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cThrownEggEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cThrownEggEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcThrownEnderPearlEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cThrownEnderPearlEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cThrownEnderPearlEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcThrownEnderPearlEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cThrownEnderPearlEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cThrownEnderPearlEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcThrownSnowballEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cThrownSnowballEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cThrownSnowballEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcThrownSnowballEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cThrownSnowballEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cThrownSnowballEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcTNTEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cTNTEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cTNTEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcTNTEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cTNTEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cTNTEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcTracer & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cTracer", false, &err))
	{
		a_ReturnedVal = *(static_cast<cTracer **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcTracer & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cTracer", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cTracer **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcUUID & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cUUID", false, &err))
	{
		a_ReturnedVal = *(static_cast<cUUID **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcUUID & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cUUID", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cUUID **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcWebAdmin & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cWebAdmin", false, &err))
	{
		a_ReturnedVal = *(static_cast<cWebAdmin **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcWebAdmin & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cWebAdmin", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cWebAdmin **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcWindow & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cWindow", false, &err))
	{
		a_ReturnedVal = *(static_cast<cWindow **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcWindow & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cWindow", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cWindow **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcWitherSkullEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cWitherSkullEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<cWitherSkullEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcWitherSkullEntity & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cWitherSkullEntity", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cWitherSkullEntity **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrcWorld & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "cWorld", false, &err))
	{
		a_ReturnedVal = *(static_cast<cWorld **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrcWorld & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const cWorld", false, &err))
	{
		a_ReturnedVal = *(static_cast<const cWorld **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrHTTPFormData & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "HTTPFormData", false, &err))
	{
		a_ReturnedVal = *(static_cast<HTTPFormData **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrHTTPFormData & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const HTTPFormData", false, &err))
	{
		a_ReturnedVal = *(static_cast<const HTTPFormData **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrHTTPRequest & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "HTTPRequest", false, &err))
	{
		a_ReturnedVal = *(static_cast<HTTPRequest **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrHTTPRequest & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const HTTPRequest", false, &err))
	{
		a_ReturnedVal = *(static_cast<const HTTPRequest **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrHTTPTemplateRequest & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "HTTPTemplateRequest", false, &err))
	{
		a_ReturnedVal = *(static_cast<HTTPTemplateRequest **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrHTTPTemplateRequest & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const HTTPTemplateRequest", false, &err))
	{
		a_ReturnedVal = *(static_cast<const HTTPTemplateRequest **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrTakeDamageInfo & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "TakeDamageInfo", false, &err))
	{
		a_ReturnedVal = *(static_cast<TakeDamageInfo **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrTakeDamageInfo & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const TakeDamageInfo", false, &err))
	{
		a_ReturnedVal = *(static_cast<const TakeDamageInfo **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrVector3d & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "Vector3<double>", false, &err))
	{
		a_ReturnedVal = *(static_cast<Vector3<double> **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrVector3d & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const Vector3<double>", false, &err))
	{
		a_ReturnedVal = *(static_cast<const Vector3<double> **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrVector3f & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "Vector3<float>", false, &err))
	{
		a_ReturnedVal = *(static_cast<Vector3<float> **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrVector3f & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const Vector3<float>", false, &err))
	{
		a_ReturnedVal = *(static_cast<const Vector3<float> **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, PtrVector3i & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "Vector3<int>", false, &err))
	{
		a_ReturnedVal = *(static_cast<Vector3<int> **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





bool cLuaState::GetStackValue(int a_StackPos, ConstPtrVector3i & a_ReturnedVal)
{
	ASSERT(IsValid());
	if (lua_isnil(m_LuaState, a_StackPos))
	{
		a_ReturnedVal = nullptr;
		return false;
	}
	tolua_Error err;
	if (tolua_isusertype(m_LuaState, a_StackPos, "const Vector3<int>", false, &err))
	{
		a_ReturnedVal = *(static_cast<const Vector3<int> **>(lua_touserdata(m_LuaState, a_StackPos)));
		return true;
	}
	return false;
}





