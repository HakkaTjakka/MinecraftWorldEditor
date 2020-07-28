return
{
	cItems =
	{
		Desc = "This class bridges a vector of cItem for safe access via Lua. It checks boundaries for all accesses\
Note that this class is zero-indexed!",
		Functions =
		{
			Add =
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
				},
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemType",
						},
						{
							Type = "char",
							Name = "a_ItemCount",
						},
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
					},
					Returns =
					{
					},
				},
			},
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
			Contains =
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
						{
							Type = "bool",
						},
					},
				},
			},
			ContainsType =
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
						{
							Type = "bool",
						},
					},
				},
			},
			Delete =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Idx",
						},
					},
					Returns =
					{
					},
				},
			},
			Get =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Idx",
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
			Set =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Idx",
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
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Idx",
						},
						{
							Type = "short",
							Name = "a_ItemType",
						},
						{
							Type = "char",
							Name = "a_ItemCount",
						},
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
					},
					Returns =
					{
					},
				},
			},
			Size =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "size_t",
						},
					},
				},
			},
			new =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItems",
						},
					},
					Desc = "Need a Lua-accessible constructor",
				},
			},
		},
	},
}
