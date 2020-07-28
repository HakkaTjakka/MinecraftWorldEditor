return
{
	cBlockEntityWithItems =
	{
		Inherits =
		{
			"cBlockEntity",
			"cBlockEntityWindowOwner",
		},
		Functions =
		{
			GetContents =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItemGrid",
						},
					},
					Desc = "Returns the ItemGrid used for storing the contents",
				},
			},
			GetSlot =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_SlotNum",
						},
					},
					Returns =
					{
						{
							Type = "const cItem",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_X",
						},
						{
							Type = "int",
							Name = "a_Y",
						},
					},
					Returns =
					{
						{
							Type = "const cItem",
						},
					},
				},
			},
			SetSlot =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_SlotNum",
						},
						{
							Type = "cItem",
							Name = "a_Item",
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
							Type = "int",
							Name = "a_X",
						},
						{
							Type = "int",
							Name = "a_Y",
						},
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
				},
			},
		},
	},
}
