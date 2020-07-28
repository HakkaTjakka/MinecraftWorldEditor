return
{
	cJukeboxEntity =
	{
		Inherits =
		{
			"cBlockEntity",
		},
		Functions =
		{
			EjectRecord =
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
					Desc = "Ejects the currently held record as a pickup. Return false when no record had been inserted.",
				},
			},
			GetRecord =
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
			IsPlayingRecord =
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
					Desc = "Is in the Jukebox a Record?",
				},
			},
			IsRecordItem =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Item",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
			PlayRecord =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Record",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Plays the specified Record. Return false if a_Record isn't a playable Record (E_ITEM_XXX_DISC).\
	If there is a record already playing, ejects it first.",
				},
			},
			SetRecord =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Record",
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
