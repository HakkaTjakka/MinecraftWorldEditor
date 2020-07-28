return
{
	cInventory =
	{
		Desc = "This class represents the player's inventory\
The slots are divided into three areas:\
- armor slots     (1 x 4)\
- inventory slots (9 x 3)\
- hotbar slots    (9 x 1)\
The generic GetSlot(), SetSlot() and HowManyCanFit() functions take the index of the slots,\
as if armor slots, inventory slots and then hotbar slots were put one after another.\
You can use the invArmorOffset, invInventoryOffset and invHotbarOffset constants.",
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
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Adds as many items out of a_ItemStack as can fit.\
	If a_AllowNewStacks is set to false, only existing stacks can be topped up;\
	if a_AllowNewStacks is set to true, empty slots can be used for the rest.\
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
	if a_AllowNewStacks is set to true, empty slots can be used for the rest.\
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
	Returns the new count, or -1 if the slot number is invalid.",
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
					Desc = "Removes all items from the entire inventory",
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
					Desc = "Copies the non-empty slots into a_ItemStacks; preserves the original a_Items contents",
				},
			},
			DamageEquippedItem =
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
					Desc = "Adds the specified damage to the currently held item; deletes the item and returns true if the item broke.",
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
					Desc = "Adds the specified damage to the specified item; deletes the item and returns true if the item broke.",
				},
			},
			GetArmorGrid =
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
					Desc = "Returns the cItemGrid object representing the armor slots",
				},
			},
			GetArmorSlot =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_ArmorSlotNum",
						},
					},
					Returns =
					{
						{
							Type = "const cItem",
						},
					},
					Desc = "Returns current item in a_ArmorSlotNum in armor slots",
				},
			},
			GetEquippedBoots =
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
				},
			},
			GetEquippedChestplate =
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
				},
			},
			GetEquippedHelmet =
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
				},
			},
			GetEquippedItem =
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
					Desc = "Returns current equiped item",
				},
			},
			GetEquippedLeggings =
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
				},
			},
			GetEquippedSlotNum =
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
					Desc = "Returns slot number of equiped item",
				},
			},
			GetHotbarGrid =
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
					Desc = "Returns the cItemGrid object representing the hotbar slots",
				},
			},
			GetHotbarSlot =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_HotBarSlotNum",
						},
					},
					Returns =
					{
						{
							Type = "const cItem",
						},
					},
					Desc = "Returns current item in a_ArmorSlotNum in hotbar slots",
				},
			},
			GetInventoryGrid =
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
					Desc = "Returns the cItemGrid object representing the main inventory slots",
				},
			},
			GetInventorySlot =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_InventorySlotNum",
						},
					},
					Returns =
					{
						{
							Type = "const cItem",
						},
					},
					Desc = "Returns current item in a_ArmorSlotNum in inventory slots",
				},
			},
			GetOwner =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cPlayer",
						},
					},
					Desc = "Returns the player associated with this inventory",
				},
			},
			GetShieldSlot =
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
					Desc = "Returns current item in shield slot",
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
					Desc = "Returns current item in a_SlotNum slot",
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
							Name = "a_ConsiderEmptySlots",
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
				{
					Params =
					{
						{
							Type = "cItem",
							Name = "a_ItemStack",
						},
						{
							Type = "int",
							Name = "a_BeginSlotNum",
						},
						{
							Type = "int",
							Name = "a_EndSlotNum",
						},
						{
							Type = "bool",
							Name = "a_ConsiderEmptySlots",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Returns how many items of the specified type would fit into the slot range specified",
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
					Desc = "Removes the specified item from the inventory, as many as possible, up to a_ItemStack.m_ItemCount.\
	Returns the number of items that were removed.",
				},
			},
			RemoveOneEquippedItem =
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
					Desc = "Removes one item out of the currently equipped item stack, returns true if successful, false if empty-handed",
				},
			},
			SendEquippedSlot =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Sends the equipped item slot to the client",
				},
			},
			SetArmorSlot =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_ArmorSlotNum",
						},
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "Puts a_Item item in a_ArmorSlotNum slot number in armor slots",
				},
			},
			SetEquippedSlotNum =
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
					},
					Desc = "Sets equiped item to the a_SlotNum slot number",
				},
			},
			SetHotbarSlot =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_HotBarSlotNum",
						},
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "Puts a_Item item in a_HotBarSlotNum slot number in hotbar slots",
				},
			},
			SetInventorySlot =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_InventorySlotNum",
						},
						{
							Type = "cItem",
							Name = "a_Item",
						},
					},
					Returns =
					{
					},
					Desc = "Puts a_Item item in a_InventorySlotNum slot number in inventory slots",
				},
			},
			SetShieldSlot =
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
					Desc = "Sets current item in shield slot",
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
					Desc = "Puts a_Item item in a_SlotNum slot number",
				},
			},
		},
		Enums =
		{
			unnamedEnum_1 =
			{
				{
					Name = "invArmorCount",
				},
				{
					Name = "invArmorOffset",
				},
				{
					Name = "invHotbarCount",
				},
				{
					Name = "invHotbarOffset",
				},
				{
					Name = "invInventoryCount",
				},
				{
					Name = "invInventoryOffset",
				},
				{
					Name = "invNumSlots",
				},
				{
					Name = "invShieldCount",
				},
				{
					Name = "invShieldOffset",
				},
			},
		},
	},
}
