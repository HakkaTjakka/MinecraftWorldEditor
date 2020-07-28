return
{
	cBlockInfo =
	{
		Desc = "Returns true if a_BlockType is equal to any of the variadic template arguments.\
Some example usage:\
\\code\
	IsOneOf<>(E_BLOCK_AIR)                           == false\
	IsOneOf<E_BLOCK_AIR>(E_BLOCK_DIRT)               == false\
	IsOneOf<E_BLOCK_AIR, E_BLOCK_DIRT>(E_BLOCK_DIRT) == true\
\\endcode\
The implementation is ugly but it is equivalent to this C++17 fold expression:\
\\code\
	((a_BlockType == Types) || ...)\
\\endcode\
Just written to be valid without fold expressions or SFINAE.",
		Functions =
		{
			CanBeTerraformed =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
			FullyOccupiesVoxel =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
			GetBlockHeight =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "float",
						},
					},
					IsStatic = true,
				},
			},
			GetHardness =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "float",
						},
					},
					IsStatic = true,
				},
			},
			GetLightValue =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
					IsStatic = true,
					Desc = "Returns the associated BlockInfo structure for the specified block type.\
	This accessor makes sure that the cBlockInfo structures are properly initialized exactly once.\
	It does so by using the C++ singleton approximation - storing the actual singleton as the function's static variable.",
				},
			},
			GetSpreadLightFalloff =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
					IsStatic = true,
				},
			},
			IsOneHitDig =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
			IsPistonBreakable =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
			IsRainBlocker =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
			IsSkylightDispersant =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
			IsSnowable =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
			IsSolid =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
			IsTransparent =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
			IsUseableBySpectator =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Type",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
				},
			},
		},
	},
}
