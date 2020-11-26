/*

% Description of my shader.
% Second line of description for my shader.

keywords: material classic

date: YYMMDD

*/
float4x4 gWorldViewProj : WorldViewProjection;
float gOutlineWidth = 0.3f;
float2 gCharactor2DPos = {0,0};
//texture2D gTexture;

struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal: NORMAL;   
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION;
   float4 mColor : COLOR;
   float2 PosOut : TEXCOORD0;
};

struct PS_INPUT 
{
   float2 PosOut : TEXCOORD0;
   float4 mColor : COLOR;
};


/*
VS_OUTPUT scopeVS(VS_INPUT input)
{
	VS_OUTPUT Output;
	Output.mColor = float4(0.5,0.5,0.5,0.3) * float4(input.mNormal,1.f);
	Output.mPosition = mul(input.mPosition , gWorldViewProj);
	return Output;
}


float4 scopePS(VS_OUTPUT input) : COLOR 
{
	float4 albedo = float4(0,0,0,0);
	albedo.a = pow(pow(input.mPosition.x, 2.0) + pow(input.mPosition.y, 2), 0.5);
	return albedo;
}
*/

VS_OUTPUT mainVS1(VS_INPUT input)
{
	VS_OUTPUT Output;
	Output.mColor = float4(0.5,0.5,0.5,0.3) * float4(input.mNormal,1.f);
	Output.mPosition = mul(input.mPosition , gWorldViewProj);
	Output.PosOut =  Output.mPosition.xy;
	return Output;
}

float4 mainPS1(PS_INPUT input) : COLOR 
{
	return float4(input.mColor.rgb, 3*sqrt(pow(input.PosOut.x - gCharactor2DPos.x, 2) + pow(input.PosOut.y - gCharactor2DPos.y, 2)));
}

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
