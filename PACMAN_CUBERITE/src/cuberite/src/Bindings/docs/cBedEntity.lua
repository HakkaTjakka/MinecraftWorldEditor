return
{
	cBedEntity =
	{
		Inherits =
		{
			"cBlockEntity",
		},
		Functions =
		{
			GetColor =
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
					Desc = "Returns the color of the bed",
				},
			},
			IsPillowBlock =
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
					Desc = "Returns true if this is the pillow block, it has then the meta 8.",
				},
			},
			SetColor =
			{
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_Color",
						},
					},
					Returns =
					{
					},
					Desc = "Set the color of the bed.",
				},
			},
		},
	},
}
