return
{
	cExpOrb =
	{
		Inherits =
		{
			"cEntity",
		},
		Functions =
		{
			GetAge =
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
					Desc = "Returns the number of ticks that this entity has existed",
				},
			},
			GetReward =
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
					Desc = "Get the exp amount",
				},
			},
			SetAge =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Age",
						},
					},
					Returns =
					{
					},
					Desc = "Set the number of ticks that this entity has existed",
				},
			},
			SetReward =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Reward",
						},
					},
					Returns =
					{
					},
					Desc = "Set the exp amount",
				},
			},
		},
	},
}
