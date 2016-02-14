//fragment shader
//Erstellt: 07.02.2016

#version 440

uniform mat4 mView;
uniform vec4 color;
uniform sampler2D samp;
uniform sampler2D samp2;

in vec4 vertexPosition;
in vec4 normalPosition;
in vec2 textureCoords;
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

float calcDiscriminant(vec3 vertex, vec3 sphere, vec3 s)
{
	vec3 u = vertex - sphere;
	return dot(u,s)*dot(u,s) - (dot(u,u) - 1.0);
}

float calcSpereIntersection(vec3 vertex, vec3 sphere, vec3 s, float discriminant)
{
	vec3 u = vertex - sphere;
	float t1 = -dot(u,s) + sqrt(discriminant);
	float t2 = -dot(u,s) - sqrt(discriminant);
	return t1;
}

vec3 calcSphereReflection(vec3 vertex, vec3 sphere, vec3 light, vec3 s, vec3 c, vec3 ADS)
{
	float t;
	vec3 y;
	vec3 normalSphere;
	vec3 ADSsphere;
	//float fade;
	float d = calcDiscriminant(vertex, sphere, s);

	if (d>=0)
	{
		t = calcSpereIntersection(vertex,sphere,s,d);
		y = vertex + t*s;
		normalSphere = y-sphere;
		//fade = dot(s,normalize(normalSphere));
		ADSsphere = calcADS(c, y, normalSphere, light);
		return mix(ADSsphere,ADS,0.5);
	}
	else
	{
		return ADS;
	}
}

void main()
{		
	vec4 tex1 = texture2D(samp, textureCoords*8.0);
	vec4 tex2 = texture2D(samp2, textureCoords*8.0);
	vec4 tex = mix(tex1,tex2,1.0);
	vec4 spherePosition[4];
	float c = 1.0;	
					
	vec4 lightPosition = mView * vec4(lightSource, 1.0);
	spherePosition[0] = mView * vec4(-5.0, 1.0, 0.0, 1.0);
	spherePosition[1] = mView * vec4( 5.0, 1.0, 0.0, 1.0);
	spherePosition[2] = mView * vec4( 0.0, 1.0, -5.0, 1.0);
	spherePosition[3] = mView * vec4( 0.0, 1.0,  5.0, 1.0);
			
	vec3 ADS = calcADS(tex.xyz, vertexPosition.xyz, normalPosition.xyz, lightPosition.xyz);
	
	vec3 s = normalize(lightPosition.xyz - vertexPosition.xyz);
	if (calcDiscriminant(vertexPosition.xyz,spherePosition[0].xyz,s)>=0) c = 0.2;
	if (calcDiscriminant(vertexPosition.xyz,spherePosition[1].xyz,s)>=0) c = 0.2;
	if (calcDiscriminant(vertexPosition.xyz,spherePosition[2].xyz,s)>=0) c = 0.2;
	if (calcDiscriminant(vertexPosition.xyz,spherePosition[3].xyz,s)>=0) c = 0.2;

	vec3 n = normalize(normalPosition.xyz);
	s = reflect(-normalize(vertexPosition.xyz),n);

	ADS = calcSphereReflection(vertexPosition.xyz, spherePosition[0].xyz, lightPosition.xyz, s, vec3(0.0, 0.0, 1.0), ADS);	
	ADS = calcSphereReflection(vertexPosition.xyz, spherePosition[1].xyz, lightPosition.xyz, s, vec3(1.0, 1.0, 0.0), ADS);
	ADS = calcSphereReflection(vertexPosition.xyz, spherePosition[2].xyz, lightPosition.xyz, s, vec3(1.0, 0.0, 0.0), ADS);
	ADS = calcSphereReflection(vertexPosition.xyz, spherePosition[3].xyz, lightPosition.xyz, s, vec3(1.0, 0.0, 1.0), ADS);
	
	FragColor = vec4(c*ADS, 1.0);	
}

