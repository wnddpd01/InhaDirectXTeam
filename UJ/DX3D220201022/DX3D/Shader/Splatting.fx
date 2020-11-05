//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Splatting
//--------------------------------------------------------------//

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjectionMatrix : Projection;

float4   gWorldLightPosition
<
   string UIName = "gWorldLightPosition";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 500.00, 500.00, -500.00, 1.00 );
float4   gWorldCameraPosition : ViewPosition;

struct VS_INPUT 
{
   float4 mPosition : POSITION0;
   float3 mNormal   : NORMAL;
   float2 mUV       : TEXCOORD0;

};

struct VS_OUTPUT 
{
   float4 mPosition  : POSITION0;
   float2 mUV       : TEXCOORD0;
   float3 mDiffuse   : TEXCOORD1;
   float3 mViewDir   : TEXCOORD2;
   float3 mReflection: TEXCOORD3;
};

VS_OUTPUT vs( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.mPosition = mul( Input.mPosition, gWorldMatrix);

   float3 lightDir = Output.mPosition.xyz - gWorldLightPosition.xyz;
   lightDir = normalize(lightDir);

   float3 viewDir = normalize(Output.mPosition.xyz - gWorldCameraPosition.xyz);
   Output.mViewDir = viewDir;

   Output.mPosition = mul( Output.mPosition, gViewMatrix);
   Output.mPosition = mul( Output.mPosition, gProjectionMatrix);

   float3  worldNormal = mul(Input.mNormal, (float3x3)gWorldMatrix);
   worldNormal = normalize(worldNormal);

   Output.mDiffuse = dot(-lightDir, worldNormal);
   Output.mReflection = reflect(lightDir, worldNormal);

   Output.mUV = Input.mUV;

   return( Output );

}




struct PS_INPUT
{
   float2 mUV      : TEXCOORD0;
   float3 mDiffuse : TEXCOORD1;
   float3 mViewDir : TEXCOORD2;
   float3 mReflection : TEXCOORD3;
};

texture DiffuseMap_Tex1;
sampler2D DiffuseSampler1 = sampler_state
{
   Texture = (DiffuseMap_Tex1);
};

texture DiffuseMap_Tex2;
sampler2D DiffuseSampler2 = sampler_state
{
	Texture = (DiffuseMap_Tex2);
};

texture AlphaMap_Tex;
sampler2D AlphaSampler = sampler_state
{
   Texture = (AlphaMap_Tex);
};
float3 gLightColor
<
   string UIName = "gLightColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 0.70, 0.70, 1.00 );


float4 ps(PS_INPUT Input) : COLOR0
{   
   float4 albedo1 = tex2D(DiffuseSampler1, Input.mUV);
   float4 albedo2 = tex2D(DiffuseSampler2, Input.mUV);
   float4 alpha = tex2D(AlphaSampler, Input.mUV);

   float3 diffuse1 = gLightColor * (albedo1.rgb * alpha);
   float3 diffuse2 = gLightColor * (albedo2.rgb * (1 - alpha));
   float3 diffuse = diffuse1 + diffuse2;

   float3 reflection = normalize(Input.mReflection);
   float3 viewDir = normalize(Input.mViewDir);
   float3 specular = 0;
 
   if(diffuse.x > 0)
   {
      specular = saturate(dot(reflection, -viewDir));
      specular = pow(specular, 20.0f);
      
      float4 specularIntensity = tex2D(AlphaMap_Tex, Input.mUV);
      specular *= specularIntensity.rgb * gLightColor;
   }
   float3 ambient = float3(0.1f, 0.1f, 0.1f);
   
   
   return( float4( diffuse + specular + ambient, 1.0f));
}




//--------------------------------------------------------------//
// Technique Section for SpecularMapping
//--------------------------------------------------------------//
technique SpecularMapping
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 vs();
      PixelShader = compile ps_2_0 ps();
   }

}

