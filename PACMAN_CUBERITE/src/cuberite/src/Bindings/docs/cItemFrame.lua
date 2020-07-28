return
{
	cItemFrame =
	{
		Inherits =
		{
			"cHangingEntity",
		},
		Functions =
		{
			GetItem =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const cItem",
						},
					},
					Desc = "Returns the item in the frame",
				},
			},
			GetItemRotation =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "Byte",
						},
					},
					Desc = "Returns the rotation from the item in the frame",
				},
			},
			SetItem =
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
					Desc = "Set the item in the frame",
				},
			},
			SetItemRotation =
			{
				{
					Params =
					{
						{
							Type = "Byte",
							Name = "a_ItemRotation",
						},
					},
					Returns =
					{
					},
					Desc = "Set the rotation from the item in the frame",
				},
			},
		},
	},
}
