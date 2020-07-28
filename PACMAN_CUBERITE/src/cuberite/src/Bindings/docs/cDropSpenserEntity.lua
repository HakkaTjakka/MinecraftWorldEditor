return
{
	cDropSpenserEntity =
	{
		Inherits =
		{
			"cBlockEntityWithItems",
		},
		Functions =
		{
			Activate =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Sets the dropspenser to dropspense an item in the next tick",
				},
			},
			AddDropSpenserDir =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_BlockX",
						},
						{
							Type = "int",
							Name = "a_BlockY",
						},
						{
							Type = "int",
							Name = "a_BlockZ",
						},
						{
							Type = "char",
							Name = "a_Direction",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
						{
							Type = "int",
						},
						{
							Type = "int",
						},
					},
					Desc = "Modifies the block coords to match the dropspenser direction given (where the dropspensed pickups should materialize)",
				},
			},
		},
		Enums =
		{
			unnamedEnum_1 =
			{
				{
					Name = "ContentsHeight",
				},
				{
					Name = "ContentsWidth",
				},
			},
		},
	},
}
