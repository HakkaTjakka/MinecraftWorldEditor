return
{
	cFile =
	{
		Desc = "Reads the list of ports from the INI file, possibly upgrading from IPv4 / IPv6-specific values into new version-agnostic value.\
Reads the list of ports from a_PortsValueName. If that value doesn't exist or is empty, the list is combined from values\
in a_OldIPv4ValueName and a_OldIPv6ValueName; in this case the old values are removed from the INI file.\
If there is none of the three values or they are all empty, the default is used and stored in the Ports value.",
		Functions =
		{
			GetExecutableExt =
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
					IsStatic = true,
					Desc = "Returns the customary executable extension used by the current platform.",
				},
			},
			GetPathSeparator =
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
					IsStatic = true,
					Desc = "Returns the path separator used by the current platform.\
	Note that the platform / CRT may support additional path separators (such as slashes on Windows), these don't get reported.",
				},
			},
		},
	},
}
