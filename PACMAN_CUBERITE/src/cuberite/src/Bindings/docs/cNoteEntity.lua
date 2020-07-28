return
{
	cNoteEntity =
	{
		Inherits =
		{
			"cBlockEntity",
		},
		Functions =
		{
			GetPitch =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
					Desc = "Creates a new note entity. a_World may be nullptr",
				},
			},
			IncrementPitch =
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
			MakeSound =
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
			SetPitch =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Pitch",
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
