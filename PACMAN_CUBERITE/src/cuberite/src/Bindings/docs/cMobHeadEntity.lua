return
{
	cMobHeadEntity =
	{
		Inherits =
		{
			"cBlockEntity",
		},
		Functions =
		{
			GetOwnerName =
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
					Desc = "Returns the player name of the mob head",
				},
			},
			GetOwnerTexture =
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
					Desc = "Returns the texture of the mob head",
				},
			},
			GetOwnerTextureSignature =
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
					Desc = "Returns the texture signature of the mob head",
				},
			},
			GetRotation =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eMobHeadRotation",
						},
					},
					Desc = "Returns the rotation of the mob head",
				},
			},
			GetType =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eMobHeadType",
						},
					},
					Desc = "Returns the type of the mob head",
				},
			},
			SetOwner =
			{
				{
					Params =
					{
						{
							Type = "cPlayer",
							Name = "a_Owner",
						},
					},
					Returns =
					{
					},
					Desc = "Set the player for mob heads with player type",
				},
			},
			SetRotation =
			{
				{
					Params =
					{
						{
							Type = "eMobHeadRotation",
							Name = "a_Rotation",
						},
					},
					Returns =
					{
					},
					Desc = "Set the rotation of the mob head",
				},
			},
			SetType =
			{
				{
					Params =
					{
						{
							Type = "eMobHeadType",
							Name = "a_SkullType",
						},
					},
					Returns =
					{
						{
							Type = "eMobHeadType",
						},
					},
					Desc = "Set the type of the mob head",
				},
			},
		},
	},
}
