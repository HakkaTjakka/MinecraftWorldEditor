return
{
	cPlugin =
	{
		Functions =
		{
			GetFolderName =
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
					Desc = "Returns the name of the folder (in the Plugins folder) from which the plugin is loaded.",
				},
			},
			GetLoadError =
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
					Desc = "Returns the error encountered while loading the plugin. Only valid if m_Status == psError.",
				},
			},
			GetLocalFolder =
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
					Desc = "Returns the folder relative to the MCS Executable, from which the plugin is loaded.",
				},
			},
			GetName =
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
					Desc = "Calls the specified hook with the params given. Returns the bool that the hook callback returns.",
				},
			},
			GetStatus =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "cPluginManager::ePluginStatus",
						},
					},
				},
			},
			GetVersion =
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
			IsLoaded =
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
			SetName =
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
							Type = "AString",
						},
					},
				},
			},
			SetVersion =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "a_Version",
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
