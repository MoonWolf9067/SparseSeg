#include "pointCloud.h"

/* ------------------------------------------------------------
	Function: Stores point cloud from a text in a vector 
	Parameters:
	   - file path (string)
	   - vector to store the point cloud (vector<point_XYZIRL>)
	Returns: 
	   - nothing (void) 
   ------------------------------------------------------------ */
std::istream& operator>>(std::istream& is, point_XYZIRL& p) {
	return is >> p.x >> p.y >> p.z >> p.i >> p.r >> p.l;
}
int getPointCloud(std::string pathToFile, std::vector<point_XYZIRL>& pointCloud) {
	std::ifstream velodyneFile(pathToFile.c_str());	
	if (!velodyneFile.fail()) {
		point_XYZIRL point;
		while (velodyneFile >> point) { // Overload operator>>
			pointCloud.push_back(point); 
		}
		return 1;	
	} else return 0;
}

/* ------------------------------------------------------------
	Function: Copy point cloud into another point cloud
	Parameters:
	   - Source  point cloud (vector<point_XYZIRL>)
	   - Destination point cloud (vector<point_XYZIRL>)
	Returns: 
	   - Nothing (void) 
   ------------------------------------------------------------ */
void copyPointCloud(const std::vector<point_XYZIRL> & pointCloud1, std::vector<point_XYZIRL>& pointCloud2){
	for (int i = 0; i < pointCloud1.size(); i++) {
		pointCloud2.push_back(pointCloud1[i]);
	}
}

/* ------------------------------------------------------------
	Function: Print point cloud coordinates
	Parameters:
	   - vector of point cloud (vector<point_XYZIRL>)
	Returns: 
	   - Nothing (void) 
   ------------------------------------------------------------ */
void printPointCloud(const std::vector<point_XYZIRL>& pointCloud, int num) {
	// Print coordinates of each point
	for (int i = 0; i < num; i++) {
		std::cout << "Point [" << i << "] with coordinates (x, y, z, i, r, l): (" 
		          << pointCloud[i].x << ", "
		          << pointCloud[i].y << ", "
		          << pointCloud[i].z << ", "
		          << pointCloud[i].i << ", " 
		          << pointCloud[i].r << ","
		          << pointCloud[i].l << ") " << std::endl;
	}
}

/* ------------------------------------------------------------
	Function: Sort point cloud based on chosen axis
	Parameters:
	   - vector of point cloud (vector<point_XYZIRL>)
	   - path to point cloud (string)
	   - sorting axis (string)
	Returns: 
	   - Nothing (void) 
   ------------------------------------------------------------ */
bool compareValuesOnAxis(point_XYZIRL& p1, point_XYZIRL& p2) {
	return p1.z < p2.z;
}
void sortPointCloud(std::vector<point_XYZIRL>& pointCloud, bool filter) {
	sort(pointCloud.begin(), pointCloud.end(), compareValuesOnAxis);
	
	// Filter noise due to mirror reflection
	if (filter) {
		std::vector<point_XYZIRL>::iterator iter = pointCloud.begin();
		for (int i = 0; i < pointCloud.size(); ++i) {
			if (pointCloud[i].z < THRESH_ERROR) { 
				iter++;
			} else {
				break;
			}
		}
		pointCloud.erase(pointCloud.begin(), iter);
	}
}

/* --------------------------------------------------
	Function: Convert lidar point to vector
	Parameters:
	   - Point from point cloud (point_XYZIRL)
	Returns: 
	   - Vectorized point (MatrixXf)
   -------------------------------------------------- */
Eigen::MatrixXf convertPointToMatXf(point_XYZIRL point) {
	Eigen::MatrixXf pointXf(1, 3);
	pointXf(0, 0) = point.x;
	pointXf(0, 1) = point.y;
	pointXf(0, 2) = point.z;
	return pointXf;
} 
