return
{
	cProjectileEntity =
	{
		Inherits =
		{
			"cEntity",
		},
		Functions =
		{
			GetCreatorName =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Returns the name of the player that created the projectile\
	Will be empty for non-player creators",
				},
			},
			GetCreatorUniqueID =
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
					Desc = "Returns the unique ID of the entity who created this projectile\
	May return an ID <0",
				},
			},
			GetMCAClassName =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Returns the string that is used as the entity type (class name) in MCA files",
				},
			},
			GetProjectileKind =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cProjectileEntity::eKind",
						},
					},
					Desc = "Returns the kind of the projectile (fast class identification)",
				},
			},
			IsInGround =
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
					Desc = "Returns true if the projectile has hit the ground and is stuck there",
				},
			},
		},
		Enums =
		{
			eKind =
			{
				{
					Name = "pkArrow",
				},
				{
					Name = "pkEgg",
				},
				{
					Name = "pkEnderPearl",
				},
				{
					Name = "pkExpBottle",
				},
				{
					Name = "pkFireCharge",
				},
				{
					Name = "pkFirework",
				},
				{
					Name = "pkFishingFloat",
				},
				{
					Name = "pkGhastFireball",
				},
				{
					Name = "pkSnowball",
				},
				{
					Name = "pkSplashPotion",
				},
				{
					Name = "pkWitherSkull",
				},
			},
		},
	},
}
