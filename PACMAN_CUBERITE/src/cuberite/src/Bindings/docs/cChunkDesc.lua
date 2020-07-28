return
{
	cChunkDesc =
	{
		Functions =
		{
			FillBlocks =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_BlockType",
						},
						{
							Type = "char",
							Name = "a_BlockMeta",
						},
					},
					Returns =
					{
					},
				},
			},
			FillRelCuboid =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_MinX",
						},
						{
							Type = "int",
							Name = "a_MaxX",
						},
						{
							Type = "int",
							Name = "a_MinY",
						},
						{
							Type = "int",
							Name = "a_MaxY",
						},
						{
							Type = "int",
							Name = "a_MinZ",
						},
						{
							Type = "int",
							Name = "a_MaxZ",
						},
						{
							Type = "char",
							Name = "a_BlockType",
						},
						{
							Type = "char",
							Name = "a_BlockMeta",
						},
					},
					Returns =
					{
					},
					Desc = "Fills the relative cuboid with specified block; allows cuboid out of range of this chunk",
				},
				{
					Params =
					{
						{
							Type = "cCuboid",
							Name = "a_RelCuboid",
						},
						{
							Type = "char",
							Name = "a_BlockType",
						},
						{
							Type = "char",
							Name = "a_BlockMeta",
						},
					},
					Returns =
					{
					},
					Desc = "Fills the relative cuboid with specified block; allows cuboid out of range of this chunk",
				},
			},
			FloorRelCuboid =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_MinX",
						},
						{
							Type = "int",
							Name = "a_MaxX",
						},
						{
							Type = "int",
							Name = "a_MinY",
						},
						{
							Type = "int",
							Name = "a_MaxY",
						},
						{
							Type = "int",
							Name = "a_MinZ",
						},
						{
							Type = "int",
							Name = "a_MaxZ",
						},
						{
							Type = "char",
							Name = "a_DstType",
						},
						{
							Type = "char",
							Name = "a_DstMeta",
						},
					},
					Returns =
					{
					},
					Desc = "Replaces the blocks in the cuboid by the dst blocks if they are considered non-floor (air, water); allows cuboid out of range of this chunk",
				},
				{
					Params =
					{
						{
							Type = "cCuboid",
							Name = "a_RelCuboid",
						},
						{
							Type = "char",
							Name = "a_DstType",
						},
						{
							Type = "char",
							Name = "a_DstMeta",
						},
					},
					Returns =
					{
					},
					Desc = "Replaces the blocks in the cuboid by the dst blocks if they are considered non-floor (air, water); allows cuboid out of range of this chunk",
				},
			},
			GetBiome =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
					},
					Returns =
					{
						{
							Type = "EMCSBiome",
						},
					},
				},
			},
			GetBlockEntity =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelY",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
					},
					Returns =
					{
						{
							Type = "cBlockEntity",
						},
					},
					Desc = "Returns the block entity at the specified coords.\
	If there is no block entity at those coords, tries to create one, based on the block type\
	If the blocktype doesn't support a block entity, returns nullptr.",
				},
			},
			GetBlockMeta =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelY",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
				},
			},
			GetBlockType =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelY",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
				},
			},
			GetChunkX =
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
					Desc = "Uncompressed block metas, 1 meta per byte",
				},
			},
			GetChunkZ =
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
			GetHeight =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
					},
					Returns =
					{
						{
							Type = "char",
						},
					},
				},
			},
			GetMaxHeight =
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
					Desc = "Returns the maximum height value in the heightmap.",
				},
			},
			GetMinHeight =
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
					Desc = "Returns the minimum height value in the heightmap.",
				},
			},
			IsUsingDefaultBiomes =
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
				},
			},
			IsUsingDefaultComposition =
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
				},
			},
			IsUsingDefaultFinish =
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
				},
			},
			IsUsingDefaultHeight =
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
				},
			},
			RandomFillRelCuboid =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_MinX",
						},
						{
							Type = "int",
							Name = "a_MaxX",
						},
						{
							Type = "int",
							Name = "a_MinY",
						},
						{
							Type = "int",
							Name = "a_MaxY",
						},
						{
							Type = "int",
							Name = "a_MinZ",
						},
						{
							Type = "int",
							Name = "a_MaxZ",
						},
						{
							Type = "char",
							Name = "a_BlockType",
						},
						{
							Type = "char",
							Name = "a_BlockMeta",
						},
						{
							Type = "int",
							Name = "a_RandomSeed",
						},
						{
							Type = "int",
							Name = "a_ChanceOutOf10k",
						},
					},
					Returns =
					{
					},
					Desc = "Fills the relative cuboid with specified block with a random chance; allows cuboid out of range of this chunk",
				},
				{
					Params =
					{
						{
							Type = "cCuboid",
							Name = "a_RelCuboid",
						},
						{
							Type = "char",
							Name = "a_BlockType",
						},
						{
							Type = "char",
							Name = "a_BlockMeta",
						},
						{
							Type = "int",
							Name = "a_RandomSeed",
						},
						{
							Type = "int",
							Name = "a_ChanceOutOf10k",
						},
					},
					Returns =
					{
					},
					Desc = "Fills the relative cuboid with specified block with a random chance; allows cuboid out of range of this chunk",
				},
			},
			ReadBlockArea =
			{
				{
					Params =
					{
						{
							Type = "cBlockArea",
							Name = "a_Dest",
						},
						{
							Type = "int",
							Name = "a_MinRelX",
						},
						{
							Type = "int",
							Name = "a_MaxRelX",
						},
						{
							Type = "int",
							Name = "a_MinRelY",
						},
						{
							Type = "int",
							Name = "a_MaxRelY",
						},
						{
							Type = "int",
							Name = "a_MinRelZ",
						},
						{
							Type = "int",
							Name = "a_MaxRelZ",
						},
					},
					Returns =
					{
					},
					Desc = "Reads an area from the chunk into a cBlockArea, blocktypes and blockmetas",
				},
			},
			ReplaceRelCuboid =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_MinX",
						},
						{
							Type = "int",
							Name = "a_MaxX",
						},
						{
							Type = "int",
							Name = "a_MinY",
						},
						{
							Type = "int",
							Name = "a_MaxY",
						},
						{
							Type = "int",
							Name = "a_MinZ",
						},
						{
							Type = "int",
							Name = "a_MaxZ",
						},
						{
							Type = "char",
							Name = "a_SrcType",
						},
						{
							Type = "char",
							Name = "a_SrcMeta",
						},
						{
							Type = "char",
							Name = "a_DstType",
						},
						{
							Type = "char",
							Name = "a_DstMeta",
						},
					},
					Returns =
					{
					},
					Desc = "Replaces the specified src blocks in the cuboid by the dst blocks; allows cuboid out of range of this chunk",
				},
				{
					Params =
					{
						{
							Type = "cCuboid",
							Name = "a_RelCuboid",
						},
						{
							Type = "char",
							Name = "a_SrcType",
						},
						{
							Type = "char",
							Name = "a_SrcMeta",
						},
						{
							Type = "char",
							Name = "a_DstType",
						},
						{
							Type = "char",
							Name = "a_DstMeta",
						},
					},
					Returns =
					{
					},
					Desc = "Replaces the specified src blocks in the cuboid by the dst blocks; allows cuboid out of range of this chunk",
				},
			},
			SetBiome =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
						{
							Type = "EMCSBiome",
							Name = "a_BiomeID",
						},
					},
					Returns =
					{
					},
				},
			},
			SetBlockMeta =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelY",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
						{
							Type = "char",
							Name = "a_BlockMeta",
						},
					},
					Returns =
					{
					},
				},
			},
			SetBlockType =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelY",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
						{
							Type = "char",
							Name = "a_BlockType",
						},
					},
					Returns =
					{
					},
					Desc = "Returns the BlockType and BlockMeta at the specified coords.\
	Exported to Lua manually to avoid extra parameters generated by ToLua++.",
				},
			},
			SetBlockTypeMeta =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelY",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
						{
							Type = "char",
							Name = "a_BlockType",
						},
						{
							Type = "char",
							Name = "a_BlockMeta",
						},
					},
					Returns =
					{
					},
				},
			},
			SetHeight =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
						{
							Type = "char",
							Name = "a_Height",
						},
					},
					Returns =
					{
					},
				},
			},
			SetUseDefaultBiomes =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_bUseDefaultBiomes",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the shape in a_Shape to match the heightmap stored currently in m_HeightMap.",
				},
			},
			SetUseDefaultComposition =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_bUseDefaultComposition",
						},
					},
					Returns =
					{
					},
				},
			},
			SetUseDefaultFinish =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_bUseDefaultFinish",
						},
					},
					Returns =
					{
					},
				},
			},
			SetUseDefaultHeight =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_bUseDefaultHeight",
						},
					},
					Returns =
					{
					},
				},
			},
			UpdateHeightmap =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Updates the heightmap to match the current contents.\
	Useful for plugins when writing custom block areas into the chunk",
				},
			},
			WriteBlockArea =
			{
				{
					Params =
					{
						{
							Type = "cBlockArea",
							Name = "a_BlockArea",
						},
						{
							Type = "int",
							Name = "a_RelX",
						},
						{
							Type = "int",
							Name = "a_RelY",
						},
						{
							Type = "int",
							Name = "a_RelZ",
						},
						{
							Type = "cBlockArea::eMergeStrategy",
							Name = "a_MergeStrategy",
						},
					},
					Returns =
					{
					},
					Desc = "Writes the block area into the chunk, with its origin set at the specified relative coords. Area's data overwrite everything in the chunk.",
				},
			},
		},
	},
}
