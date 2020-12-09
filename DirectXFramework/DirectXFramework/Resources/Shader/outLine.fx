/*

% Description of my shader.
% Second line of description for my shader.

keywords: material classic

date: YYMMDD

*/

float4x4 gWorldViewProj : WorldViewProjection;
float gOutlineWidth = 0.3f;
float2 gCharactor2DPos = {0,0};
sampler2D gTexture;
texture DiffuseMap_Tex
<
   string ResourceName = "..\\..\\..\\InhaTeamProj\\DirectXFramework\\DirectXFramework\\Resources\\XFile\\PolygonOffice_Texture_01_A.png";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};

struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal: NORMAL;   
   float2 mUV: TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION;
   float4 mColor : COLOR;   
   float2 mUV: TEXCOORD0;
   float2 PosOut : TEXCOORD1;
};

struct PS_INPUT 
{
   float2 PosOut : TEXCOORD1;
   float4 mColor : COLOR;   
   float2 mUV: TEXCOORD0;
};

VS_OUTPUT mainVS1(VS_INPUT input)
{
	VS_OUTPUT Output;
	Output.mColor = float4(0.5,0.5,0.5,0.3) * float4(input.mNormal,1.f);
	Output.mPosition = mul(input.mPosition , gWorldViewProj);
	Output.PosOut =  Output.mPosition.xy;
	Output.mUV = input.mUV;
	return Output;
}

float4 mainPS1(PS_INPUT input) : COLOR 
{
	float4 albedo = tex2D(DiffuseSampler, input.mUV);
	return float4(albedo.xyz, 2*sqrt(pow(input.PosOut.x - gCharactor2DPos.x, 2) + pow(input.PosOut.y - gCharactor2DPos.y, 2)));
}

/*
VS_OUTPUT OutlineVertexShader(VS_INPUT input)
{
	VS_OUTPUT Output;
	Output.mColor = float4(1.0,1.0,1.0,0.3);
	Output.mPosition = mul(float4(input.mPosition.xyz + input.mNormal.xyz * 0.03f , 1.0), gWorldViewProj);
	return Output;
}

float4 OutlinePixelShader(VS_OUTPUT input) : COLOR 
{
	return input.mColor;
}
*/

technique technique0 {
	/*
	pass p0 {
		ZWriteEnable = false;
		VertexShader = compile vs_3_0 OutlineVertexShader();
		PixelShader = compile ps_3_0 OutlinePixelShader();
	}
	*/
	
	pass p1 {
		//ZWriteEnable = true;
		ColorWritEenable = 0;
		VertexShader = compile vs_3_0 mainVS1();
		PixelShader = compile ps_3_0 mainPS1();
	}
	pass p2{
		ColorWritEenable = 7;
		alphablendenable = true;
		srcBlend = srcAlpha;
		destBlend = invSrcAlpha;
	}
}
