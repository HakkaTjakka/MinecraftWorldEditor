return
{
	cLuaWindow =
	{
		Desc = "A window that has been created by a Lua plugin and is handled entirely by that plugin\
This object needs extra care with its lifetime management:\
- It is created by Lua, so Lua expects to garbage-collect it later\
- Normal cWindow objects are deleted in their ClosedByPlayer() function if the last player closes them\
	To overcome this, this object overloads the Destroy functions, which doesn't let the ClosedByPlayer()\
	delete the window, but rather leaves it dangling, with only Lua having the reference to it.\
- Lua could GC the window while a player is still using it\
	The object creates a Lua reference to itself when opened by a player and\
	removes the reference when the last player closes the window.",
		Inherits =
		{
			"cWindow",
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
					Desc = "Returns the internal representation of the contents that are manipulated by Lua",
				},
			},
			delete =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "",
						},
					},
					Desc = "Create a window of the specified type, with a slot grid of a_SlotsX * a_SlotsY size.\
	Exported in ManualBindings.cpp",
				},
			},
		},
	},
}
