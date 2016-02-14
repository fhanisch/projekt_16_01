//fragment shader
//Erstellt: 13.02.2016

#version 440

uniform mat4 mView;
uniform vec4 color;
uniform sampler2D samp;
uniform sampler2D samp2;

in vec3 lightDir;
in vec3 viewDir;
in vec2 textureCoords;
out vec4 FragColor;

vec3 calcADS(vec3 c, vec3 normal)
{
	vec3 A = 0.1*c.rgb;
	vec3 D = c.rgb;
	vec3 S = vec3(0.0);
	
	vec3 n = normalize(normal);
	vec3 l = normalize(lightDir);
	vec3 d = normalize(-viewDir);
	vec3 r = reflect(-l,n);

	float diffuseIntensity = max(dot(l,n), 0.0);	
	if( diffuseIntensity > 0.0 )
		S = vec3(1.0,1.0,0.6) * pow( max( dot(r,d), 0.0 ), 100.0 );

	return A + diffuseIntensity*D + S;
}

void main()
{	
	float phiX = -3.14159/2.0;
	mat4 mRotX = mat4(1.0);
	mRotX[1].y=cos(phiX);
	mRotX[2].y=-sin(phiX);
	mRotX[1].z=sin(phiX);
	mRotX[2].z=cos(phiX);

	float phiY = -3.14159;
	mat4 mRotY = mat4(1.0);
	mRotY[0].x=cos(phiY);
	mRotY[2].x=-sin(phiY);
	mRotY[0].z=sin(phiY);
	mRotY[2].z=cos(phiY);

	float phiZ = 3.14159;
	mat4 mRotZ = mat4(1.0);
	mRotZ[0].x=cos(phiZ);
	mRotZ[1].x=-sin(phiZ);
	mRotZ[0].y=sin(phiZ);
	mRotZ[1].y=cos(phiZ);		

	vec4 tex1 = texture2D(samp, textureCoords);				
	vec4 normal = texture2D(samp2, textureCoords);	
			
	//vec4 normTrans = vec4(0.0,1.0,0.0,1.0);
	vec4 normTrans = mRotX * vec4(2.0*normal.rgb-1.0, 1.0);
			
	//vec3 ADS = calcADS(vec3(0.1, 0.1, 0.1), vec3(transpose(inverse(mView))*normTrans));
	vec3 ADS = calcADS(vec3(0.1, 0.1, 0.1), vec3(normTrans));

	FragColor = vec4(ADS, 1.0);
}

