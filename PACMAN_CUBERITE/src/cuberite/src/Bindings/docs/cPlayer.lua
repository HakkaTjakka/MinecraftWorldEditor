return
{
	cPlayer =
	{
		Inherits =
		{
			"cPawn",
		},
		Functions =
		{
			AddFoodExhaustion =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_Exhaustion",
						},
					},
					Returns =
					{
					},
					Desc = "Adds the specified exhaustion to m_FoodExhaustion. Expects only positive values.",
				},
			},
			CalcLevelFromXp =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_CurrentXp",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					IsStatic = true,
					Desc = "Inverse of XpForLevel\
	Ref: https://minecraft.gamepedia.com/XP\
	values are as per this with pre-calculations",
				},
			},
			CanFly =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns wheter the player can fly or not.",
				},
			},
			CanMobsTarget =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player can be targeted by Mobs",
				},
			},
			CloseWindow =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_CanRefuse",
						},
					},
					Returns =
					{
					},
					Desc = "Closes the current window, resets current window to m_InventoryWindow. A plugin may refuse the closing if a_CanRefuse is true",
				},
			},
			CloseWindowIfID =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_WindowID",
						},
						{
							Type = "bool",
							Name = "a_CanRefuse",
						},
					},
					Returns =
					{
					},
					Desc = "Closes the current window if it matches the specified ID, resets current window to m_InventoryWindow",
				},
			},
			DeltaExperience =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Xp_delta",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
				},
			},
			Feed =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Food",
						},
						{
							Type = "double",
							Name = "a_Saturation",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Adds to FoodLevel and FoodSaturationLevel, returns true if any food has been consumed, false if player \"full\"",
				},
			},
			ForceSetSpeed =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Speed",
						},
					},
					Returns =
					{
					},
					Desc = "Forces the player to move in the given direction.\
	@deprecated Use SetSpeed instead.",
				},
			},
			Freeze =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Location",
						},
					},
					Returns =
					{
					},
					Desc = "Prevent the player from moving and lock him into a_Location.",
				},
			},
			GetClientHandle =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cClientHandle",
						},
					},
					Desc = "Returns the raw client handle associated with the player.",
				},
			},
			GetColor =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Returns the full color code to use for this player, based on their rank.\
	The returned value either is empty, or includes the cChatColor::Delimiter.",
				},
			},
			GetCurrentXp =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Gets the current experience",
				},
			},
			GetCustomName =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const AString",
						},
					},
					Desc = "Returns the custom name of this player. If the player hasn't a custom name, it will return an empty string.",
				},
			},
			GetDraggingItem =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "In UI windows, get the item that the player is dragging",
				},
			},
			GetEffectiveGameMode =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eGameMode",
						},
					},
					Desc = "Returns the current effective gamemode (inherited gamemode is resolved before returning)",
				},
			},
			GetEquippedItem =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const cItem",
						},
					},
					Desc = "Gets the contents of the player's associated enderchest",
				},
			},
			GetEyeHeight =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
					Desc = "Returns true if the player is currently charging the bow",
				},
			},
			GetEyePosition =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
			},
			GetFloaterID =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
				},
			},
			GetFlyingMaxSpeed =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
					Desc = "Gets the flying relative maximum speed",
				},
			},
			GetFoodExhaustionLevel =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetFoodLevel =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
				},
			},
			GetFoodSaturationLevel =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetFoodTickTimer =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
				},
			},
			GetGameMode =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eGameMode",
						},
					},
					Desc = "Returns the current gamemode. Partly OBSOLETE, you should use IsGameModeXXX() functions wherever applicable",
				},
			},
			GetIP =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
			},
			GetInventory =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cInventory",
						},
					},
				},
			},
			GetLastBedPos =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "Vector3<int>",
						},
					},
					Desc = "Gets the last position that the player slept in\
	This is initialised to the world spawn point if the player has not slept in a bed as of yet",
				},
			},
			GetMainHand =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eMainHand",
						},
					},
				},
			},
			GetMaxSpeed =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
					Desc = "Returns the current relative maximum speed (takes current sprinting / flying state into account)",
				},
			},
			GetName =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const AString",
						},
					},
				},
			},
			GetNormalMaxSpeed =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
					Desc = "Gets the normal relative maximum speed",
				},
			},
			GetPlayerListName =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Returns the name that is used in the playerlist.",
				},
			},
			GetPrefix =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Returns the player name prefix, may contain @ format directives",
				},
			},
			GetSkinParts =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
				},
			},
			GetSprintingMaxSpeed =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
					Desc = "Gets the sprinting relative maximum speed",
				},
			},
			GetStance =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetSuffix =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Returns the player name suffix, may contain @ format directives",
				},
			},
			GetTeam =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cTeam",
						},
					},
					Desc = "Returns the associated team, nullptr if none",
				},
			},
			GetThrowSpeed =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_SpeedCoeff",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
					Desc = "Returns the initial speed vector of a throw, with a 3D length of a_SpeedCoeff.",
				},
			},
			GetThrowStartPos =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
					Desc = "Returns the position where projectiles thrown by this player should start, player eye position + adjustment",
				},
			},
			GetWindow =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cWindow",
						},
					},
				},
			},
			GetXpLevel =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Gets the current level - XpLevel",
				},
			},
			GetXpLifetimeTotal =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Gets the experience total - XpTotal for score on death",
				},
			},
			GetXpPercentage =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "float",
						},
					},
					Desc = "Gets the experience bar percentage - XpP",
				},
			},
			HasCustomName =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player has a custom name.",
				},
			},
			HasPermission =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Permission",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			HasSkinPart =
			{
				{
					Params =
					{
						{
							Type = "eSkinPart",
							Name = "a_Part",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			Heal =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Health",
						},
					},
					Returns =
					{
					},
					Desc = "Heals the player by the specified amount of HPs (positive only); sends health update",
				},
			},
			IsEating =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player is currently in the process of eating the currently equipped item",
				},
			},
			IsFireproof =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player is fireproof\
	Stops players burning in creative or spectator modes.",
				},
			},
			IsFishing =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player has thrown out a floater",
				},
			},
			IsFlying =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player is currently flying",
				},
			},
			IsFrozen =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Is the player frozen?",
				},
			},
			IsGameModeAdventure =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player is in Adventure mode, either explicitly, or by inheriting from current world",
				},
			},
			IsGameModeCreative =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player is in Creative mode, either explicitly, or by inheriting from current world",
				},
			},
			IsGameModeSpectator =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player is in Spectator mode, either explicitly, or by inheriting from current world",
				},
			},
			IsGameModeSurvival =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player is in Survival mode, either explicitly, or by inheriting from current world",
				},
			},
			IsInBed =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if a player is sleeping in a bed",
				},
			},
			IsSatiated =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the player is satiated, i. e. their foodlevel is at the max and they cannot eat anymore",
				},
			},
			IsVisible =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			LoadRank =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "(Re)loads the rank and permissions from the cRankManager.\
	Expects the m_UUID member to be valid.\
	Loads the m_Rank, m_Permissions, m_MsgPrefix, m_MsgSuffix and m_MsgNameColorCode members.",
				},
			},
			OpenWindow =
			{
				{
					Params =
					{
						{
							Type = "cWindow",
							Name = "a_Window",
						},
					},
					Returns =
					{
					},
					Desc = "Opens the specified window; closes the current one first using CloseWindow()",
				},
			},
			PlaceBlock =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_BlockX",
						},
						{
							Type = "int",
							Name = "a_BlockY",
						},
						{
							Type = "int",
							Name = "a_BlockZ",
						},
						{
							Type = "char",
							Name = "a_BlockType",
						},
						{
							Type = "char",
							Name = "a_BlockMeta",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Calls the block-placement hook and places the block in the world, unless refused by the hook.\
	If the hook prevents the placement, sends the current block at the specified coords back to the client.\
	Assumes that the block is in a currently loaded chunk.\
	Returns true if the block is successfully placed.",
				},
			},
			Respawn =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Aborts the current eating operation",
				},
			},
			SendAboveActionBarMessage =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "cCompositeChat",
							Name = "a_Message",
						},
					},
					Returns =
					{
					},
				},
			},
			SendBlocksAround =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_BlockX",
						},
						{
							Type = "int",
							Name = "a_BlockY",
						},
						{
							Type = "int",
							Name = "a_BlockZ",
						},
						{
							Type = "int",
							Name = "a_Range",
						},
					},
					Returns =
					{
					},
					Desc = "Sends the block in the specified range around the specified coord to the client\
	as a block change packet.\
	The blocks in range (a_BlockX - a_Range, a_BlockX + a_Range) are sent (NY-metric).",
				},
			},
			SendMessage =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Returns the SharedPtr to client handle associated with the player.",
				},
				{
					Params =
					{
						{
							Type = "cCompositeChat",
							Name = "a_Message",
						},
					},
					Returns =
					{
					},
				},
			},
			SendMessageFailure =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
			},
			SendMessageFatal =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
			},
			SendMessageInfo =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
			},
			SendMessagePrivateMsg =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
						{
							Type = "AString",
							Name = "a_Sender",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			SendMessageRaw =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_MessageRaw",
						},
						{
							Type = "eChatType",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
			},
			SendMessageSuccess =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
			},
			SendMessageWarning =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
			},
			SendRotation =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_YawDegrees",
						},
						{
							Type = "double",
							Name = "a_PitchDegrees",
						},
					},
					Returns =
					{
					},
					Desc = "Sends the \"look\" packet to the player, forcing them to set their rotation to the specified values.\
	a_YawDegrees is clipped to range [-180, +180),\
	a_PitchDegrees is clipped to range [-180, +180) but the client only uses [-90, +90]",
				},
			},
			SendSystemMessage =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "cCompositeChat",
							Name = "a_Message",
						},
					},
					Returns =
					{
					},
				},
			},
			SetBedPos =
			{
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_Pos",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the player's bed (home / respawn) position to the specified position.\
	Sets the respawn world to the player's world.",
				},
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_Pos",
						},
						{
							Type = "cWorld",
							Name = "a_World",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the player's bed (home / respawn) position and respawn world to the specified parameters.",
				},
			},
			SetCanFly =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_CanFly",
						},
					},
					Returns =
					{
					},
					Desc = "If true the player can fly even when he's not in creative.",
				},
			},
			SetCrouch =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_IsCrouched",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the crouch status, broadcasts to all visible players",
				},
			},
			SetCurrentExperience =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_XpTotal",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Sets the experience total\
	Returns true on success\
	\"should\" really only be called at init or player death, plugins excepted",
				},
			},
			SetCustomName =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_CustomName",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Sets the custom name of this player. If you want to disable the custom name, simply set an empty string.\
	The custom name will be used in the tab-list, in the player nametag and in the tab-completion.",
				},
			},
			SetDraggingItem =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "In UI windows, set the item that the player is dragging",
				},
			},
			SetFlying =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_IsFlying",
						},
					},
					Returns =
					{
					},
					Desc = "Flags the player as flying",
				},
			},
			SetFlyingMaxSpeed =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_Speed",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the flying relative maximum speed. Sends the update to player, if needed.",
				},
			},
			SetFoodExhaustionLevel =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_FoodExhaustionLevel",
						},
					},
					Returns =
					{
					},
				},
			},
			SetFoodLevel =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_FoodLevel",
						},
					},
					Returns =
					{
					},
				},
			},
			SetFoodSaturationLevel =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_FoodSaturationLevel",
						},
					},
					Returns =
					{
					},
				},
			},
			SetFoodTickTimer =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_FoodTickTimer",
						},
					},
					Returns =
					{
					},
				},
			},
			SetGameMode =
			{
				{
					Params =
					{
						{
							Type = "eGameMode",
							Name = "a_GameMode",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the gamemode for the player.\
	The gamemode may be gmNotSet, in that case the player inherits the world's gamemode.\
	Updates the gamemode on the client (sends the packet)",
				},
			},
			SetIsFishing =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_IsFishing",
						},
						{
							Type = "int",
							Name = "a_FloaterID",
						},
					},
					Returns =
					{
					},
				},
			},
			SetMainHand =
			{
				{
					Params =
					{
						{
							Type = "eMainHand",
							Name = "a_Hand",
						},
					},
					Returns =
					{
					},
				},
			},
			SetName =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Name",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
			},
			SetNormalMaxSpeed =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_Speed",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the normal relative maximum speed. Sends the update to player, if needed.",
				},
			},
			SetSkinParts =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Parts",
						},
					},
					Returns =
					{
					},
				},
			},
			SetSprint =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_IsSprinting",
						},
					},
					Returns =
					{
					},
					Desc = "Starts or stops sprinting, sends the max speed update to the client, if needed",
				},
			},
			SetSprintingMaxSpeed =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_Speed",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the sprinting relative maximum speed. Sends the update to player, if needed.",
				},
			},
			SetTeam =
			{
				{
					Params =
					{
						{
							Type = "cTeam",
							Name = "a_Team",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the player team, nullptr if none",
				},
			},
			SetVisible =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_bVisible",
						},
					},
					Returns =
					{
					},
				},
			},
			TossEquippedItem =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Amount",
						},
					},
					Returns =
					{
					},
					Desc = "tosses the item in the selected hotbar slot",
				},
			},
			TossHeldItem =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Amount",
						},
					},
					Returns =
					{
					},
					Desc = "tosses the item held in hand (when in UI windows)",
				},
			},
			TossPickup =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "tosses a pickup newly created from a_Item",
				},
			},
			Unfreeze =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Cancels Freeze(...) and allows the player to move naturally.",
				},
			},
			XpForLevel =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Level",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					IsStatic = true,
					Desc = "Calculates the amount of XP needed for a given level\
	Ref: https://minecraft.gamepedia.com/XP",
				},
			},
		},
		Constants =
		{
			EATING_TICKS =
			{
				Type = "const int",
				Desc = "Number of ticks it takes to eat an item",
			},
			MAX_FOOD_LEVEL =
			{
				Type = "const int",
			},
			MAX_HEALTH =
			{
				Type = "const int",
			},
		},
	},
}
