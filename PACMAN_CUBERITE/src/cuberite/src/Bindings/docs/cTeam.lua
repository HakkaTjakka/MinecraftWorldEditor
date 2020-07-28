return
{
	cTeam =
	{
		Functions =
		{
			AddPlayer =
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
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Adds a new player to the team",
				},
			},
			AllowsFriendlyFire =
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
			CanSeeFriendlyInvisible =
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
			GetDisplayName =
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
					Desc = "Returns the number of registered players",
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
							Type = "const AString",
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
							Type = "const AString",
						},
					},
				},
			},
			HasPlayer =
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
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Returns whether the specified player is in this team",
				},
			},
			RemovePlayer =
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
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Removes a player from the team",
				},
			},
			Reset =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Removes all registered players",
				},
			},
			SetCanSeeFriendlyInvisible =
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
			SetDisplayName =
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
			SetFriendlyFire =
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
			SetPrefix =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Prefix",
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
			SetSuffix =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Suffix",
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
		},
	},
}
