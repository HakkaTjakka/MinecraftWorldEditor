return
{
	cTracer =
	{
		Functions =
		{
			delete =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "",
						},
					},
				},
			},
			new =
			{
				{
					Params =
					{
						{
							Type = "cWorld",
							Name = "a_World",
						},
					},
					Returns =
					{
						{
							Type = "cTracer",
						},
					},
				},
			},
		},
		Variables =
		{
			BlockHitPosition =
			{
				Type = "Vector3<float>",
				Desc = "Contains the position of the block that caused the collision",
			},
			HitNormal =
			{
				Type = "Vector3<float>",
				Desc = "Contains which face was hit",
			},
			RealHit =
			{
				Type = "Vector3<float>",
				Desc = "Contains the exact position where a collision occured. (BlockHitPosition + Offset on block)",
			},
		},
	},
}
