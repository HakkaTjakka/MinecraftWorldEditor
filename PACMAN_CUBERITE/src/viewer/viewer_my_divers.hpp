


void columnMatrixToAngles( Angles& angles, float colMatrix[4][4] )
{
    double sinPitch, cosPitch, sinRoll, cosRoll, sinYaw, cosYaw;

	sinPitch = -colMatrix[2][0];
	cosPitch = sqrt(1 - sinPitch*sinPitch);

	if ( abs(cosPitch) > 0.01 )
	{
	    sinRoll = colMatrix[2][1] / cosPitch;
	    cosRoll = colMatrix[2][2] / cosPitch;
	    sinYaw = colMatrix[1][0] / cosPitch;
	    cosYaw = colMatrix[0][0] / cosPitch;
    }
    else
    {
	    sinRoll = -colMatrix[1][2];
	    cosRoll = colMatrix[1][1];
	    sinYaw = 0;
	    cosYaw = 1;
    }

	angles.yaw   = atan2(sinYaw, cosYaw) * 180 / PI;
	angles.pitch = atan2(sinPitch, cosPitch) * 180 / PI;
	angles.roll  = atan2(sinRoll, cosRoll) * 180 / PI;
}



