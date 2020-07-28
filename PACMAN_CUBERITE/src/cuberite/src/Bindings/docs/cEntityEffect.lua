return
{
	cEntityEffect =
	{
		Functions =
		{
			GetPotionColor =
			{
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					IsStatic = true,
					Desc = "Returns the potion color (used by the client for visuals), based on the potion's damage value",
				},
			},
			GetPotionEffectDuration =
			{
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					IsStatic = true,
					Desc = "Returns the effect duration, in ticks, based on the potion's damage value",
				},
			},
			GetPotionEffectIntensity =
			{
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
					},
					Returns =
					{
						{
							Type = "short",
						},
					},
					IsStatic = true,
					Desc = "Retrieves the intensity level from the potion's damage value. Returns 0 for level I potions, 1 for level II potions.",
				},
			},
			GetPotionEffectType =
			{
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
					},
					Returns =
					{
						{
							Type = "cEntityEffect::eType",
						},
					},
					IsStatic = true,
					Desc = "Translates the potion's damage value into the entity effect that the potion gives",
				},
			},
			IsPotionDrinkable =
			{
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
					Desc = "Returns true if the potion with the given damage is drinkable",
				},
			},
		},
		Enums =
		{
			eType =
			{
				{
					Name = "effAbsorption",
				},
				{
					Name = "effBlindness",
				},
				{
					Name = "effFireResistance",
				},
				{
					Name = "effHaste",
				},
				{
					Name = "effHealthBoost",
				},
				{
					Name = "effHunger",
				},
				{
					Name = "effInstantDamage",
				},
				{
					Name = "effInstantHealth",
				},
				{
					Name = "effInvisibility",
				},
				{
					Name = "effJumpBoost",
				},
				{
					Name = "effMiningFatigue",
				},
				{
					Name = "effNausea",
				},
				{
					Name = "effNightVision",
				},
				{
					Name = "effNoEffect",
				},
				{
					Name = "effPoison",
				},
				{
					Name = "effRegeneration",
				},
				{
					Name = "effResistance",
				},
				{
					Name = "effSaturation",
				},
				{
					Name = "effSlowness",
				},
				{
					Name = "effSpeed",
				},
				{
					Name = "effStrength",
				},
				{
					Name = "effWaterBreathing",
				},
				{
					Name = "effWeakness",
				},
				{
					Name = "effWither",
				},
			},
		},
	},
}
