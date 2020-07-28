return
{
	cPluginManager =
	{
		Functions =
		{
			ExecuteCommand =
			{
				{
					Params =
					{
						{
							Type = "cPlayer",
							Name = "a_Player",
						},
						{
							Type = "AString",
							Name = "a_Command",
						},
					},
					Returns =
					{
						{
							Type = "cPluginManager::CommandResult",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Executes the command, as if it was requested by a_Player. Checks permissions first. Returns crExecuted if executed.",
				},
			},
			ForceExecuteCommand =
			{
				{
					Params =
					{
						{
							Type = "cPlayer",
							Name = "a_Player",
						},
						{
							Type = "AString",
							Name = "a_Command",
						},
					},
					Returns =
					{
						{
							Type = "cPluginManager::CommandResult",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Executes the command, as if it was requested by a_Player. Permisssions are not checked. Returns crExecuted if executed.",
				},
			},
			Get =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cPluginManager",
						},
					},
					IsStatic = true,
					Desc = "Returns the instance of the Plugin Manager (there is only ever one)",
				},
			},
			GetCommandPermission =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Command",
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
					Desc = "Returns the permission needed for the specified command; empty string if command not found",
				},
			},
			GetNumLoadedPlugins =
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
					Desc = "Returns the number of plugins that are psLoaded.",
				},
			},
			GetNumPlugins =
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
					Desc = "Returns the number of all plugins in m_Plugins (includes disabled, unloaded and errored plugins).",
				},
			},
			GetPluginFolderName =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_PluginName",
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
					Desc = "Returns the name of the folder (cPlugin::GetFolderName()) from which the specified plugin was loaded.",
				},
			},
			GetPluginsPath =
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
					IsStatic = true,
					Desc = "Returns the path where individual plugins' folders are expected.\
	The path doesn't end in a slash.",
				},
			},
			IsCommandBound =
			{
				{
					Params =
					{
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
					Desc = "Returns true if the command is in the command map",
				},
			},
			IsConsoleCommandBound =
			{
				{
					Params =
					{
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
					Desc = "Returns true if the console command is in the command map",
				},
			},
			IsPluginLoaded =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_PluginName",
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
					Desc = "Returns true if the specified plugin is loaded.",
				},
			},
			LoadPlugin =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_PluginFolder",
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
					Desc = "Loads the plugin from the specified plugin folder.\
	Returns true if the plugin was loaded successfully or was already loaded before, false otherwise.",
				},
			},
			RefreshPluginList =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Refreshes the m_Plugins list based on the current contents of the Plugins folder.\
	If an active plugin's folder is not found anymore, the plugin is set as psNotFound, but not yet unloaded.",
				},
			},
			ReloadPlugins =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Schedules a reload of the plugins to happen within the next call to Tick().",
				},
			},
			UnloadPlugin =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_PluginFolder",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Queues the specified plugin to be unloaded in the next call to Tick().\
	Note that this function returns before the plugin is unloaded, to avoid deadlocks.",
				},
			},
		},
		Enums =
		{
			CommandResult =
			{
				{
					Name = "crBlocked",
				},
				{
					Name = "crError",
				},
				{
					Name = "crExecuted",
				},
				{
					Name = "crNoPermission",
				},
				{
					Name = "crUnknownCommand",
				},
			},
			PluginHook =
			{
				{
					Name = "HOOK_BLOCK_SPREAD",
				},
				{
					Name = "HOOK_BLOCK_TO_PICKUPS",
				},
				{
					Name = "HOOK_BREWING_COMPLETED",
				},
				{
					Name = "HOOK_BREWING_COMPLETING",
				},
				{
					Name = "HOOK_CHAT",
				},
				{
					Name = "HOOK_CHUNK_AVAILABLE",
				},
				{
					Name = "HOOK_CHUNK_GENERATED",
				},
				{
					Name = "HOOK_CHUNK_GENERATING",
				},
				{
					Name = "HOOK_CHUNK_UNLOADED",
				},
				{
					Name = "HOOK_CHUNK_UNLOADING",
				},
				{
					Name = "HOOK_COLLECTING_PICKUP",
				},
				{
					Name = "HOOK_CRAFTING_NO_RECIPE",
				},
				{
					Name = "HOOK_DISCONNECT",
				},
				{
					Name = "HOOK_ENTITY_ADD_EFFECT",
				},
				{
					Name = "HOOK_ENTITY_CHANGED_WORLD",
				},
				{
					Name = "HOOK_ENTITY_CHANGING_WORLD",
				},
				{
					Name = "HOOK_ENTITY_TELEPORT",
				},
				{
					Name = "HOOK_EXECUTE_COMMAND",
				},
				{
					Name = "HOOK_EXPLODED",
				},
				{
					Name = "HOOK_EXPLODING",
				},
				{
					Name = "HOOK_HANDSHAKE",
				},
				{
					Name = "HOOK_HOPPER_PULLING_ITEM",
				},
				{
					Name = "HOOK_HOPPER_PUSHING_ITEM",
				},
				{
					Name = "HOOK_KILLED",
				},
				{
					Name = "HOOK_KILLING",
				},
				{
					Name = "HOOK_LOGIN",
				},
				{
					Name = "HOOK_LOGIN_FORGE",
				},
				{
					Name = "HOOK_PLAYER_ANIMATION",
				},
				{
					Name = "HOOK_PLAYER_BREAKING_BLOCK",
				},
				{
					Name = "HOOK_PLAYER_BROKEN_BLOCK",
				},
				{
					Name = "HOOK_PLAYER_DESTROYED",
				},
				{
					Name = "HOOK_PLAYER_EATING",
				},
				{
					Name = "HOOK_PLAYER_FISHED",
				},
				{
					Name = "HOOK_PLAYER_FISHING",
				},
				{
					Name = "HOOK_PLAYER_FOOD_LEVEL_CHANGE",
				},
				{
					Name = "HOOK_PLAYER_JOINED",
				},
				{
					Name = "HOOK_PLAYER_LEFT_CLICK",
				},
				{
					Name = "HOOK_PLAYER_MOVING",
				},
				{
					Name = "HOOK_PLAYER_OPENING_WINDOW",
				},
				{
					Name = "HOOK_PLAYER_PLACED_BLOCK",
				},
				{
					Name = "HOOK_PLAYER_PLACING_BLOCK",
				},
				{
					Name = "HOOK_PLAYER_RIGHT_CLICK",
				},
				{
					Name = "HOOK_PLAYER_RIGHT_CLICKING_ENTITY",
				},
				{
					Name = "HOOK_PLAYER_SHOOTING",
				},
				{
					Name = "HOOK_PLAYER_SPAWNED",
				},
				{
					Name = "HOOK_PLAYER_TOSSING_ITEM",
				},
				{
					Name = "HOOK_PLAYER_USED_BLOCK",
				},
				{
					Name = "HOOK_PLAYER_USED_ITEM",
				},
				{
					Name = "HOOK_PLAYER_USING_BLOCK",
				},
				{
					Name = "HOOK_PLAYER_USING_ITEM",
				},
				{
					Name = "HOOK_PLUGINS_LOADED",
				},
				{
					Name = "HOOK_PLUGIN_MESSAGE",
				},
				{
					Name = "HOOK_POST_CRAFTING",
				},
				{
					Name = "HOOK_PRE_CRAFTING",
				},
				{
					Name = "HOOK_PROJECTILE_HIT_BLOCK",
				},
				{
					Name = "HOOK_PROJECTILE_HIT_ENTITY",
				},
				{
					Name = "HOOK_SERVER_PING",
				},
				{
					Name = "HOOK_SPAWNED_ENTITY",
				},
				{
					Name = "HOOK_SPAWNED_MONSTER",
				},
				{
					Name = "HOOK_SPAWNING_ENTITY",
				},
				{
					Name = "HOOK_SPAWNING_MONSTER",
				},
				{
					Name = "HOOK_TAKE_DAMAGE",
				},
				{
					Name = "HOOK_TICK",
				},
				{
					Name = "HOOK_UPDATED_SIGN",
				},
				{
					Name = "HOOK_UPDATING_SIGN",
				},
				{
					Name = "HOOK_WEATHER_CHANGED",
				},
				{
					Name = "HOOK_WEATHER_CHANGING",
				},
				{
					Name = "HOOK_WORLD_STARTED",
				},
				{
					Name = "HOOK_WORLD_TICK",
				},
			},
			ePluginStatus =
			{
				{
					Name = "psDisabled",
					Desc = "The plugin is disabled in settings.ini.",
				},
				{
					Name = "psError",
					Desc = "The plugin is enabled in settings.ini but has failed to load.\
		m_LoadError is the description of the error.",
				},
				{
					Name = "psLoaded",
					Desc = "The plugin has been loaded successfully.",
				},
				{
					Name = "psNotFound",
					Desc = "The plugin has been loaded before, but after a folder refresh it is no longer present.\
		The plugin will be unloaded in the next call to ReloadPlugins().",
				},
				{
					Name = "psUnloaded",
					Desc = "The plugin is enabled in settings.ini but has been unloaded (by a command).",
				},
			},
		},
	},
}
