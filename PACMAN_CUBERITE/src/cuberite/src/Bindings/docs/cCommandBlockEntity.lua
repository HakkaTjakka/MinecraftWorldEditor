return
{
	cCommandBlockEntity =
	{
		Inherits =
		{
			"cBlockEntity",
		},
		Functions =
		{
			Activate =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Sets the command block to execute a command in the next tick",
				},
			},
			GetCommand =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const AString",
						},
					},
					Desc = "Retrieves stored command",
				},
			},
			GetLastOutput =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "const AString",
						},
					},
					Desc = "Retrieves the last line of output generated by the command block",
				},
			},
			GetResult =
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
					Desc = "Retrieves the result (signal strength) of the last operation",
				},
			},
			SetCommand =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Cmd",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Sets the command",
				},
			},
		},
	},
}
