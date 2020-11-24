/*

% Description of my shader.
% Second line of description for my shader.

keywords: material classic

date: YYMMDD

*/

float4x4 gWorldViewProj : WorldViewProjection;
float gOutlineWidth = 0.3f;

struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal: NORMAL;   
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION;
   float4 mColor : COLOR;
};

VS_OUTPUT mainVS1(VS_INPUT input)
{
	VS_OUTPUT Output;
	Output.mColor = float4(0.5,0.5,0.5,0.3) * float4(input.mNormal,1.f);
	Output.mPosition = mul(input.mPosition , gWorldViewProj);
	return Output;
}

float4 mainPS1(VS_OUTPUT input) : COLOR 
{
	return input.mColor;
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
