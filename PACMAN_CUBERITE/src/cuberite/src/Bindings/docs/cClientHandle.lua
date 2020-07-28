return
{
	cClientHandle =
	{
		Functions =
		{
			GetClientBrand =
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
					Desc = "Returns the client brand received in the MC|Brand plugin message or set by a plugin.",
				},
			},
			GetForgeMods =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const AStringMap",
						},
					},
					Desc = "Returns the Forge mods installed on the client.",
				},
			},
			GetIPString =
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
					Desc = "Creates a new client with the specified IP address in its description and the specified initial view distance.",
				},
			},
			GetLocale =
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
			GetPing =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "short",
						},
					},
				},
			},
			GetPlayer =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cPlayer",
						},
					},
					Desc = "Sets the IP string that the client is using. Overrides the IP string that was read from the socket.\
	Used mainly by BungeeCord compatibility code.",
				},
			},
			GetProtocolVersion =
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
					Desc = "Returns the protocol version number of the protocol that the client is talking. Returns zero if the protocol version is not (yet) known.",
				},
			},
			GetRequestedViewDistance =
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
					Desc = "Returns the view distance that the player request, not the used view distance.",
				},
			},
			GetUniqueID =
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
			GetUsername =
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
			GetViewDistance =
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
					Desc = "Returns the view distance that the player currently have.",
				},
			},
			HasPluginChannel =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_PluginChannel",
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
			IsForgeClient =
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
					Desc = "Returns true if the client is modded with Forge.",
				},
			},
			Kick =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Reason",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Formats the type of message with the proper color and prefix for sending to the client.",
				},
			},
			SendBlockChange =
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
					Desc = "Called while the client is being ticked from the cServer object",
				},
			},
			SendEntityAnimation =
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
					},
					Returns =
					{
					},
				},
			},
			SendHideTitle =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
				},
			},
			SendResetTitle =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
				},
			},
			SendSetRawSubTitle =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_SubTitle",
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
			SendSetRawTitle =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Title",
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
			SendSetSubTitle =
			{
				{
					Params =
					{
						{
							Type = "cCompositeChat",
							Name = "a_SubTitle",
						},
					},
					Returns =
					{
					},
				},
			},
			SendSetTitle =
			{
				{
					Params =
					{
						{
							Type = "cCompositeChat",
							Name = "a_Title",
						},
					},
					Returns =
					{
					},
				},
			},
			SendSoundEffect =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_SoundName",
						},
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
							Type = "float",
							Name = "a_Volume",
						},
						{
							Type = "float",
							Name = "a_Pitch",
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
							Type = "AString",
							Name = "a_SoundName",
						},
						{
							Type = "Vector3<double>",
							Name = "a_Position",
						},
						{
							Type = "float",
							Name = "a_Volume",
						},
						{
							Type = "float",
							Name = "a_Pitch",
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
			SendTimeUpdate =
			{
				{
					Params =
					{
						{
							Type = "long",
							Name = "a_WorldAge",
						},
						{
							Type = "long",
							Name = "a_TimeOfDay",
						},
						{
							Type = "bool",
							Name = "a_DoDaylightCycle",
						},
					},
					Returns =
					{
					},
				},
			},
			SendTitleTimes =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_FadeInTicks",
						},
						{
							Type = "int",
							Name = "a_DisplayTicks",
						},
						{
							Type = "int",
							Name = "a_FadeOutTicks",
						},
					},
					Returns =
					{
					},
				},
			},
			SetClientBrand =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_ClientBrand",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Called by the protocol when it receives the MC|Brand plugin message. Also callable by plugins.\
	Simply stores the string value.",
				},
			},
			SetLocale =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Locale",
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
			SetUsername =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Username",
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
			SetViewDistance =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_ViewDistance",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the maximal view distance.",
				},
			},
		},
	},
}
