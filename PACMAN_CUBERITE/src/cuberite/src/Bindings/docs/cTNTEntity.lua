return
{
	cTNTEntity =
	{
		Inherits =
		{
			"cEntity",
		},
		Functions =
		{
			Explode =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Explode the tnt",
				},
			},
			GetFuseTicks =
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
					Desc = "Returns the fuse ticks until the tnt will explode",
				},
			},
			SetFuseTicks =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_FuseTicks",
						},
					},
					Returns =
					{
					},
					Desc = "Set the fuse ticks until the tnt will explode",
				},
			},
		},
	},
}
