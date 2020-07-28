return
{
	cMap =
	{
		Desc = "Encapsulates an in-game world map.",
		Functions =
		{
			GetCenterX =
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
			GetCenterZ =
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
			GetDimension =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eDimension",
						},
					},
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
			GetID =
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
			GetName =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
			},
			GetNumPixels =
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
			GetPixel =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_X",
						},
						{
							Type = "int",
							Name = "a_Z",
						},
					},
					Returns =
					{
						{
							Type = "Byte",
						},
					},
				},
			},
			GetPixelWidth =
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
			GetScale =
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
			GetWorld =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cWorld",
						},
					},
				},
			},
			Resize =
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
					},
					Desc = "Send next update packet to the specified player and remove invalid decorators / clients.",
				},
			},
			SetPixel =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_X",
						},
						{
							Type = "int",
							Name = "a_Z",
						},
						{
							Type = "Byte",
							Name = "a_Data",
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
			SetPosition =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_CenterX",
						},
						{
							Type = "int",
							Name = "a_CenterZ",
						},
					},
					Returns =
					{
					},
				},
			},
			SetScale =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Scale",
						},
					},
					Returns =
					{
					},
				},
			},
		},
		Enums =
		{
			eBaseColor =
			{
				{
					Name = "E_BASE_COLOR_BLUE",
				},
				{
					Name = "E_BASE_COLOR_BROWN",
				},
				{
					Name = "E_BASE_COLOR_DARK_BROWN",
				},
				{
					Name = "E_BASE_COLOR_DARK_GRAY",
				},
				{
					Name = "E_BASE_COLOR_DARK_GREEN",
				},
				{
					Name = "E_BASE_COLOR_GRAY_1",
				},
				{
					Name = "E_BASE_COLOR_GRAY_2",
				},
				{
					Name = "E_BASE_COLOR_LIGHT_BLUE",
				},
				{
					Name = "E_BASE_COLOR_LIGHT_BROWN",
				},
				{
					Name = "E_BASE_COLOR_LIGHT_GRAY",
				},
				{
					Name = "E_BASE_COLOR_LIGHT_GREEN",
				},
				{
					Name = "E_BASE_COLOR_PALE_BLUE",
				},
				{
					Name = "E_BASE_COLOR_RED",
				},
				{
					Name = "E_BASE_COLOR_TRANSPARENT",
				},
				{
					Name = "E_BASE_COLOR_WHITE",
				},
			},
		},
	},
}
