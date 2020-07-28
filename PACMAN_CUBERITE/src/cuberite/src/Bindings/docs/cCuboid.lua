return
{
	cCuboid =
	{
		Functions =
		{
			Clamp =
			{
				{
					Params =
					{
						{
							Type = "cCuboid",
							Name = "a_Limits",
						},
					},
					Returns =
					{
					},
					Desc = "Clamps this cuboid, so that it doesn't reach outside of a_Limits in any direction.\
	Assumes both this and a_Limits are sorted.",
				},
			},
			ClampSize =
			{
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_MaxSize",
						},
					},
					Returns =
					{
					},
					Desc = "Clamps this cuboid's p2 so that the cuboid's size doesn't exceed the specified max size.\
	Assumes this cuboid is sorted.",
				},
			},
			ClampX =
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
					},
					Returns =
					{
					},
					Desc = "Clamps both X coords to the specified range. Works on unsorted cuboids, too.",
				},
			},
			ClampY =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_MinY",
						},
						{
							Type = "int",
							Name = "a_MaxY",
						},
					},
					Returns =
					{
					},
					Desc = "Clamps both Y coords to the specified range. Works on unsorted cuboids, too.",
				},
			},
			ClampZ =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_MinZ",
						},
						{
							Type = "int",
							Name = "a_MaxZ",
						},
					},
					Returns =
					{
					},
					Desc = "Clamps both Z coords to the specified range. Works on unsorted cuboids, too.",
				},
			},
			DifX =
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
			DifY =
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
			DifZ =
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
			DoesIntersect =
			{
				{
					Params =
					{
						{
							Type = "cCuboid",
							Name = "a_Other",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the cuboids have at least one voxel in common. Both coords are considered inclusive.\
	Assumes both cuboids are sorted.",
				},
			},
			Engulf =
			{
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_Point",
						},
					},
					Returns =
					{
					},
					Desc = "If needed, expands the cuboid so that it contains the specified point. Assumes sorted. Doesn't contract.",
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
					Desc = "Expands the cuboid by the specified amount in each direction.\
	Works on unsorted cuboids as well.\
	Note that this function doesn't check for underflows when using negative amounts.",
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
					Desc = "Returns the volume of the cuboid, in blocks.\
	Note that the volume considers both coords inclusive.\
	Works on unsorted cuboids, too.",
				},
			},
			IsCompletelyInside =
			{
				{
					Params =
					{
						{
							Type = "cCuboid",
							Name = "a_Outer",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if this cuboid is completely inside the specified cuboid (in all 6 coords).\
	Assumes both cuboids are sorted.",
				},
			},
			IsSorted =
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
					Desc = "Returns true if the coords are properly sorted (lesser in p1, greater in p2)",
				},
			},
			Sort =
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
			new =
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
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_p1",
						},
						{
							Type = "Vector3<int>",
							Name = "a_p2",
						},
					},
					Returns =
					{
						{
							Type = "cCuboid",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_X1",
						},
						{
							Type = "int",
							Name = "a_Y1",
						},
						{
							Type = "int",
							Name = "a_Z1",
						},
					},
					Returns =
					{
						{
							Type = "cCuboid",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "cCuboid",
							Name = "a_Cuboid",
						},
					},
					Returns =
					{
						{
							Type = "cCuboid",
						},
					},
				},
			},
		},
		Variables =
		{
			p1 =
			{
				Type = "Vector3<int>",
			},
			p2 =
			{
				Type = "Vector3<int>",
			},
		},
	},
}
