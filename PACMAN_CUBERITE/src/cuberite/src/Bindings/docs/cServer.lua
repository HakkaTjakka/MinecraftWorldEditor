return
{
	cServer =
	{
		Functions =
		{
			DoesAllowMultiLogin =
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
					Desc = "Can login more than once with same username.\
	Returns false if it is not allowed, true otherwise.",
				},
			},
			GetDescription =
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
			GetMaxPlayers =
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
			GetNumPlayers =
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
			GetServerID =
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
					Desc = "Authenticates the specified user, called by cAuthenticator",
				},
			},
			GetShutdownMessage =
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
			IsHardcore =
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
			IsPlayerInQueue =
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
							Type = "bool",
						},
					},
					Desc = "Check if the player is queued to be transferred to a World.\
	Returns true is Player is found in queue.",
				},
			},
			SetMaxPlayers =
			{
				{
					Params =
					{
						{
							Type = "size_t",
							Name = "a_MaxPlayers",
						},
					},
					Returns =
					{
					},
				},
			},
			ShouldAuthenticate =
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
					Desc = "Returns true if authentication has been turned on in server settings.",
				},
			},
			UnregisterForgeMod =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_ModName",
						},
						{
							Type = "int",
							Name = "a_ProtocolVersionNumber",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Remove a Forge mod to the server ping list.",
				},
			},
		},
	},
}
