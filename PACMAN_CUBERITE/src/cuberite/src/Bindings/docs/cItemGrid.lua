return
{
	cItemGrid =
	{
		Desc = "Used to store loot probability tables",
		Functions =
		{
			AddItem =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_ItemStack",
						},
						{
							Type = "bool",
							Name = "a_AllowNewStacks",
						},
						{
							Type = "int",
							Name = "a_PrioritySlot",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Adds as many items out of a_ItemStack as can fit.\
	If a_AllowNewStacks is set to false, only existing stacks can be topped up;\
	If a_AllowNewStacks is set to true, empty slots can be used for the rest.\
	If a_PrioritySlot is set to a positive value, then the corresponding slot will be used  first (if empty or compatible with added items).\
	If a_PrioritySlot is set to -1, regular order applies.\
	Returns the number of items that fit.",
				},
			},
			AddItems =
			{
				{
					Params =
					{
						{
							Type = "cItems",
							Name = "a_ItemStackList",
						},
						{
							Type = "bool",
							Name = "a_AllowNewStacks",
						},
						{
							Type = "int",
							Name = "a_PrioritySlot",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Same as AddItem, but works on an entire list of item stacks.\
	The a_ItemStackList is modified to reflect the leftover items.\
	If a_AllowNewStacks is set to false, only existing stacks can be topped up;\
	If a_AllowNewStacks is set to true, empty slots can be used for the rest.\
	If a_PrioritySlot is set to a positive value, then the corresponding slot will be used first (if empty or compatible with added items).\
	If a_PrioritySlot is set to -1, regular order applies.\
	Returns the total number of items that fit.",
				},
			},
			ChangeSlotCount =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_SlotNum",
						},
						{
							Type = "int",
							Name = "a_AddToCount",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Adds (or subtracts, if a_AddToCount is negative) to the count of items in the specified slot.\
	If the slot is empty, ignores the call.\
	Returns the new count.",
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
							Type = "int",
							Name = "a_AddToCount",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Adds (or subtracts, if a_AddToCount is negative) to the count of items in the specified slot.\
	If the slot is empty, ignores the call.\
	Returns the new count.",
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
					Desc = "Sets all items as empty",
				},
			},
			CopyToItems =
			{
				{
					Params =
					{
						{
							Type = "cItems",
							Name = "a_Items",
						},
					},
					Returns =
					{
					},
					Desc = "Copies the contents into a cItems object; preserves the original a_Items contents",
				},
			},
			DamageItem =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_SlotNum",
						},
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
					Desc = "Adds the specified damage to the specified item; returns true if the item broke (but the item is left intact)",
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
					Desc = "Adds the specified damage to the specified item; returns true if the item broke (but the item is left intact)",
				},
			},
			EmptySlot =
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
							Name = "a_Y",
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
							Name = "a_SlotNum",
						},
					},
					Returns =
					{
					},
				},
			},
			GetFirstEmptySlot =
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
					Desc = "Returns the index of the first empty slot; -1 if all full",
				},
			},
			GetFirstUsedSlot =
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
					Desc = "Returns the index of the first non-empty slot; -1 if all empty",
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
			GetLastEmptySlot =
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
					Desc = "Returns the index of the last empty slot; -1 if all full",
				},
			},
			GetLastUsedSlot =
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
					Desc = "Returns the index of the last used slot; -1 if all empty",
				},
			},
			GetNextEmptySlot =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_StartFrom",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns the index of the first empty slot following a_StartFrom (a_StartFrom is not checked)",
				},
			},
			GetNextUsedSlot =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_StartFrom",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns the index of the first used slot following a_StartFrom (a_StartFrom is not checked)",
				},
			},
			GetNumSlots =
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
			GetSlot =
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
							Name = "a_Y",
						},
					},
					Returns =
					{
						{
							Type = "const cItem",
						},
					},
					Desc = "Copies all items from a_Src to this grid.\
	Doesn't copy the listeners.",
				},
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
			},
			GetSlotNum =
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
							Name = "a_Y",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Converts XY coords into slot number; returns -1 on invalid coords",
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
					Desc = "Called whenever a slot changes",
				},
			},
			HasItems =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_ItemStack",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Returns true if there are at least as many items of type a_ItemStack as in a_ItemStack",
				},
			},
			HowManyCanFit =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_ItemStack",
						},
						{
							Type = "bool",
							Name = "a_AllowNewStacks",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns number of items out of a_ItemStack that can fit in the storage",
				},
			},
			HowManyItems =
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
							Type = "int",
						},
					},
					Desc = "Returns the number of items of type a_Item that are stored",
				},
			},
			IsSlotEmpty =
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
							Type = "bool",
						},
					},
					Desc = "Returns true if the specified slot is empty or the slot doesn't exist",
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
							Type = "bool",
						},
					},
					Desc = "Returns true if the specified slot is empty or the slot doesn't exist",
				},
			},
			RemoveItem =
			{
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_ItemStack",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Removes the specified item from the grid, as many as possible, up to a_ItemStack.m_ItemCount.\
	Returns the number of items that were removed.",
				},
			},
			RemoveOneItem =
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
							Type = "cItem",
						},
					},
					Desc = "Removes one item from the stack in the specified slot, and returns it.\
	If the slot was empty, returns an empty item",
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
							Type = "cItem",
						},
					},
					Desc = "Removes one item from the stack in the specified slot, and returns it.\
	If the slot was empty, returns an empty item",
				},
			},
			SetSlot =
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
					},
				},
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
							Name = "a_SlotNum",
						},
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
					},
				},
			},
		},
	},
}
