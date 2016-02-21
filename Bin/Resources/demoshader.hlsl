#define NLIGHTS 2

struct VertexIn
{
    float3 pos     : POSITION;  // in object coordinates
    float3 normal  : NORMAL;    // in object coordinates
    float3 tangent : TANGENT;   // in object coordinates
    float2 uv      : TEXCOORD0; // in object coordinates
};

struct VertexOut
{
    float4 posH               : SV_POSITION; // in homogenous coordinates
    float2 uv                 : TEXCOORD0;
    float3 posV               : TEXCOORD1;   // in camera coordinates
    float3 normalV            : TEXCOORD2;   // in camera coordinates
    float3 tangentV           : TEXCOORD3;   // in camera coordinates
    float3 lightDirV[NLIGHTS] : TEXCOORD4;   // in camera coordinates
};

struct LightSource
{
    float4 pos;
    float4 dir;
    float4 color;
};

cbuffer MatrixBuffer : register(b0)
{
    float4x4 gWorldMatrix;
    float4x4 gViewMatrix;
    float4x4 gProjMatrix;
    //float4x4 gModelViewMatrix;
    //float4x4 gModelViewProjMatrix;
    float4x4 gNormalMatrix;
};

cbuffer MaterialBuffer : register(b1)
{
    float4 gMatColorDiffuse;
    float4 gMatColorSpecular;
    float  gMatRoughness;
    float  gMatF0;
};

cbuffer LightBuffer : register(b2)
{
    LightSource gLights[NLIGHTS];
};

Texture2D gMaterialDiffuseTex;
SamplerState gMaterialDiffuseTexSampler;

float safediv(float num, float den, float def)
{
    if (den < 0.00001)
        return def;
    return num / den;
}

VertexOut v(VertexIn IN)
{
    VertexOut OUT = (VertexOut)0;
    
    float4 posH = float4(IN.pos, 1.0);
    posH = mul(posH, gWorldMatrix);
    posH = mul(posH, gViewMatrix);
    posH = mul(posH, gProjMatrix);
    OUT.posH = posH;
    //OUT.posH     = mul(float4(IN.pos,     1.0), gModelViewProjMatrix);

    OUT.posV     = mul(float4(IN.pos,     1.0), gViewMatrix  ).xyz;
    OUT.normalV  = mul(float4(IN.normal,  0.0), gNormalMatrix).xyz;
    OUT.tangentV = mul(float4(IN.tangent, 0.0), gNormalMatrix).xyz;
    
    OUT.uv = IN.uv;
    
    for(int i = 0; i < NLIGHTS; ++i)
        if (gLights[i].pos.w == 0) // directional or point light
            OUT.lightDirV[i] = mul(float4(gLights[i].dir.xyz, 0.0), gNormalMatrix).xyz;
        else
            OUT.lightDirV[i] = OUT.posV - mul(float4(gLights[i].pos.xyz, 0.0), gViewMatrix).xyz;
    
    return OUT;
}

