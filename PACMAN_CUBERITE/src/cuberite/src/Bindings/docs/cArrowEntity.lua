return
{
	cArrowEntity =
	{
		Inherits =
		{
			"cProjectileEntity",
		},
		Functions =
		{
			CanPickup =
			{
				{
					Params =
					{
						{
							Type = "cPlayer",
							Name = "a_Player",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the specified player can pick the arrow up",
				},
			},
			GetBlockHit =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "Vector3<int>",
						},
					},
					Desc = "Gets the block arrow is in",
				},
			},
			GetDamageCoeff =
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
					Desc = "Returns the damage modifier coeff.",
				},
			},
			GetPickupState =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cArrowEntity::ePickupState",
						},
					},
					Desc = "Returns whether the arrow can be picked up by players",
				},
			},
			IsCritical =
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
					Desc = "Returns true if the arrow is set as critical",
				},
			},
			SetDamageCoeff =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_DamageCoeff",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the damage modifier coeff",
				},
			},
			SetIsCritical =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_IsCritical",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the IsCritical flag",
				},
			},
			SetPickupState =
			{
				{
					Params =
					{
						{
							Type = "cArrowEntity::ePickupState",
							Name = "a_PickupState",
						},
					},
					Returns =
					{
					},
					Desc = "Sets a new pickup state",
				},
			},
		},
		Enums =
		{
			ePickupState =
			{
				{
					Name = "psInCreative",
				},
				{
					Name = "psInSurvivalOrCreative",
				},
				{
					Name = "psNoPickup",
				},
			},
		},
	},
}
