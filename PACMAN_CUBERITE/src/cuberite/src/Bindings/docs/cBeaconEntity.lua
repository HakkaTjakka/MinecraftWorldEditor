return
{
	cBeaconEntity =
	{
		Inherits =
		{
			"cBlockEntityWithItems",
		},
		Functions =
		{
			CalculatePyramidLevel =
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
					Desc = "Calculate the amount of layers the pyramid below the beacon has.",
				},
			},
			GetBeaconLevel =
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
					Desc = "Returns the beacon level. (0 - 4)",
				},
			},
			GetPrimaryEffect =
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
			GetSecondaryEffect =
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
			GiveEffects =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Give the near-players the effects.",
				},
			},
			IsActive =
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
					Desc = "Is the beacon active?",
				},
			},
			IsBeaconBlocked =
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
					Desc = "Is the beacon blocked by non-transparent blocks that are higher than the beacon?",
				},
			},
			IsMineralBlock =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_BlockType",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
					Desc = "Returns true if the block is a diamond block, a golden block, an iron block or an emerald block.",
				},
			},
			IsValidEffect =
			{
				{
					Params =
					{
						{
							Type = "cEntityEffect::eType",
							Name = "a_Effect",
						},
						{
							Type = "char",
							Name = "a_BeaconLevel",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
					Desc = "Returns true if the effect can be used.",
				},
			},
			SetPrimaryEffect =
			{
				{
					Params =
					{
						{
							Type = "cEntityEffect::eType",
							Name = "a_Effect",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Sets the primary effect. Returns false when the effect is invalid.",
				},
			},
			SetSecondaryEffect =
			{
				{
					Params =
					{
						{
							Type = "cEntityEffect::eType",
							Name = "a_Effect",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Sets the secondary effect. Returns false when the effect is invalid.",
				},
			},
			UpdateBeacon =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Update the beacon.",
				},
			},
		},
	},
}
