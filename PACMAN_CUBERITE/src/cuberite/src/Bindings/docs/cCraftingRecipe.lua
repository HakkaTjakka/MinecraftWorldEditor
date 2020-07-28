return
{
	cCraftingRecipe =
	{
		Functions =
		{
			Clear =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
				},
			},
			ConsumeIngredients =
			{
				{
					Params =
					{
						{
							Type = "cCraftingGrid",
							Name = "a_CraftingGrid",
						},
					},
					Returns =
					{
					},
					Desc = "Consumes ingredients from the crafting grid specified",
				},
			},
			Dump =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Dumps the entire recipe using LOGD()",
				},
			},
			GetIngredient =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "x",
						},
						{
							Type = "int",
							Name = "y",
						},
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
				},
			},
			GetIngredientsHeight =
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
			GetIngredientsWidth =
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
			GetResult =
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
				},
			},
			SetIngredient =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "x",
						},
						{
							Type = "int",
							Name = "y",
						},
						{
							Type = "ENUM_ITEM_ID",
							Name = "a_ItemType",
						},
						{
							Type = "char",
							Name = "a_ItemCount",
						},
						{
							Type = "short",
							Name = "a_ItemHealth",
						},
					},
					Returns =
					{
					},
				},
				{
					Params =
					{
						{
							Type = "int",
							Name = "x",
						},
						{
							Type = "int",
							Name = "y",
						},
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
				},
			},
			SetResult =
			{
				{
					Params =
					{
						{
							Type = "ENUM_ITEM_ID",
							Name = "a_ItemType",
						},
						{
							Type = "char",
							Name = "a_ItemCount",
						},
						{
							Type = "short",
							Name = "a_ItemHealth",
						},
					},
					Returns =
					{
					},
				},
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
				},
			},
		},
	},
}
