return
{
	Vector3d =
	{
		Functions =
		{
			[".add"] =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
			},
			[".div"] =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_v",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
			},
			[".mul"] =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_v",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
			},
			[".sub"] =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
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
			Abs =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Updates each coord to its absolute value",
				},
			},
			Clamp =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_Min",
						},
						{
							Type = "double",
							Name = "a_Max",
						},
					},
					Returns =
					{
					},
					Desc = "Clamps each coord into the specified range.",
				},
			},
			Cross =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
			},
			Dot =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
				},
			},
			Equals =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Rhs",
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
			EqualsEps =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Rhs",
						},
						{
							Type = "double",
							Name = "a_Eps",
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
			Floor =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "Vector3<int>",
						},
					},
					Desc = "Returns a new Vector3i with coords set to std::floor() of this vector's coords.",
				},
			},
			HasNonZeroLength =
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
					Desc = "Sets the given vector to the normalized version of this vector.\
	Removed from LuaAPI, because Lua doesn't need distinguishing from the other overload.",
				},
			},
			Length =
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
			LineCoeffToXYPlane =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_OtherEnd",
						},
						{
							Type = "double",
							Name = "a_Z",
						},
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
					Desc = "Returns the coefficient for the (a_OtherEnd - this) line to reach the specified Z coord.\
	The result satisfies the following equation:\
	(*this + Result * (a_OtherEnd - *this)).z = a_Z\
	If the line is too close to being parallel, this function returns NO_INTERSECTION",
				},
			},
			LineCoeffToXZPlane =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_OtherEnd",
						},
						{
							Type = "double",
							Name = "a_Y",
						},
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
					Desc = "Returns the coefficient for the (a_OtherEnd - this) line to reach the specified Y coord.\
	The result satisfies the following equation:\
	(*this + Result * (a_OtherEnd - *this)).y = a_Y\
	If the line is too close to being parallel, this function returns NO_INTERSECTION",
				},
			},
			LineCoeffToYZPlane =
			{
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_OtherEnd",
						},
						{
							Type = "double",
							Name = "a_X",
						},
					},
					Returns =
					{
						{
							Type = "double",
						},
					},
					Desc = "Returns the coefficient for the (a_OtherEnd - this) line to reach the specified X coord.\
	The result satisfies the following equation:\
	(*this + Result * (a_OtherEnd - *this)).x = a_X\
	If the line is too close to being parallel, this function returns NO_INTERSECTION",
				},
			},
			Move =
			{
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
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Diff",
						},
					},
					Returns =
					{
					},
				},
			},
			Normalize =
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
			NormalizeCopy =
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
			Set =
			{
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_x",
						},
						{
							Type = "double",
							Name = "a_y",
						},
						{
							Type = "double",
							Name = "a_z",
						},
					},
					Returns =
					{
					},
				},
			},
			SqrLength =
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
			TurnCCW =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Rotates the vector 90 degrees counterclockwise around the vertical axis.\
	Note that this is specific to minecraft's axis ordering, which is X+ left, Z+ down.",
				},
			},
			TurnCW =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Rotates the vector 90 degrees clockwise around the vertical axis.\
	Note that this is specific to minecraft's axis ordering, which is X+ left, Z+ down.",
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
							Type = "Vector3<double>",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "double",
							Name = "a_x",
						},
						{
							Type = "double",
							Name = "a_y",
						},
						{
							Type = "double",
							Name = "a_z",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<float>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<double>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "Vector3<int>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<double>",
						},
					},
				},
			},
		},
		Variables =
		{
			x =
			{
				Type = "double",
			},
			y =
			{
				Type = "double",
			},
			z =
			{
				Type = "double",
			},
		},
		Constants =
		{
			EPS =
			{
				Type = "const double",
				Desc = "The max difference between two coords for which the coords are assumed equal.",
			},
			NO_INTERSECTION =
			{
				Type = "const double",
				Desc = "Return value of LineCoeffToPlane() if the line is parallel to the plane.",
			},
		},
	},
}
