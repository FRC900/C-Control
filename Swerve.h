#include <vector>
#include <array>
#include <string>
#include <Eigen/Dense>
#include "SwerveMath.h"

using namespace std;
using namespace eigen;
//meters or radians
class swerve
{
	public:
		swerve(array<Vector2d, WHEELCOUNT> _wheelCoordinates, double _maxSpeed, string _fileAddress, double _ratioEncodertoRotations, double _ratioEncodertoSteering, double _ratioMotortoRotations, double _ratioMotortoSteering, double _wheelRadius);
		motorOutputs(Vector2d velocityVector, double rotation, Vector2d centerOfRotation = {0, 0}, int rotationCenterID = 0, bool overrideID = false); 


























}
