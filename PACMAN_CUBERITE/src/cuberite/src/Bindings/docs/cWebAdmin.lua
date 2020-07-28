return
{
	cWebAdmin =
	{
		Functions =
		{
			GetBaseURL =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_URL",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Returns the prefix needed for making a link point to the webadmin root from the given URL (\"../../../webadmin\"-style).",
				},
			},
			GetContentTypeFromFileExt =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_FileExtension",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Returns the content type from the file extension.\
	If the extension isn't in the list, the function returns an empty string.",
				},
			},
			GetHTMLEscapedString =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_Input",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
					IsStatic = true,
					Desc = "Escapes text passed into it, so it can be embedded into html.",
				},
			},
			GetPorts =
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
					Desc = "Returns the list of ports on which the webadmin is configured to listen.",
				},
			},
			Reload =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Reloads m_IniFile, m_LoginPage and m_TemplateScript.\
	Note that reloading will not change the \"enabled\" state of the server, and it will not update listening ports.",
				},
			},
		},
	},
}
