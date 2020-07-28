return
{
	cBlockArea =
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
					Desc = "Clears the data stored to reclaim memory",
				},
			},
			CopyFrom =
			{
				{
					Params =
					{
						{
							Type = "cBlockArea",
							Name = "a_From",
						},
					},
					Returns =
					{
					},
					Desc = "Copies the contents from the specified BlockArea into this object.",
				},
			},
			CopyTo =
			{
				{
					Params =
					{
						{
							Type = "cBlockArea",
							Name = "a_Into",
						},
					},
					Returns =
					{
					},
					Desc = "Copies this object's contents into the specified BlockArea.",
				},
			},
			CountNonAirBlocks =
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
					Desc = "Returns the count of blocks that are not air.\
	Returns 0 if blocktypes not available. Block metas are ignored (if present, air with any meta is still considered air).",
				},
			},
			CountSpecificBlocks =
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
							Type = "size_t",
						},
					},
					Desc = "Returns how many times the specified block is contained in the area.\
	The blocks' meta values are ignored, only the blocktype is compared.",
				},
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
						{
							Type = "size_t",
						},
					},
					Desc = "Returns how many times the specified block is contained in the area.\
	Both the block's type and meta must match in order to be counted in.\
	If the block metas aren't present in the area, logs a warning and ignores the meta specification.",
				},
			},
			Crop =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_AddMinX",
						},
						{
							Type = "int",
							Name = "a_SubMaxX",
						},
						{
							Type = "int",
							Name = "a_AddMinY",
						},
						{
							Type = "int",
							Name = "a_SubMaxY",
						},
						{
							Type = "int",
							Name = "a_AddMinZ",
						},
						{
							Type = "int",
							Name = "a_SubMaxZ",
						},
					},
					Returns =
					{
					},
					Desc = "Crops the internal contents by the specified amount of blocks from each border.",
				},
			},
			DumpToRawFile =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_FileName",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "For testing purposes only, dumps the area into a file.",
				},
			},
			Expand =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_SubMinX",
						},
						{
							Type = "int",
							Name = "a_AddMaxX",
						},
						{
							Type = "int",
							Name = "a_SubMinY",
						},
						{
							Type = "int",
							Name = "a_AddMaxY",
						},
						{
							Type = "int",
							Name = "a_SubMinZ",
						},
						{
							Type = "int",
							Name = "a_AddMaxZ",
						},
					},
					Returns =
					{
					},
					Desc = "Expands the internal contents by the specified amount of blocks from each border",
				},
			},
			Fill =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_DataTypes",
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
							Type = "char",
							Name = "a_BlockLight",
						},
						{
							Type = "char",
							Name = "a_BlockSkyLight",
						},
					},
					Returns =
					{
					},
					Desc = "Fills the entire block area with the specified data",
				},
			},
			GetBounds =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cCuboid",
						},
					},
				},
			},
			GetDataTypes =
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
					Desc = "Returns the datatypes that are stored in the object (bitmask of baXXX values)",
				},
			},
			GetOriginX =
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
			GetOriginY =
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
			GetOriginZ =
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
			GetSizeX =
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
			GetSizeY =
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
			GetSizeZ =
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
			GetVolume =
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
					Desc = "Returns the volume of the area, as number of blocks",
				},
			},
			GetWEOffset =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const Vector3<int>",
						},
					},
				},
			},
			HasBlockEntities =
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
			HasBlockLights =
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
			HasBlockMetas =
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
			HasBlockSkyLights =
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
			HasBlockTypes =
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
			IsValidCoords =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_BlockX",
						},
						{
							Type = "int",
							Name = "a_BlockY",
						},
						{
							Type = "int",
							Name = "a_BlockZ",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the specified coords are within this area's coord range (as indicated by m_Origin).",
				},
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_Coords",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the specified coords are within this area's coord range (as indicated by m_Origin).",
				},
			},
			IsValidDataTypeCombination =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_DataTypes",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
					Desc = "Returns true if the datatype combination is valid.\
	Invalid combinations include BlockEntities without BlockTypes.",
				},
			},
			IsValidRelCoords =
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
							Type = "bool",
						},
					},
					Desc = "Returns true if the specified relative coords are within this area's coord range (0 - m_Size).",
				},
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_RelCoords",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the specified relative coords are within this area's coord range (0 - m_Size).",
				},
			},
			Merge =
			{
				{
					Params =
					{
						{
							Type = "cBlockArea",
							Name = "a_Src",
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
							Name = "a_Strategy",
						},
					},
					Returns =
					{
					},
					Desc = "Merges another block area into this one, using the specified block combinating strategy\
	This function combines another BlockArea into the current object.\
	The a_RelX, a_RelY and a_RelZ parameters specify the coords of this BA where a_Src should be copied.\
	If both areas contain baBlockEntities, the BEs are merged (with preference of keeping this' ones) (MergeBlockEntities()).\
	If only this contains BEs, but a_Src doesn't, the BEs are checked after merge to remove the overwritten ones and create\
	the missing ones (UpdateBlockEntities()).\
	The strategy parameter specifies how individual blocks are combined together, using the table below.\
\
	| area block |                 result              |\
	| this | Src | msOverwrite | msFillAir | msImprint |\
	+------+-----+-------------+-----------+-----------+\
	| air  | air | air         | air       | air       |\
	| A    | air | air         | A         | A         |\
	| air  | B   | B           | B         | B         |\
	| A    | B   | B           | A         | B         |\
\
	So to sum up:\
	- msOverwrite completely overwrites all blocks with the Src's blocks\
	- msFillAir overwrites only those blocks that were air\
	- msImprint overwrites with only those blocks that are non-air\
\
	Special strategies (evaluate top-down, first match wins):\
	msLake:\
	|    area block     |        |\
	|   this   | Src    | result |\
	+----------+--------+--------+\
	| A        | sponge | A      |  Sponge is the NOP block\
	| *        | air    | air    |  Air always gets hollowed out, even under the oceans\
	| water    | *      | water  |  Water is never overwritten\
	| lava     | *      | lava   |  Lava is never overwritten\
	| *        | water  | water  |  Water always overwrites anything\
	| *        | lava   | lava   |  Lava always overwrites anything\
	| dirt     | stone  | stone  |  Stone overwrites dirt\
	| grass    | stone  | stone  |    ... and grass\
	| mycelium | stone  | stone  |    ... and mycelium\
	| A        | stone  | A      |    ... but nothing else\
	| A        | *      | A      |  Everything else is left as it is\
\
	msSpongePrint:\
	Used for most generators, it allows carving out air pockets, too, and uses the Sponge as the NOP block\
	|    area block     |        |\
	|   this   | Src    | result |\
	+----------+--------+--------+\
	| A        | sponge | A      |  Sponge is the NOP block\
	| *        | B      | B      |  Everything else overwrites anything\
\
	msDifference:\
	Used to determine the differences between two areas. Only the differring blocks are preserved:\
	|  area block  |        |\
	| this | Src   | result |\
	+------+-------+--------+\
	| A    | A     | air    |  Same blocks are replaced with air\
	| A    | non-A | A      |  Differring blocks are kept from \"this\"\
\
	msSimpleCompare:\
	Used to determine the differences between two areas. Blocks that differ are replaced with stone, same blocks are replaced with air\
	|  area block  |        |\
	| this | Src   | result |\
	+------+-------+--------+\
	| A    | A     | air    |  Same blocks are replaced with air\
	| A    | non-A | stone  |  Differring blocks are replaced with stone\
\
	msMask:\
	Combines two areas, the blocks that are the same are kept, differing ones are reset to air\
	|  area block  |        |\
	| this | Src   | result |\
	+------+-------+--------+\
	| A    | A     | A      |  Same blocks are kept\
	| A    | non-A | air    |  Everything else is replaced with air",
				},
				{
					Params =
					{
						{
							Type = "cBlockArea",
							Name = "a_Src",
						},
						{
							Type = "Vector3<int>",
							Name = "a_RelMinCoords",
						},
						{
							Type = "cBlockArea::eMergeStrategy",
							Name = "a_Strategy",
						},
					},
					Returns =
					{
					},
					Desc = "Merges another block area into this one, using the specified block combinating strategy.\
	See Merge() above for details.",
				},
			},
			MirrorXY =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Mirrors the entire area around the XY plane",
				},
			},
			MirrorXYNoMeta =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Mirrors the entire area around the XY plane, doesn't use blockhandlers for block meta",
				},
			},
			MirrorXZ =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Mirrors the entire area around the XZ plane",
				},
			},
			MirrorXZNoMeta =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Mirrors the entire area around the XZ plane, doesn't use blockhandlers for block meta",
				},
			},
			MirrorYZ =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Mirrors the entire area around the YZ plane",
				},
			},
			MirrorYZNoMeta =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Mirrors the entire area around the YZ plane, doesn't use blockhandlers for block meta",
				},
			},
			RotateCCW =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Rotates the entire area counter-clockwise around the Y axis",
				},
			},
			RotateCCWNoMeta =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Rotates the entire area counter-clockwise around the Y axis, doesn't use blockhandlers for block meta",
				},
			},
			RotateCW =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Rotates the entire area clockwise around the Y axis",
				},
			},
			RotateCWNoMeta =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Rotates the entire area clockwise around the Y axis, doesn't use blockhandlers for block meta",
				},
			},
			SetOrigin =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_OriginX",
						},
						{
							Type = "int",
							Name = "a_OriginY",
						},
						{
							Type = "int",
							Name = "a_OriginZ",
						},
					},
					Returns =
					{
					},
					Desc = "Resets the origin. No other changes are made, contents are untouched.",
				},
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_Origin",
						},
					},
					Returns =
					{
					},
					Desc = "Resets the origin. No other changes are made, contents are untouched.",
				},
			},
			SetWEOffset =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_OffsetX",
						},
						{
							Type = "int",
							Name = "a_OffsetY",
						},
						{
							Type = "int",
							Name = "a_OffsetZ",
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
							Type = "Vector3<int>",
							Name = "a_Offset",
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
					},
					Returns =
					{
						{
							Type = "cBlockArea",
						},
					},
				},
			},
		},
		Enums =
		{
			unnamedEnum_1 =
			{
				{
					Name = "baBlockEntities",
				},
				{
					Name = "baLight",
				},
				{
					Name = "baMetas",
				},
				{
					Name = "baSkyLight",
				},
				{
					Name = "baTypes",
				},
			},
			eMergeStrategy =
			{
				{
					Name = "msDifference",
				},
				{
					Name = "msFillAir",
				},
				{
					Name = "msImprint",
				},
				{
					Name = "msLake",
				},
				{
					Name = "msMask",
				},
				{
					Name = "msOverwrite",
				},
				{
					Name = "msSimpleCompare",
				},
				{
					Name = "msSpongePrint",
				},
			},
		},
	},
}
