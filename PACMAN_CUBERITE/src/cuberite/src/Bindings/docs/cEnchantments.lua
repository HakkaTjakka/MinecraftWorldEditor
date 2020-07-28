return
{
	cEnchantments =
	{
		Desc = "Class that stores item enchantments or stored-enchantments\
The enchantments may be serialized to a stringspec and read back from such stringspec.\
The format for the stringspec is \"id=lvl;id=lvl;id=lvl...\", with an optional semicolon at the end,\
mapping each enchantment's id onto its level. ID may be either a number or the enchantment name.\
Level value of 0 means no such enchantment, and it will not be stored in the m_Enchantments.\
Serialization will never put zero-level enchantments into the stringspec and will always use numeric IDs.",
		Functions =
		{
			[".eq"] =
			{
				{
					Params =
					{
						{
							Type = "cEnchantments",
							Name = "a_Other",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if a_Other contains exactly the same enchantments and levels",
				},
			},
			Add =
			{
				{
					Params =
					{
						{
							Type = "cEnchantments",
							Name = "a_Other",
						},
					},
					Returns =
					{
					},
					Desc = "Adds the enchantments contained in a_Other into this object.\
	Existing enchantments are preserved, unless a_Other specifies a different level, in which case the level is changed to the a_Other's one.",
				},
			},
			AddFromString =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_StringSpec",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Adds enchantments in the stringspec; if a specified enchantment already exists, overwrites it",
				},
			},
			CanAddEnchantment =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_EnchantmentID",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if the given enchantment could be legally added to this object. Note that adding the enchantment may not actually increase the level.",
				},
			},
			Clear =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Removes all enchantments",
				},
			},
			Count =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "size_t",
						},
					},
					Desc = "Get the count of enchantments",
				},
			},
			GetLevel =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_EnchantmentID",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns the level for the specified enchantment; 0 if not stored",
				},
			},
			IsEmpty =
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
					Desc = "Returns true if there are no enchantments",
				},
			},
			SetLevel =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_EnchantmentID",
						},
						{
							Type = "int",
							Name = "a_Level",
						},
					},
					Returns =
					{
					},
					Desc = "Sets the level for the specified enchantment, adding it if not stored before or removing it if level <= 0",
				},
			},
			StringToEnchantmentID =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_EnchantmentName",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Converts enchantment name or ID (number in string) to the numeric representation; returns -1 if enchantment name not found; case insensitive",
				},
			},
			ToString =
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
					Desc = "Serializes all the enchantments into a string",
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
							Type = "cEnchantments",
						},
					},
					Desc = "Creates an empty enchantments container",
				},
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_StringSpec",
						},
					},
					Returns =
					{
						{
							Type = "cEnchantments",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Creates an enchantments container filled with enchantments parsed from stringspec",
				},
			},
		},
		Enums =
		{
			eEnchantment =
			{
				{
					Name = "enchAquaAffinity",
				},
				{
					Name = "enchBaneOfArthropods",
				},
				{
					Name = "enchBlastProtection",
				},
				{
					Name = "enchDepthStrider",
				},
				{
					Name = "enchEfficiency",
				},
				{
					Name = "enchFeatherFalling",
				},
				{
					Name = "enchFireAspect",
				},
				{
					Name = "enchFireProtection",
				},
				{
					Name = "enchFlame",
				},
				{
					Name = "enchFortune",
				},
				{
					Name = "enchInfinity",
				},
				{
					Name = "enchKnockback",
				},
				{
					Name = "enchLooting",
				},
				{
					Name = "enchLuckOfTheSea",
				},
				{
					Name = "enchLure",
				},
				{
					Name = "enchPower",
				},
				{
					Name = "enchProjectileProtection",
				},
				{
					Name = "enchProtection",
				},
				{
					Name = "enchPunch",
				},
				{
					Name = "enchRespiration",
				},
				{
					Name = "enchSharpness",
				},
				{
					Name = "enchSilkTouch",
				},
				{
					Name = "enchSmite",
				},
				{
					Name = "enchThorns",
				},
				{
					Name = "enchUnbreaking",
				},
			},
		},
	},
}
