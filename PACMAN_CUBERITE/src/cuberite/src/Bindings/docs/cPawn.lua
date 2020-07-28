return
{
	cPawn =
	{
		Inherits =
		{
			"cEntity",
		},
		Functions =
		{
			AddEntityEffect =
			{
				{
					Params =
					{
						{
							Type = "cEntityEffect::eType",
							Name = "a_EffectType",
						},
						{
							Type = "int",
							Name = "a_EffectDurationTicks",
						},
						{
							Type = "short",
							Name = "a_EffectIntensity",
						},
						{
							Type = "double",
							Name = "a_DistanceModifier",
						},
					},
					Returns =
					{
					},
					Desc = "Applies an entity effect.\
	Checks with plugins if they allow the addition.\
	a_EffectIntensity is the level of the effect (0 = Potion I, 1 = Potion II, etc).\
	a_DistanceModifier is the scalar multiplied to the potion duration (only applies to splash potions).",
				},
			},
			ClearEntityEffects =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Removes all currently applied entity effects (used when drinking milk)",
				},
			},
			HasEntityEffect =
			{
				{
					Params =
					{
						{
							Type = "cEntityEffect::eType",
							Name = "a_EffectType",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true, if the entity effect is currently applied.",
				},
			},
			RemoveEntityEffect =
			{
				{
					Params =
					{
						{
							Type = "cEntityEffect::eType",
							Name = "a_EffectType",
						},
					},
					Returns =
					{
					},
					Desc = "Removes a currently applied entity effect.",
				},
			},
		},
	},
}
