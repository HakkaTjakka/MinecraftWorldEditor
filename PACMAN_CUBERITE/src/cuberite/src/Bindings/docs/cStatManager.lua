return
{
	cStatManager =
	{
		Desc = "Class that manages the statistics and achievements of a single player.",
		Functions =
		{
			AddValue =
			{
				{
					Params =
					{
						{
							Type = "eStatistic",
							Name = "a_Stat",
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
					},
					Desc = "Increments the specified stat.\
	Returns the new value.",
				},
			},
			GetValue =
			{
				{
					Params =
					{
						{
							Type = "eStatistic",
							Name = "a_Stat",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Return the value of the specified stat.",
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
					Desc = "Reset everything.",
				},
			},
			SetValue =
			{
				{
					Params =
					{
						{
							Type = "eStatistic",
							Name = "a_Stat",
						},
						{
							Type = "int",
							Name = "a_Value",
						},
					},
					Returns =
					{
					},
					Desc = "Set the value of the specified stat.",
				},
			},
		},
	},
}
