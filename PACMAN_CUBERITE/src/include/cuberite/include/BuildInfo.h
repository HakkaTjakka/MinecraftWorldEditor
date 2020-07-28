
#pragma once

#define BUILD_ID

#ifdef BUILD_ID

#undef BUILD_ID

#define BUILD_SERIES_NAME "local build"
#define BUILD_ID          "Unknown"
#define BUILD_COMMIT_ID   "approx: Unknown"
#define BUILD_DATETIME    "approx: Unknown"
#endif

