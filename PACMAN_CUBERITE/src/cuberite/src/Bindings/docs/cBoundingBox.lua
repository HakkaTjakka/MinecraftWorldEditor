return
{
	cBoundingBox =
	{
		Desc = "Represents two sets of coords, minimum and maximum for each direction.\
All the coords within those limits (inclusive the edges) are considered \"inside\" the box.\
For intersection purposes, though, if the intersection is \"sharp\" in any coord (i. e. zero volume),\
the boxes are considered non-intersecting.",
		Functions =
		{
			DoesIntersect =
			{
				{
					Params =
					{
						{
							Type = "cBoundingBox",
							Name = "a_Other",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the two bounding boxes intersect",
				},
			},
			Expand =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_ExpandX",
						},
						{
							Type = "double",
							Name = "a_ExpandY",
						},
						{
							Type = "double",
							Name = "a_ExpandZ",
						},
					},
					Returns =
					{
					},
					Desc = "Expands the bounding box by the specified amount in each direction (so the box becomes larger by 2 * Expand in each direction)",
				},
			},
			GetMax =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
			},
			GetMaxX =
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
				},
			},
			GetMaxY =
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
				},
			},
			GetMaxZ =
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
				},
			},
			GetMin =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
			},
			GetMinX =
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
					Desc = "Calculates the intersection of the two bounding boxes; returns true if nonempty.\
	Exported manually, because ToLua++ would generate needless input params (a_Intersection).",
				},
			},
			GetMinY =
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
				},
			},
			GetMinZ =
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
				},
			},
			IsInside =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Point",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the point is inside the bounding box",
				},
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_X",
						},
						{
							Type = "double",
							Name = "a_Y",
						},
						{
							Type = "double",
							Name = "a_Z",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the point is inside the bounding box",
				},
				{
					Params =
					{
						{
							Type = "cBoundingBox",
							Name = "a_Other",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if a_Other is inside this bounding box",
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Min",
						},
						{
							Type = "Vector3<double>",
							Name = "a_Max",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if a boundingbox specified by a_Min and a_Max is inside this bounding box",
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Min",
						},
						{
							Type = "Vector3<double>",
							Name = "a_Max",
						},
						{
							Type = "Vector3<double>",
							Name = "a_Point",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
					Desc = "Returns true if the specified point is inside the bounding box specified by its min / max corners",
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Min",
						},
						{
							Type = "Vector3<double>",
							Name = "a_Max",
						},
						{
							Type = "double",
							Name = "a_X",
						},
						{
							Type = "double",
							Name = "a_Y",
						},
						{
							Type = "double",
							Name = "a_Z",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
					Desc = "Returns true if the specified point is inside the bounding box specified by its min / max corners",
				},
			},
			Move =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_OffX",
						},
						{
							Type = "double",
							Name = "a_OffY",
						},
						{
							Type = "double",
							Name = "a_OffZ",
						},
					},
					Returns =
					{
					},
					Desc = "Moves the entire boundingbox by the specified offset",
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Off",
						},
					},
					Returns =
					{
					},
					Desc = "Moves the entire boundingbox by the specified offset",
				},
			},
			Union =
			{
				{
					Params =
					{
						{
							Type = "cBoundingBox",
							Name = "a_Other",
						},
					},
					Returns =
					{
						{
							Type = "cBoundingBox",
						},
					},
					Desc = "Returns the union of the two bounding boxes",
				},
			},
			new =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_MinX",
						},
						{
							Type = "double",
							Name = "a_MaxX",
						},
						{
							Type = "double",
							Name = "a_MinY",
						},
						{
							Type = "double",
							Name = "a_MaxY",
						},
						{
							Type = "double",
							Name = "a_MinZ",
						},
						{
							Type = "double",
							Name = "a_MaxZ",
						},
					},
					Returns =
					{
						{
							Type = "cBoundingBox",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Min",
						},
						{
							Type = "Vector3<double>",
							Name = "a_Max",
						},
					},
					Returns =
					{
						{
							Type = "cBoundingBox",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Pos",
						},
						{
							Type = "double",
							Name = "a_Radius",
						},
						{
							Type = "double",
							Name = "a_Height",
						},
					},
					Returns =
					{
						{
							Type = "cBoundingBox",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Pos",
						},
						{
							Type = "double",
							Name = "a_Radius",
						},
						{
							Type = "double",
							Name = "a_Height",
						},
						{
							Type = "double",
							Name = "a_VerticalOffset",
						},
					},
					Returns =
					{
						{
							Type = "cBoundingBox",
						},
					},
					Desc = "Constructor that allows to define a bounding box given a center point (a_Pos), a horizontal radius (a_Radius),\
	a height starting from given center point (a_Height) and a vertical offset (a_VerticalOffset) to adjust the vertical starting point.\
	For example: cBoundingBox([0, 0, 0], 6, 6, -3) would create a bounding cube from (-3, -3, -3) to (3, 3, 3).",
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Pos",
						},
						{
							Type = "double",
							Name = "a_CubeLength",
						},
					},
					Returns =
					{
						{
							Type = "cBoundingBox",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "cBoundingBox",
							Name = "a_Orig",
						},
					},
					Returns =
					{
						{
							Type = "cBoundingBox",
						},
					},
				},
			},
		},
	},
}
