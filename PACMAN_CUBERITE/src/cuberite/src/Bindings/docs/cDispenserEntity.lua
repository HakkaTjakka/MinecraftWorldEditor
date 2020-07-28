return
{
	cDispenserEntity =
	{
		Inherits =
		{
			"cDropSpenserEntity",
		},
		Functions =
		{
			GetShootVector =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_BlockMeta",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
					IsStatic = true,
					Desc = "Returns a unit vector in the cardinal direction of where the dispenser with the specified meta would be facing.",
				},
			},
			SpawnProjectileFromDispenser =
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
							Type = "cProjectileEntity::eKind",
							Name = "a_Kind",
						},
						{
							Type = "Vector3<double>",
							Name = "a_Speed",
						},
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Spawns a projectile of the given kind in front of the dispenser with the specified speed.\
	Returns the UniqueID of the spawned projectile, or cEntity::INVALID_ID on failure.",
				},
			},
		},
	},
}
