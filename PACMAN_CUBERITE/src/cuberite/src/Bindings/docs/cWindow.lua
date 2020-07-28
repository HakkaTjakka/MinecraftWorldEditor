return
{
	cWindow =
	{
		Desc = "Represents a UI window.\
\
Each window has a list of players that are currently using it\
When there's no player using a window, it is destroyed.\
A window consists of several areas of slots with similar functionality - for example the crafting grid area, or\
the inventory area. Each area knows what its slots are (GetSlot() function) and can handle mouse clicks.\
The window acts only as a top-level container for those areas, redirecting the click events to the correct areas.\
Inventory painting, introduced in 1.5, is handled by the window, too",
		Functions =
		{
			GetSlot =
			{
				{
					Params =
					{
						{
							Type = "cPlayer",
							Name = "a_Player",
						},
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
					Desc = "Returns the item at the specified slot for the specified player. Returns nullptr if invalid SlotNum requested",
				},
			},
			GetWindowID =
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
				},
			},
			GetWindowTitle =
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
					Desc = "Sends the contents of the whole window to all clients of this window.",
				},
			},
			GetWindowType =
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
			GetWindowTypeName =
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
					Desc = "Returns the textual representation of the window's type, such as \"minecraft:chest\".",
				},
			},
			IsSlotInPlayerHotbar =
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
					Desc = "Returns true if the specified slot is in the Player Hotbar slotarea",
				},
			},
			IsSlotInPlayerInventory =
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
					Desc = "Returns true if the specified slot is in the Player Main Inventory or Hotbar slotareas. Note that returns false for Armor.",
				},
			},
			IsSlotInPlayerMainInventory =
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
					Desc = "Returns true if the specified slot is in the Player Main Inventory slotarea",
				},
			},
			SetProperty =
			{
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_Property",
						},
						{
							Type = "short",
							Name = "a_Value",
						},
					},
					Returns =
					{
					},
					Desc = "Updates a numerical property associated with the window. Typically used for furnace progressbars.\
	Sends the UpdateWindowProperty packet to all clients of the window",
				},
				{
					Params =
					{
						{
							Type = "short",
							Name = "a_Property",
						},
						{
							Type = "short",
							Name = "a_Value",
						},
						{
							Type = "cPlayer",
							Name = "a_Player",
						},
					},
					Returns =
					{
					},
					Desc = "Updates a numerical property associated with the window. Typically used for furnace progressbars.\
	Sends the UpdateWindowProperty packet only to the specified player",
				},
			},
			SetSlot =
			{
				{
					Params =
					{
						{
							Type = "cPlayer",
							Name = "a_Player",
						},
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
					Desc = "Sets the item to the specified slot for the specified player",
				},
			},
			SetWindowTitle =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_WindowTitle",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
			},
		},
		Enums =
		{
			WindowType =
			{
				{
					Name = "wtAnimalChest",
				},
				{
					Name = "wtAnvil",
				},
				{
					Name = "wtBeacon",
				},
				{
					Name = "wtBrewery",
				},
				{
					Name = "wtChest",
				},
				{
					Name = "wtDropSpenser",
				},
				{
					Name = "wtDropper",
				},
				{
					Name = "wtEnchantment",
				},
				{
					Name = "wtFurnace",
				},
				{
					Name = "wtHopper",
				},
				{
					Name = "wtInventory",
				},
				{
					Name = "wtNPCTrade",
				},
				{
					Name = "wtWorkbench",
				},
			},
		},
	},
}
