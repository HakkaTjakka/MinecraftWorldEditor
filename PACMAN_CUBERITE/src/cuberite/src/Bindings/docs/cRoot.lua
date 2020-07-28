return
{
	cRoot =
	{
		Desc = "The root of the object hierarchy",
		Functions =
		{
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
					Desc = "Sends a chat message to all connected clients (in all worlds)",
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
			BroadcastChatDeath =
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
			BroadcastChatFailure =
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
			BroadcastChatFatal =
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
			BroadcastChatInfo =
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
			BroadcastChatJoin =
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
			BroadcastChatLeave =
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
			BroadcastChatSuccess =
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
			BroadcastChatWarning =
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
			Get =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cRoot",
						},
					},
					IsStatic = true,
				},
			},
			GetCraftingRecipes =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cCraftingRecipes",
						},
					},
					Desc = "Writes chunkstats, for each world and totals, to the output callback",
				},
			},
			GetDefaultWorld =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cWorld",
						},
					},
				},
			},
			GetFurnaceFuelBurnTime =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_Fuel",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					IsStatic = true,
					Desc = "Returns the number of ticks for how long the item would fuel a furnace. Returns zero if not a fuel",
				},
			},
			GetPhysicalRAMUsage =
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
					IsStatic = true,
					Desc = "Returns the amount of virtual RAM used, in KiB. Returns a negative number on error",
				},
			},
			GetPluginManager =
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
				},
			},
			GetProtocolVersionTextFromInt =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_ProtocolVersionNum",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Returns the textual description of the protocol version: 49 -> \"1.4.4\". Provided specifically for Lua API",
				},
			},
			GetServer =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cServer",
						},
					},
					Desc = "Stops the server, as if \"/stop\" was typed in the console.",
				},
			},
			GetServerUpTime =
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
					Desc = "Returns the up time of the server in seconds",
				},
			},
			GetTotalChunkCount =
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
					Desc = "Returns the number of chunks loaded",
				},
			},
			GetVirtualRAMUsage =
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
					IsStatic = true,
					Desc = "Returns the amount of virtual RAM used, in KiB. Returns a negative number on error",
				},
			},
			GetWebAdmin =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cWebAdmin",
						},
					},
					Desc = "The current time where the startup of the server has been completed",
				},
			},
			GetWorld =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_WorldName",
						},
					},
					Returns =
					{
						{
							Type = "cWorld",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Returns a pointer to the world specified. If no world of that name exists, returns a nullptr.",
				},
			},
			QueueExecuteConsoleCommand =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Cmd",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Queues a console command for execution through the cServer class.\
	The command will be executed in the tick thread\
	The command's output will be sent to console\
	\"stop\" and \"restart\" commands have special handling.",
				},
			},
			SaveAllChunks =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Saves all chunks in all worlds",
				},
			},
			SetSavingEnabled =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_SavingEnabled",
						},
					},
					Returns =
					{
					},
					Desc = "Sets whether saving chunks is enabled in all worlds (overrides however the worlds were already set)",
				},
			},
		},
	},
}
