return
{
	cFlowerPotEntity =
	{
		Inherits =
		{
			"cBlockEntity",
		},
		Functions =
		{
			GetItem =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Get the item in the flower pot",
				},
			},
			IsItemInPot =
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
					Desc = "Is a flower in the pot?",
				},
			},
			SetItem =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "Set the item in the flower pot",
				},
			},
		},
	},
}
