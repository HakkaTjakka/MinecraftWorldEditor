return
{
	cFireworkEntity =
	{
		Inherits =
		{
			"cProjectileEntity",
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
							Type = "const cItem",
						},
					},
					Desc = "Returns the item used to create the rocket (has all the firework effects on it)",
				},
			},
			GetTicksToExplosion =
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
					Desc = "Returns the number of ticks left until the firework explosion.",
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
					Desc = "Sets the item that is used to create the rocket (has all the firework effects on it)",
				},
			},
			SetTicksToExplosion =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_TicksToExplosion",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the number of ticks left until the firework explosion.",
				},
			},
		},
	},
}
