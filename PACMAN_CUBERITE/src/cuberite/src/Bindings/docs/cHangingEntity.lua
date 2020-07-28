return
{
	cHangingEntity =
	{
		Inherits =
		{
			"cEntity",
		},
		Functions =
		{
			GetFacing =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eBlockFace",
						},
					},
					Desc = "Returns the direction in which the entity is facing.",
				},
			},
			SetFacing =
			{
				{
					Params =
					{
						{
							Type = "eBlockFace",
							Name = "a_Facing",
						},
					},
					Returns =
					{
					},
					Desc = "Set the direction in which the entity is facing.",
				},
			},
		},
	},
}
