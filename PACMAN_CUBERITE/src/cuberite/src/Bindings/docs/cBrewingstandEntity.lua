return
{
	cBrewingstandEntity =
	{
		Inherits =
		{
			"cBlockEntityWithItems",
		},
		Functions =
		{
			GetBrewingTimeLeft =
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
					Desc = "Returns the time until the current items finishes brewing, in ticks",
				},
			},
			GetFuelSlot =
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
					Desc = "Returns the item in the fuel slot.",
				},
			},
			GetIndgredientSlot =
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
					Desc = "Returns the item in the ingredient slot",
				},
			},
			GetLeftBottleSlot =
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
					Desc = "Returns the item in the left bottle slot",
				},
			},
			GetMiddleBottleSlot =
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
					Desc = "Returns the item in the middle bottle slot",
				},
			},
			GetRemainingFuel =
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
					Desc = "Returns the remaining fuel that is left.",
				},
			},
			GetResultItem =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_SlotNumber",
						},
					},
					Returns =
					{
						{
							Type = "const cItem",
						},
					},
					Desc = "Get the expected result item for the given slot number",
				},
			},
			GetRightBottleSlot =
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
					Desc = "Returns the item in the right bottle slot",
				},
			},
			GetTimeBrewed =
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
					Desc = "Returns the time that the current items has been brewing, in ticks",
				},
			},
			SetFuelSlot =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the item in the fuel slot",
				},
			},
			SetIngredientSlot =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the item in the ingredient slot",
				},
			},
			SetLeftBottleSlot =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the item in the left bottle slot",
				},
			},
			SetMiddleBottleSlot =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the item in the middle bottle slot",
				},
			},
			SetRightBottleSlot =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the item in the right bottle slot",
				},
			},
		},
		Enums =
		{
			unnamedEnum_1 =
			{
				{
					Name = "ContentsHeight",
				},
				{
					Name = "ContentsWidth",
				},
				{
					Name = "bsFuel",
				},
				{
					Name = "bsIngredient",
				},
				{
					Name = "bsLeftBottle",
				},
				{
					Name = "bsMiddleBottle",
				},
				{
					Name = "bsRightBottle",
				},
			},
		},
	},
}
