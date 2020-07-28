return
{
	cFurnaceEntity =
	{
		Inherits =
		{
			"cBlockEntityWithItems",
		},
		Functions =
		{
			GetAndResetReward =
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
					Desc = "Calculates, resets, and returns the experience reward in this furnace",
				},
			},
			GetCookTimeLeft =
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
					Desc = "Returns the time until the current item finishes cooking, in ticks",
				},
			},
			GetFuelBurnTimeLeft =
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
					Desc = "Returns the time until the current fuel is depleted, in ticks",
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
					Desc = "Returns the item in the fuel slot",
				},
			},
			GetInputSlot =
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
					Desc = "Returns the item in the input slot",
				},
			},
			GetOutputSlot =
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
					Desc = "Returns the item in the output slot",
				},
			},
			GetTimeCooked =
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
					Desc = "Returns the time that the current item has been cooking, in ticks",
				},
			},
			HasFuelTimeLeft =
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
					Desc = "Returns true if there's time left before the current fuel is depleted",
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
			SetInputSlot =
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
					Desc = "Sets the item in the input slot",
				},
			},
			SetOutputSlot =
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
					Desc = "Sets the item in the output slot",
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
					Name = "fsFuel",
				},
				{
					Name = "fsInput",
				},
				{
					Name = "fsOutput",
				},
			},
		},
	},
}
