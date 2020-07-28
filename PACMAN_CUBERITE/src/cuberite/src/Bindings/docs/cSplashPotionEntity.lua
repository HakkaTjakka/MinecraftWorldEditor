return
{
	cSplashPotionEntity =
	{
		Inherits =
		{
			"cProjectileEntity",
		},
		Functions =
		{
			GetEntityEffectType =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cEntityEffect::eType",
						},
					},
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
							Type = "const cItem",
						},
					},
				},
			},
			GetPotionColor =
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
				},
			},
			SetEntityEffectType =
			{
				{
					Params =
					{
						{
							Type = "cEntityEffect::eType",
							Name = "a_EntityEffectType",
						},
					},
					Returns =
					{
					},
				},
			},
			SetPotionColor =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_PotionColor",
						},
					},
					Returns =
					{
					},
				},
			},
		},
	},
}
