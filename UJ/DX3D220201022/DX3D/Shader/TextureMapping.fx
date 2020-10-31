//--------------------------------------------------------------//
// TextureMapping
//--------------------------------------------------------------//

struct VS_INPUT
{
   float4 mPosition : POSITION;
   float2 mTexCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
   float4 mPosition : POSITION;
   float2 mTexCoord : TEXCOORD0; 
};

float4x4 gWorldMatrix : World ;
float4x4 gViewMatrix : View;
float4x4 gProjectionMatrix : Projection;

VS_OUTPUT VS(VS_INPUT Input)
{
   VS_OUTPUT Output;
   Output.mPosition = mul(Input.mPosition, gWorldMatrix);
   Output.mPosition = mul(Output.mPosition, gViewMatrix);
   Output.mPosition = mul(Output.mPosition, gProjectionMatrix);
   Output.mTexCoord = Input.mTexCoord;
   return Output; 
}


texture DiffuseMap_Tex;

sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};
struct PS_INPUT
{
   float2 mTexCoord : TEXCOORD0;
};

float4 PS(PS_INPUT Input) : COLOR
{ 
	float4 albedo = tex2D(DiffuseSampler, Input.mTexCoord);

	if (0.24f < Input.mTexCoord.x && Input.mTexCoord.x < 0.25f)
		albedo = 1;
	else if (0.49f < Input.mTexCoord.x && Input.mTexCoord.x < 0.50f)
		albedo = 1;
	else if (0.74f < Input.mTexCoord.x && Input.mTexCoord.x < 0.75f)
		albedo = 1;
	else if (0.99f < Input.mTexCoord.x && Input.mTexCoord.x < 1.f)
		albedo = 1;

	if (0.24f < Input.mTexCoord.y && Input.mTexCoord.y < 0.25f)
		albedo = 1;
	else if (0.49f < Input.mTexCoord.y && Input.mTexCoord.y < 0.50f)
		albedo = float4(1, 0, 0, 1);
	else if (0.74f < Input.mTexCoord.y && Input.mTexCoord.y < 0.75f)
		albedo = 1;
	return albedo.rgba;
}
//--------------------------------------------------------------//
// Technique Section for TextureMapping
//--------------------------------------------------------------//
technique TextureMapping
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }
}

