return
{
	cItem =
	{
		Functions =
		{
			AddCount =
			{
				{
					Params =
					{
						{
							Type = "char",
							Name = "a_AmountToAdd",
						},
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Adds the specified count to this object and returns the reference to self (useful for chaining)",
				},
			},
			AddEnchantment =
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
						{
							Type = "bool",
							Name = "a_FromBook",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Adds this specific enchantment to this item, returning the cost.\
	FromBook specifies whether the enchantment should be treated as coming\
	from a book. If true, then the cost returned uses the book values, if\
	false it uses the normal item multipliers.",
				},
			},
			AddEnchantmentsFromItem =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_Other",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Adds the enchantments on a_Other to this item, returning the\
	XP cost of the transfer.",
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
				},
			},
			CopyOne =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Returns a copy of this item with m_ItemCount set to 1. Useful to preserve enchantments etc. on stacked items",
				},
			},
			DamageItem =
			{
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_Amount",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Damages a weapon / tool. Returns true when damage reaches max value and the item should be destroyed",
				},
			},
			Empty =
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
			EnchantByXPLevels =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_NumXPLevels",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Randomly enchants the item using the specified number of XP levels.\
	Returns true if the item was enchanted, false if not (not enchantable / too many enchantments already).",
				},
			},
			GetEnchantability =
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
					Desc = "Returns the enchantability of the item. When the item hasn't a enchantability, it will returns 0",
				},
			},
			GetMaxDamage =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "short",
						},
					},
					Desc = "Returns the maximum damage value that this item can have; zero if damage is not applied",
				},
			},
			GetMaxStackSize =
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
					Desc = "Returns the maximum amount of stacked items of this type.",
				},
			},
			IsBothNameAndLoreEmpty =
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
				},
			},
			IsCustomNameEmpty =
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
				},
			},
			IsDamageable =
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
				},
			},
			IsEnchantable =
			{
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemType",
						},
						{
							Type = "bool",
							Name = "a_FromBook",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					IsStatic = true,
					Desc = "Returns true if the specified item type is enchantable.\
	If FromBook is true, the function is used in the anvil inventory with book enchantments.\
	So it checks the \"only book enchantments\" too. Example: You can only enchant a hoe with a book.",
				},
			},
			IsEqual =
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
							Type = "bool",
						},
					},
				},
			},
			IsFullStack =
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
					Desc = "Returns true if the item is stacked up to its maximum stacking.",
				},
			},
			IsLoreEmpty =
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
				},
			},
			IsSameType =
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
							Type = "bool",
						},
					},
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
							Type = "cItem",
						},
					},
					Desc = "Creates an empty item",
				},
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemType",
						},
						{
							Type = "char",
							Name = "a_ItemCount",
						},
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Creates an item of the specified type, by default 1 piece with no damage and no enchantments",
				},
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemType",
						},
						{
							Type = "char",
							Name = "a_ItemCount",
						},
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
						{
							Type = "AString",
							Name = "a_Enchantments",
						},
					},
					Returns =
					{
						{
							Type = "cItem",
						},
						{
							Type = "AString",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemType",
						},
						{
							Type = "char",
							Name = "a_ItemCount",
						},
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
						{
							Type = "AString",
							Name = "a_Enchantments",
						},
						{
							Type = "AString",
							Name = "a_CustomName",
						},
					},
					Returns =
					{
						{
							Type = "cItem",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_ItemType",
						},
						{
							Type = "char",
							Name = "a_ItemCount",
						},
						{
							Type = "short",
							Name = "a_ItemDamage",
						},
						{
							Type = "AString",
							Name = "a_Enchantments",
						},
						{
							Type = "AString",
							Name = "a_CustomName",
						},
						{
							Type = "AStringVector",
							Name = "a_LoreTable",
						},
					},
					Returns =
					{
						{
							Type = "cItem",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_CopyFrom",
						},
					},
					Returns =
					{
						{
							Type = "cItem",
						},
					},
					Desc = "Creates an exact copy of the item",
				},
			},
		},
		Variables =
		{
			m_CustomName =
			{
				Type = "AString",
			},
			m_Enchantments =
			{
				Type = "cEnchantments",
			},
			m_FireworkItem =
			{
				Type = "cFireworkItem",
			},
			m_ItemColor =
			{
				Type = "cColor",
			},
			m_ItemCount =
			{
				Type = "char",
			},
			m_ItemDamage =
			{
				Type = "short",
			},
			m_ItemType =
			{
				Type = "short",
				Desc = "Returns whether or not this item is allowed to have the given enchantment. Note: Does not check whether the enchantment is exclusive with the current enchantments on the item.",
			},
			m_RepairCost =
			{
				Type = "int",
			},
		},
	},
}
