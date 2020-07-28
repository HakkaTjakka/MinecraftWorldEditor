return
{
	cObjective =
	{
		Functions =
		{
			AddScore =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Name",
						},
						{
							Type = "int",
							Name = "a_Delta",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Adds a_Delta and returns the new score",
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
			GetScore =
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
							Type = "int",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Returns the score of the specified player",
				},
			},
			GetType =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cObjective::eType",
						},
					},
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
					Desc = "Resets the objective",
				},
			},
			ResetScore =
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
					Desc = "Resets the score of the specified player",
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
			SetScore =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Name",
						},
						{
							Type = "int",
							Name = "a_Score",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Sets the score of the specified player",
				},
			},
			SubScore =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Name",
						},
						{
							Type = "int",
							Name = "a_Delta",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Subtracts a_Delta and returns the new score",
				},
			},
		},
		Enums =
		{
			eType =
			{
				{
					Name = "otAchievement",
				},
				{
					Name = "otDeathCount",
				},
				{
					Name = "otDummy",
				},
				{
					Name = "otHealth",
				},
				{
					Name = "otPlayerKillCount",
				},
				{
					Name = "otStat",
				},
				{
					Name = "otStatBlockMine",
				},
				{
					Name = "otStatEntityKill",
				},
				{
					Name = "otStatEntityKilledBy",
				},
				{
					Name = "otStatItemBreak",
				},
				{
					Name = "otStatItemCraft",
				},
				{
					Name = "otStatItemUse",
				},
				{
					Name = "otTotalKillCount",
				},
			},
		},
	},
}
