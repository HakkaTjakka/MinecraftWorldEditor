return
{
	cMobSpawnerEntity =
	{
		Inherits =
		{
			"cBlockEntity",
		},
		Functions =
		{
			GetEntity =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eMonsterType",
						},
					},
					Desc = "Returns the entity type that will be spawn by this mob spawner.",
				},
			},
			GetNearbyMonsterNum =
			{
				{
					Params =
					{
						{
							Type = "eMonsterType",
							Name = "a_EntityType",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns the amount of this monster type in a 8-block radius (Y: 4-block radius).",
				},
			},
			GetNearbyPlayersNum =
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
					Desc = "Returns the amount of the nearby players in a 16-block radius.",
				},
			},
			GetSpawnDelay =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "short",
						},
					},
					Desc = "Returns the spawn delay. This is the tick delay that is needed to spawn new monsters.",
				},
			},
			ResetTimer =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Sets the spawn delay to a new random value.",
				},
			},
			SetEntity =
			{
				{
					Params =
					{
						{
							Type = "eMonsterType",
							Name = "a_EntityType",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the entity type who will be spawn by this mob spawner.",
				},
			},
			SetSpawnDelay =
			{
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_Delay",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the spawn delay.",
				},
			},
			SpawnEntity =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Spawns the entity. This function automaticly change the spawn delay!",
				},
			},
			UpdateActiveState =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Upate the active flag from the mob spawner. This function will called every 5 seconds from the Tick() function.",
				},
			},
		},
	},
}
