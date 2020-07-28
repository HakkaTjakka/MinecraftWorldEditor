return
{
	cScoreboard =
	{
		Functions =
		{
			AddPlayerScore =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Name",
						},
						{
							Type = "cObjective::eType",
							Name = "a_Type",
						},
						{
							Type = "int",
							Name = "a_Value",
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
			GetNumObjectives =
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
			GetNumTeams =
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
			GetObjective =
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
							Type = "cObjective",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Retrieves the objective with the specified name, nullptr if not found",
				},
			},
			GetObjectiveIn =
			{
				{
					Params =
					{
						{
							Type = "cScoreboard::eDisplaySlot",
							Name = "a_Slot",
						},
					},
					Returns =
					{
						{
							Type = "cObjective",
						},
					},
				},
			},
			GetTeam =
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
							Type = "cTeam",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Retrieves the team with the specified name, nullptr if not found",
				},
			},
			RegisterObjective =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Name",
						},
						{
							Type = "AString",
							Name = "a_DisplayName",
						},
						{
							Type = "cObjective::eType",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "cObjective",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Registers a new scoreboard objective, returns the cObjective instance, nullptr on name collision",
				},
			},
			RegisterTeam =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Name",
						},
						{
							Type = "AString",
							Name = "a_DisplayName",
						},
						{
							Type = "AString",
							Name = "a_Prefix",
						},
						{
							Type = "AString",
							Name = "a_Suffix",
						},
					},
					Returns =
					{
						{
							Type = "cTeam",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Registers a new team, returns the cTeam instance, nullptr on name collision",
				},
			},
			RemoveObjective =
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
					Desc = "Removes a registered objective, returns true if operation was successful",
				},
			},
			RemoveTeam =
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
					Desc = "Removes a registered team, returns true if operation was successful",
				},
			},
			SetDisplay =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Objective",
						},
						{
							Type = "cScoreboard::eDisplaySlot",
							Name = "a_Slot",
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
		Enums =
		{
			eDisplaySlot =
			{
				{
					Name = "dsCount",
				},
				{
					Name = "dsList",
				},
				{
					Name = "dsName",
				},
				{
					Name = "dsSidebar",
				},
			},
		},
	},
}
