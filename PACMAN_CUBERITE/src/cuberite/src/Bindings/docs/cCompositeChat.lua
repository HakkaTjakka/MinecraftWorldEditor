return
{
	cCompositeChat =
	{
		Desc = "Container for a single chat message composed of multiple functional parts.\
Each part corresponds roughly to the behavior supported by the client messaging:\
	- plain text, optionaly colorized / styled\
	- clickable URLs\
	- clickable commands (run)\
	- clickable commands (suggest)\
Each part has a text assigned to it that can be styled. The style is specified using a string,\
each character / character combination in the string specifies the style to use:\
	- b = bold\
	- i = italic\
	- u = underlined\
	- s = strikethrough\
	- o = obfuscated\
	- @X = color X (X is 0 - 9 or a - f, same as dye meta\
If the protocol version doesn't support all the features, it degrades gracefully.",
		Functions =
		{
			CreateJsonString =
			{
				{
					Params =
					{
						{
							Type = "bool",
							Name = "a_ShouldUseChatPrefixes",
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
			ExtractText =
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
					Desc = "Returns the text from the parts that comprises the human-readable data.\
	Used for older protocols that don't support composite chat\
	and for console-logging.",
				},
			},
			GetAdditionalMessageTypeData =
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
					Desc = "Returns additional data pertaining to message type, for example, the name of a mtPrivateMsg sender",
				},
			},
			GetMessageType =
			{
				{
					Params =
					{
					},
					Returns =
					{
						{
							Type = "eMessageType",
						},
					},
					Desc = "Returns the message type set previously by SetMessageType().",
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
					Desc = "Creates a new chat message and parses the text into parts.\
	Recognizes \"http:\" and \"https:\" links and @color-codes.\
	Uses ParseText() for the actual parsing.\
	Exported manually due to ToLua++ generating extra output parameter.",
				},
			},
		},
	},
}
