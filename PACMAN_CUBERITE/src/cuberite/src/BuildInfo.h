
#pragma once

#define BUILD_ID

#ifdef BUILD_ID

#undef BUILD_ID

#define BUILD_SERIES_NAME "local build"
#define BUILD_ID          "Unknown"
#define BUILD_COMMIT_ID   "approx: e0ca4d83991d80865781c1dbbbfa1f92259a366a"
#define BUILD_DATETIME    "approx: 2019-08-11 11:39:43 +0200"
#endif

