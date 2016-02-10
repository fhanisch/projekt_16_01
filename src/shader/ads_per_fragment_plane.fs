//fragment shader
//Erstellt: 07.02.2016

#version 440

uniform mat4 mView;
uniform vec4 color;

in vec4 vertexPosition;
in vec4 normalPosition;
out vec4 FragColor;

const vec3 lightSource = vec3(100.0, 100.0, 100.0);

vec3 calcADS(vec3 c, vec3 vertex, vec3 normal, vec3 light)
{
	vec3 A = 0.1*c.rgb;
	vec3 D = c.rgb;
	vec3 S = vec3(0.0);

	vec3 s = normalize(light - vertex);
	vec3 n = normalize(normal);
	vec3 v = normalize(-vertex);	
	vec3 r = reflect(-s,n);

	float diffuseIntensity = max(dot(s,n), 0.0);	
	if( diffuseIntensity > 0.0 )
		S = vec3(1.0,1.0,0.6) * pow( max( dot(r,v), 0.0 ), 100.0 );

	return A + diffuseIntensity*D + S;
}

float calcIntersection(vec3 vertex, vec3 sphere, vec3 s)
{
	vec3 u = vertex - sphere;
	return dot(u,s)*dot(u,s) - (dot(u,u) - 1.0);
}

void main()
{		
	vec3 u;
	float d;
	float c1 = 1.0;
	float c2 = 1.0;
	float c3 = 1.0;
	float c4 = 1.0;
				
	vec4 lightPosition = mView * vec4(lightSource, 1.0);
	vec4 sphere1Position = mView * vec4(-5.0, 1.5, 0.0, 1.0);
	vec4 sphere2Position = mView * vec4( 5.0, 1.5, 0.0, 1.0);
	vec4 sphere3Position = mView * vec4( 0.0, 1.5, -5.0, 1.0);
	vec4 sphere4Position = mView * vec4( 0.0, 1.5,  5.0, 1.0);
			
	vec3 ADS = calcADS(color.rgb, vertexPosition.xyz, normalPosition.xyz, lightPosition.xyz);
	
	vec3 s = normalize(lightPosition.xyz - vertexPosition.xyz);
	if (calcIntersection(vertexPosition.xyz,sphere1Position.xyz,s)>=0) c1 = 0.0;
	if (calcIntersection(vertexPosition.xyz,sphere2Position.xyz,s)>=0) c2 = 0.0;
	if (calcIntersection(vertexPosition.xyz,sphere3Position.xyz,s)>=0) c3 = 0.0;
	if (calcIntersection(vertexPosition.xyz,sphere4Position.xyz,s)>=0) c4 = 0.0;

	vec3 n = normalize(normalPosition.xyz);
	s = reflect(-normalize(vertexPosition.xyz),n);	
	if (calcIntersection(vertexPosition.xyz,sphere1Position.xyz,s)>=0)
		ADS = mix(vec3(0.0,0.0,1.0),ADS,0.9);
	
	FragColor = vec4(c1*c2*c3*c4*ADS, 1.0);	
}

