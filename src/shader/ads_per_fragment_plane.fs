//fragment shader
//Erstellt: 07.02.2016

#version 440

uniform mat4 mView;
uniform vec4 color;

in vec4 vertexPosition;
in vec4 normalPosition;
out vec4 FragColor;

const vec3 lightSource = vec3(100.0, 100.0, 100.0);

void main()
{	
	vec3 A=0.1*color.rgb;
	vec3 D=color.rgb;
	vec3 S = vec3(0.0);
	vec3 u;
	float d;
	float c1 = 0.0;
	float c2 = 0.0;
	float c3 = 0.0;
	float c4 = 0.0;
				
	vec4 lightPosition = mView * vec4(lightSource, 1.0);
	vec4 sphere1Position = mView * vec4(-5.0, 1.5, 0.0, 1.0);
	vec4 sphere2Position = mView * vec4( 5.0, 1.5, 0.0, 1.0);
	vec4 sphere3Position = mView * vec4( 0.0, 1.5, -5.0, 1.0);
	vec4 sphere4Position = mView * vec4( 0.0, 1.5,  5.0, 1.0);
	
	vec3 s = normalize(lightPosition.xyz - vertexPosition.xyz);
	vec3 n = normalize(normalPosition.xyz);
	vec3 v = normalize(-vertexPosition.xyz);	
	vec3 r = reflect(-s,n);

	float diffuseIntensity = max(dot(s,n), 0.0);	
	if( diffuseIntensity > 0.0 )
		S = vec3(1.0,1.0,0.6) * pow( max( dot(r,v), 0.0 ), 100.0 );

	vec3 ADS = A + diffuseIntensity*D + S;
	
	u = vertexPosition.xyz - sphere1Position.xyz;
	d = dot(u,s)*dot(u,s) - (dot(u,u) - 1.0);
	if (d<0) c1 = 1.0;

	vec3 s2 = reflect(-normalize(vertexPosition.xyz),n);
	d = dot(u,s2)*dot(u,s2) - (dot(u,u) - 1.0);
	if (d>0) ADS = mix(vec3(0.0,0.0,1.0),ADS,0.9);

	u = vertexPosition.xyz - sphere2Position.xyz;
	d = dot(u,s)*dot(u,s) - (dot(u,u) - 1.0);
	if (d<0) c2 = 1.0;

	u = vertexPosition.xyz - sphere3Position.xyz;
	d = dot(u,s)*dot(u,s) - (dot(u,u) - 1.0);
	if (d<0) c3 = 1.0;

	u = vertexPosition.xyz - sphere4Position.xyz;
	d = dot(u,s)*dot(u,s) - (dot(u,u) - 1.0);
	if (d<0) c4 = 1.0;

	FragColor = vec4(c1*c2*c3*c4*ADS, 1.0);	
}

