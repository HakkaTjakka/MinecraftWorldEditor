return
{
	cMonster =
	{
		Inherits =
		{
			"cPawn",
		},
		Functions =
		{
			BurnsInDaylight =
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
				},
			},
			CanBeLeashed =
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
					Desc = "Returns whether the mob can be leashed.",
				},
			},
			FamilyFromType =
			{
				{
					Params =
					{
						{
							Type = "eMonsterType",
							Name = "a_MobType",
						},
					},
					Returns =
					{
						{
							Type = "cMonster::eFamily",
						},
					},
					IsStatic = true,
					Desc = "Returns the mob family based on the type",
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
				},
			},
			GetCustomName =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const AString",
						},
					},
					Desc = "Gets the custom name of the monster. If no custom name is set, the function returns an empty string.",
				},
			},
			GetLeashedTo =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cEntity",
						},
					},
					Desc = "Returns the entity to where this mob is leashed, returns nullptr if it's not leashed",
				},
			},
			GetMobFamily =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cMonster::eFamily",
						},
					},
				},
			},
			GetMobType =
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
				},
			},
			GetRelativeWalkSpeed =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			GetSpawnDelay =
			{
				{
					Params =
					{
						{
							Type = "cMonster::eFamily",
							Name = "a_MobFamily",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					IsStatic = true,
					Desc = "Returns the spawn delay (number of game ticks between spawn attempts) for the given mob family",
				},
			},
			HasCustomName =
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
					Desc = "Returns true if the monster has a custom name.",
				},
			},
			IsBaby =
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
				},
			},
			IsCustomNameAlwaysVisible =
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
					Desc = "Is the custom name of this monster always visible? If not, you only see the name when you sight the mob.",
				},
			},
			IsLeashed =
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
					Desc = "Returns whether the monster is leashed to an entity.",
				},
			},
			LeashTo =
			{
				{
					Params =
					{
						{
							Type = "cEntity",
							Name = "a_Entity",
						},
						{
							Type = "bool",
							Name = "a_ShouldBroadcast",
						},
					},
					Returns =
					{
					},
					Desc = "Leash the monster to an entity.",
				},
			},
			MobTypeToString =
			{
				{
					Params =
					{
						{
							Type = "eMonsterType",
							Name = "a_MobType",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Translates MobType enum to a string, empty string if unknown",
				},
			},
			MobTypeToVanillaName =
			{
				{
					Params =
					{
						{
							Type = "eMonsterType",
							Name = "a_MobType",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Translates MobType enum to the vanilla name of the mob, empty string if unknown.",
				},
			},
			MoveToPosition =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Position",
						},
					},
					Returns =
					{
					},
					Desc = "Engage pathfinder and tell it to calculate a path to a given position, and move the mob accordingly.",
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
				},
			},
			SetBurnsInDaylight =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_BurnsInDaylight",
						},
					},
					Returns =
					{
					},
					Desc = "Returns whether this mob is undead (skeleton, zombie, etc.)",
				},
			},
			SetCanBeLeashed =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_CanBeLeashed",
						},
					},
					Returns =
					{
					},
					Desc = "Sets whether the mob can be leashed, for extensibility in plugins",
				},
			},
			SetCustomName =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_CustomName",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Sets the custom name of the monster. You see the name over the monster.\
	If you want to disable the custom name, simply set an empty string.",
				},
			},
			SetCustomNameAlwaysVisible =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_CustomNameAlwaysVisible",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the custom name visiblity of this monster.\
	If it's false, you only see the name when you sight the mob. If it's true, you always see the custom name.",
				},
			},
			SetRelativeWalkSpeed =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_WalkSpeed",
						},
					},
					Returns =
					{
					},
				},
			},
			StringToMobType =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_MobTypeName",
						},
					},
					Returns =
					{
						{
							Type = "eMonsterType",
						},
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Translates MobType string to the enum, mtInvalidType if not recognized",
				},
			},
			Unleash =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_ShouldDropLeashPickup",
						},
					},
					Returns =
					{
					},
					Desc = "Unleash the monster. Overload for the Unleash(bool, bool) function for plugins",
				},
			},
		},
		Enums =
		{
			eFamily =
			{
				{
					Name = "mfAmbient",
				},
				{
					Name = "mfHostile",
				},
				{
					Name = "mfNoSpawn",
				},
				{
					Name = "mfPassive",
				},
				{
					Name = "mfUnhandled",
				},
				{
					Name = "mfWater",
				},
			},
		},
	},
}
