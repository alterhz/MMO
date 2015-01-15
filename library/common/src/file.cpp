#include "common/file.h"

NS_LIB_HEADER;

std::string HZCore::GetExeRootPath()
{
	std::string strRootPath = boost::filesystem::initial_path<boost::filesystem::path>().string();

	return strRootPath;
}

NS_LIB_FOOTER;
