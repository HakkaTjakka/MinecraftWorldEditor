return
{
	cFallingBlock =
	{
		Inherits =
		{
			"cEntity",
		},
		Functions =
		{
			GetBlockMeta =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
				},
			},
			GetBlockType =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
					Desc = "Creates a new falling block. a_BlockPosition is expected in world coords",
				},
			},
		},
	},
}
