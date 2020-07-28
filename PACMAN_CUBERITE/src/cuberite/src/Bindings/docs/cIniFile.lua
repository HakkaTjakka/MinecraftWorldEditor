return
{
	cIniFile =
	{
		Inherits =
		{
			"cSettingsRepositoryInterface",
		},
		Functions =
		{
			AddHeaderComment =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "comment",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Adds a header comment",
				},
			},
			AddKeyComment =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
						{
							Type = "AString",
							Name = "comment",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Add a key comment",
				},
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "comment",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Add a key comment",
				},
			},
			AddKeyName =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
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
					Desc = "Add a key name",
				},
			},
			AddValue =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_KeyName",
						},
						{
							Type = "AString",
							Name = "a_ValueName",
						},
						{
							Type = "AString",
							Name = "a_Value",
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
						{
							Type = "AString",
						},
					},
				},
			},
			AddValueB =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_KeyName",
						},
						{
							Type = "AString",
							Name = "a_ValueName",
						},
						{
							Type = "bool",
							Name = "a_Value",
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
				},
			},
			AddValueF =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_KeyName",
						},
						{
							Type = "AString",
							Name = "a_ValueName",
						},
						{
							Type = "double",
							Name = "a_Value",
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
				},
			},
			AddValueI =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_KeyName",
						},
						{
							Type = "AString",
							Name = "a_ValueName",
						},
						{
							Type = "int",
							Name = "a_Value",
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
				},
			},
			CaseInsensitive =
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
			CaseSensitive =
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
			Clear =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Deletes all stored ini data (but doesn't touch the file)",
				},
			},
			DeleteHeaderComment =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "commentID",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
					Desc = "Deletes a header comment. Returns true if successful",
				},
			},
			DeleteHeaderComments =
			{
				{
					Params =
					{
					},
					Returns =
					{
					},
					Desc = "Deletes all header comments",
				},
			},
			DeleteKey =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			DeleteKeyComment =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
						{
							Type = "int",
							Name = "commentID",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "int",
							Name = "commentID",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			DeleteKeyComments =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			DeleteValue =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			DeleteValueByID =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
						{
							Type = "int",
							Name = "valueID",
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
			FindKey =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
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
					Desc = "Returns index of specified key, or noID if not found",
				},
			},
			FindValue =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
						{
							Type = "AString",
							Name = "valuename",
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
					Desc = "Returns index of specified value, in the specified key, or noID if not found",
				},
			},
			Flush =
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
			GetHeaderComment =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "commentID",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Returns a header comment, or empty string if out of range",
				},
			},
			GetKeyComment =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
						{
							Type = "int",
							Name = "commentID",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
					Desc = "Return a key comment",
				},
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "int",
							Name = "commentID",
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
				},
			},
			GetKeyName =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
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
			GetNumHeaderComments =
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
					Desc = "Returns the number of header comments",
				},
			},
			GetNumKeyComments =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
					Desc = "Get number of key comments",
				},
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
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
					Desc = "Get number of key comments",
				},
			},
			GetNumKeys =
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
					Desc = "Returns number of keys currently in the ini",
				},
			},
			GetNumValues =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
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
				},
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
					},
					Returns =
					{
						{
							Type = "int",
						},
					},
				},
			},
			GetValue =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
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
						{
							Type = "AString",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
						},
						{
							Type = "AString",
							Name = "defValue",
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
							Type = "int",
							Name = "keyID",
						},
						{
							Type = "int",
							Name = "valueID",
						},
					},
					Returns =
					{
						{
							Type = "AString",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
						{
							Type = "int",
							Name = "valueID",
						},
						{
							Type = "AString",
							Name = "defValue",
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
				},
			},
			GetValueB =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
						},
						{
							Type = "bool",
							Name = "defValue",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			GetValueF =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
						},
						{
							Type = "double",
							Name = "defValue",
						},
					},
					Returns =
					{
						{
							Type = "double",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			GetValueI =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
						},
						{
							Type = "int",
							Name = "defValue",
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
						{
							Type = "AString",
						},
					},
				},
			},
			GetValueName =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "int",
							Name = "valueID",
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
				},
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
						{
							Type = "int",
							Name = "valueID",
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
			GetValueSet =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
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
						{
							Type = "AString",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
						},
						{
							Type = "AString",
							Name = "defValue",
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
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			GetValueSetB =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
						},
						{
							Type = "bool",
							Name = "defValue",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			GetValueSetF =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
						},
						{
							Type = "double",
							Name = "defValue",
						},
					},
					Returns =
					{
						{
							Type = "double",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			GetValueSetI =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
						},
						{
							Type = "int",
							Name = "defValue",
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
						{
							Type = "AString",
						},
					},
				},
				{
					Params =
					{
						{
							Type = "AString",
							Name = "keyname",
						},
						{
							Type = "AString",
							Name = "valuename",
						},
						{
							Type = "long",
							Name = "defValue",
						},
					},
					Returns =
					{
						{
							Type = "long",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			HasValue =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_KeyName",
						},
						{
							Type = "AString",
							Name = "a_ValueName",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Returns true iff the specified value exists.",
				},
			},
			ReadFile =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_FileName",
						},
						{
							Type = "bool",
							Name = "a_AllowExampleRedirect",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Reads the contents of the specified ini file\
	If the file doesn't exist and a_AllowExampleRedirect is true, tries to read <basename>.example.ini, and\
	writes its contents as <basename>.ini, if successful.\
	Returns true if successful, false otherwise.",
				},
			},
			SetValue =
			{
				{
					Params =
					{
						{
							Type = "int",
							Name = "keyID",
						},
						{
							Type = "int",
							Name = "valueID",
						},
						{
							Type = "AString",
							Name = "value",
						},
					},
					Returns =
					{
						{
							Type = "bool",
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
							Type = "AString",
							Name = "a_KeyName",
						},
						{
							Type = "AString",
							Name = "a_ValueName",
						},
						{
							Type = "AString",
							Name = "a_Value",
						},
						{
							Type = "bool",
							Name = "a_CreateIfNotExists",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			SetValueB =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_KeyName",
						},
						{
							Type = "AString",
							Name = "a_ValueName",
						},
						{
							Type = "bool",
							Name = "a_Value",
						},
						{
							Type = "bool",
							Name = "a_CreateIfNotExists",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			SetValueF =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_KeyName",
						},
						{
							Type = "AString",
							Name = "a_ValueName",
						},
						{
							Type = "double",
							Name = "a_Value",
						},
						{
							Type = "bool",
							Name = "a_CreateIfNotExists",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			SetValueI =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_KeyName",
						},
						{
							Type = "AString",
							Name = "a_ValueName",
						},
						{
							Type = "int",
							Name = "a_Value",
						},
						{
							Type = "bool",
							Name = "a_CreateIfNotExists",
						},
					},
					Returns =
					{
						{
							Type = "bool",
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
							Type = "AString",
							Name = "a_Keyname",
						},
						{
							Type = "AString",
							Name = "a_ValueName",
						},
						{
							Type = "long",
							Name = "a_Value",
						},
						{
							Type = "bool",
							Name = "a_CreateIfNotExists",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
						{
							Type = "AString",
						},
					},
				},
			},
			WriteFile =
			{
				{
					Params =
					{
						{
							Type = "AString",
							Name = "a_FileName",
						},
					},
					Returns =
					{
						{
							Type = "bool",
						},
						{
							Type = "AString",
						},
					},
					Desc = "Writes data stored in class to the specified ini file.\
	Returns true on success, false on failure.",
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
							Type = "cIniFile",
						},
					},
					Desc = "Creates a new instance with no data",
				},
			},
		},
		Enums =
		{
			unnamedEnum_1 =
			{
				{
					Name = "noID",
				},
			},
		},
	},
}
