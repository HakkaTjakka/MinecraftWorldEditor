return
{
	cBoat =
	{
		Inherits =
		{
			"cEntity",
		},
		Functions =
		{
			GetMaterial =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cBoat::eMaterial",
						},
					},
					Desc = "Returns the eMaterial of the boat",
				},
			},
			ItemToMaterial =
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
						{
							Type = "cBoat::eMaterial",
						},
					},
					IsStatic = true,
					Desc = "Returns the eMaterial that should be used for a boat created from the specified item. Returns bmOak if not a boat item",
				},
			},
			MaterialToItem =
			{
				{
					Params =
					{
						{
							Type = "cBoat::eMaterial",
							Name = "a_Material",
						},
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					IsStatic = true,
					Desc = "Returns the boat item of the boat material",
				},
			},
			MaterialToString =
			{
				{
					Params =
					{
						{
							Type = "cBoat::eMaterial",
							Name = "a_Material",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Returns the eMaterial as string",
				},
			},
			SetMaterial =
			{
				{
					Params =
					{
						{
							Type = "cBoat::eMaterial",
							Name = "a_Material",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the eMaterial of the boat",
				},
			},
			StringToMaterial =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Material",
						},
					},
					Returns =
					{
						{
							Type = "cBoat::eMaterial",
						},
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Returns the boat material for the passed string. Returns oak if not valid",
				},
			},
		},
		Enums =
		{
			eMaterial =
			{
				{
					Name = "bmAcacia",
				},
				{
					Name = "bmBirch",
				},
				{
					Name = "bmDarkOak",
				},
				{
					Name = "bmJungle",
				},
				{
					Name = "bmOak",
				},
				{
					Name = "bmSpruce",
				},
			},
		},
	},
}
