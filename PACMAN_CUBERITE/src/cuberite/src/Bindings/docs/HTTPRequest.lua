return
{
	HTTPRequest =
	{
		Variables =
		{
			Method =
			{
				Type = "AString",
				Desc = "HTTP method used for the request (\"GET\", \"POST\" etc.)",
			},
			Path =
			{
				Type = "AString",
				Desc = "The Path part of the request's URL (excluding GET params).",
			},
			URL =
			{
				Type = "AString",
				Desc = "The entire URL presented to the HTTP server.",
			},
			Username =
			{
				Type = "AString",
				Desc = "Name of the logged-in user. Empty if not logged in.",
			},
		},
	},
}
