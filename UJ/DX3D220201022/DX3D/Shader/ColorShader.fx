
//--------------------------------------------------------------//
// ColorShader
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//

struct VS_INPUT
{
   float4 mPosition : POSITION;
};

struct VS_OUTPUT
{
   float4 mPosition : POSITION; 
};

float4x4 gWorldMatrix ;
float4x4 gViewMatrix ;
float4x4 gProjectionMatrix ;
float4   gColor = float4(0.0f, 1.0f, 0.3f, 1.0f);

VS_OUTPUT VS(VS_INPUT Input)
{
   VS_OUTPUT Output;
   Output.mPosition = mul(Input.mPosition, gWorldMatrix);
   Output.mPosition = mul(Output.mPosition, gViewMatrix);
   Output.mPosition = mul(Output.mPosition, gProjectionMatrix);
   return Output; 
}


float4 PS() : COLOR
{
   return (gColor);
}
//--------------------------------------------------------------//
// Technique Section for ColorShader
//--------------------------------------------------------------//
technique ColorShader
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 VS();
      PixelShader  = compile ps_2_0 PS();
   }
}

