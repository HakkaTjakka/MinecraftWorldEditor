return
{
	cWorld =
	{
		Functions =
		{
			AreCommandBlocksEnabled =
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
			BroadcastChat =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
						{
							Type = "cClientHandle",
							Name = "a_Exclude",
						},
						{
							Type = "eMessageType",
							Name = "a_ChatPrefix",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Retrieves the world height at the specified coords; returns false if chunk not loaded / generated",
				},
				{
					Params =
					{
						{
							Type = "cCompositeChat",
							Name = "a_Message",
						},
						{
							Type = "cClientHandle",
							Name = "a_Exclude",
						},
					},
					Returns =
					{
					},
				},
			},
			BroadcastChatDeath =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
						{
							Type = "cClientHandle",
							Name = "a_Exclude",
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
			BroadcastChatFailure =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
						{
							Type = "cClientHandle",
							Name = "a_Exclude",
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
			BroadcastChatFatal =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
						{
							Type = "cClientHandle",
							Name = "a_Exclude",
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
			BroadcastChatInfo =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
						{
							Type = "cClientHandle",
							Name = "a_Exclude",
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
			BroadcastChatSuccess =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
						{
							Type = "cClientHandle",
							Name = "a_Exclude",
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
			BroadcastChatWarning =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Message",
						},
						{
							Type = "cClientHandle",
							Name = "a_Exclude",
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
			BroadcastEntityAnimation =
			{
				{
					Params =
					{
						{
							Type = "cEntity",
							Name = "a_Entity",
						},
						{
							Type = "char",
							Name = "a_Animation",
						},
						{
							Type = "cClientHandle",
							Name = "a_Exclude",
						},
					},
					Returns =
					{
					},
				},
			},
			CastThunderbolt =
			{
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_Block",
						},
					},
					Returns =
					{
					},
					Desc = "Casts a thunderbolt at the specified coords",
				},
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
					},
					Returns =
					{
					},
				},
			},
			ChangeWeather =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Forces a weather change in the next game tick",
				},
			},
			CreateProjectile =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_PosX",
						},
						{
							Type = "double",
							Name = "a_PosY",
						},
						{
							Type = "double",
							Name = "a_PosZ",
						},
						{
							Type = "cProjectileEntity::eKind",
							Name = "a_Kind",
						},
						{
							Type = "cEntity",
							Name = "a_Creator",
						},
						{
							Type = "cItem",
							Name = "a_Item",
						},
						{
							Type = "Vector3<double>",
							Name = "a_Speed",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Creates a projectile of the specified type. Returns the projectile's UniqueID if successful, cEntity::INVALID_ID otherwise\
	Item parameter is currently used for Fireworks to correctly set entity metadata based on item metadata.",
				},
			},
			DigBlock =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_X",
						},
						{
							Type = "int",
							Name = "a_Y",
						},
						{
							Type = "int",
							Name = "a_Z",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Retrieves block types of the specified blocks. If a chunk is not loaded, doesn't modify the block. Returns true if all blocks were read.",
				},
			},
			FastSetBlock =
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
					},
					Desc = "Sets the block at the specified coords to the specified value.\
	The replacement doesn't trigger block updates.\
	The replaced blocks aren't checked for block entities (block entity is leaked if it exists at this block)",
				},
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_Pos",
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
					},
				},
			},
			GenerateChunk =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_ChunkX",
						},
						{
							Type = "int",
							Name = "a_ChunkZ",
						},
					},
					Returns =
					{
					},
					Desc = "Generates the given chunk",
				},
			},
			GetBiomeAt =
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
							Name = "a_BlockZ",
						},
					},
					Returns =
					{
						{
							Type = "EMCSBiome",
						},
					},
					Desc = "Returns the biome at the specified coords. Reads the biome from the chunk, if loaded, otherwise uses the world generator to provide the biome value",
				},
			},
			GetBlock =
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
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
				},
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
						{
							Type = "char",
						},
					},
				},
			},
			GetBlockBlockLight =
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
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
				},
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
						{
							Type = "char",
						},
					},
				},
			},
			GetBlockMeta =
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
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
				},
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
						{
							Type = "char",
						},
					},
				},
			},
			GetBlockSkyLight =
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
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
				},
			},
			GetDataPath =
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
					Desc = "Returns the data path to the world data",
				},
			},
			GetDefaultWeatherInterval =
			{
				{
					Params =
					{
						{
							Type = "eWeather",
							Name = "a_Weather",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns the default weather interval for the specific weather type.\
	Returns -1 for any unknown weather.",
				},
			},
			GetDimension =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eDimension",
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
					Desc = "Returns the current game mode. Partly OBSOLETE, you should use IsGameModeXXX() functions wherever applicable",
				},
			},
			GetGeneratorQueueLength =
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
					Desc = "Returns the number of chunks loaded and dirty, and in the lighting queue",
				},
			},
			GetHeight =
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
							Name = "a_BlockZ",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns the world height at the specified coords; waits for the chunk to get loaded / generated",
				},
			},
			GetIniFileName =
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
					Desc = "Returns the name of the world.ini file used by this world",
				},
			},
			GetLightingQueueLength =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "size_t",
						},
					},
				},
			},
			GetLinkedEndWorldName =
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
			GetLinkedNetherWorldName =
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
			GetLinkedOverworldName =
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
			GetMapManager =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cMapManager",
						},
					},
					Desc = "Returns the associated map manager instance.",
				},
			},
			GetMaxCactusHeight =
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
			GetMaxNetherPortalHeight =
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
			GetMaxNetherPortalWidth =
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
			GetMaxSugarcaneHeight =
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
			GetMaxViewDistance =
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
			GetMinNetherPortalHeight =
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
					Desc = "Returns or sets the minumim or maximum netherportal height",
				},
			},
			GetMinNetherPortalWidth =
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
					Desc = "Returns or sets the minumim or maximum netherportal width",
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
					Desc = "Returns the name of the world",
				},
			},
			GetNumChunks =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "size_t",
						},
					},
					Desc = "Returns the number of chunks loaded",
				},
			},
			GetNumUnusedDirtyChunks =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "size_t",
						},
					},
					Desc = "Returns the number of unused dirty chunks. That's the number of chunks that we can save and then unload.",
				},
			},
			GetScoreBoard =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cScoreboard",
						},
					},
					Desc = "Returns the associated scoreboard instance.",
				},
			},
			GetSeed =
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
					Desc = "Returns the seed of the world.",
				},
			},
			GetSpawnX =
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
			GetSpawnY =
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
			GetSpawnZ =
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
			GetStorageLoadQueueLength =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "size_t",
						},
					},
				},
			},
			GetStorageSaveQueueLength =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "size_t",
						},
					},
				},
			},
			GetTNTShrapnelLevel =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eShrapnelLevel",
						},
					},
				},
			},
			GetTicksUntilWeatherChange =
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
			GetTimeOfDay =
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
			GetWeather =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eWeather",
						},
					},
					Desc = "Returns the current weather. Instead of comparing values directly to the weather constants, use IsWeatherXXX() functions, if possible",
				},
			},
			GetWorldAge =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "long",
						},
					},
				},
			},
			GrowCactus =
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
							Name = "a_NumBlocksToGrow",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Grows a cactus present at the block specified by the amount of blocks specified, up to the max height specified in the config; returns the amount of blocks the cactus grew inside this call",
				},
			},
			GrowMelonPumpkin =
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
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Grows a melon or a pumpkin next to the block specified (assumed to be the stem); returns true if the pumpkin or melon sucessfully grew.",
				},
			},
			GrowRipePlant =
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
							Type = "bool",
							Name = "a_IsByBonemeal",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Grows the plant at the specified block to its ripe stage (bonemeal used); returns false if the block is not growable. If a_IsBonemeal is true, block is not grown if not allowed in world.ini",
				},
			},
			GrowSugarcane =
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
							Name = "a_NumBlocksToGrow",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Grows a sugarcane present at the block specified by the amount of blocks specified, up to the max height specified in the config; returns the amount of blocks the sugarcane grew inside this call",
				},
			},
			GrowTree =
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
					},
					Returns =
					{
					},
					Desc = "Grows a tree at the specified coords, either from a sapling there, or based on the biome",
				},
			},
			GrowTreeByBiome =
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
					},
					Returns =
					{
					},
					Desc = "Grows a tree at the specified coords, based on the biome in the place",
				},
			},
			GrowTreeFromSapling =
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
							Name = "a_SaplingMeta",
						},
					},
					Returns =
					{
					},
					Desc = "Grows a tree at the specified coords, based on the sapling meta provided",
				},
			},
			IsBlockDirectlyWatered =
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
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
			IsDaylightCycleEnabled =
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
					Desc = "Is the daylight cycle enabled?",
				},
			},
			IsDeepSnowEnabled =
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
					Desc = "Returns true if the world is in Adventure mode",
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
					Desc = "Returns true if the world is in Creative mode",
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
					Desc = "Returns true if the world is in Spectator mode",
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
					Desc = "Returns true if the world is in Survival mode",
				},
			},
			IsPVPEnabled =
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
			IsSavingEnabled =
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
					Desc = "Get whether saving chunks is enabled",
				},
			},
			IsTrapdoorOpen =
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
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Is the trapdoor open? Returns false if there is no trapdoor at the specified coords.",
				},
			},
			IsWeatherRain =
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
					Desc = "Returns true if the current weather is rainy.",
				},
			},
			IsWeatherRainAt =
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
							Name = "a_BlockZ",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if it is raining at the specified location. This takes into account biomes.",
				},
			},
			IsWeatherStorm =
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
					Desc = "Returns true if the current weather is stormy.",
				},
			},
			IsWeatherStormAt =
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
							Name = "a_BlockZ",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the weather is stormy at the specified location. This takes into account biomes.",
				},
			},
			IsWeatherSunny =
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
					Desc = "Returns true if the current weather is sunny.",
				},
			},
			IsWeatherSunnyAt =
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
							Name = "a_BlockZ",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if it is sunny at the specified location. This takes into account biomes.",
				},
			},
			IsWeatherWet =
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
					Desc = "Returns true if the world currently has any precipitation - rain, storm or snow.",
				},
			},
			IsWeatherWetAt =
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
							Name = "a_BlockZ",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if it is raining or storming at the specified location.\
	This takes into account biomes.",
				},
			},
			IsWeatherWetAtXYZ =
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
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the specified location has wet weather (rain or storm),\
	using the same logic as IsWeatherWetAt, except that any rain-blocking blocks\
	above the specified position will block the precipitation and this function\
	will return false.",
				},
			},
			QueueBlockForTick =
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
							Name = "a_TicksToWait",
						},
					},
					Returns =
					{
					},
					Desc = "Queues the block to be ticked after the specified number of game ticks",
				},
			},
			QueueSaveAllChunks =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Queues a task to save all chunks onto the tick thread. The prefferred way of saving chunks from external sources",
				},
			},
			QueueUnloadUnusedChunks =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Queues a task to unload unused chunks onto the tick thread. The prefferred way of unloading.",
				},
			},
			RegenerateChunk =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_ChunkX",
						},
						{
							Type = "int",
							Name = "a_ChunkZ",
						},
					},
					Returns =
					{
					},
					Desc = "Regenerate the given chunk:",
				},
			},
			SendBlockTo =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_X",
						},
						{
							Type = "int",
							Name = "a_Y",
						},
						{
							Type = "int",
							Name = "a_Z",
						},
						{
							Type = "cPlayer",
							Name = "a_Player",
						},
					},
					Returns =
					{
					},
				},
			},
			SetAreaBiome =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_MinX",
						},
						{
							Type = "int",
							Name = "a_MaxX",
						},
						{
							Type = "int",
							Name = "a_MinZ",
						},
						{
							Type = "int",
							Name = "a_MaxZ",
						},
						{
							Type = "EMCSBiome",
							Name = "a_Biome",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Sets the biome at the area. Returns true if successful, false if any subarea failed (chunk not loaded).\
	(Re)sends the chunks to their relevant clients if successful.",
				},
				{
					Params =
					{
						{
							Type = "cCuboid",
							Name = "a_Area",
						},
						{
							Type = "EMCSBiome",
							Name = "a_Biome",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Sets the biome at the area. Returns true if successful, false if any subarea failed (chunk not loaded).\
	(Re)sends the chunks to their relevant clients if successful.\
	The cuboid needn't be sorted.",
				},
			},
			SetBiomeAt =
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
							Name = "a_BlockZ",
						},
						{
							Type = "EMCSBiome",
							Name = "a_Biome",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Sets the biome at the specified coords. Returns true if successful, false if not (chunk not loaded).\
	Doesn't resend the chunk to clients, use ForceSendChunkTo() for that.",
				},
			},
			SetBlock =
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
						{
							Type = "bool",
							Name = "a_SendToClients",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the block at the specified coords to the specified value.\
	Full processing, incl. updating neighbors, is performed.",
				},
			},
			SetBlockMeta =
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
							Name = "a_MetaData",
						},
						{
							Type = "bool",
							Name = "a_ShouldMarkDirty",
						},
						{
							Type = "bool",
							Name = "a_ShouldInformClients",
						},
					},
					Returns =
					{
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_Pos",
						},
						{
							Type = "char",
							Name = "a_MetaData",
						},
					},
					Returns =
					{
					},
				},
			},
			SetChunkAlwaysTicked =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_ChunkX",
						},
						{
							Type = "int",
							Name = "a_ChunkZ",
						},
						{
							Type = "bool",
							Name = "a_AlwaysTicked",
						},
					},
					Returns =
					{
					},
					Desc = "Increments (a_AlwaysTicked == true) or decrements (false) the m_AlwaysTicked counter for the specified chunk.\
	If the m_AlwaysTicked counter is greater than zero, the chunk is ticked in the tick-thread regardless of\
	whether it has any clients or not.\
	This function allows nesting and task-concurrency (multiple separate tasks can request ticking and as long\
	as at least one requests is active the chunk will be ticked).",
				},
			},
			SetCommandBlockCommand =
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
							Type = "AString",
							Name = "a_Command",
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
					Desc = "Sets the command block command. Returns true if command changed.",
				},
			},
			SetCommandBlocksEnabled =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_Flag",
						},
					},
					Returns =
					{
					},
				},
			},
			SetDaylightCycleEnabled =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_IsDaylightCycleEnabled",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the daylight cycle to true / false.",
				},
			},
			SetLinkedEndWorldName =
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
			SetLinkedNetherWorldName =
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
			SetLinkedOverworldName =
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
			SetMaxNetherPortalHeight =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_NewMaxHeight",
						},
					},
					Returns =
					{
					},
				},
			},
			SetMaxNetherPortalWidth =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_NewMaxWidth",
						},
					},
					Returns =
					{
					},
				},
			},
			SetMaxViewDistance =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_MaxViewDistance",
						},
					},
					Returns =
					{
					},
				},
			},
			SetMinNetherPortalHeight =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_NewMinHeight",
						},
					},
					Returns =
					{
					},
				},
			},
			SetMinNetherPortalWidth =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_NewMinWidth",
						},
					},
					Returns =
					{
					},
				},
			},
			SetNextBlockTick =
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
					},
					Returns =
					{
					},
					Desc = "Sets the blockticking to start at the specified block. Only one blocktick per chunk may be set, second call overwrites the first call",
				},
			},
			SetSavingEnabled =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_IsSavingEnabled",
						},
					},
					Returns =
					{
					},
					Desc = "Set whether saving chunks is enabled",
				},
			},
			SetShouldUseChatPrefixes =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_Flag",
						},
					},
					Returns =
					{
					},
				},
			},
			SetSpawn =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_X",
						},
						{
							Type = "double",
							Name = "a_Y",
						},
						{
							Type = "double",
							Name = "a_Z",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Set default spawn at the given coordinates.\
	Returns false if the new spawn couldn't be stored in the INI file.",
				},
			},
			SetTNTShrapnelLevel =
			{
				{
					Params =
					{
						{
							Type = "eShrapnelLevel",
							Name = "a_Flag",
						},
					},
					Returns =
					{
					},
				},
			},
			SetTicksUntilWeatherChange =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_WeatherInterval",
						},
					},
					Returns =
					{
					},
				},
			},
			SetTimeOfDay =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_TimeOfDay",
						},
					},
					Returns =
					{
					},
				},
			},
			SetTrapdoorOpen =
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
							Type = "bool",
							Name = "a_Open",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Set the state of a trapdoor. Returns true if the trapdoor was updated, false if there was no trapdoor at those coords.",
				},
			},
			SetWeather =
			{
				{
					Params =
					{
						{
							Type = "eWeather",
							Name = "a_NewWeather",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the specified weather; resets weather interval; asks and notifies plugins of the change",
				},
			},
			ShouldBroadcastAchievementMessages =
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
			ShouldBroadcastDeathMessages =
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
			ShouldLavaSpawnFire =
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
			ShouldUseChatPrefixes =
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
			SpawnBoat =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_X",
						},
						{
							Type = "double",
							Name = "a_Y",
						},
						{
							Type = "double",
							Name = "a_Z",
						},
						{
							Type = "cBoat::eMaterial",
							Name = "a_Material",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Pos",
						},
						{
							Type = "cBoat::eMaterial",
							Name = "a_Material",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Spawns a boat at the given coordinates.\
	Returns the UniqueID of the spawned boat, or cEntity::INVALID_ID on failure.",
				},
			},
			SpawnExperienceOrb =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_X",
						},
						{
							Type = "double",
							Name = "a_Y",
						},
						{
							Type = "double",
							Name = "a_Z",
						},
						{
							Type = "int",
							Name = "a_Reward",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Spawns an experience orb at the given location with the given reward.\
	Returns the UniqueID of the spawned experience orb, or cEntity::INVALID_ID on failure.",
				},
			},
			SpawnFallingBlock =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_X",
						},
						{
							Type = "int",
							Name = "a_Y",
						},
						{
							Type = "int",
							Name = "a_Z",
						},
						{
							Type = "char",
							Name = "BlockType",
						},
						{
							Type = "char",
							Name = "BlockMeta",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Spawns an falling block entity at the given position.\
	Returns the UniqueID of the spawned falling block, or cEntity::INVALID_ID on failure.",
				},
			},
			SpawnItemPickup =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_PosX",
						},
						{
							Type = "double",
							Name = "a_PosY",
						},
						{
							Type = "double",
							Name = "a_PosZ",
						},
						{
							Type = "cItem",
							Name = "a_Item",
						},
						{
							Type = "float",
							Name = "a_SpeedX",
						},
						{
							Type = "float",
							Name = "a_SpeedY",
						},
						{
							Type = "float",
							Name = "a_SpeedZ",
						},
						{
							Type = "int",
							Name = "a_LifetimeTicks",
						},
						{
							Type = "bool",
							Name = "a_CanCombine",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Spawns a single pickup containing the specified item.",
				},
			},
			SpawnItemPickups =
			{
				{
					Params =
					{
						{
							Type = "cItems",
							Name = "a_Pickups",
						},
						{
							Type = "double",
							Name = "a_BlockX",
						},
						{
							Type = "double",
							Name = "a_BlockY",
						},
						{
							Type = "double",
							Name = "a_BlockZ",
						},
						{
							Type = "double",
							Name = "a_FlyAwaySpeed",
						},
						{
							Type = "bool",
							Name = "IsPlayerCreated",
						},
					},
					Returns =
					{
					},
					Desc = "Spawns item pickups for each item in the list. May compress pickups if too many entities:",
				},
				{
					Params =
					{
						{
							Type = "cItems",
							Name = "a_Pickups",
						},
						{
							Type = "double",
							Name = "a_BlockX",
						},
						{
							Type = "double",
							Name = "a_BlockY",
						},
						{
							Type = "double",
							Name = "a_BlockZ",
						},
						{
							Type = "double",
							Name = "a_SpeedX",
						},
						{
							Type = "double",
							Name = "a_SpeedY",
						},
						{
							Type = "double",
							Name = "a_SpeedZ",
						},
						{
							Type = "bool",
							Name = "IsPlayerCreated",
						},
					},
					Returns =
					{
					},
					Desc = "Spawns item pickups for each item in the list. May compress pickups if too many entities. All pickups get the speed specified.",
				},
			},
			SpawnMinecart =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_X",
						},
						{
							Type = "double",
							Name = "a_Y",
						},
						{
							Type = "double",
							Name = "a_Z",
						},
						{
							Type = "int",
							Name = "a_MinecartType",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Spawns an minecart at the given coordinates.\
	Returns the UniqueID of the spawned minecart, or cEntity::INVALID_ID on failure.",
				},
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_X",
						},
						{
							Type = "double",
							Name = "a_Y",
						},
						{
							Type = "double",
							Name = "a_Z",
						},
						{
							Type = "int",
							Name = "a_MinecartType",
						},
						{
							Type = "cItem",
							Name = "a_Content",
						},
						{
							Type = "int",
							Name = "a_BlockHeight",
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
			SpawnMob =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_PosX",
						},
						{
							Type = "double",
							Name = "a_PosY",
						},
						{
							Type = "double",
							Name = "a_PosZ",
						},
						{
							Type = "eMonsterType",
							Name = "a_MonsterType",
						},
						{
							Type = "bool",
							Name = "a_Baby",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Spawns a mob of the specified type. Returns the mob's UniqueID if recognized and spawned, cEntity::INVALID_ID otherwise",
				},
			},
			SpawnPrimedTNT =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_X",
						},
						{
							Type = "double",
							Name = "a_Y",
						},
						{
							Type = "double",
							Name = "a_Z",
						},
						{
							Type = "int",
							Name = "a_FuseTimeInSec",
						},
						{
							Type = "double",
							Name = "a_InitialVelocityCoeff",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Spawns experience orbs of the specified total value at the given location. The orbs' values are split according to regular Minecraft rules.\
	Returns an vector of UniqueID of all the orbs.",
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Pos",
						},
						{
							Type = "int",
							Name = "a_FuseTimeInSec",
						},
						{
							Type = "double",
							Name = "a_InitialVelocityCoeff",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Spawns a new primed TNT entity at the specified block coords and specified fuse duration.\
	Initial velocity is given based on the relative coefficient provided.\
	Returns the UniqueID of the created entity, or cEntity::INVALID_ID on failure.",
				},
			},
			UseBlockEntity =
			{
				{
					Params =
					{
						{
							Type = "cPlayer",
							Name = "a_Player",
						},
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
					},
					Returns =
					{
					},
					Desc = "a_Player is using block entity at [x, y, z], handle that:",
				},
			},
			VillagersShouldHarvestCrops =
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
			WakeUpSimulators =
			{
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_Block",
						},
					},
					Returns =
					{
					},
					Desc = "Wakes up the simulators for the specified block",
				},
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
					},
					Returns =
					{
					},
				},
			},
			WakeUpSimulatorsInArea =
			{
				{
					Params =
					{
						{
							Type = "cCuboid",
							Name = "a_Area",
						},
					},
					Returns =
					{
					},
					Desc = "Wakes up the simulators for the specified area of blocks",
				},
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_MinBlockX",
						},
						{
							Type = "int",
							Name = "a_MaxBlockX",
						},
						{
							Type = "int",
							Name = "a_MinBlockY",
						},
						{
							Type = "int",
							Name = "a_MaxBlockY",
						},
						{
							Type = "int",
							Name = "a_MinBlockZ",
						},
						{
							Type = "int",
							Name = "a_MaxBlockZ",
						},
					},
					Returns =
					{
					},
				},
			},
		},
	},
}
