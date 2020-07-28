return
{
	Vector3f =
	{
		Functions =
		{
			[".add"] =
			{
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
							Type = "Vector3<float>",
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
							Type = "Vector3<float>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<float>",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "float",
							Name = "a_v",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<float>",
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
							Type = "Vector3<float>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<float>",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "float",
							Name = "a_v",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<float>",
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
							Type = "Vector3<float>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<float>",
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
							Type = "Vector3<float>",
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
							Type = "float",
							Name = "a_Min",
						},
						{
							Type = "float",
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
							Type = "Vector3<float>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<float>",
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
							Type = "Vector3<float>",
							Name = "a_Rhs",
						},
					},
					Returns =
					{
						{
							Type = "float",
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
							Type = "Vector3<float>",
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
							Type = "Vector3<float>",
							Name = "a_Rhs",
						},
						{
							Type = "float",
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
							Type = "Vector3<float>",
							Name = "a_OtherEnd",
						},
						{
							Type = "float",
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
							Type = "Vector3<float>",
							Name = "a_OtherEnd",
						},
						{
							Type = "float",
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
							Type = "Vector3<float>",
							Name = "a_OtherEnd",
						},
						{
							Type = "float",
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
							Type = "float",
							Name = "a_X",
						},
						{
							Type = "float",
							Name = "a_Y",
						},
						{
							Type = "float",
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
							Type = "Vector3<float>",
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
							Type = "Vector3<float>",
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
							Type = "float",
							Name = "a_x",
						},
						{
							Type = "float",
							Name = "a_y",
						},
						{
							Type = "float",
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
							Type = "Vector3<float>",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "float",
							Name = "a_x",
						},
						{
							Type = "float",
							Name = "a_y",
						},
						{
							Type = "float",
							Name = "a_z",
						},
					},
					Returns =
					{
						{
							Type = "Vector3<float>",
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
							Type = "Vector3<float>",
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
							Type = "Vector3<float>",
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
							Type = "Vector3<float>",
						},
					},
				},
			},
		},
		Variables =
		{
			x =
			{
				Type = "float",
			},
			y =
			{
				Type = "float",
			},
			z =
			{
				Type = "float",
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
