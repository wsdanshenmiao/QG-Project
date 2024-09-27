Shader "VampireSurvivors/Melt"
{
    Properties
    {
        _MainTex ("主要纹理", 2D) = "white" {}
        _NoiseTex ("噪声纹理", 2D) = "white" {}
        _Color_First ("第一消融色", Color) = (1, 0, 0, 1)
        _Color_Second ("第二消融色", Color) = (1, 0, 0, 1)
        _Width ("消融边缘宽度", Range(0,1)) = 0
        _Value ("消融阈值", Range(0,1)) = 0
    }
    SubShader
    {
        Tags 
        { 
            "RenderType"="Opaque"  
        }

        LOD 100

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            //声明各个变量
            sampler2D _MainTex;
            float4 _MainTex_ST;
            sampler2D _NoiseTex;

            // 将 _Value 声明在全局范围
            float _Value ;
            float _Width ;
            float4 _Color_First;
            float4 _Color_Second;

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                //计算灰度值
                float gray = dot(tex2D(_NoiseTex, i.uv).rgb, float3(0.299, 0.587, 0.114));
                //剔除完全消融像素
                clip(gray - _Value);

                //计算点是否在过渡区域以及混合系数
                fixed t = 1 - smoothstep(0.0, _Width, gray - _Value);
                //根据混合系数计算消融颜色
                fixed3 dissolveColor = lerp(_Color_First, _Color_Second, t);
                dissolveColor = pow(dissolveColor, 5);

                fixed3 origin = tex2D(_MainTex, i.uv);
                // 最终颜色 = 原始颜色和消融色的插值
                fixed3 finalColor = lerp(origin, dissolveColor, t * step(0.0001, _Value));

                return fixed4(finalColor, 1.0);
            }
            ENDCG
        }
    }
}