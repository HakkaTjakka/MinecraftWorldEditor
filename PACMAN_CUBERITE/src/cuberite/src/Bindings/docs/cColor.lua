return
{
	cColor =
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
					Desc = "Resets the color",
				},
			},
			GetBlue =
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
					Desc = "Returns the blue value of the color",
				},
			},
			GetGreen =
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
					Desc = "Returns the green value of the color",
				},
			},
			GetRed =
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
					Desc = "Returns the red value of the color",
				},
			},
			IsValid =
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
					Desc = "Returns whether the color is a valid color",
				},
			},
			SetBlue =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Blue",
						},
					},
					Returns =
					{
					},
					Desc = "Alters the blue value of the color",
				},
			},
			SetColor =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Red",
						},
						{
							Type = "char",
							Name = "a_Green",
						},
						{
							Type = "char",
							Name = "a_Blue",
						},
					},
					Returns =
					{
					},
					Desc = "Changes the color",
				},
			},
			SetGreen =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Green",
						},
					},
					Returns =
					{
					},
					Desc = "Alters the green value of the color",
				},
			},
			SetRed =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Red",
						},
					},
					Returns =
					{
					},
					Desc = "Alters the red value of the color",
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
							Type = "cColor",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_Red",
						},
						{
							Type = "char",
							Name = "a_Green",
						},
						{
							Type = "char",
							Name = "a_Blue",
						},
					},
					Returns =
					{
						{
							Type = "cColor",
						},
					},
				},
			},
		},
		Enums =
		{
			eColorLimits =
			{
				{
					Name = "COLOR_LIMIT",
				},
				{
					Name = "COLOR_MAX",
				},
				{
					Name = "COLOR_MIN",
				},
				{
					Name = "COLOR_NONE",
				},
			},
		},
	},
}
