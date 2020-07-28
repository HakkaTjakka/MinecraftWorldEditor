return
{
	cCraftingGrid =
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
			ConsumeGrid =
			{
				{
					Params =
					{
						{
							Type = "cCraftingGrid",
							Name = "a_Grid",
						},
					},
					Returns =
					{
					},
					Desc = "Removes items in a_Grid from m_Items[] (used by cCraftingRecipe::ConsumeIngredients())",
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
					Desc = "Dumps the entire crafting grid using LOGD()",
				},
			},
			GetHeight =
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
			GetItem =
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
			GetWidth =
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
			SetItem =
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
			new =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Width",
						},
						{
							Type = "int",
							Name = "a_Height",
						},
					},
					Returns =
					{
						{
							Type = "cCraftingGrid",
						},
					},
				},
			},
		},
	},
}
