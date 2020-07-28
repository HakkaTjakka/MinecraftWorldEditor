return
{
	cPickup =
	{
		Inherits =
		{
			"cEntity",
		},
		Functions =
		{
			CanCombine =
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
					Desc = "Returns whether this pickup is allowed to combine with other similar pickups",
				},
			},
			CollectedBy =
			{
				{
					Params =
					{
						{
							Type = "cPlayer",
							Name = "a_Dest",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
			},
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
				},
			},
			GetLifetime =
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
					Desc = "Returns the number of ticks that this pickup should live for",
				},
			},
			IsCollected =
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
					Desc = "Returns true if the pickup has already been collected",
				},
			},
			IsPlayerCreated =
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
					Desc = "Returns true if created by player (i.e. vomiting), used for determining picking-up delay time",
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
			SetCanCombine =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_CanCombine",
						},
					},
					Returns =
					{
					},
					Desc = "Sets whether this pickup is allowed to combine with other similar pickups",
				},
			},
			SetLifetime =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Lifetime",
						},
					},
					Returns =
					{
					},
					Desc = "Set the number of ticks that this pickup should live for",
				},
			},
		},
	},
}