float4 p(VertexOut IN) : SV_TARGET
{
    float3 rcolor = float3(0.0,0.0,0.0);

    float3 N = normalize(IN.normalV);
    
    for(int i = 0; i < NLIGHTS; ++i)
    {
        float3 L = normalize(-IN.lightDirV[i]);
        float3 V = normalize(-IN.posV);
        float3 H = normalize(V+L);
        
        float NdotL = saturate( dot( N, L ) );
        float NdotH = saturate( dot( N, H ) );
        float NdotV = saturate( dot( N, V ) );
        float VdotH = saturate( dot( V, H ) );
        float LdotH = saturate( dot( L, H ) );
        
        // ---------------- FRESNEL TERM ---------------- 

        float F0 = gMatF0;
        // -- classic
        float F_term = pow(1.0 - VdotH, 5.0) * (1.0 - F0) + F0;
        // -- Cook-Torrance (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)
        //float F_F0sqrt = sqrt(F0);
        //float F_n = (1.0 + F_F0sqrt) / (1.0 - F_F0sqrt);
        //float F_c = VdotH;
        //float F_g = sqrt(F_n * F_n + F_c * F_c - 1.0);
        //float F_a = (F_g - F_c) / (F_g + F_c);
        //float F_b = ((F_g + F_c) * F_c - 1.0) / ((F_g - F_c) * F_c + 1.0);
        //float F_term = 0.5 * F_a * F_a * (1 + F_b*F_b);
        
        // ---------------- ROUGHNESS TERM ---------------- 
        
        float rsq = gMatRoughness * gMatRoughness;
        // -- ?? method
        //float R_c = 1.0;
        //float R_exp = - NdotH / (gMatRoughness * gMatRoughness);
        //float R_term = R_c * exp( R_exp );
        // -- ?? method
        //float R_a = 1.0f / ( 4.0f * rsq * pow( NdotH, 4 ) );
        //float R_b = NdotH * NdotH - 1.0f;
        //float R_c = rsq * NdotH * NdotH;
        //float R_term = R_a * exp(R_b / R_c);
        // -- Gauss method (http://content.gpwiki.org/index.php/D3DBook:(Lighting)_Cook-Torrance)
        //float R_c = 0.8; // varying coeff
        //float R_exp = - acos(NdotH) / rsq;
        //float R_term = R_c * exp(R_exp);
        // -- Beckman method (http://content.gpwiki.org/index.php/D3DBook:(Lighting)_Cook-Torrance)
        //float R_NdotH2 = NdotH * NdotH;
        //float R_c = safediv(1.0, rsq * R_NdotH2 * R_NdotH2, 0.0);
        //float R_exp = safediv(R_NdotH2 - 1.0, rsq * R_NdotH2, 0.0);
        //float R_term = R_c * exp(R_exp);
        // -- Gauss method (http://renderman.pixar.com/view/cook-torrance-shader)
        //float R_c = 4; // varying coeff
        //float R_alpha = acos(NdotH);
        //float R_exp = safediv(-R_alpha*R_alpha, rsq,0);
        //float R_term = R_c * exp(R_exp);
        // -- GGX method (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)
        float R_num = rsq;
        float R_a = NdotH * NdotH * (rsq - 1.0) + 1.0;
        float R_den = 3.14 * R_a * R_a;
        float R_term = safediv(R_num, R_den, 0);

        // ---------------- GEOMETRY TERM ---------------- 
        
        // -- Implicit (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)
        //float G_term = NdotL * NdotV;
        // -- Cook-Torrance (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)
        //float G1 = 2.0 * NdotH * safediv(NdotV, VdotH, 0.0);
        //float G2 = 2.0 * NdotH * safediv(NdotL, VdotH, 0.0);
        //float G_term = min(1.0, min(G1, G2));
        // -- Kelemen (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)
        float G_term = safediv(NdotL * NdotV, VdotH * VdotH, 0.0);
        // -- Neumann (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)
        //float G_term = safediv(NdotL * NdotV, max(NdotL, NdotV), 0.0);
        
        // ---------------- SUM IT UP ---------------- 

        //float Rs_num = F_term * R_term * G_term;
        //float Rs_den = NdotV * NdotL;
        //float Rs = safediv(Rs_num, Rs_den, 0.0);
        float Rs_num = F_term * R_term * G_term;
        //float Rs_den = 4.0 * NdotV * NdotL;
        float Rs_den = NdotV * NdotL;
        float Rs = safediv(Rs_num, Rs_den, 0);
        
        float4 diffuseTexColor = gMaterialDiffuseTex.Sample(gMaterialDiffuseTexSampler, IN.uv);

        rcolor += gLights[i].color.rgb * NdotL * (gMatColorSpecular * Rs + gMatColorDiffuse * diffuseTexColor);

        //rcolor = F_term;
        //rcolor = R_term;
        //rcolor = G_term;
        //rcolor = float4(Rs,NdotL*NdotV,0,1);
        //rcolor = Rs;
        //if (rcolor.x == 0)
        //    rcolor = float4(1, 0, 0, 1);
    }
    
    // HDR mapping
    //rcolor = rcolor / (0.5 + rcolor);

    return float4(rcolor, 1.0);
}
