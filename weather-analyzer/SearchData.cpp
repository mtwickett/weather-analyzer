#include "SearchData.h"

#include <cmath>

int SearchData::getRowIndex(const std::vector<TemperatureRow>& rows, 
				const std::string& searchTimestamp)
{
	int left = 0, right = rows.size() - 1;

	while (left <= right) {
		int mid = floor((left + right) / 2);
		std::string tsMid = rows[mid].timestamp;

		if (searchTimestamp == tsMid)
			return mid;

		if (searchTimestamp < tsMid)
			right = mid - 1;
		else
			left = mid + 1;
	}

	return -1;
}
