//fragment shader
//Erstellt: 04.02.2016

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
				
	vec4 lightPosition = mView * vec4(lightSource, 1.0);
	
	vec3 s = normalize(lightPosition.xyz - vertexPosition.xyz);
	vec3 n = normalize(normalPosition.xyz);
	vec3 v = normalize(-vertexPosition.xyz);	
	vec3 r = reflect(-s,n);

	float diffuseIntensity = max(dot(s,n), 0.0);	
	if( diffuseIntensity > 0.0 )
		S = vec3(1.0,1.0,0.6) * pow( max( dot(r,v), 0.0 ), 30.0 );

	vec3 ADS = A + diffuseIntensity*D + S;

	FragColor = vec4(ADS, 1.0);	
}
