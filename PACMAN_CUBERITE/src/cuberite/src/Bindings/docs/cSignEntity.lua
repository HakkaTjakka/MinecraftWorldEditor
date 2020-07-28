return
{
	cSignEntity =
	{
		Inherits =
		{
			"cBlockEntity",
		},
		Functions =
		{
			GetLine =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Index",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Retrieves individual line (zero-based index)",
				},
			},
			SetLine =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Index",
						},
						{
							Type = "AString",
							Name = "a_Line",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Sets individual line (zero-based index)",
				},
			},
			SetLines =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Line1",
						},
						{
							Type = "AString",
							Name = "a_Line2",
						},
						{
							Type = "AString",
							Name = "a_Line3",
						},
						{
							Type = "AString",
							Name = "a_Line4",
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
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Sets all the sign's lines",
				},
			},
		},
	},
}
