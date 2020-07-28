return
{
	cUUID =
	{
		Functions =
		{
			Compare =
			{
				{
					Params =
					{
						{
							Type = "cUUID",
							Name = "a_Other",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Lexicographically compare bytes with another UUID.\
	Returns:\
		0 when equal to a_Other,\
		< 0 when less than a_Other,\
		> 0 when greater than a_Other",
				},
			},
			FromString =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_StringUUID",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Tries to interpret the string as a short or long form UUID and assign from it.\
	On error, returns false and does not set the value.",
				},
			},
			GenerateVersion3 =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Name",
						},
					},
					Returns =
					{
						{
							Type = "cUUID",
						},
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Generates a version 3, variant 1 UUID based on the md5 hash of a_Name.",
				},
			},
			IsNil =
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
					Desc = "Returns true if this contains the \"nil\" UUID with all bits set to 0",
				},
			},
			ToLongString =
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
					Desc = "Converts the UUID to a long form string (i.e. with dashes).",
				},
			},
			ToShortString =
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
					Desc = "Converts the UUID to a short form string (i.e without dashes).",
				},
			},
			Variant =
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
					Desc = "Returns the variant number of the UUID.",
				},
			},
			Version =
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
					Desc = "Returns the version number of the UUID.",
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
							Type = "cUUID",
						},
					},
					Desc = "Default constructed \"nil\" UUID",
				},
			},
		},
	},
}
